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
		int size = count();
		int left = 0;
		int right = size - 1;
		int mid = 0;
		// The user is inserted in an alpha sorted list
		while (right >= left)
		{
			// We reduce the left and the right marker
			// until we find the right place to insert the user
			mid = (left + right) / 2;
			User* curUser = at(mid);
			if (user->nick().compare(curUser->nick(), Qt::CaseInsensitive) > 0)
				left = mid + 1;
			else
				right = mid - 1;
		}
		if (left > right)
			insert(left, user);
		else
			insert(right, user);
	}

	void
	UserList::add(const QString& nick)
	{
		User* user = new User(nick);
		add(user);
		// When the user's nickname changes,
		// we need to re-insert it at the right position
		connect(user, SIGNAL(onChangeNick(User*, const QString&)),
				this, SLOT(on_change_nick(User*, const QString&)));
	}

	void
	UserList::remove(const QString& nick)
	{
		int idx = index_of(nick);
		if (idx > -1)
			delete takeAt(idx);
	}

	void
	UserList::clear()
	{
		while (count() > 0)
			delete takeFirst();
	}

	int
	UserList::index_of(const QString& nick)
	{
		int ret = -1;
		int size = count();
		int left = 0;
		int right = size - 1;
		// Simple dichotomic search
		while (right >= left)
		{
			int mid = (left + right) / 2;
			User* curUser = at(mid);
			if (nick == curUser->nick())
				return mid;
			if (nick.compare(curUser->nick(), Qt::CaseInsensitive) > 0)
				left = mid + 1;
			else
				right = mid - 1;
		}
		return ret;
	}

	User*
	UserList::get(const QString& nick)
	{
		int idx = index_of(nick);
		if (idx < 0)
			return NULL;
		return at(idx);
	}

	void
	UserList::on_change_nick(User* user, const QString& nick)
	{
		// The user's nickname has changed
		int idx = index_of(user->nick());
		if (idx > -1)
		{
			// We remove it and re-insert it
			removeAt(idx);
			user->set_nick(nick);
			add(user);
		}
	}

} // namespace com
