#ifndef COM_USERLIST_HH
# define COM_USERLIST_HH

# include <QList>
# include <QDebug>

# include <user.hh>

namespace com
{

	class UserList : public QObject, public QList<User*>
	{

		Q_OBJECT

	public:
		explicit UserList();
		~UserList();
	public:
		void add(User* user);
		void add(const QString& nick);
		void remove(const QString& nick);
		void clear();
		int index_of(const QString& nick);
		User* get(const QString& nick);
	private slots:
		void on_change_nick(User* user, const QString& newNick);
	};

} // namespace com

#endif /* !COM_USERLIST_HH */
