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
 * \file user-list.cc
 * \author shaoner
 * \brief Channel userlist
 */

#include "user-list.hh"

namespace irc
{

	UserList::UserList()
	{
	}

	UserList::~UserList()
	{
		clear();
	}

	void
	UserList::add(User* user)
	{
		insert(user->nick(), user);
	}

	void
	UserList::add(const QString& nick)
	{
		User* user = new User(nick);
		insert(nick, user);
	}

	void
	UserList::remove(const QString& nick)
	{
		if (contains(nick))
			delete take(nick);
	}

	void
	UserList::clear()
	{
		QList<User*> uList = values();
		foreach (User* user, uList)
		{
			delete user;
		}
		QHash<QString, User*>::clear();
	}

	User*
	UserList::get(const QString& nick)
	{
		return value(nick, NULL);
	}

	bool
	UserList::change_nick(const QString& oldNick, const QString& newNick)
	{
		if (contains(oldNick))
		{
			User* user = take(oldNick);
			user->change_nick(newNick);
			insert(newNick, user);
		}
		return false;
	}

} // namespace irc
