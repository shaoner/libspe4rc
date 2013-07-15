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
 * \file user-list.hh
 * \author shaoner
 * \brief Channel userlist
 */

#ifndef COM_USERLIST_HH
# define COM_USERLIST_HH

# include <QString>
# include <QHash>

# include "user.hh"

namespace irc
{

	/*!
	 * \class UserList
	 * \brief This class is used to retrieve a userlist by channel
	 */
	class UserList : public QHash<QString, User*>
	{
	public:
		/// Ctor
		explicit UserList();
		/// Dtor
		~UserList();
	public:
		/// Add an IRC user
		void add(User* user);
		void add(const QString& nick);
		/// Remove an IRC user
		void remove(const QString& nick);
		/// Remove all
		void clear();
		/// Find an IRC user, which is pretty fast
		/// using a dichotomic search
		User* get(const QString& nick);
		/// Change a nickname
		bool change_nick(const QString& oldNick, const QString& newNick);
	};

} // namespace irc

#endif /* !COM_USERLIST_HH */
