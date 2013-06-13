#include <user.hh>

namespace com
{

	User::User(const QString& fullnick) :
		_fullnick(fullnick),
		_nick(fullnick),
		_roles(ROLE_NORMAL)
	{
		char prefix = fullnick[0].toAscii();
		if ((prefix == '@') || (prefix == '%') || (prefix == '+'))
		{
			_roles = char_to_role(prefix);
			_nick.remove(0, 1);
		}
	}

	UserRole
	User::char_to_role(char c)
	{
		switch (c)
		{
		case 0:
			return ROLE_NORMAL;
		case '@':
			return ROLE_OP;
		case '%':
			return ROLE_HALFOP;
		case '+':
			return ROLE_VOICE;
		}
		return ROLE_OTHER;
	}

	const QString&
	User::fullnick() const
	{
		return _fullnick;
	}

	const QString&
	User::nick() const
	{
		return _nick;
	}

	UserRole
	User::roles() const
	{
		return _roles;
	}

	void
	User::add_role(UserRole role)
	{
		_roles = (UserRole)(_roles | role);
	}

	bool
	User::is_op()
	{
		return (_roles & ROLE_OP) == ROLE_OP;
	}

	bool
	User::is_halfop()
	{
		return (_roles & ROLE_HALFOP) == ROLE_HALFOP;
	}

	bool
	User::is_voice()
	{
		return (_roles & ROLE_VOICE) == ROLE_VOICE;
	}

	bool
	operator==(User& user1, User& user2)
	{
		return !QString::compare(user1.nick(), user2.nick(), Qt::CaseInsensitive);
	}

	bool
	operator<(User& user1, User& user2)
	{
		if (user1.roles() == user2.roles())
			return QString::compare(user1.nick(), user2.nick(), Qt::CaseInsensitive) > 0;
		return user1.roles() < user2.roles();
	}

} // namespace com
