/*!
 * \file protocol.cc
 * \author shaoner
 * \brief Handle the network communication
 */

# include <protocol.hh>

namespace com
{

	Protocol::Protocol() :
		_connected(false)
	{
		_socket = new QTcpSocket();//this);
	}

	Protocol::~Protocol()
	{
		close();
		delete _socket;
	}

	Error
	Protocol::open(const QString& hostname, int port) const
	{
		if (_connected)
			return ERR_ALREADY_CONNECTED;
		_socket->connectToHost(hostname, port);
		return ERR_NO_ERROR;
	}

	Error
	Protocol::close() const
	{
		if (!_connected)
			return ERR_ALREADY_DISCONNECTED;
		_socket->disconnectFromHost();
		return ERR_NO_ERROR;
	}

	int
	Protocol::write(const QString& message) const
	{
		/*
		 * FIXME: Output charset should be configurable
		 */
		int i = _socket->write(message.toUtf8() + MSG_DELIMITER);
		_socket->flush();
		qDebug() << "Sent:" << message;
		return i;
	}

	QTcpSocket*
	Protocol::socket() const
	{
		return _socket;
	}

	bool
	Protocol::isConnected() const
	{
		return _connected;
	}

	void
	Protocol::connected(bool connected)
	{
		_connected = connected;
	}

} // namespace com
