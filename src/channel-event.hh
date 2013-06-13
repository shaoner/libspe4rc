/*!
 * \file channel-event.hh
 * \author shaoner
 * \brief Channel IRC event
 */

#ifndef COM_CHANNEL_EVENT_HH
# define COM_CHANNEL_EVENT_HH

# include <command-event.hh>

namespace com
{
	/*!
	 * \class ChannelEvent
	 * \brief This class represents an irc message as a channel event
	 */
	class ChannelEvent : public CommandEvent
	{
	public:
		/// Ctor
		ChannelEvent();
	public:
		/// Fill ChannelEvent field with an irc message
		void fill_in(Message& message);
		/// Get channel's name
		const QString& channel() const;
	private:
		QString _channel;
	};

} // namespace com

#endif /* !COM_CHANNEL_EVENT_HH */
