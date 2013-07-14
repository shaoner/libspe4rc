#include <role.hh>

namespace irc
{

	Role* Role::_instance = NULL;

	Role*
	Role::get()
	{
		if (!_instance)
			_instance = new Role();
		return _instance;
	}

	void
	Role::reset()
	{
		delete _instance;
		_instance = NULL;
	}

	char
	Role::to_prefix(quint8 role)
	{
		return _supportedRoles.key(role, 0);
	}

	quint8
	Role::from_prefix(char prefix)
	{
		return _supportedRoles.value(prefix, 0);
	}

	char
	Role::from_mode(char mode)
	{
		return _supportedPrefixes.value(mode, 0);
	}

	void
	Role::add(char mode, char prefix, quint8 level)
	{
		_supportedPrefixes.insert(mode, prefix);
		_supportedRoles.insert(prefix, level);
	}

	Role::Role()
	{
		// Set tradional modes by default
		// It will be replaced during event RPL_BOUNCE
		_supportedPrefixes['v'] = '+';
		_supportedRoles['+'] = 1;
		_supportedPrefixes['h'] = '%';
		_supportedRoles['%'] = 2;
		_supportedPrefixes['o'] = '@';
		_supportedRoles['@'] = 4;
	}

} // namespace irc
