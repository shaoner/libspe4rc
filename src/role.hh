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
 * \file role.hh
 * \author shaoner
 * \brief An IRC channel role helper
 */

#ifndef IRC_ROLE_HH
# define IRC_ROLE_HH

# include <QHash>

namespace irc
{

	/*!
	 * \class Role
	 * \brief This class dynamicly handles IRC channel roles
	 */
	class Role
	{
	public:
		static Role* get();
		static void reset();
	public:
		quint8 highest(quint8 role);
		char to_prefix(quint8 role);
		quint8 from_prefix(char prefix);
		char from_mode(char mode);
		void add(char mode, char prefix, quint8 role);
	private:
		static Role* _instance;
	private:
		Role();
	private:
		QHash<char, char> _supportedPrefixes;
		QHash<char, quint8> _supportedRoles;
	};

	/// Get the most significant bit
	quint8 uint8_msb(quint8 role);

	inline char
	Role::to_prefix(quint8 role)
	{
		return _supportedRoles.key(role, 0);
	}

	inline quint8
	Role::from_prefix(char prefix)
	{
		return _supportedRoles.value(prefix, 0);
	}

	inline char
	Role::from_mode(char mode)
	{
		return _supportedPrefixes.value(mode, 0);
	}

	inline quint8
	uint8_msb(quint8 role)
	{
		role |= role >> 1;
		role |= role >> 2;
		role |= role >> 4;
		return role - (role >> 1);
	}

} // namespace irc

#endif /* !IRC_ROLE_HH */
