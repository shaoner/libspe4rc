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
 * \file role.cc
 * \author shaoner
 * \brief An IRC channel role helper
 */

#include "role.hh"

namespace irc
{

	Role* Role::_instance = NULL;

	Role*
	Role::get()
	{
		if (!_instance)
			_instance = new Role();
		return _instance;
	}

	void
	Role::reset()
	{
		delete _instance;
		_instance = NULL;
	}

	void
	Role::add(char mode, char prefix, quint8 level)
	{
		_supportedPrefixes.insert(mode, prefix);
		_supportedRoles.insert(prefix, level);
	}

	Role::Role()
	{
		// Set tradional modes by default
		// It will be replaced during event RPL_BOUNCE
		_supportedPrefixes['v'] = '+';
		_supportedRoles['+'] = 1;
		_supportedPrefixes['h'] = '%';
		_supportedRoles['%'] = 2;
		_supportedPrefixes['o'] = '@';
		_supportedRoles['@'] = 4;
	}

} // namespace irc
