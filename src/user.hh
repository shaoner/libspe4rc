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
 * \file user.hh
 * \author shaoner
 * \brief IRC user
 */

#ifndef COM_USER_HH
# define COM_USER_HH

# include <QString>

# include "role.hh"

namespace irc
{

	class UserList;

	/*!
	 * \class User
	 * \brief This class represents an IRC user in a channel
	 */
    class User : public QObject
	{
		Q_OBJECT

		friend UserList;
	public:
		/// Dtor
		~User();
	public:
		/// user attributes
		const QString& fullnick() const { return _fullnick; }
		const QString& nick() const { return _nick; }
		quint8 roles() const { return _roles; }
		/// Change user attributes
		void change_nick(const QString& nick);
		void add_prefix(char prefix);
		void del_prefix(char prefix);
		/// Check tradional roles
		bool is_op() const;
		bool is_halfop() const;
		bool is_voice() const;
	public:
		/// Comparing users
		friend bool operator==(User& user1, User& user2);
		friend bool operator<(User& user1, User& user2);
	signals:
		void onChangeFullNick(const QString&);
	private:
		/// Ctor
		User(const QString& fullnick);
	private:
		void set_nick(const QString& nick) { _nick = nick; }
	private:
		QString _fullnick;
		QString _nick;
		char _prefix;
		quint8 _roles;
	};

} // namespace irc

#endif /* !COM_USER_HH */
