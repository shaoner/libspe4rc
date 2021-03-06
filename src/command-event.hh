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
 * \file command-event.hh
 * \author shaoner
 * \brief IRC event command
 */

#ifndef IRC_COMMAND_EVENT_HH
# define IRC_COMMAND_EVENT_HH

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
		CommandEvent(Message& message, Session* session);
	public:
		/// Get client info
		const QString& nick() const;
		const QString& user() const;
		const QString& host() const;
	protected:
		const QString& _nick;
		const QString& _user;
		const QString& _host;
	};

	inline
	CommandEvent::CommandEvent(Message& message, Session* session) :
		Event(session),
		_nick(message.nick),
		_user(message.user),
		_host(message.host)
	{
	}

	inline const QString&
	CommandEvent::nick() const
	{
		return _nick;
	}

	inline const QString&
	CommandEvent::user() const
	{
		return _user;
	}

	inline const QString&
	CommandEvent::host() const
	{
		return _host;
	}

} // namespace irc

#endif /* !IRC_COMMAND_EVENT_HH */
