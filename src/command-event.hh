/*!
 * \file command-event.hh
 * \author shaoner
 * \brief IRC event command
 */

#ifndef COM_COMMAND_EVENT_HH
# define COM_COMMAND_EVENT_HH

# include <event.hh>

namespace com
{
	/*!
	 * \class CommandEvent
	 * \brief This class represents an irc message as a command event
	 */
	class CommandEvent : public Event
	{
	public:
		/// Ctor
		CommandEvent(Message& message, Client* session);
	public:
		/// Get client info
		const QString& nick() const;
		const QString& user() const;
		const QString& host() const;
	protected:
		const QString& _nick;
		const QString& _user;
		const QString& _host;
	};

} // namespace com

#endif /* !COM_COMMAND_EVENT_HH */
