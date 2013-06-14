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

		while (right >= left)
		{
			mid = (left + right) / 2;
			User* curUser = at(mid);
			if (*user < *curUser)
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
		add(new User(nick));
	}

	void
	UserList::remove(const QString& nick)
	{
		int idx = indexOf(nick);
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
	UserList::indexOf(const QString& nick)
	{
		int ret = -1;
		int size = count();
		int left = 0;
		int right = size - 1;

		while (right > left)
		{
			int mid = (left + right) / 2;
			User* curUser = at(mid);
			if (nick == curUser->nick())
				return mid;
			if (nick < curUser->nick())
				right = mid - 1;
			else
				left = mid + 1;
		}
		return ret;
	}

	User*
	UserList::get(const QString& nick)
	{
		int idx = indexOf(nick);

		if (idx < 0)
			return NULL;
		return at(idx);
	}

} // namespace com
