/*!
 * \file session.hh
 * \author shaoner
 * \brief IRC client session
 */

#include <session.hh>

namespace com
{
	Session::Session() :
		_hostname(""),
		_port(6667),
		_password(""),
		_prefix(""),
		_nickname(""),
		_username(""),
		_realname(""),
		_proto(new Protocol()),
		_channelEvent(new ChannelEvent()),
		_userEvent(new UserEvent()),
		_serverEvent(new ServerEvent()),
		_rawEvent(new RawEvent())
	{

		// register socket event listeners
		connect(_proto->socket(), SIGNAL(connected()), this, SLOT(on_connect()));
		connect(_proto->socket(), SIGNAL(disconnected()), this, SLOT(on_disconnect()));
		connect(_proto->socket(), SIGNAL(readyRead()), this, SLOT(on_receive_data()));
		connect(_proto->socket(), SIGNAL(error(QAbstractSocket::SocketError)), this,
				SLOT(on_socket_error(QAbstractSocket::SocketError)));
	}

	Session::~Session()
	{
		delete _rawEvent;
		delete _serverEvent;
		delete _userEvent;
		delete _channelEvent;
		delete _proto;
	}

	void
	Session::on_connect()
	{
		_proto->connected(true);
		_proto->write("NICK " + _nickname);
		/*
		 * FIXME: Alternative nickname is not handled
		 */
		_proto->write("USER " + _username + " 8 * :" + _realname);
		/*
		 * FIXME: Server password
		 */
	}

	void
	Session::on_disconnect()
	{
		_proto->connected(false);
	}

	void
	Session::on_socket_error(QAbstractSocket::SocketError error)
	{
		/*
		 * FIXME: Handling errors
		 */
		switch (error)
		{
		case QAbstractSocket::RemoteHostClosedError:
			qDebug("remote host close error");
			break;
		case QAbstractSocket::HostNotFoundError:
			qDebug("host not found error");
			break;
		case QAbstractSocket::ConnectionRefusedError:
			qDebug("connection refused error");
			break;
		default:
			qDebug("unknown socket error");
		}
	}

	void
	Session::on_receive_data()
	{
		QByteArray line;
		int end = 0;
		Message message;

		// Append new data
		_readData += _proto->socket()->readAll();
		// Read all irc messages in the buffer _readData
		while ((end = _readData.indexOf(MSG_DELIMITER)) != -1)
		{
			line = _readData.left(end);
			_readData = _readData.mid(end + sizeof(MSG_DELIMITER) - 1);
			if (!line.isEmpty())
			{
				message.clear();
				_parserDriver.parse(line, &message);
				if (message.isValid())
				{
					process(message);
				}
			}
		}
	}

	Error
	Session::start() const
	{
		if (_hostname.isEmpty())
			return ERR_BAD_PARAMETERS;
		if (_nickname.isEmpty())
			return ERR_BAD_PARAMETERS;
		if (_username.isEmpty())
			return ERR_BAD_PARAMETERS;
		if (_realname.isEmpty())
			return ERR_BAD_PARAMETERS;
		_proto->open(_hostname, _port);
		return ERR_NO_ERROR;
	}

	void
	Session::stop() const
	{
		_proto->close();
	}

	void
	Session::send_raw(const QString& raw)
	{
		_proto->write(raw);
	}

	void
	Session::join(const QString& channel)
	{
		_proto->write("JOIN " + channel);
	}

	void
	Session::part(const QString& channel)
	{
		_proto->write("PART " + channel);
	}

	void
	Session::notice(const QString& who, const QString& message)
	{
		_proto->write("NOTICE " + who + " " + message);
	}

	void
	Session::mode(const QString& who, const QString& mode)
	{
		_proto->write("MODE " + who + " " + mode);
	}

	void
	Session::process(Message& message)
	{
		// bool isDefaultProcessed = true;
		// EventName eType;
		// QList<Event*> eventList;
		// Event* event = 0;

		if (message.commandType == Message::MSG_CMDNAME)
		{
			// Handle mandatory events
			// This is not elegant, but it allows to handle non standard cases
			// like PING and it avoids a complex mechanism
			if (message.commandName == "NOTICE")
			{
				_userEvent->fill_in(message);
				emit onNotice(_userEvent);
			}
			else if (message.commandName == "PING")
			{
				_serverEvent->fill_in(message);
				emit onPing(_serverEvent);
				_proto->write("PONG " + message.params[0]);
			}
			else
			{
				qDebug() << "Unknown command " << message.commandName;
			}

		}
		else // message.commandType == Message::MSG_RAWNUM
		{
			_rawEvent->fill_in(message);
			emit onRaw(_rawEvent);
		}


		// eventList = _eventMap[eType];
		// Call each event callback
		// for (QList<Event*>::iterator it = eventList.begin();
		// 	 it != eventList.end();
		// 	 ++it)
		// {
		// 	event = *it;
		// 	if (event)
		// 	{
		// 		event->fill_in(message);
		// 		isDefaultProcessed = isDefaultProcessed && event->notify();
		// 	}
		// }
		// // Default event
		// if (isDefaultProcessed)
		// {
		// 	event = _defaultEventMap[eType];
		// 	if (event)
		// 	{
		// 		event->fill_in(message);
		// 		event->notify();
		// 	}
		// }
	}

	const QString&
	Session::hostname() const
	{
		return _hostname;
	}

	quint16
	Session::port() const
	{
		return _port;
	}

	const QString&
	Session::nickname() const
	{
		return _nickname;
	}

	const QString&
	Session::altnickname() const
	{
		return _altnickname;
	}

	const QString&
	Session::username() const
	{
		return _username;
	}

	const QString&
	Session::realname() const
	{
		return _realname;
	}

	void
	Session::hostname(const QString& hostname)
	{
		if (!hostname.isEmpty())
			_hostname = hostname;
	}

	void
	Session::port(quint16 port)
	{
		_port = port;
	}

	void
	Session::password(const QString& password)
	{
		_password = password;
	}

	void
	Session::nickname(const QString& nickname)
	{
		if (!nickname.isEmpty())
		{
			_nickname = nickname;
			if (_altnickname.isEmpty())
				_altnickname = nickname + "_";
		}
	}

	void
	Session::altnickname(const QString& altnickname)
	{
		if (!altnickname.isEmpty())
			_altnickname = altnickname;
	}

	void
	Session::username(const QString& username)
	{
		if (!username.isEmpty())
			_username = username;
	}

	void
	Session::realname(const QString& realname)
	{
		if (!realname.isEmpty())
			_realname = realname;
	}

} // namespace com
