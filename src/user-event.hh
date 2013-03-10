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
    /// Fill UserEvent field with an IRC message
    void                fill_in(Message& message);
  protected:
    /// Get sender's attributes
    const QString&      senderNick() const;
    const QString&      senderUser() const;
    const QString&      senderHost() const;
    /// Get target
    const QString&      target() const;
    /// Get text message
    const QString&      message() const;
  private:
    QString             _senderNick;
    QString             _senderUser;
    QString             _senderHost;
    QString             _target;
    QString             _message;
  };

} // namespace com

#endif /* !COM_USER_EVENT_HH */
