/*!
 * \file event.cc
 * \author shaoner
 * \brief IRC event interface
 */

#include <event.hh>

namespace com
{

	Event::~Event()
	{
	}


	void
	Event::set_client(Client* client)
	{
		_client = client;
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

} // namespace com
