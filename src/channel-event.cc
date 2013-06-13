/*!
 * \file channel-event.cc
 * \author shaoner
 * \brief Channel IRC event
 */

#include <channel-event.hh>

namespace com
{

	ChannelEvent::ChannelEvent() :
		_channel("")
	{
	}

	void
	ChannelEvent::fill_in(Message& message)
	{
		 _nick = message.nick;
		 _user = message.user;
		 _host = message.host;

		if (message.params.size() > 0)
			_channel = message.params.takeFirst();
		else
			_channel = "";
		_args = message.params;
	}

	const QString&
	ChannelEvent::channel() const
	{
		return _channel;
	}

} // namespace com
