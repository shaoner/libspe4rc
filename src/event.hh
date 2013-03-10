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

  /// Event listener's types
  enum                  EventName
  {
                        ON_NOTICE,
                        ON_MODE,
                        ON_NICK,
                        ON_PRIVMSG,
                        ON_CHANMSG,
                        ON_CONNECT,
                        ON_DISCONNECT,
                        ON_KILL,
                        ON_PING,
                        ON_JOIN,
                        ON_RAW
  };

  /// Define the number of event listener's types
# define N_EVENTS       11

  class Session;

  /*!
   * \class Event
   * \brief This class is an interface representing an irc message as an event
   */
  class Event
  {
  public:
    /// Describes how to fill an event from an irc message
    virtual void        fill_in(Message& message) = 0;
    /// Set the associated session to have access in the notifier
    void                session(Session* session);
    /// Describes how to notify
    /// This has to be defined by the notifier class
    /// It acts as a callback
    virtual bool        notify() = 0;
  protected:
    /// Get associated irc session
    const Session&      session() const;
    Session&            session();
  private:
    Session*            _session;
  };

} // namespace com

#endif /* !COM_EVENT_HH */
