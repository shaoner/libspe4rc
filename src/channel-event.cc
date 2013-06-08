/*!
 * \file channel-event.cc
 * \author shaoner
 * \brief Channel IRC event
 */

#include <channel-event.hh>

namespace com
{

	ChannelEvent::ChannelEvent() :
		_nick(""),
		_user(""),
		_host(""),
		_channel(""),
		_arg("")
	{
	}

	void
	ChannelEvent::fill_in(Message& message)
	{
		 _nick = message.nick;
		 _user = message.user;
		 _host = message.host;

		if (message.params.size() > 0)
		{
			_channel = message.params[0];
			if (message.params.size() > 1)
				_arg = message.params[1];
			else
				_arg = "";
		}
		else
			_channel = "";
	}

	const QString&
	ChannelEvent::nick() const
	{
		return _nick;
	}

	const QString&
	ChannelEvent::user() const
	{
		return _user;
	}

	const QString&
	ChannelEvent::host() const
	{
		return _host;
	}

	const QString&
	ChannelEvent::channel() const
	{
		return _channel;
	}

	const QString&
	ChannelEvent::arg() const
	{
		return _arg;
	}

} // namespace com
