/*!
 * \file server-event.hh
 * \author shaoner
 * \brief Server IRC event
 */

#ifndef COM_SERVER_EVENT_HH
# define COM_SERVER_EVENT_HH

# include <command-event.hh>

namespace com
{
	/*!
	 * \class ServerEvent
	 * \brief This class represents an irc message as a channel event
	 */
	class ServerEvent : public CommandEvent
	{
	public:
		/// Fill ServerEvent field with an irc message
		void fill_in(Message& m);
		void fill_in(const QString& response);
	public:
		/// Get server response
		const QString& response() const;
	private:
		QString _response;
	};

} // namespace com

#endif /* !COM_SERVER_EVENT_HH */
