/*!
 * \file parser.cc
 * \author shaoner
 * \brief Parser for IRC message
 */

#include <parser.hh>

namespace irc
{
	Parser::Parser()
	{
	}

	void
	Parser::parse(const QByteArray& line, Message* message)
	{
		Status err;
		// clear();
		_line = line;
		_message = message;
		err = parse_message();
		_message->setValid(err == STS_NO_ERROR);
	}

	void
	Parser::inc(int x)
	{
		_line = _line.mid(x);
	}

	Parser::Status
	Parser::expected_tok(QString& key, Token token)
	{
		int i = _line.indexOf(token);
		if (i == -1)
		{
			return STS_SYNTAX;
		}
		key = _line.left(i);
		inc(i + 1);
		return STS_NO_ERROR;
	}

	Parser::Status
	Parser::parse_message()
	{
		if (_line.startsWith(TOK_COLON))
		{
			inc(1);
			CHECK_RULE(parse_prefix());
			space();
		}
		CHECK_RULE(parse_command());
		CHECK_RULE(parse_params());
		return STS_NO_ERROR;
	}

	Parser::Status
	Parser::parse_prefix()
	{
		int i = 0;
		QString qPrefix;

		CHECK_RULE(expected_tok(qPrefix, TOK_SPACE));
		// Get nickname or the servername and user
		if ((i = qPrefix.indexOf(TOK_EXCLAMATION_MARK)) != -1)
		{
			_message->nick = qPrefix.left(i);
			qPrefix = qPrefix.mid(i);
			// Get user and host
			if ((i = qPrefix.indexOf(TOK_AT)) != -1)
			{
				_message->user = qPrefix.mid(1, i - 1);
				qPrefix = qPrefix.mid(i);
				i = qPrefix.indexOf(TOK_SPACE);
				_message->host = qPrefix.mid(1, i - 1);
			}
			else // Get user
			{
				i = qPrefix.indexOf(TOK_SPACE);
				_message->user = qPrefix.left(i);
			}
		}
		// Get nickname or servername and host
		else if ((i = qPrefix.indexOf(TOK_AT)) != -1)
		{
			_message->nick = qPrefix.mid(1, i - 1);
			qPrefix = qPrefix.mid(i);
			i = qPrefix.indexOf(TOK_SPACE);
			_message->host = qPrefix.mid(1, i - 1);
		}
		else // Get nickname or servername
		{
			_message->nick = qPrefix;
		}
		return STS_NO_ERROR;
	}

	void
	Parser::space()
	{
		int i = 0;

		while(_line[i++] == (char)TOK_SPACE);
		if (i > 1)
			inc(i - 1);
	}

	Parser::Status
	Parser::parse_command()
	{
		// Raw number
		if (_line[0] >= '0' && _line[0] <= '9')
		{
			_message->rawNumber = _line.left(3).toInt();
			if (!_message->rawNumber)
				return STS_SYNTAX;
			_message->commandType = Message::MSG_RAWNUM;
			inc(3);
		}
		else // Command
		{
			CHECK_RULE(expected_tok(_message->commandName, TOK_SPACE));
			_message->commandType = Message::MSG_CMDNAME;
		}
		return STS_NO_ERROR;
	}

	Parser::Status
	Parser::parse_params()
	{
		QByteArray param;
		int i;

		space();
		while (!_line.isEmpty())
		{
			if (_line.startsWith(TOK_COLON))
			{
				inc(1);
			}
			else if ((i = _line.indexOf(TOK_SPACE)) != -1)
			{
				_message->params += _line.left(i);
				inc(i + 1);
				continue;
			}
			_message->params += _line.trimmed();
			_line.clear();
		}
		return STS_NO_ERROR;
	}

} // namespace irc
