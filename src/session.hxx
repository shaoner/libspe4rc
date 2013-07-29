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
	Session::msg(const QString& target, const QString& message) const
	{
		write("PRIVMSG " + target + " :" + message);
	}

	inline void
	Session::action(const QString& target, const QString& message) const
	{
		write("PRIVMSG " + target + " :\001ACTION " + message + "\001");
	}

	inline void
	Session::notice(const QString& target, const QString& message) const
	{
		write("NOTICE " + target + " :" + message);
	}

	inline void
	Session::join(const QString& channels, const QString& keys) const
	{
		if (keys.isEmpty())
			write("JOIN " + channels);
		else
			write("JOIN " + channels + " " + keys);
	}

	inline void
	Session::part(const QString& channels, const QString& reason) const
	{
		if (reason.isEmpty())
			write("PART " + channels);
		else
			write("PART " + channels + " :" + reason);
	}

	inline void
	Session::quit(const QString& reason) const
	{
		if (reason.isEmpty())
			write("QUIT");
		else
			write("QUIT :" + reason);
	}

	inline void
	Session::kick(const QString& channels, const QString& nicks, const QString& reason) const
	{
		if (reason.isEmpty())
			write("KICK " + channels + " " + nicks);
		else
			write("KICK " + channels + " " + nicks + " :" + reason);
	}

	inline void
	Session::invite(const QString& nick, const QString& channel) const
	{
		write("INVITE " + nick + " " + channel);
	}

	inline void
	Session::mode(const QString& target, const QString& mode) const
	{
		if (mode.isEmpty())
			write("MODE " + target);
		else
			write("MODE " + target + " " + mode);
	}

	inline void
	Session::topic(const QString& channel, const QString& topic) const
	{
		if (topic.isEmpty())
			write("TOPIC " + channel);
		else
			write("TOPIC " + channel + " :" + topic);
	}

	inline void
	Session::cleartopic(const QString& channel) const
	{
		write("TOPIC " + channel + " :");
	}

	inline void
	Session::whois(const QString& nicks) const
	{
		write("WHOIS " + nicks);
	}

	inline void
	Session::names(const QString& channels) const
	{
		write("NAMES " + channels);
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
