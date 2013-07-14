/*!
 * \file user-event.hh
 * \author shaoner
 * \brief User IRC event
 */

#ifndef COM_USER_EVENT_HH
# define COM_USER_EVENT_HH

# include <command-event.hh>

namespace irc
{

	/*!
	 * \class UserEvent
	 * \brief This class represents an irc message as a user event
	 */
	class UserEvent : public CommandEvent
	{
	public:
		/// Ctor
		UserEvent();
	public:
		/// Fill UserEvent field with an IRC message
		void fill_in(Message& message);
		/// Get target
		const QString& target() const;
	private:
		QString _target;
	};

} // namespace irc

#endif /* !COM_USER_EVENT_HH */
