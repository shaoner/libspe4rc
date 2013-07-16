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
 * \file user.cc
 * \author shaoner
 * \brief IRC user
 */

#include "user.hh"

namespace irc
{

	User::~User()
	{
	}

	void
	User::change_nick(const QString& nick)
	{
		if (_roles)
			_fullnick = _prefix + nick;
		else
			_fullnick = nick;
		_nick = nick;
		emit onChangeFullNick(nick);
	}

	void
	User::add_prefix(char prefix)
	{
		quint8 role = Role::get()->from_prefix(prefix);
  		if (role > _roles)
		{
			_prefix = prefix;
			// If there already is a prefix, we replace it
			// Otherwise, we prepend it
			if (_roles)
				_fullnick.replace(0, 1, _prefix);
			else
				_fullnick.prepend(_prefix);
			emit onChangeFullNick(_nick);
		}
		_roles |= role;
	}

	void
	User::del_prefix(char prefix)
	{
		quint8 delRole = Role::get()->from_prefix(prefix);
		quint8 oldRole = _roles;
		_roles -= delRole;
		// Change the fullnick when the highest role is removed
		if (delRole > _roles)
		{
			char newPrefix = Role::get()->to_prefix(uint8_msb(_roles));
			_prefix = newPrefix;
			if (!_prefix)
				_fullnick = _nick;
			else if (oldRole)
				_fullnick.replace(0, 1, _prefix);
			else
				_fullnick.prepend(_prefix);
			emit onChangeFullNick(_nick);
		}
	}

	bool
	User::is_op() const
	{
		static quint8 opRole = Role::get()->from_prefix('@');
		return (_roles & opRole) == opRole;
	}

	bool
	User::is_halfop() const
	{
		static quint8 halfopRole = Role::get()->from_prefix('%');
		return (_roles & halfopRole) == halfopRole;
	}

	bool
	User::is_voice() const
	{
		static quint8 voiceRole = Role::get()->from_prefix('%');
		return (_roles & voiceRole) == voiceRole;
	}

	User::User(const QString& fullnick) :
		_fullnick(fullnick),
		_nick(fullnick)
	{
		_prefix = fullnick[0].toAscii();
		_roles = Role::get()->from_prefix(_prefix);
		// The nick does not contain the prefix
		if (_roles)
			_nick.remove(0, 1);
		else
			_prefix = 0;
	}

} // namespace irc
