/*
 *
 * Copyright 2013, Alexandre LAURENT <shaoner>
 *
 * This file is part of Libspe4rc.
 *
 * Libspe4rc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Libspe4rc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Libspe4rc. If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*!
 * \file parser.hh
 * \author shaoner
 * \brief Parser for IRC message
 */

#ifndef IRC_PARSER_HH
# define IRC_PARSER_HH

# include <QString>

/*!
 *
 * From RFC 1439
 *
 ***********************************************************************
 * BNF representation
 *
 * <message> ::= [':' <prefix> <SPACE> ] <command> <params> <crlf>
 * <prefix> ::= <servername> | <nick> [ '!' <user> ] [ '@' <host> ]
 * <command> ::= <letter> { <letter> } | <number> <number> <number>
 * <SPACE> ::= ' ' { ' ' }
 * <params> ::= <SPACE> [ ':' <trailing> | <middle> <params> ]
 * <middle> ::= <Any *non-empty* sequence of octets not including SPACE
 * or NUL or CR or LF, the first of which may not be ':'>
 * <trailing> ::= <Any, possibly *empty*, sequence of octets not including
 * NUL or CR or LF>
 * <crlf> ::= CR LF
 ***********************************************************************
 */

# define CHECK_RULE(R) \
	do \
	{ \
		if ((R) != STS_NO_ERROR) \
		{ \
			return STS_SYNTAX; \
		} \
	} while (0)

namespace irc
{

	class Message;

	/*!
	 * \class Parser
	 * \brief This class is a SLR parser for the IRC grammar
	 */
	class Parser
	{
	public:
		/// Ctor
		Parser();
	public:
		/// \enum Token
		enum Token
		{
			TOK_COLON = ':',
			TOK_EXCLAMATION_MARK = '!',
			TOK_AT = '@',
			TOK_SPACE = ' '
		};
	public:
		/// Parser entry point
		void parse(const QByteArray& line, Message* message);
	private:
		/// \enum Status
		enum Status
		{
			STS_NO_ERROR,
			STS_SYNTAX
		};
		/// Increment the line pointer
		void inc(int x);
		/// Set the key from current pos until token
		Status expected_tok(QString& key, Token token);
		/// Truncate space
		void space();
		/// <message> ::= [':' <prefix> <SPACE> ] <command> <params> <crlf>
		Status parse_message();
		/// <prefix> ::= <servername> | <nick> [ '!' <user> ] [ '@' <host> ]
		Status parse_prefix();
		/// <command> ::= <letter> { <letter> } | <number> <number> <number>
		Status parse_command();
		/// <params> ::= <SPACE> [ ':' <trailing> | <middle> <params> ]
		Status parse_params();
	private:
		QString _line;
		Message* _message;
	};

} // namespace irc

#endif /* !IRC_PARSER_HH */
