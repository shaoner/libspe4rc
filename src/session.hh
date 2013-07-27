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
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Libspe4rc. If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*!
 * \file session.hh
 * \author shaoner
 * \brief An IRC session
 */

#ifndef IRC_SESSION_HH
# define IRC_SESSION_HH

# include <QString>
# include <QStringList>
# include <QHash>

# include "session-parameters.hh"
# include "connector.hh"

namespace irc
{

	class UserList;
	class CommandEvent;
	class RawEvent;

	/*!
	 * \class Session
	 * \brief This class represents an IRC client session
	 */
	class Session : public Connector
	{
		Q_OBJECT

	public:
        /// Ctor
		Session(const SessionParameters& sessionParam);
		/// Dtor
		~Session();
	public:
		/// Connection
		void start();
		void start(const QString& hostname,
				   quint16 port = DEFAULT_IRC_PORT,
				   const QString& password = "");
		void stop();
		/// Commands
		void msg(const QString& target, const QString& message) const;
		void action(const QString& target, const QString& message) const;
		void notice(const QString& target, const QString& message) const;
		void join(const QString& channels, const QString& keys = "") const;
		void part(const QString& channel, const QString& reason = "") const;
		void quit(const QString& reason = "") const;
		void kick(const QString& channel, const QString& nick, const QString& reason = "") const;
		void invite(const QString& nick, const QString& channel) const;
		void mode(const QString& target, const QString& mode = "") const;
		void topic(const QString& channel, const QString& topic = "") const;
		void cleartopic(const QString& channel) const;
		void whois(const QString& nicks) const;
		void names(const QString& channel) const;
		/// Session parameters
		void change_nickname(const QString& nickname);
		void add_altnickname(const QString& nickname);
		void change_user(const QString& user);
		void change_realname(const QString& realname);
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
		void onChannelAction(CommandEvent& event, const QString& target, const QString& msg);
		void onPrivateMessage(CommandEvent& event, const QString& msg);
		void onPrivateAction(CommandEvent& event, const QString& msg);

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
		void onNoTopic(const QString& channel, const QString& msg);
	private slots:
		/// Socket event listeners
		void on_socket_connect();
		void on_socket_disconnect();
		void on_irc_data(Message& message);
	private:
		void process_privmsg(CommandEvent& event, const QString& target, const QString& msg);
		void process_mode_channel(CommandEvent& event, const QString& channel, const QString& modes, const QStringList& args);
		void process_raw_data(Message& message);
		void process_server_params(const QStringList& serverParams);
		void clean();
	private:
		/// Server info
		QString _name;
		QString _hostname;
		int _port;
		QString _password;
		/// User info
		QString _nickname;
		QStringList _altnickname;
		QString _user;
		QString _realname;
		quint8 _umode;
		QHash<QString, UserList*> _channels;
		QString _channelPrefixes;
		bool _uListCreating;
	};

} // namespace irc

# include "session.hxx"

#endif /* !IRC_SESSION_HH */
