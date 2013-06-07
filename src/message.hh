/*!
 * \file message.hh
 * \author shaoner
 * \brief IRC Message
 */

#ifndef COM_MESSAGE_HH
# define COM_MESSAGE_HH

# include <QtCore>

namespace com
{

	/*!
	 * \class Message
	 * \brief This class represents an irc message
	 */
	class Message
	{
	public:
		/// Ctor
		Message();
	public:
		/// \enum CommandType
		enum CommandType
		{
			MSG_RAWNUM,
			MSG_CMDNAME
		};
		/// Clear the message
		void clear();
		/// Set the message validity according to the RFC1459
		void setValid(bool valid);
		/// Get the message validy
		bool isValid();
	public:
		/// Destination name
		QString nick;
		/// User ident
		QString user;
		/// User host
		QString host;
		/// Message type, which can be a raw or command
		CommandType commandType;
		/// Name of the command
		QString commandName;
		/// Facultative additional parameters
		QStringList params;
		/// Raw number
		quint16 rawNumber;
	private:
		bool _valid;
	};

} // namespace com

#endif /* !COM_MESSAGE_HH */
