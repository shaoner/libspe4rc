/*!
 * \file message.cc
 * \author shaoner
 * \brief IRC Message
 */

#include <message.hh>

namespace com
{

	Message::Message() :
		_valid(false)
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

	void
	Message::setValid(bool valid)
	{
		_valid = valid;
	}

	bool
	Message::isValid()
	{
		return _valid;
	}

} // namespace com
