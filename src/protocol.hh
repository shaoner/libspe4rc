/*!
 * \file protocol.hh
 * \author shaoner
 * \brief Handle the network communication
 */

#ifndef COM_PROTOCOL_HH
# define COM_PROTOCOL_HH

# include <QTcpSocket>
# include <QString>

# include <common.hh>

/// IRC Message delimiter
# define MSG_DELIMITER "\r\n"

namespace com
{
	/*!
	 * \class Protocol
	 * \brief This class handles a socket communication
	 */
	class Protocol
	{
	public:
		/// Ctor
		Protocol();
		/// Dtor
		~Protocol();
	public:
		/// Connect to hostname and port
		Error open(const QString& hostname, int port) const;
		/// Disconnect the socket if connected
		Error close() const;
		/// Send a simple message
		int write(const QString& message) const;
	public:
		/// Get the current socket
		QTcpSocket* socket() const;
		/// Get the connection status
		bool isConnected() const;
		/// Set the connection status
		void connected(bool connected);
	private:
		bool _connected;
		QTcpSocket* _socket;
	};

} // namespace com

#endif /* !COM_PROTOCOL_HH */
