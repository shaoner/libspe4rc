/*!
 * \file channel-event.hh
 * \author shaoner
 * \brief Channel IRC event
 */

#ifndef COM_CHANNEL_EVENT_HH
# define COM_CHANNEL_EVENT_HH

# include <event.hh>

namespace com
{
	/*!
	 * \class ChannelEvent
	 * \brief This class represents an irc message as a channel event
	 */
	class ChannelEvent : public Event
	{
	public:
		/// Ctor
		ChannelEvent();
	public:
		/// Fill ChannelEvent field with an irc message
		void fill_in(Message& message);
		/// Get client info
		const QString& nick() const;
		const QString& user() const;
		const QString& host() const;
		/// Get channel's name
		const QString& channel() const;
		const QString& arg() const;
	private:
		QString _nick;
		QString _user;
		QString _host;
		QString _channel;
		QString _arg;
	};

} // namespace com

#endif /* !COM_CHANNEL_EVENT_HH */
