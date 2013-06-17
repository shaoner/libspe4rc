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
		/// Ctor
		Event(Client* client);
		/// Dtor
		virtual ~Event();
	protected:
		/// Get associated irc client session
		const Client& client() const;
		Client& client();
	private:
		Client* _client;
	};

} // namespace com

#endif /* !COM_EVENT_HH */
