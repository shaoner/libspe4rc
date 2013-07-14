/*!
 * \file connector.cc
 * \author shaoner
 * \brief Handle the network communication
 */

# include <connector.hh>

namespace irc
{

	Connector::Connector() :
		_connected(false),
		_connecting(false),
		_socket(new QTcpSocket())
	{
		connect(_socket, SIGNAL(connected()), this, SLOT(on_connect()));
		connect(_socket, SIGNAL(disconnected()), this, SLOT(on_disconnect()));
		connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
				SLOT(on_socket_error(QAbstractSocket::SocketError)));
		connect(_socket, SIGNAL(readyRead()), this, SLOT(on_receive_data()));
	}

	Connector::~Connector()
	{
		close();
		delete _socket;
	}

	int
	Connector::write(const QString& message) const
	{
		/*
		 * FIXME: Output charset should be configurable
		 */
		int i = _socket->write(message.toUtf8() + MSG_DELIMITER);
		_socket->flush();
		return i;
	}

	bool
	Connector::open(const QString& hostname, int port)
	{
		if (connection_established())
			return false;
		_connecting = true;
		emit onConnecting();
		_socket->connectToHost(hostname, port);
		return true;
	}

	void
	Connector::close() const
	{
		_socket->disconnectFromHost();
	}

	bool
	Connector::connection_established() const
	{
		return (_socket->state() == QAbstractSocket::ConnectedState);
	}

	bool
	Connector::is_connected() const
	{
		return (connection_established() && _connected);
	}

	bool
	Connector::is_connecting() const
	{
		return ((_socket->state() == QAbstractSocket::ConnectingState) &&
				_connecting);
	}

	void
	Connector::on_connect()
	{
		emit onSocketConnect();
	}

	void
	Connector::on_disconnect()
	{
		_connecting = false;
		_connected = false;
		emit onSocketDisconnect();
	}

	void
	Connector::on_receive_data()
	{
		QByteArray line;
		int end = 0;
		Message message;

		// Append new data
		_readData += _socket->readAll();
		// Read all irc messages in the buffer _readData
		while ((end = _readData.indexOf(MSG_DELIMITER)) != -1)
		{
			line = _readData.left(end);
			_readData = _readData.mid(end + sizeof(MSG_DELIMITER) - 1);
			message.clear();
			_parserDriver.parse(line, &message);
			if (message.isValid)
			{
				qDebug() << line;
				emit onIrcData(message);
			}
		}
	}

	void
	Connector::on_socket_error(QAbstractSocket::SocketError error)
	{
		switch (error)
		{
			case QAbstractSocket::RemoteHostClosedError:
				emit onError(SOCKET_REMOTECLOSE_ERROR);
				break;
			case QAbstractSocket::HostNotFoundError:
				emit onError(SOCKET_HOSTNOTFOUND_ERROR);
				break;
			case QAbstractSocket::ConnectionRefusedError:
				emit onError(SOCKET_CONNECTIONREFUSED_ERROR);
				break;
			default:
				emit onError(UNKNOWN_ERROR);
				return;
		}
		emit onSocketDisconnect();
	}

} // namespace irc
