/*!
 * \file connector.cc
 * \author shaoner
 * \brief Handle the network communication
 */

# include <connector.hh>

namespace com
{

	Connector::Connector() :
		_connected(false),
		_socket(new QTcpSocket())
	{
		connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
				SLOT(on_socket_error(QAbstractSocket::SocketError)));
		connect(_socket, SIGNAL(connected()), this, SLOT(on_connect()));
		connect(_socket, SIGNAL(disconnected()), this, SLOT(on_disconnect()));
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
	Connector::isConnected() const
	{
		return _connected;
	}

	void
	Connector::connected(bool connected)
	{
		_connected = connected;
	}

	bool
	Connector::open(const QString& hostname, int port)
	{
		if (_connected)
			return false;
		emit onConnecting();
		_socket->connectToHost(hostname, port);
		return true;
	}

	bool
	Connector::close() const
	{
		if (!_connected)
			return false;
		_socket->disconnectFromHost();
		return true;
	}

	void
	Connector::on_connect()
	{
		_connected = true;
		emit onSocketConnect();
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
			if (message.isValid())
			{
				qDebug() << line;
				emit onIrcData(message);
			}
			else
				emit onError(SYNTAX_ERROR);
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
		}
	}

	void
	Connector::on_disconnect()
	{
		_connected = false;
		emit onSocketDisconnect();
	}

} // namespace com
