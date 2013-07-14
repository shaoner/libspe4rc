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
 * \file command-event.hh
 * \author shaoner
 * \brief IRC event command
 */

#ifndef COM_COMMAND_EVENT_HH
# define COM_COMMAND_EVENT_HH

# include "event.hh"
# include "message.hh"

namespace irc
{

	/*!
	 * \class CommandEvent
	 * \brief This class represents an irc message as a command event
	 */
	class CommandEvent : public Event
	{
	public:
		/// Ctor
		CommandEvent(Message& message, Client* client) :
			Event(client),
			_nick(message.nick),
			_user(message.user),
			_host(message.host)
		 {
		 }

	public:
		/// Get client info
		const QString& nick() const { return _nick; }
		const QString& user() const { return _user; }
		const QString& host() const { return _host; }
	protected:
		const QString& _nick;
		const QString& _user;
		const QString& _host;
	};

} // namespace irc

#endif /* !COM_COMMAND_EVENT_HH */
