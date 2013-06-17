/*!
 * \file user-list.hh
 * \author shaoner
 * \brief Channel userlist
 */

#ifndef COM_USERLIST_HH
# define COM_USERLIST_HH

# include <QList>
# include <QDebug>

# include <user.hh>

namespace com
{

	/*!
	 * \class UserList
	 * \brief This class is used to retrieve a userlist by channel
	 */
	class UserList : public QObject, public QList<User*>
	{

		Q_OBJECT

	public:
		/// Ctor
		explicit UserList();
		/// Dtor
		~UserList();
	public:
		/// Add an IRC user
		void add(User* user);
		void add(const QString& nick);
		/// Remove an IRC user
		void remove(const QString& nick);
		/// Remove all
		void clear();
		/// Find an IRC user, which is pretty fast
		/// using a dichotomic search
		int index_of(const QString& nick);
		User* get(const QString& nick);
	private slots:
		void on_change_nick(User* user, const QString& newNick);
	};

} // namespace com

#endif /* !COM_USERLIST_HH */
