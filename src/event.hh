/*!
 * \file event.hh
 * \author shaoner
 * \brief IRC event interface
 */

#ifndef COM_EVENT_HH
# define COM_EVENT_HH

# include <message.hh>

namespace com
{

/// Define the number of event listener's types
# define N_EVENTS 11

	class Client;

	/*!
	 * \class Event
	 * \brief This class is an interface representing an irc message as an event
	 */
	class Event
	{
	public:
		virtual ~Event();
	public:
		/// Describes how to fill an event from an irc message
		virtual void fill_in(Message& message) = 0;
		/// Set the associated session to have access in the notifier
		void set_client(Client* Client);
	protected:
		/// Get associated irc client session
		const Client& client() const;
		Client& client();
	private:
		Client* _client;
	};

} // namespace com

#endif /* !COM_EVENT_HH */
