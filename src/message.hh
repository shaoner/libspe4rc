/*!
 * \file message.hh
 * \author shaoner
 * \brief IRC Message
 */

#ifndef COM_MESSAGE_HH
# define COM_MESSAGE_HH

# include <QtCore>

namespace irc
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
	public:
		/// Get the message validy
		bool isValid;
		/// Sender info
		QString nick;
		QString user;
		QString host;
		/// Message type, which can be a raw or command
		CommandType commandType;
		/// Name of the command
		QString commandName;
		/// Facultative additional parameters
		QStringList params;
		/// Raw number
		quint16 rawNumber;
	};

} // namespace irc

#endif /* !COM_MESSAGE_HH */
