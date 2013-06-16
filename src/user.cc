#include <user.hh>

namespace com
{

	User::User(const QString& fullnick) :
		_fullnick(fullnick),
		_nick(fullnick)
	{
		_prefix = fullnick[0].toAscii();
		_roles = Role::get()->from_prefix(_prefix);
		if (_roles)
			_nick.remove(0, 1);
		else
			_prefix = 0;
	}

	void
	User::change_nick(const QString& nick)
	{
		_nick = nick;
		if (_roles)
			_fullnick = _prefix + _nick;
		else
			_fullnick = _nick;
		emit onChangeNick(this);
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

	quint8
	User::roles() const
	{
		return _roles;
	}

	void
	User::add_prefix(char prefix)
	{
		quint8 role = Role::get()->from_prefix(prefix);
  		if (role > _roles)
		{
			_prefix = prefix;
			if (_roles)
				_fullnick.replace(0, 1, _prefix);
			else
				_fullnick.prepend(_prefix);
		}
		_roles |= role;
		emit onChangeNick(this);
	}

	void
	User::del_prefix(char prefix)
	{
		quint8 delRole = Role::get()->from_prefix(prefix);
		quint8 oldRole = _roles;
		_roles -= delRole;
		if (delRole > _roles)
		{
			char newPrefix = Role::get()->to_prefix(uint8_msb(_roles));
			_prefix = newPrefix;
			if (!_prefix)
				_fullnick = _nick;
			else if (oldRole)
				_fullnick.replace(0, 1, _prefix);
			else
				_fullnick.prepend(_prefix);
		}
		emit onChangeNick(this);
	}

	bool
	User::is_op() const
	{
		static quint8 opRole = Role::get()->from_prefix('@');
		return (_roles & opRole) == opRole;
	}

	bool
	User::is_halfop() const
	{
		static quint8 halfopRole = Role::get()->from_prefix('%');
		return (_roles & halfopRole) == halfopRole;
	}

	bool
	User::is_voice() const
	{
		static quint8 voiceRole = Role::get()->from_prefix('%');
		return (_roles & voiceRole) == voiceRole;
	}

	bool
	operator==(User& user1, User& user2)
	{
		return !QString::compare(user1._nick, user2._nick, Qt::CaseInsensitive);
	}

	bool
	operator<(User& user1, User& user2)
	{
		quint8 r1 = uint8_msb(user1._roles);
		quint8 r2 = uint8_msb(user2._roles);

		if (r1 == r2)
			return QString::compare(user1._nick, user2._nick, Qt::CaseInsensitive) > 0;
		return r1 < r2;
	}

} // namespace com
