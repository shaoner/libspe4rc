/*!
 * \file server-event.cc
 * \author shaoner
 * \brief Server IRC event
 */

#include <server-event.hh>

namespace com
{

	void
	ServerEvent::fill_in(Message& message)
	{
		_nick = message.nick;
		_user = message.user;
		_host = message.host;
		if (message.params.size() > 0)
			_response = message.params[0];
		else
			_response = "";
		_args = message.params;
	}

	void
	ServerEvent::fill_in(const QString& response)
	{
		_response = response;
	}

	const QString&
	ServerEvent::response() const
	{
		return _response;
	}

} // namespace com
