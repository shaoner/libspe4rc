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
		/// Get client info
		const QString& nick() const;
		const QString& user() const;
		const QString& host() const;
		const QStringList& args() const;
	protected:
		QString _nick;
		QString _user;
		QString _host;
		QStringList _args;
	};

} // namespace com

#endif /* !COM_COMMAND_EVENT_HH */
