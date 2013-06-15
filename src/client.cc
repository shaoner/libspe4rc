#include <client.hh>

namespace com
{
	Client::Client(const QString& nickname,
				   const QString& altnickname,
				   const QString& user,
				   const QString& realname) :

		_hostname(""),
		_port(DEFAULT_PORT),
		_password(""),
		_nickname(nickname),
		_altnickname(altnickname),
		_user(user),
		_realname(realname),
		_userEvent(new UserEvent()),
		_serverEvent(new ServerEvent()),
		_rawEvent(new RawEvent())

	{
		connect(this, SIGNAL(onConnect()), this, SLOT(on_connect()));
		connect(this, SIGNAL(onIrcData(Message&)), this, SLOT(on_irc_data(Message&)));
		_userEvent->set_client(this);
		_serverEvent->set_client(this);
		_rawEvent->set_client(this);
	}

	Client::~Client()
	{
		delete _rawEvent;
		delete _serverEvent;
		delete _userEvent;
	}

	void
	Client::start(const QString& hostname, quint16 port, const QString& password)
	{
		if (!hostname.isEmpty() && !_nickname.isEmpty() && !_user.isEmpty())
		{
			_hostname = hostname;
			_port = port;
			_password = password;
			open(_hostname, _port);
		}
	}

	void
	Client::stop()
	{
		close();
	}

	void
	Client::send(const QString& target, const QString& message)
	{
		write("PRIVMSG " + target + " :" + message);
	}

	void
	Client::set_nickname(const QString& nickname)
	{
		if (!nickname.isEmpty())
		{
			_nickname = nickname;
		}
	}

	void
	Client::set_altnickname(const QString& altnickname)
	{
		if (!altnickname.isEmpty())
			_altnickname = altnickname;
	}

	void
	Client::set_user(const QString& user)
	{
		if (!user.isEmpty())
			_user = user;
	}

	void
	Client::set_realname(const QString& realname)
	{
		if (!realname.isEmpty())
			_realname = realname;
	}

	const QString&
	Client::nickname() const
	{
		return _nickname;
	}

	const QString&
	Client::altnickname() const
	{
		return _altnickname;
	}

	const QString&
	Client::user() const
	{
		return _user;
	}

	const QString&
	Client::realname() const
	{
		return _realname;
	}

	const QHash<QString, UserList*>&
	Client::channels() const
	{
		return _channels;
	}

	const QString&
	Client::hostname() const
	{
		return _hostname;
	}

	quint16
	Client::port() const
	{
		return _port;
	}

	void
	Client::on_connect()
	{
		if (!_password.isEmpty())
			write("PASS " + _password);
		write("NICK " + _nickname);
		/*
		 * FIXME: Alternative nickname is not handled
		 */
		write("USER " + _user + " 8 * :" + _realname);
		_serverEvent->fill_in("");
		emit onConnect(_serverEvent);
	}

	void
	Client::on_irc_data(Message& message)
	{
		if (message.commandType == Message::MSG_CMDNAME)
		{
			// Handle mandatory events
			// This is not elegant, but it allows to handle non standard cases
			// like PING and it avoids a complex mechanism
			if (message.commandName == "PING")
			{
				_serverEvent->fill_in(message);
				emit onPing(_serverEvent);
				write("PONG " + message.params[0]);
			}
			else if (message.commandName == "QUIT")
			{
				_serverEvent->fill_in(message);
				// Remove the user from each channel list
				if (_serverEvent->nick() != _nickname)
				{
					foreach(UserList* users, _channels)
					{
						users->remove(_serverEvent->nick());
					}
				}
				else // Remove all channels, which includes deleting each user
				{
					while (_channels.count() > 0)
						delete _channels.take(_userEvent->target());
				}
				emit onQuit(_serverEvent);
			}

			else if (message.commandName == "PRIVMSG")
			{
				_userEvent->fill_in(message);
				if (_userEvent->target().startsWith('#'))
					emit onChannelMessage(_userEvent);
				else
					emit onPrivateMessage(_userEvent);
			}
			else if (message.commandName == "JOIN")
			{
				_userEvent->fill_in(message);
				if ((_userEvent->nick() != _nickname) && (_channels.contains(_userEvent->target())))
					_channels[_userEvent->target()]->add(_userEvent->nick());
				emit onJoin(_userEvent);
			}
			else if (message.commandName == "PART")
			{
				_userEvent->fill_in(message);
				if (_userEvent->nick() == _nickname)
					delete _channels.take(_userEvent->target());
				else if (_channels.contains(_userEvent->target()))
					_channels[_userEvent->target()]->remove(_userEvent->nick());
				emit onPart(_userEvent);
			}
			else if (message.commandName == "MODE")
			{
				_userEvent->fill_in(message);
				process_mode_channel(message);
			}
			else if (message.commandName == "NOTICE")
			{
				_userEvent->fill_in(message);
				emit onNotice(_userEvent);
			}
			else
			{
				qDebug() << "Unknown command " << message.commandName;
			}
		}
		else // message.commandType == Message::MSG_RAWNUM
			process_raw_data(message);
	}

	void
	Client::process_mode_channel(Message& message)
	{
		const QString& modes = _userEvent->args()[0];
		const QStringList& modeArgs = _userEvent->args()[1].split(' ');
		int argIdx = 0;
		bool add = false;
		char prefix;
		Role* roleHandler = Role::get();

		for (int i = 0, len = modes.size(); i < len; ++i)
		{
			if (modes[i] == '+')
				add = true;
			else if (modes[i] == '-')
				add = false;
			else if (((prefix = roleHandler->from_mode(modes[i].toAscii())) != 0) &&
					 (modeArgs.count() > argIdx) &&
					 (_channels.contains(_userEvent->target())))
			{
				const QString& target = modeArgs[argIdx];
				User* user = _channels[_userEvent->target()]->get(target);
				if (user)
				{
					if (add)
					 	user->add_prefix(prefix);
					else
					 	user->del_prefix(prefix);
				}
				// if (add)
				// {
				// }
			}

		}


		if (_userEvent->target().startsWith('#'))
		{
			emit onChannelMode(_userEvent);
		}
		else
			emit onUserMode(_userEvent);
	}

	void
	Client::process_raw_data(Message& message)
	{
		static bool start_name_rpl = true;
		_rawEvent->fill_in(message);
		switch (_rawEvent->raw())
		{
			// Get server parameters
			case RPL_BOUNCE:
			{
				process_server_params(message.params);
				break;
			}
			// Handle NAME command
			case RPL_NAMREPLY:
			{
				const QStringList& nicks = message.params[2].split(" ");
				UserList* users = NULL;
				if (_channels.contains(message.params[1]))
				{
					users = _channels[message.params[1]];
					if (start_name_rpl)
					{
						users->clear();
						start_name_rpl = false;
					}
				}
				else
				{
					users = new UserList();
					_channels.insert(message.params[1], users);
				}
				foreach(QString nick, nicks)
				{
					users->add(nick);
				}
				break;
			}
			case RPL_ENDOFNAMES:
			{
				if (_channels.contains(message.params[0]))
				{
					UserList* users = _channels[message.params[0]];
					// 	// users.sort();
					emit onUserList(message.params[0], users);
					start_name_rpl = true;
				}
				break;
			}
		}
		emit onRaw(_rawEvent);
	}

	void
	Client::process_server_params(const QStringList& serverParams)
	{

		for (QStringList::const_iterator it = serverParams.begin(),
				 end = serverParams.end(); it != end; ++it)
		{
			const QStringList& params = it->split('=');
			if (params[0] == "PREFIX")
			{
				const QStringList& prefixes = params[1].split(')');
				const QString& modes = prefixes[0];
				const QString& chars = prefixes[1];
				Role* roleHandler = Role::get();
				quint8 level = 1;
				for (int i = modes.size() - 1; i > 0; --i)
				{
					char cmode = modes[i].toAscii();
					char cprefix = chars[i - 1].toAscii();
					roleHandler->add(cmode, cprefix, level);
					level <<= 1;
				}
			}
		}
	}

	// void
	// Client::remove_user_from(QStringList& userList, QString& user)
	// {
	// 	//while (user[0]
	// }

} // namespace com
