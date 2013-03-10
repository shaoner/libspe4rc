/*!
 * \file event-processor.cc
 * \author shaoner
 * \brief Process an IRC message
 */

#include <event-processor.hh>

namespace com
{

  EventProcessor::EventProcessor(Protocol* proto) :
    _proto(proto)
  {
    // Clean up notifier lists
    _eventMap = new QList<Event*>[N_EVENTS];

    for (int i = 0; i < N_EVENTS; ++i)
    {
      _defaultEventMap[i] = 0;
    }
    _commandMap.insert("NOTICE", ON_NOTICE);
    _commandMap.insert("MODE", ON_MODE);
    _commandMap.insert("NICK", ON_NICK);
    _commandMap.insert("PRIVMSG", ON_PRIVMSG);
    _commandMap.insert("PING", ON_PING);
    _commandMap.insert("JOIN", ON_JOIN);
  }

  EventProcessor::~EventProcessor()
  {
    delete _eventMap;
  }

  void
  EventProcessor::process(Message& message)
  {
    bool isDefaultProcessed = true;
    EventName eType;
    QList<Event*> eventList;
    Event* event = 0;

    if (message.commandType == Message::MSG_CMDNAME)
    {
      // Ignore unknown commands
      if (!_commandMap.contains(message.commandName))
      {
        qDebug("Unknown command");
        qDebug() << message.commandName;
        return;
      }
      // Handle mandatory events
      if (message.commandName == "PING")
        _proto->write("PONG " + message.params[0]);

      // Get the event list object callbacks
      eType = _commandMap[message.commandName];

    }
    else // message.commandType == Message::MSG_RAWNUM
    {
      eType = ON_RAW;
    }

    eventList = _eventMap[eType];
    // Call each event callback
    for (QList<Event*>::iterator it = eventList.begin();
         it != eventList.end();
         ++it)
    {
      event = *it;
      if (event)
      {
        event->fill_in(message);
        isDefaultProcessed = isDefaultProcessed && event->notify();
      }
    }
    // Default event
    if (isDefaultProcessed)
    {
      event = _defaultEventMap[eType];
      if (event)
      {
          event->fill_in(message);
          event->notify();
      }
    }
  }

  void
  EventProcessor::add_notifier(EventName type, Event* notifier)
  {
    _eventMap[type] << notifier;
  }

  void
  EventProcessor::remove_notifier(EventName type, Event* notifier)
  {
    _eventMap[type].removeOne(notifier);
  }

  void
  EventProcessor::set_default_notifier(EventName type, Event* notifier)
  {
    _defaultEventMap[type] = notifier;
  }

  void
  EventProcessor::reset_default_notifier(EventName type)
  {
    _defaultEventMap[type] = 0;
  }

} // namespace com
