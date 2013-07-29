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
 * \file session.hxx
 * \author shaoner
 * \brief An IRC session
 */

#ifndef IRC_SESSION_HXX
# define IRC_SESSION_HXX

# include "session.hh"

namespace irc
{

	inline void
	Session::action(const QString& target, const QString& message) const
	{
		write("PRIVMSG " + target + " :\001ACTION " + message + "\001");
	}

	inline void
	Session::admin(const QString& target) const
	{
		write("ADMIN" + (target.isEmpty() ? "" : " " + target));
	}

	inline void
	Session::away(const QString& reason) const
	{
		write("AWAY" + (reason.isEmpty() ? "" : " :" + reason));
	}

	inline void
	Session::cleartopic(const QString& channel) const
	{
		write("TOPIC " + channel + " :");
	}

	inline void
	Session::die() const
	{
		write("DIE");
	}

	inline void
	Session::info(const QString& server) const
	{
		write("INFO" + (server.isEmpty() ? "" : " " + server));
	}

	inline void
	Session::invite(const QString& nick, const QString& channel) const
	{
		write("INVITE " + nick + " " + channel);
	}

	inline void
	Session::join(const QString& channels, const QString& keys) const
	{
		write("JOIN " + channels + (keys.isEmpty() ? "" : " " + keys));
	}

	inline void
	Session::kick(const QString& channels, const QString& nicks, const QString& reason) const
	{
		write("KICK " + channels + " " + nicks + (reason.isEmpty() ? "" : " " + reason));
	}

	inline void
	Session::kill(const QString& nick, const QString& reason) const
	{
		write("KILL " + nick + " " + reason);
	}

	inline void
	Session::knock(const QString& channel, const QString& message) const
	{
		write("KNOCK " + channel + (message.isEmpty() ? "" : " " + message));
	}

	inline void
	Session::links(const QString& server, const QString& mask) const
	{
		write("LINKS" + (server.isEmpty() ? "" : " " + server + (mask.isEmpty() ? "" : " " + mask)));
	}

	inline void
	Session::list(const QString& channels, const QString& server) const
	{
		write("LIST" + (channels.isEmpty() ? "" : " " + channels + (server.isEmpty() ? "" : " " + server)));
	}

	inline void
	Session::lusers(const QString& mask, const QString& server) const
	{
		write("LUSERS" + (mask.isEmpty() ? "" : " " + mask + (server.isEmpty() ? "" : " " + server)));
	}

	inline void
	Session::mode(const QString& target, const QString& mode) const
	{
		write("MODE " + target + (mode.isEmpty() ? "" : " " + mode));
	}

	inline void
	Session::motd(const QString& server) const
	{
		write("MOTD" + (server.isEmpty() ? "" : " " + server));
	}

	inline void
	Session::names(const QString& channels) const
	{
		write("NAMES " + channels);
	}

	inline void
	Session::nick(const QString& newNick)
	{
		change_nickname(newNick);
	}

	inline void
	Session::notice(const QString& target, const QString& message) const
	{
		write("NOTICE " + target + " :" + message);
	}

	inline void
	Session::part(const QString& channels, const QString& reason) const
	{
		write("PART " + channels + (reason.isEmpty() ? "" : " :" + reason));
	}

	inline void
	Session::privmsg(const QString& target, const QString& message) const
	{
		write("PRIVMSG " + target + " :" + message);
	}

	inline void
	Session::quit(const QString& reason) const
	{
		write("QUIT" + (reason.isEmpty() ? "" : " :" + reason));
	}

	inline void
	Session::rehash() const
	{
		write("REHASH");
	}

	inline void
	Session::restart() const
	{
		write("RESTART");
	}

	inline void
	Session::serverconnect(const QString& server, const QString& port, const QString& remote) const
	{
		write("CONNECT " + server + " " + port + (remote.isEmpty() ? "" : " " + remote));
	}

	inline void
	Session::squit(const QString& server, const QString& comment) const
	{
		write("SQUIT " + server + " " + comment);
	}

	inline void
	Session::stats(const QString& query, const QString& server) const
	{
		write("STATS" + (query.isEmpty() ? "" : " " + query + (server.isEmpty() ? "" : " " + server)));
	}

	inline void
	Session::time(const QString& server) const
	{
		write("TIME" + (server.isEmpty() ? "" : " " + server));
	}

	inline void
	Session::topic(const QString& channel, const QString& topic) const
	{
		write("TOPIC " + channel + (topic.isEmpty() ? "" : " :" + topic));
	}

	inline void
	Session::trace(const QString& server) const
	{
		write("TRACE" + (server.isEmpty() ? "" : " " + server));
	}

	inline void
	Session::version(const QString& server) const
	{
		write("VERSION" + (server.isEmpty() ? "" : " " + server));
	}

	inline void
	Session::wallops(const QString& message) const
	{
		write("WALLOPS :" + message);
	}

	inline void
	Session::who(const QString& mask) const
	{
		write("WHO " + mask);
	}

	inline void
	Session::whois(const QString& nicks) const
	{
		write("WHOIS " + nicks);
	}

	inline void
	Session::whowas(const QString& nicks) const
	{
		write("WHOWAS " + nicks);
	}

	inline void
	Session::whowas(const QString& nicks, int count, const QString& server) const
	{
		write("WHOWAS " + nicks + " " + QString::number(count) + (server.isEmpty() ? "" : " " + server));
	}

	inline void
	Session::change_nickname(const QString& nickname)
	{
		if (!nickname.isEmpty())
		{
			if (!is_disconnected())
				write("NICK " + nickname);
			// To avoid setting a nickname already in use or with a bad syntax
			// In this case, _nickname is set during the onNick event
			if (!is_connected())
				_nickname = nickname;
		}
	}

	inline void
	Session::add_altnickname(const QString& nickname)
	{
		if (!nickname.isEmpty())
			_altnickname.append(nickname);
	}

	inline void
	Session::change_user(const QString& user)
	{
		if (!user.isEmpty() && !connection_established())
			_user = user;
	}

	inline void
	Session::change_realname(const QString& realname)
	{
		if (!realname.isEmpty() && !connection_established())
			_realname = realname;
	}

	inline const QString&
	Session::nickname() const
	{
		return _nickname;
	}

	inline const QString&
	Session::user() const
	{
		return _user;
	}

	inline const QString&
	Session::realname() const
	{
		return _realname;
	}

	inline const QHash<QString, UserList*>&
	Session::channels() const
	{
		return _channels;
	}

	inline const QString&
	Session::name() const
	{
		return _name;
	}

	inline const QString&
	Session::hostname() const
	{
		return _hostname;
	}

	inline quint16
	Session::port() const
	{
		return _port;
	}

	inline bool
	Session::is_channel(const QString& channel) const
	{
		return _channelPrefixes.contains(channel[0]);
	}

} // namespace irc

#endif /* !IRC_SESSION_HXX */
