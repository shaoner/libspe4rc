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
 * \file client.hh
 * \author shaoner
 * \brief An IRC session
 */

#ifndef COM_CLIENT_HH
# define COM_CLIENT_HH

# include <QString>
# include <QHash>

# include "user-list.hh"
# include "command-event.hh"
# include "raw-event.hh"
# include "connector.hh"

/// The default IRC port
# define DEFAULT_PORT 6667

namespace irc
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
		void start(const QString& hostname,
				   quint16 port = DEFAULT_PORT,
				   const QString& password = "");
		void stop();
		/// Commands
		void msg(const QString& target, const QString& message) const;
		void join(const QStringList& channels) const;
		void join(const QString& channel) const;
		void part(const QString& channel, const QString& reason = "") const;

		/// Client parameters
		void change_nickname(const QString& nickname);
		void add_altnickname(const QString& nickname);
		void change_user(const QString& user);
		void change_realname(const QString& realname);
		const QString& nickname() const { return _nickname; }
		const QString& user() const { return _user; }
		const QString& realname() const { return _realname; }
		const QHash<QString, UserList*>& channels() const { return _channels; }
		/// Server paramaters
		const QString& name() const { return _name; }
		const QString& hostname() const { return _hostname; }
		quint16 port() const { return _port; }
		bool is_channel(const QString& channel) const {
			return _channelPrefixes.contains(channel[0]);
		}
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
		QHash<QString, UserList*> _channels;
		QString _channelPrefixes;
	};

} // namespace irc

#endif /* !COM_CLIENT_HH */
