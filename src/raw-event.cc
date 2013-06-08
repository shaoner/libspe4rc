/*!
 * \file raw-event.cc
 * \author shaoner
 * \brief Raw IRC event
 */

#include <raw-event.hh>

namespace com
{

	void
	RawEvent::fill_in(Message& message)
	{
		_raw = message.rawNumber;
		_target = message.params.takeFirst();
		_rawmsg = message.params.join(" ");
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
	RawEvent::rawmsg() const
	{
		return _rawmsg;
	}

} // namespace com
