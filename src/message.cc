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
 * \file message.cc
 * \author shaoner
 * \brief IRC Message
 */

#include "message.hh"

namespace irc
{

	Message::Message() :
		isValid(false)
	{
	}

	void
	Message::clear()
	{
		nick.clear();
		user.clear();
		host.clear();
		commandName.clear();
		params.clear();
		rawNumber = 0;
	}

} // namespace irc
