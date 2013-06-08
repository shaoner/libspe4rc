/*!
 * \file user-event.hh
 * \author shaoner
 * \brief User IRC event
 */

#ifndef COM_USER_EVENT_HH
# define COM_USER_EVENT_HH

# include <event.hh>

namespace com
{

	/*!
	 * \class UserEvent
	 * \brief This class represents an irc message as a user event
	 */
	class UserEvent : public Event
	{
	public:
		/// Ctor
		UserEvent();
	public:
		/// Fill UserEvent field with an IRC message
		void fill_in(Message& message);
		/// Get sender's attributes
		const QString& nick() const;
		const QString& user() const;
		const QString& host() const;
		/// Get target
		const QString& target() const;
		/// Get text message
		const QString& arg() const;
	private:
		QString _nick;
		QString _user;
		QString _host;
		QString _target;
		QString _arg;
	};

} // namespace com

#endif /* !COM_USER_EVENT_HH */
