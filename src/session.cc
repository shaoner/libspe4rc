/*
 *
 * Copyright 2013, Alexandre LAURENT <shaoner>
 *
 * This file is part of Libspe4rc.
 *
 * Libspe4rc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Libspe4rc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Libspe4rc. If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*!
 * \file session.cc
 * \author shaoner
 * \brief An IRC session
 */

#include "session.hh"
#include "user-list.hh"
#include "user.hh"
#include "role.hh"
#include "command-event.hh"
#include "raw-event.hh"

namespace irc
{
	Session::Session(const SessionParameters& sessionParam) :
		_name(sessionParam._name),
		_hostname(sessionParam._hostname),
		_port(sessionParam._port),
		_password(sessionParam._password),
		_nickname(sessionParam._nickname),
		_altnickname(sessionParam._altnickname),
		_user(sessionParam._user),
		_realname(sessionParam._realname),
		_umode(sessionParam._umode),
		_uListCreating(false)
	{
		// Socket events
		connect(this, SIGNAL(onSocketConnect()), this, SLOT(on_socket_connect()));
		connect(this, SIGNAL(onSocketDisconnect()), this, SLOT(on_socket_disconnect()));
		connect(this, SIGNAL(onIrcData(Message&)), this, SLOT(on_irc_data(Message&)));
		// Default channel prefixes
		_channelPrefixes = "#&!";
	}

	Session::~Session()
	{
		close();
	}

	void
	Session::start()
	{
		if (!_hostname.isEmpty() && !_nickname.isEmpty() && !_user.isEmpty())
		{
			open(_hostname, _port);
		}
	}

	void
	Session::start(const QString& hostname, quint16 port, const QString& password)
	{
		_hostname = hostname;
		_port = port;
		_password = password;
		start();
	}

	void
	Session::stop()
	{
		close();
	}

	void
	Session::on_socket_connect()
	{
		// Send IRC auth
		if (!_password.isEmpty())
			write("PASS " + _password);
		write("NICK " + _nickname);
		write("USER " + _user + " " + QString::number(_umode) + " * :" + _realname);
	}

	void
	Session::on_socket_disconnect()
	{
		emit onDisconnect();
		clean();
	}

	void
	Session::on_irc_data(Message& message)
	{
		if (message.commandType == Message::MSG_CMDNAME)
		{
			// Handle mandatory events
			// This is not elegant, but it allows to handle non standard cases
			// like PING and it avoids a complex mechanism
			CommandEvent event(message, this);

			if ((message.commandName == "PING") && (message.params.count() > 0))
			{
				emit onPing(event, message.params[0]);
				write("PONG " + message.params[0]);
			}
			else if ((message.commandName == "QUIT") && (message.params.count() > 0))
			{
				emit onQuit(event, message.params[0]);
				// Remove the user from each channel list
				if (event.nick() != _nickname)
				{
					foreach(UserList* users, _channels)
					{
						users->remove(event.nick());
					}
				}
			}
			else if ((message.commandName == "PRIVMSG") && (message.params.count() > 1))
			{
				process_privmsg(event, message.params[0], message.params[1]);
			}
			else if ((message.commandName == "JOIN") && (message.params.count() > 0))
			{
				const QString& channel = message.params[0];
				// If the session join, add the channel to the channel list
				if (event.nick() == _nickname)
				{
					_channels.insert(channel, new UserList());
					_uListCreating = true;
				}
				// Add the new user to the channel
				else if (_channels.contains(channel))
					_channels[channel]->add(event.nick());
				emit onJoin(event, channel);
			}
			else if ((message.commandName == "PART") && (message.params.count() > 0))
			{
				const QString& channel = message.params[0];
				// Check if there is a part reason
				if (message.params.count() > 1)
					emit onPart(event, channel, message.params[1]);
				else
					emit onPart(event, channel, "");

				// If the session leaves, remove the channel
				// from my channel list
				if (event.nick() == _nickname)
					delete _channels.take(channel);
				// Remove the user from the channel
				else if (_channels.contains(channel))
					_channels[channel]->remove(event.nick());
			}
			else if ((message.commandName == "KICK") && (message.params.count() > 2))
			{
				const QString& channel = message.params[0];
				const QString& target = message.params[1];
				emit onKick(event, channel, target, message.params[2]);
				// If the session leaves, I can remove the channel
				// from my channel list
				if (target == _nickname)
					delete _channels.take(channel);
				// Remove the user from the channel
				else if (_channels.contains(channel))
					_channels[channel]->remove(target);
			}
			else if ((message.commandName == "MODE") && (message.params.count() > 1))
			{
				const QString& target = message.params[0];
				const QString& modes = message.params[1];
				// Channel mode
				if (is_channel(target))
				{
					QStringList modeArgs;
					if (message.params.count() > 2)
						modeArgs = message.params[2].split(' ');
					process_mode_channel(event, target, modes, modeArgs);
				}
				else
					emit onUserMode(event, target, modes);
			}
			else if ((message.commandName == "NICK") && (message.params.count() > 0))
			{
				const QString& newNick = message.params[0];

				emit onNick(event, newNick);
				// Change the nick of the user from each channel
				foreach(UserList* users, _channels)
				{
					if (users->contains(event.nick()))
						users->change_nick(event.nick(), newNick);
				}
				// Change the client's nick
				if (event.nick() == _nickname)
					_nickname = newNick;
			}
			else if ((message.commandName == "NOTICE") && (message.params.count() > 1))
			{
				emit onNotice(event, message.params[0], message.params[1]);
			}
			else if ((message.commandName == "INVITE") && (message.params.count() > 1))
			{
				emit onInvite(event, message.params[0], message.params[1]);
			}
			else if ((message.commandName == "TOPIC") && (message.params.count() > 1))
			{
				emit onChangeTopic(event, message.params[0], message.params[1]);
			}
			else if ((message.commandName == "ERROR") && (message.params.count() > 0))
			{
				emit onError(message.params[0]);
			}
			else // Unsupported command
			{
				qWarning() << "Unknown command " << message.commandName;
			}
		}
		else // message.commandType == Message::MSG_RAWNUM
			process_raw_data(message);
	}

	void
	Session::process_mode_channel(CommandEvent& event,
								 const QString& channel,
								 const QString& modes,
								 const QStringList& modeArgs)
	{
		bool add = false;
		char prefix;
		Role* roles = Role::get();
		int argIdx = 0;

		for (int i = 0, len = modes.size(); i < len; ++i)
		{
			// Keep last symbol + / -
			// because we can set modes like this: +no-h+v
			if (modes[i] == '+')
				add = true;
			else if (modes[i] == '-')
				add = false;
			// If the current char is a mode associated with a channel role
			else if (((prefix = roles->from_mode(modes[i].toAscii())) != 0) &&
					 (modeArgs.count() > argIdx) &&
					 (_channels.contains(channel)))
			{
				// Get the nickname whose role has changed
				const QString& arg = modeArgs[argIdx];
				// Add or remove this role from this channel
				User* user = _channels[channel]->get(arg);
				if (user)
				{
					if (add)
						user->add_prefix(prefix);
					else
						user->del_prefix(prefix);
				}
			}

		}
		emit onChannelMode(event, channel, modes, modeArgs);
	}

	void
	Session::process_privmsg(CommandEvent& event, const QString& target, const QString& msg)
	{
		QString message = msg;
		// CTCP
		if ((message.startsWith("\001") && message.endsWith("\001")))
		{
			// message length >= 2
			message = message.mid(1, message.size() - 2);
			// DCC
			if (message.startsWith("DCC"))
			{
				message.mid(3);
				/*
				 * TODO: Emit dcc
				 */
			}
			else if (message.startsWith("ACTION"))
			{
				message = message.mid(6);
				if (target == _nickname)
					emit onPrivateAction(event, message);
				else // if (is_channel(target))
					emit onChannelAction(event, target, message);

			}
			else
			{
				/*
				 * TODO: Emit ctcp
				 */
			}
		}
		else
		{
			if (target == _nickname)
				emit onPrivateMessage(event, message);
			else // if (is_channel(target))
				emit onChannelMessage(event, target, message);
		}
	}

	void
	Session::process_raw_data(Message& message)
	{
		RawEvent event(message, this);
		switch (event.raw())
		{
		    case RPL_WELCOME:
			{
				_connected = true;
				_connecting = false;
				emit onConnect();
				break;
			}
			// Get server parameters
			case RPL_BOUNCE:
			{
				process_server_params(message.params);
				break;
			}
			// NAME
			case RPL_NAMREPLY:
			{
				if ((_uListCreating) && (message.params.count() > 2))
				{
					const QString& channel = message.params[1];
					const QStringList& nicks = message.params[2].split(' ');
					// Append these nicks a userlist
					if (_channels.contains(channel))
					{
						UserList* users = _channels[channel];
						// If the userlist is already built
						// We do nothing, because it should be maintained
						// It avoids freeing and re-allocating memory for all users
						if (!users->isEmpty())
							break;
						foreach(QString nick, nicks)
						{
							users->add(nick);
						}
					}
					return;
				}
				break;
			}
			case RPL_ENDOFNAMES:
			{
				if (_uListCreating)
				{
					const QString& channel = message.params[0];
					if (_channels.contains(channel))
					{
						emit onUserList(channel, _channels[channel]);
					}
					_uListCreating = false;
					return;
				}
				break;
			}
			// Topic subject
			case RPL_TOPIC:
			{
				if (message.params.count() > 1)
				{
					emit onTopic(message.params[0], message.params[1]);
					return;
				}
				break;
			}
			// Topic additional infos
			case RPL_TOPICINFO:
			{
				if (message.params.count() > 2)
				{
					emit onTopicInfo(message.params[0], message.params[1], message.params[2].toUInt());
					return;
				}
				break;
			}
			// No topic
			case RPL_NOTOPIC:
			{
				if (message.params.count() > 1)
				{
					emit onNoTopic(message.params[0], message.params[1]);
					return;
				}
				break;
			}
			// Alternative nicknames
			case ERR_NICKNAMEINUSE:
			{
				if (!_connected)
				{
					static int altIdx = 0;
					if (_altnickname.count() > altIdx)
					{
						change_nickname(_altnickname[altIdx++]);
					}
				}
				break;
			}
		}
		emit onRaw(event);
	}

	void
	Session::process_server_params(const QStringList& serverParams)
	{
		// Parse server specific parameters
		for (QStringList::const_iterator it = serverParams.begin(),
				 end = serverParams.end(); it != end; ++it)
		{
			const QStringList& params = it->split('=');
			// Get prefix handled by this server
			if (params[0] == "PREFIX")
			{
				const QStringList& prefixes = params[1].split(')');
				const QString& modes = prefixes[0];
				const QString& chars = prefixes[1];
				Role* roleHandler = Role::get();
				quint8 level = 1;
				// modes are the letter modes
				// chars are the prefix associated to the mode
				// 'o' letter is usually associated to '@' prefix
				for (int i = modes.size() - 1; i > 0; --i)
				{
					char cmode = modes[i].toAscii();
					char cprefix = chars[i - 1].toAscii();
					roleHandler->add(cmode, cprefix, level);
					level <<= 1;
				}
			}
			else if (params[0] == "CHANTYPES")
			{
				_channelPrefixes = params[1];
			}
		}
	}

	void
	Session::clean()
	{
        // Remove all channels, which includes deleting each user
		QHash<QString, UserList*>::iterator i;
		for (i = _channels.begin(); i != _channels.end(); ++i)
		{
			delete i.value();
		}
		_channels.clear();
		// Clean the roles
		Role::get()->reset();
	}

} // namespace irc
