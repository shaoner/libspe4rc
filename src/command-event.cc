#include <command-event.hh>

namespace com
{
	const QString&
	CommandEvent::nick() const
	{
		return _nick;
	}

	const QString&
	CommandEvent::user() const
	{
		return _user;
	}

	const QString&
	CommandEvent::host() const
	{
		return _host;
	}

	const QStringList&
	CommandEvent::args() const
	{
		return _args;
	}

} // namespace com
