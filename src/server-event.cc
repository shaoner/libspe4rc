/*!
 * \file server-event.cc
 * \author shaoner
 * \brief Server IRC event
 */

#include <server-event.hh>

namespace com
{

  void
  ServerEvent::fill_in(Message& message)
  {
    _response = message.params[0];
  }

  const QString&
  ServerEvent::response() const
  {
    return _response;
  }

} // namespace com
