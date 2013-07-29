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
 * \file session-parameters.hxx
 * \author shaoner
 * \brief Session parameters (Named parameter idiom)
 */

#ifndef IRC_SESSION_PARAMETERS_HXX
# define IRC_SESSION_PARAMETERS_HXX

# include "session-parameters.hh"

namespace irc
{

	inline
	SessionParameters::SessionParameters(const QString& name) :
		_name(name),
		_hostname(""),
		_port(DEFAULT_IRC_PORT),
		_password(""),
		_nickname(""),
		_user(""),
		_realname(""),
		_umode(0)
	{
	}


	inline SessionParameters&
	SessionParameters::hostname(const QString& hostname)
	{
		_hostname = hostname;
		return *this;
	}

	inline SessionParameters&
	SessionParameters::port(quint16 port)
	{
		_port = port;
		return *this;
	}


	inline SessionParameters&
	SessionParameters::password(const QString& password)
	{
		_password = password;
		return *this;
	}

	inline SessionParameters&
	SessionParameters::nickname(const QString& nickname)
	{
		_nickname = nickname;
		return *this;
	}

	inline SessionParameters&
	SessionParameters::user(const QString& user)
	{
		_user = user;
		return *this;
	}

	inline SessionParameters&
	SessionParameters::realname(const QString& realname)
	{
		_realname = realname;
		return *this;
	}

	inline SessionParameters&
	SessionParameters::altnickname(const QString& nickname)
	{
		_altnickname.append(nickname);
		return *this;
	}

	inline SessionParameters&
	SessionParameters::invisible()
	{
		_umode |= 0x8;
		return *this;
	}

	inline SessionParameters&
	SessionParameters::receiveWallops()
	{
		_umode |= 0x4;
		return *this;
	}

	inline const QString&
	SessionParameters::name() const
	{
		return _name;
	}

	inline const QString&
	SessionParameters::hostname() const
	{
		return _hostname;
	}

	inline quint16
	SessionParameters::port() const
	{
		return _port;
	}

	inline const QString&
	SessionParameters::password() const
	{
		return _password;
	}

	inline const QString&
	SessionParameters::nickname() const
	{
		return _nickname;
	}

	inline const QString&
	SessionParameters::user() const
	{
		return _user;
	}

	inline const QString&
	SessionParameters::realname() const
	{
		return _realname;
	}

} // namespace irc

#endif /* !IRC_SESSION_PARAMETERS_HXX */
