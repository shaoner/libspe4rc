/*!
 * \file user-event.cc
 * \author shaoner
 * \brief User IRC event
 */

#include <user-event.hh>

namespace com
{

	UserEvent::UserEvent() :
		_target("")
	{
	}

	void
	UserEvent::fill_in(Message& message)
	{
		_nick = message.nick;
		_user = message.user;
		_host = message.host;
		if (message.params.size() > 0)
			_target = message.params.takeFirst();
		else
			_target = "";
		_args = message.params;
	}

	const QString&
	UserEvent::target() const
	{
		return _target;
	}

} // namespace com
