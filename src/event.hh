/*!
 * \file event.hh
 * \author shaoner
 * \brief IRC event interface
 */

#ifndef COM_EVENT_HH
# define COM_EVENT_HH

namespace irc
{

	class Client;

	/*!
	 * \class Event
	 * \brief This class is an interface representing an irc message as an event
	 */
	class Event
	{
	public:
		/// Ctor
		Event(Client* client) :
			_client(client)
		{
		}
	protected:
		/// Get associated irc client session
		const Client& client() const { return *_client; }
	private:
		Client* _client;
	};

} // namespace irc

#endif /* !COM_EVENT_HH */
