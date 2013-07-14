/*!
 * \file message.cc
 * \author shaoner
 * \brief IRC Message
 */

#include <message.hh>

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
