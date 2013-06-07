/*!
 * \file channel-event.cc
 * \author shaoner
 * \brief Channel IRC event
 */

#include <channel-event.hh>

namespace com
{

	void
	ChannelEvent::fill_in(Message& message)
	{
		_channel = message.params[0];
	}

	const QString&
	ChannelEvent::channel() const
	{
		return _channel;
	}

} // namespace com
