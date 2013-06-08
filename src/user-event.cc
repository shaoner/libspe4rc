/*!
 * \file user-event.cc
 * \author shaoner
 * \brief User IRC event
 */

#include <user-event.hh>

namespace com
{

	UserEvent::UserEvent() :
		_nick(""),
		_user(""),
		_host(""),
		_target(""),
		_arg("")
	{
	}

	void
	UserEvent::fill_in(Message& message)
	{
		_nick = message.nick;
		_user = message.user;
		_host = message.host;
		if (message.params.size() > 0)
		{
			_target = message.params[0];
			if (message.params.size() > 1)
				_arg = message.params[1];
			else
				_arg = "";
		}
		else
			_target = "";
	}

	const QString&
	UserEvent::nick() const
	{
		return _nick;
	}

	const QString&
	UserEvent::user() const
	{
		return _user;
	}

	const QString&
	UserEvent::host() const
	{
		return _host;
	}

	const QString&
	UserEvent::target() const
	{
		return _target;
	}

	const QString&
	UserEvent::arg() const
	{
		return _arg;
	}

} // namespace com
