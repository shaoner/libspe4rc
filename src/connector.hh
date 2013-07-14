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
# include <irc-error.hh>

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
		/// Get the connection status
		bool isConnected() const;
		/// Set the connection status
		void connected(bool connected);
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
		bool close() const;
	private slots:
		void on_connect();
		void on_receive_data();
		void on_socket_error(QAbstractSocket::SocketError error);
		void on_disconnect();
	protected:
		bool _connected;
	private:
		QTcpSocket* _socket;
		QByteArray _readData;
		Parser _parserDriver;
	};

} // namespace irc

#endif /* !COM_CONNECTOR_HH */
