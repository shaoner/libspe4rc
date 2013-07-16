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

 * You should have received a copy of the GNU Lesser General Public License
 * along with Libspe4rc. If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*!
 * \file connector.hh
 * \author shaoner
 * \brief Handle the network communication
 */

#ifndef COM_CONNECTOR_HH
# define COM_CONNECTOR_HH

# include <QTcpSocket>

# include "parser.hh"
# include "message.hh"
# include "irc-error.hh"

/// IRC Message delimiter
# define MSG_DELIMITER "\r\n"

namespace irc
{

	/*!
	 * \class Connector
	 * \brief This class handles a socket communication
	 */
	class Connector : public QObject
	{
		Q_OBJECT

	public:
		/// Ctor
		Connector();
		/// Dtor
		~Connector();
	public:
		/// Send a simple message
		int write(const QString& message) const;
		bool connection_established() const;
		bool is_connected() const;
		bool is_connecting() const;
	signals:
		void onSocketConnect();
		void onIrcData(Message& message);
		void onSocketDisconnect();
		void onError(IrcError error);
		void onConnecting();
	protected:
		/// Connect to hostname and port
		bool open(const QString& hostname, int port);
		/// Disconnect the socket if connected
		void close() const;
	private slots:
		void on_connect();
		void on_receive_data();
		void on_socket_error(QAbstractSocket::SocketError error);
		void on_disconnect();
	protected:
		bool _connected;
		bool _connecting;
		QTcpSocket* _socket;
	private:
		QByteArray _readData;
		Parser _parserDriver;
	};

	inline bool
	Connector::connection_established() const
	{
		return (_socket->state() == QAbstractSocket::ConnectedState);
	}

	inline bool
	Connector::is_connected() const
	{
		return (connection_established() && _connected);
	}

	inline bool
	Connector::is_connecting() const
	{
		return ((_socket->state() == QAbstractSocket::ConnectingState) &&
				_connecting);
	}

} // namespace irc

#endif /* !COM_CONNECTOR_HH */
