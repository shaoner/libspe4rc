/*!
 * \file raw-event.hh
 * \author shaoner
 * \brief Raw IRC event
 */

#ifndef COM_RAW_EVENT_HH
# define COM_RAW_EVENT_HH

# include <QStringList>
# include <QString>

# include <event.hh>

namespace com
{
  /*!
   * \class RawEvent
   * \brief This class represents an irc message as a raw event
   */
  class RawEvent : public Event
  {
  public:
    /// Fill RawEvent field with an irc message
    void                fill_in(Message& message);
  protected:
    /// Get the raw number
    quint16             raw() const;
    /// Get the target, usually this is the client's nickname
    const QString&      target() const;
    /// Get facultative parameters
    const QStringList&  params() const;
  private:
    quint16             _raw;
    QString             _target;
    QStringList         _params;
  };

} // namespace com

#endif /* !COM_RAW_EVENT_HH */
