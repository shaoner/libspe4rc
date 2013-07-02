/*!
 * \file client.hh
 * \author shaoner
 * \brief An IRC session
 */

#ifndef COM_CLIENT_HH
# define COM_CLIENT_HH

# include <QTcpSocket>
# include <QString>
# include <QHash>

# include <role.hh>
# include <user-list.hh>
# include <command-event.hh>
# include <raw-event.hh>
# include <connector.hh>

/// The default IRC port
# define DEFAULT_PORT 6667

namespace com
{

	/*!
	 * \class Client
	 * \brief This class is an IRC client session
	 */
	class Client : public Connector
	{
		Q_OBJECT

	public:
        /// Ctor
		Client(const QString& name,
			   const QString& hostname,
			   quint16 port = DEFAULT_PORT,
			   const QString& password = "",
			   const QString& nickname = "",
			   const QString& user = "",
			   const QString& realname = "");
		/// Dtor
		~Client();
	public:
		/// Connection
		void start();
		void stop();
		/// Commands
		void msg(const QString& target, const QString& message) const;
		void join(const QStringList& channels) const;
		void join(const QString& channel) const;
		void part(const QString& channel, const QString& reason = "") const;

		/// Client parameters
		void set_nickname(const QString& nickname);
		void add_altnickname(const QString& nickname);
		void set_user(const QString& user);
		void set_realname(const QString& realname);
		const QString& nickname() const;
		const QString& user() const;
		const QString& realname() const;
		const QHash<QString, UserList*>& channels() const;
		/// Server paramaters
		const QString& name() const;
		const QString& hostname() const;
		quint16 port() const;
		bool is_channel(const QString& channel) const;
	signals:
		/// Event notifiers
		void onError();
		void onConnect();
		void onDisconnect();

		void onPing(CommandEvent& event, const QString& server);
		void onQuit(CommandEvent& event, const QString& reason);

		void onChannelMessage(CommandEvent& event, const QString& target, const QString& msg);
		void onPrivateMessage(CommandEvent& event, const QString& target, const QString& msg);

		void onJoin(CommandEvent& event, const QString& channel);
		void onPart(CommandEvent& event, const QString& channel, const QString& reason);
		void onKick(CommandEvent& event, const QString& channel, const QString& target, const QString& reason);

		void onUserMode(CommandEvent& event, const QString& target, const QString& modes);
		void onChannelMode(CommandEvent& event, const QString& channel, const QString& modes, const QStringList& args);
		void onNick(CommandEvent& event, const QString& newNick);

		void onNotice(CommandEvent& event, const QString& target, const QString& msg);
		void onInvite(CommandEvent& event, const QString& target, const QString& channel);

		void onRaw(RawEvent& event);
		void onUserList(const QString& channel, UserList* users);

		void onChangeTopic(CommandEvent& event, const QString& channel, const QString& subject);
		void onTopic(const QString& channel, const QString& topic);
		void onTopicInfo(const QString& channel, const QString& author, uint date);
	private slots:
		/// Socket event listeners
		void on_socket_connect();
		void on_socket_disconnect();
		void on_irc_data(Message& message);
	private:
		void process_mode_channel(CommandEvent& event, const QString& channel, const QString& modes, const QStringList& args);
		void process_raw_data(Message& message);
		void process_server_params(const QStringList& serverParams);
		void clean();
	private:
		QString _name;
		QString _hostname;
		int _port;
		QString _password;
		QString _prefix;
		QString _nickname;
		QStringList _altnickname;
		QString _user;
		QString _realname;
		QHash<QString, UserList*> _channels;
		QString _channelPrefixes;
	};

} // namespace com

#endif /* !COM_CLIENT_HH */
