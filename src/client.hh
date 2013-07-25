/*
 *
 * Copyright 2013, Alexandre LAURENT <shaoner>
 *
 * This file is part of Libspe4rc.
 *
 * Libspe4rc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Libspe4rc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Libspe4rc. If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*!
 * \file client.hh
 * \author shaoner
 * \brief An IRC session
 */

#ifndef COM_CLIENT_HH
# define COM_CLIENT_HH

# include <QString>
# include <QHash>

# include "session.hh"
# include "user-list.hh"
# include "command-event.hh"
# include "raw-event.hh"
# include "connector.hh"

/// The default IRC port
# define DEFAULT_PORT 6667

namespace irc
{

	/*!
	 * \class Client
	 * \brief This class is an IRC client session
	 */
	class Client : public Connector
	{
		Q_OBJECT

	public:
        /// Ctor
		Client(const Session& session);
		/// Dtor
		~Client();
	public:
		/// Connection
		void start();
		void start(const QString& hostname,
				   quint16 port = DEFAULT_PORT,
				   const QString& password = "");
		void stop();
		/// Commands
		void msg(const QString& target, const QString& message) const;
		void action(const QString& target, const QString& message) const;
		void notice(const QString& target, const QString& message) const;
		void join(const QString& channels, const QString& keys = "") const;
		void part(const QString& channel, const QString& reason = "") const;
		void quit(const QString& reason = "") const;
		void kick(const QString& channel, const QString& nick, const QString& reason = "") const;
		void invite(const QString& nick, const QString& channel) const;
		void mode(const QString& target, const QString& mode = "") const;
		void topic(const QString& channel, const QString& topic = "") const;
		void cleartopic(const QString& channel) const;
		void whois(const QString& nicks) const;
		void names(const QString& channel) const;
		/// Client parameters
		void change_nickname(const QString& nickname);
		void add_altnickname(const QString& nickname);
		void change_user(const QString& user);
		void change_realname(const QString& realname);
		const QString& nickname() const;
		const QString& user() const;
		const QString& realname() const;
		const QHash<QString, UserList*>& channels() const;
		/// Server paramaters
		const QString& name() const;
		const QString& hostname() const;
		quint16 port() const;
		bool is_channel(const QString& channel) const;
	signals:
		/// Event notifiers
		void onError();
		void onConnect();
		void onDisconnect();

		void onPing(CommandEvent& event, const QString& server);
		void onQuit(CommandEvent& event, const QString& reason);

		void onChannelMessage(CommandEvent& event, const QString& target, const QString& msg);
		void onChannelAction(CommandEvent& event, const QString& target, const QString& msg);
		void onPrivateMessage(CommandEvent& event, const QString& msg);
		void onPrivateAction(CommandEvent& event, const QString& msg);

		void onJoin(CommandEvent& event, const QString& channel);
		void onPart(CommandEvent& event, const QString& channel, const QString& reason);
		void onKick(CommandEvent& event, const QString& channel, const QString& target, const QString& reason);

		void onUserMode(CommandEvent& event, const QString& target, const QString& modes);
		void onChannelMode(CommandEvent& event, const QString& channel, const QString& modes, const QStringList& args);
		void onNick(CommandEvent& event, const QString& newNick);

		void onNotice(CommandEvent& event, const QString& target, const QString& msg);
		void onInvite(CommandEvent& event, const QString& target, const QString& channel);

		void onRaw(RawEvent& event);
		void onUserList(const QString& channel, UserList* users);

		void onChangeTopic(CommandEvent& event, const QString& channel, const QString& subject);
		void onTopic(const QString& channel, const QString& topic);
		void onTopicInfo(const QString& channel, const QString& author, uint date);
		void onNoTopic(const QString& channel, const QString& msg);
	private slots:
		/// Socket event listeners
		void on_socket_connect();
		void on_socket_disconnect();
		void on_irc_data(Message& message);
	private:
		void process_privmsg(CommandEvent& event, const QString& target, const QString& msg);
		void process_mode_channel(CommandEvent& event, const QString& channel, const QString& modes, const QStringList& args);
		void process_raw_data(Message& message);
		void process_server_params(const QStringList& serverParams);
		void clean();
	private:
		/// Server info
		QString _name;
		QString _hostname;
		int _port;
		QString _password;
		/// User info
		QString _nickname;
		QStringList _altnickname;
		QString _user;
		QString _realname;
		quint8 _umode;
		QHash<QString, UserList*> _channels;
		QString _channelPrefixes;
		bool _uListCreating;
	};

	inline void
	Client::msg(const QString& target, const QString& message) const
	{
		write("PRIVMSG " + target + " :" + message);
	}

	inline void
	Client::action(const QString& target, const QString& message) const
	{
		write("PRIVMSG " + target + " :\001ACTION " + message + "\001");
	}

	inline void
	Client::notice(const QString& target, const QString& message) const
	{
		write("NOTICE " + target + " :" + message);
	}

	inline void
	Client::join(const QString& channels, const QString& keys) const
	{
		if (keys.isEmpty())
			write("JOIN " + channels);
		else
			write("JOIN " + channels + " " + keys);
	}

	inline void
	Client::part(const QString& channels, const QString& reason) const
	{
		if (reason.isEmpty())
			write("PART " + channels);
		else
			write("PART " + channels + " :" + reason);
	}

	inline void
	Client::quit(const QString& reason) const
	{
		if (reason.isEmpty())
			write("QUIT");
		else
			write("QUIT :" + reason);
	}

	inline void
	Client::kick(const QString& channels, const QString& nicks, const QString& reason) const
	{
		if (reason.isEmpty())
			write("KICK " + channels + " " + nicks);
		else
			write("KICK " + channels + " " + nicks + " :" + reason);
	}

	inline void
	Client::invite(const QString& nick, const QString& channel) const
	{
		write("INVITE " + nick + " " + channel);
	}

	inline void
	Client::mode(const QString& target, const QString& mode) const
	{
		if (mode.isEmpty())
			write("MODE " + target);
		else
			write("MODE " + target + " " + mode);
	}

	inline void
	Client::topic(const QString& channel, const QString& topic) const
	{
		if (topic.isEmpty())
			write("TOPIC " + channel);
		else
			write("TOPIC " + channel + " :" + topic);
	}

	inline void
	Client::cleartopic(const QString& channel) const
	{
		write("TOPIC " + channel + " :");
	}

	inline void
	Client::whois(const QString& nicks) const
	{
		write("WHOIS " + nicks);
	}

	inline void
	Client::names(const QString& channels) const
	{
		write("NAMES " + channels);
	}

	inline void
	Client::change_nickname(const QString& nickname)
	{
		if (!nickname.isEmpty())
		{
			_nickname = nickname;
			if (!is_disconnected())
				write("NICK " + nickname);
		}
	}

	inline void
	Client::add_altnickname(const QString& nickname)
	{
		if (!nickname.isEmpty())
			_altnickname.append(nickname);
	}

	inline void
	Client::change_user(const QString& user)
	{
		if (!user.isEmpty() && !connection_established())
			_user = user;
	}

	inline void
	Client::change_realname(const QString& realname)
	{
		if (!realname.isEmpty() && !connection_established())
			_realname = realname;
	}

	inline const QString&
	Client::nickname() const
	{
		return _nickname;
	}

	inline const QString&
	Client::user() const
	{
		return _user;
	}

	inline const QString&
	Client::realname() const
	{
		return _realname;
	}

	inline const QHash<QString, UserList*>&
	Client::channels() const
	{
		return _channels;
	}

	inline const QString&
	Client::name() const
	{
		return _name;
	}

	inline const QString&
	Client::hostname() const
	{
		return _hostname;
	}

	inline quint16
	Client::port() const
	{
		return _port;
	}

	inline bool
	Client::is_channel(const QString& channel) const
	{
		return _channelPrefixes.contains(channel[0]);
	}

} // namespace irc

#endif /* !COM_CLIENT_HH */
