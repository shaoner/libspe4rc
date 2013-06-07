/*!
 * \file event.cc
 * \author shaoner
 * \brief IRC event interface
 */

#include <event.hh>

namespace com
{

	void
	Event::session(Session* session)
	{
		_session = session;
	}

	const Session&
	Event::session() const
	{
		return *_session;
	}

	Session&
	Event::session()
	{
		return *_session;
	}

} // namespace com
