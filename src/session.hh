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
 * \brief Client parameters
 */

#ifndef SESSION_HH
# define SESSION_HH

# include <QString>
# include <QStringList>

/// The default IRC port
# define DEFAULT_PORT 6667

namespace irc
{

	class Client;

	/*!
	 * \class Session
	 * \brief Named parameter idiom for Client
	 */
	class Session
	{
	public:
		/// Ctor
		explicit Session(const QString& name);
	public:
		/// Parameters
		Session& hostname(const QString& hostname);
		Session& port(quint16 port);
		Session& password(const QString& password);
		Session& nickname(const QString& nickname);
		Session& user(const QString& user);
		Session& realname(const QString& user);
		Session& altnickname(const QString& nickname);
		const QString& name() const;
		const QString& hostname() const;
		quint16 port() const;
		const QString& password() const;
		const QString& nickname() const;
		const QString& user() const;
		const QString& realname() const;
	private:
		friend class Client;
		QString _name;
		QString _hostname;
		quint16 _port;
		QString _password;
		QString _nickname;
		QString _user;
		QString _realname;
		QStringList _altnickname;
	};

	inline Session&
	Session::hostname(const QString& hostname)
	{
		_hostname = hostname;
		return *this;
	}

	inline Session&
	Session::port(quint16 port)
	{
		_port = port;
		return *this;
	}


	inline Session&
	Session::password(const QString& password)
	{
		_password = password;
		return *this;
	}

	inline Session&
	Session::nickname(const QString& nickname)
	{
		_nickname = nickname;
		return *this;
	}

	inline Session&
	Session::user(const QString& user)
	{
		_user = user;
		return *this;
	}

	inline Session&
	Session::realname(const QString& realname)
	{
		_realname = realname;
		return *this;
	}

	inline Session&
	Session::altnickname(const QString& nickname)
	{
		_altnickname.append(nickname);
		return *this;
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

	inline const QString&
	Session::password() const
	{
		return _password;
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

} // namespace irc

#endif /* !SESSION_HH */
