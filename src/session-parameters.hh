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
 * \file session-parameters.hh
 * \author shaoner
 * \brief Session parameters
 */

#ifndef IRC_SESSION_PARAMETERS_HH
# define IRC_SESSION_PARAMETERS_HH

# include <QString>
# include <QStringList>

/// The default IRC port
# define DEFAULT_IRC_PORT 6667

namespace irc
{

	class Session;

    enum SessionMode
    {
        MODE_RECEIVE_WALLOPS = 0x4,
        MODE_INVISIBLE = 0x8
    };

	/*!
	 * \class SessionParameters
	 * \brief Named parameter idiom for Session
	 */
	class SessionParameters
	{
	public:
		/// Ctor
		explicit SessionParameters(const QString& name = "");
	public:
		/// Parameters
        SessionParameters& name(const QString& name);
        SessionParameters& hostname(const QString& hostname);
		SessionParameters& port(quint16 port);
		SessionParameters& password(const QString& password);
		SessionParameters& nickname(const QString& nickname);
		SessionParameters& user(const QString& user);
		SessionParameters& realname(const QString& user);
		SessionParameters& altnickname(const QString& nickname);
		SessionParameters& altnickname(const QStringList& nicknames);
		SessionParameters& set_uMode(SessionMode mode);
		const QString& name() const;
		const QString& hostname() const;
		quint16 port() const;
		const QString& password() const;
		const QString& nickname() const;
		const QString& user() const;
		const QString& realname() const;
		const QStringList& altnickname() const;
        bool has_uMode(SessionMode mode) const;
	private:
		friend class Session;
		QString _name;
		QString _hostname;
		quint16 _port;
		QString _password;
		QString _nickname;
		QString _user;
		QString _realname;
		QStringList _altnickname;
		quint8 _uMode;
    };
} // namespace irc

# include "session-parameters.hxx"

#endif /* !IRC_SESSION_PARAMETERS_HH */
