/*!
 * \file event.cc
 * \author shaoner
 * \brief IRC event interface
 */

#include <event.hh>

namespace irc
{
	Event::Event(Client* client) :
		_client(client)
	{
	}

	Event::~Event()
	{
	}

	const Client&
	Event::client() const
	{
		return *_client;
	}

	Client&
	Event::client()
	{
		return *_client;
	}

} // namespace irc
