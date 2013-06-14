#ifndef COM_USERLIST_HH
# define COM_USERLIST_HH

# include <QList>
# include <QDebug>

# include <user.hh>

namespace com
{

	class UserList : public QList<User*>
	{
	public:
		explicit UserList();
		~UserList();
	public:
		void add(User* user);
		void add(const QString& nick);
		void remove(const QString& nick);
		void clear();
		int indexOf(const QString& nick);
		User* get(const QString& nick);
	};

} // namespace com

#endif /* !COM_USERLIST_HH */
