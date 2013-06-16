#ifndef COM_CLIENT_HH
# define COM_CLIENT_HH

# include <QTcpSocket>
# include <QString>
# include <QHash>

# include <role.hh>
# include <user-list.hh>
# include <channel-event.hh>
# include <user-event.hh>
# include <server-event.hh>
# include <raw-event.hh>
# include <connector.hh>

namespace com
{

/// The default IRC port
# define DEFAULT_PORT 6667

	class Client : public Connector
	{
		Q_OBJECT

	public:
        /// Ctor
		Client(const QString& nickname = "",
			   const QString& altnickname = "",
			   const QString& user = "",
			   const QString& realname = "");
		/// Dtor
		~Client();
	public:
		/// Connection
		void start(const QString& hostname, quint16 port = DEFAULT_PORT, const QString& password = "");
		void stop();
		/// Commands
		void send(const QString& target, const QString& message);
		/// Client parameters
		void set_nickname(const QString& nickname);
		void set_altnickname(const QString& altnickname);
		void set_user(const QString& user);
		void set_realname(const QString& realname);
		const QString& nickname() const;
		const QString& altnickname() const;
		const QString& user() const;
		const QString& realname() const;
		const QHash<QString, UserList*>& channels() const;
		/// Server paramaters
		const QString& hostname() const;
		quint16 port() const;
	signals:
		/// Event notifiers
		void onError(ServerEvent* event);
		void onConnect(ServerEvent* event);
		void onPing(ServerEvent* event);
		void onNotice(UserEvent* event);
		void onChannelMessage(UserEvent* event);
		void onPrivateMessage(UserEvent* event);
		void onJoin(UserEvent* event);
		void onPart(UserEvent* event);
		void onChannelMode(UserEvent* event);
		void onUserMode(UserEvent* event);
		void onQuit(ServerEvent* event);
		void onRaw(RawEvent* event);
		void onUserList(const QString& channel, UserList* users);
		void onNick(UserEvent* event);
		void onTopic(const QString& channel, const QString& topic);
		void onTopicInfo(const QString& channel, const QString& author, uint date);
	private slots:
		/// Socket event listeners
		void on_connect();
		void on_irc_data(Message& message);
	private:
		void process_mode_channel(Message& message);
		void process_raw_data(Message& message);
		void process_server_params(const QStringList& serverParams);
		//void remove_user_from(QStringList& userList, QString& user);
	private:
		QString _hostname;
		int _port;
		QString _password;
		QString _prefix;
		QString _nickname;
		QString _altnickname;
		QString _user;
		QString _realname;
		QHash<QString, UserList*> _channels;
		UserEvent* _userEvent;
		ServerEvent* _serverEvent;
		RawEvent* _rawEvent;
	};

} // namespace com

#endif /* !COM_CLIENT_HH */
