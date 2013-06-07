/*!
 * \file event-processor.hh
 * \author shaoner
 * \brief Process an IRC message
 */

#ifndef COM_EVENT_PROCESSOR_HH
# define COM_EVENT_PROCESSOR_HH

# include <QList>
# include <QHash>

# include <all-events.hh>
# include <message.hh>
# include <protocol.hh>

namespace com
{
	/*!
	 * \class EventProcessor
	 * \brief This class process and dispatch IRC messages
	 * to the according event handler
	 */
	class EventProcessor
	{
	public:
		/// Ctor
		EventProcessor(Protocol* proto);
		/// Dtor
		~EventProcessor();
	public:
		/// Process an IRC message
		void process(Message& message);
		/// Add an event listener for the target type
		void add_notifier(EventName type, Event* notifier);
		/// Remove the first event listener notifier
		/// for the target type which is found
		void remove_notifier(EventName type, Event* notifier);
		/// Set a default event listener
		/// called only if all listeners returned true
		void set_default_notifier(EventName type, Event* notifier);
		/// Reset the default event listener matching type
		void reset_default_notifier(EventName type);
	private:
		QList<Event*>* _eventMap;
		QHash<QString, EventName> _commandMap;
		Event* _defaultEventMap[N_EVENTS];
		Protocol* _proto;
	};

} // namespace com

#endif /* !COM_EVENT_PROCESSOR_HH */
