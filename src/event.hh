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
 * \file event.hh
 * \author shaoner
 * \brief IRC event interface
 */

#ifndef IRC_EVENT_HH
# define IRC_EVENT_HH

namespace irc
{

	class Session;

	/*!
	 * \class Event
	 * \brief This class is an interface representing an irc message as an event
	 */
	class Event
	{
	public:
		/// Ctor
		Event(Session* session);

	protected:
		/// Get associated irc session session
		const Session& session() const;
	private:
		Session& _session;
	};

	inline
	Event::Event(Session* session) :
		_session(*session)
	{
	}

	inline const Session&
	Event::session() const
	{
		return _session;
	}

} // namespace irc

#endif /* !IRC_EVENT_HH */
