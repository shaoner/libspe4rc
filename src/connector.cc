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
 * \file connector.cc
 * \author shaoner
 * \brief Handle the network communication
 */

#include "connector.hh"
#include "message.hh"

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
	}

} // namespace irc
