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
		_target = message.params[0];
		message.params.pop_front();
		_params = message.params;
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

	const QStringList&
	RawEvent::params() const
	{
		return _params;
	}

} // namespace com
