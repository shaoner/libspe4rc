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
		_channelEvent(new ChannelEvent()),
		_userEvent(new UserEvent()),
		_serverEvent(new ServerEvent()),
		_rawEvent(new RawEvent())

	{
		connect(this, SIGNAL(onConnect()), this, SLOT(on_connect()));
		connect(this, SIGNAL(onIrcData(Message&)), this, SLOT(on_irc_data(Message&)));

		_channelEvent->set_client(this);
		_userEvent->set_client(this);
		_serverEvent->set_client(this);
		_rawEvent->set_client(this);
	}

	Client::~Client()
	{
		delete _rawEvent;
		delete _serverEvent;
		delete _userEvent;
		delete _channelEvent;
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
			else if (message.commandName == "PRIVMSG")
			{
				if (message.params.count() > 0 && message.params[0].startsWith('#'))
				{
					_channelEvent->fill_in(message);
					emit onChannelMessage(_channelEvent);
				}
				else
				{
					_userEvent->fill_in(message);
					emit onPrivateMessage(_userEvent);
				}
			}
			else if (message.commandName == "JOIN")
			{
				_channelEvent->fill_in(message);
				if ((_channelEvent->nick() != _nickname) && (_channels.contains(_channelEvent->channel())))
					_channels[_channelEvent->channel()]->add(_channelEvent->nick());
				emit onJoin(_channelEvent);
			}
			else if (message.commandName == "PART")
			{
				_channelEvent->fill_in(message);
				if (_channelEvent->nick() == _nickname)
					delete _channels.take(_channelEvent->channel());
				else if (_channels.contains(_channelEvent->channel()))
					_channels[_channelEvent->channel()]->remove(_channelEvent->nick());
				emit onPart(_channelEvent);
			}
			else if (message.commandName == "MODE")
			{
				if (message.params.count() > 0 && message.params[0].startsWith('#'))
				{
					_channelEvent->fill_in(message);
					emit onChannelMode(_channelEvent);
				}
				else
				{
					_userEvent->fill_in(message);
					emit onUserMode(_userEvent);
				}
			}
			else if (message.commandName == "QUIT")
			{
				_serverEvent->fill_in(message);
				foreach(UserList* users, _channels)
				{
					users->remove(_serverEvent->nick());
				}

				if (_channelEvent->nick() == _nickname)
				{
					_channels.remove(_channelEvent->channel());
				}

				emit onQuit(_serverEvent);
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
		{
			_rawEvent->fill_in(message);
			switch (_rawEvent->raw())
			{
				case RPL_NAMREPLY:
				{
					const QStringList& nicks = message.params[2].split(" ");
					if (_channels.contains(message.params[1]))
						foreach(QString nick, nicks)
							_channels[message.params[1]]->add(nick);
					else
					{
						qDebug() << "begin";
						UserList* users = new UserList();
						foreach(QString nick, nicks)
						 	users->add(nick);
						foreach(User* user, *users)
						{
							qDebug() << user->prefix() << " " << user->nick();
						}
						qDebug() << "end";
					 	//_channels.insert(message.params[1], users);
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
					 	//qDebug() << users;
					}
					break;
				}
			}
			emit onRaw(_rawEvent);
		}
	}

	// void
	// Client::remove_user_from(QStringList& userList, QString& user)
	// {
	// 	//while (user[0]
	// }

} // namespace com
