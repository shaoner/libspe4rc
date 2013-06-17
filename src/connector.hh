/*!
 * \file connector.hh
 * \author shaoner
 * \brief Handle the network communication
 */

#ifndef COM_CONNECTOR_HH
# define COM_CONNECTOR_HH

# include <QTcpSocket>
# include <parser.hh>
# include <message.hh>

/// IRC Message delimiter
# define MSG_DELIMITER "\r\n"

namespace com
{

	/// \enum Error
	enum ConnectError
	{
		NO_ERROR,
		NOT_INITIALIZED,
		ALREADY_CONNECTED,
		ALREADY_DISCONNECTED,
		BAD_PARAMETERS,
	};

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
		/// Get the connection status
		bool isConnected() const;
		/// Set the connection status
		void connected(bool connected);
	signals:
		void onSocketConnect();
		void onIrcData(Message& message);
		void onSocketDisconnect();
	protected:
		/// Connect to hostname and port
		ConnectError open(const QString& hostname, int port) const;
		/// Disconnect the socket if connected
		ConnectError close() const;
	private slots:
		void on_connect();
		void on_receive_data();
		void on_socket_error(QAbstractSocket::SocketError error) const;
		void on_disconnect();
	private:
		bool _connected;
		QTcpSocket* _socket;
		QByteArray _readData;
		Parser _parserDriver;
	};

} // namespace com

#endif /* !COM_CONNECTOR_HH */
