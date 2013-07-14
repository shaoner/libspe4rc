/*!
 * \file raw-event.cc
 * \author shaoner
 * \brief Raw IRC event
 */

#include <raw-event.hh>

namespace irc
{

	RawEvent::RawEvent(Message& message, Client* client) :
		Event(client),
		_raw(message.rawNumber),
		_target(message.params[0])
	{
		message.params.takeFirst();
		_msg = message.params.join(" ");
	}

	quint16
	RawEvent::raw() const
	{
		return _raw;
	}

	const QString&
	RawEvent::target() const
	{
		return _target;
	}

	const QString&
	RawEvent::msg() const
	{
		return _msg;
	}

} // namespace irc
