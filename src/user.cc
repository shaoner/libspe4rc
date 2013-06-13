#include <user.hh>

namespace com
{

	User::User(const QString& nick, const QString& prefix) :
		_nick(nick),
		_lowerNick(nick.toLower()),
		_prefix(prefix)
	{
	}

	User::User(const QString& nick, QChar prefix) :
		_nick(nick),
		_lowerNick(nick.toLower()),
		_prefix(prefix)
	{
	}


	User*
	User::create(const QString& fullname)
	{
		QChar first = fullname[0];
		if (first == '@' || first == '%' || first == '+')
			return new User(QString(fullname).remove(0, 1), first);
		return (new User(fullname));
	}

	const QString&
	User::nick() const
	{
		return _nick;
	}

	const QString&
	User::prefix() const
	{
		return _prefix;
	}

	bool
	User::is_op()
	{
		return _prefix.contains('@');
	}

	bool
	User::is_halfop()
	{
		return _prefix.contains('%');
	}

	bool
	User::is_voice()
	{
		return _prefix.contains('+');
	}

	bool
	User::operator==(User* user) const
	{
		return _lowerNick == user->nick().toLower();
	}

	bool
	User::operator<(User* user) const
	{
		if (_prefix == user->prefix())
			return _lowerNick < user->nick().toLower();
		return _prefix < user->prefix();
	}

} // namespace com
