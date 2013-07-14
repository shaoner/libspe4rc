#include <command-event.hh>

namespace irc
{
	CommandEvent::CommandEvent(Message& message, Client* client) :
		Event(client),
		_nick(message.nick),
		_user(message.user),
		_host(message.host)
	{
	}

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

} // namespace irc
