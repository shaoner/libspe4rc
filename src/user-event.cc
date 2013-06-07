/*!
 * \file user-event.cc
 * \author shaoner
 * \brief User IRC event
 */

#include <user-event.hh>

namespace com
{

	void
	UserEvent::fill_in(Message& ircmessage)
	{
		_senderNick = ircmessage.nick;
		_senderUser = ircmessage.user;
		_senderHost = ircmessage.host;
		if (ircmessage.params.size() > 0)
		{
			_target = ircmessage.params[0];
			if (ircmessage.params.size() > 1)
				_message = ircmessage.params[1];
		}
	}

	const QString&
	UserEvent::senderNick() const
	{
		return _senderNick;
	}

	const QString&
	UserEvent::senderUser() const
	{
		return _senderUser;
	}

	const QString&
	UserEvent::senderHost() const
	{
		return _senderHost;
	}

	const QString&
	UserEvent::target() const
	{
		return _target;
	}

	const QString&
	UserEvent::message() const
	{
		return _message;
	}

} // namespace com
