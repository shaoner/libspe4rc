#include <user-list.hh>

namespace com
{

	UserList::UserList()
	{
	}

	UserList::~UserList()
	{
		clear();
	}

	void
	UserList::add(User* user)
	{
		insert(user->nick(), user);
	}

	void
	UserList::add(const QString& nick)
	{
		User* user = new User(nick);
		insert(nick, user);
	}

	void
	UserList::remove(const QString& nick)
	{
		if (contains(nick))
			delete take(nick);
	}

	void
	UserList::clear()
	{
		QList<User*> uList = values();
		foreach (User* user, uList)
		{
			delete user;
		}
		QHash<QString, User*>::clear();
	}

	User*
	UserList::get(const QString& nick)
	{
		return value(nick, NULL);
	}

} // namespace com
