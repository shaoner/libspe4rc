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
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Libspe4rc. If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*!
 * \file message.hh
 * \author shaoner
 * \brief IRC Message
 */

#ifndef IRC_MESSAGE_HH
# define IRC_MESSAGE_HH

# include <QStringList>

namespace irc
{

	/*!
	 * \class Message
	 * \brief This class represents an irc message
	 */
	class Message
	{
	public:
		/// Ctor
		Message();
	public:
		/// \enum CommandType
		enum CommandType
		{
			MSG_RAWNUM,
			MSG_CMDNAME
		};
		/// Clear the message
		void clear();
	public:
		/// Get the message validy
		bool isValid;
		/// Sender info
		QString nick;
		QString user;
		QString host;
		/// Message type, which can be a raw or command
		CommandType commandType;
		/// Name of the command
		QString commandName;
		/// Facultative additional parameters
		QStringList params;
		/// Raw number
		quint16 rawNumber;
	};

	inline
	Message::Message() :
		isValid(false)
	{
	}

	inline void
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

#endif /* !IRC_MESSAGE_HH */
