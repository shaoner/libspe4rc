/*!
 * \file command-event.hh
 * \author shaoner
 * \brief IRC event command
 */

#ifndef COM_COMMAND_EVENT_HH
# define COM_COMMAND_EVENT_HH

# include <event.hh>
# include <message.hh>

namespace irc
{

	/*!
	 * \class CommandEvent
	 * \brief This class represents an irc message as a command event
	 */
	class CommandEvent : public Event
	{
	public:
		/// Ctor
		CommandEvent(Message& message, Client* client) :
			Event(client),
			_nick(message.nick),
			_user(message.user),
			_host(message.host)
		 {
		 }

	public:
		/// Get client info
		const QString& nick() const { return _nick; }
		const QString& user() const { return _user; }
		const QString& host() const { return _host; }
	protected:
		const QString& _nick;
		const QString& _user;
		const QString& _host;
	};

} // namespace irc

#endif /* !COM_COMMAND_EVENT_HH */
