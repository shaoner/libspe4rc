/*!
 * \file user.hh
 * \author shaoner
 * \brief IRC user
 */

#ifndef COM_USER_HH
# define COM_USER_HH

# include <QString>
# include <QDebug>

# include <role.hh>

namespace irc
{

	class UserList;

	/*!
	 * \class User
	 * \brief This class represents an IRC user in a channel
	 */
    class User : public QObject
	{
		Q_OBJECT

		friend UserList;
	public:
		/// Dtor
		~User();
	public:
		/// user attributes
		const QString& fullnick() const;
		const QString& nick() const;
		quint8 roles() const;
		/// Change user attributes
		void change_nick(const QString& nick);
		void add_prefix(char prefix);
		void del_prefix(char prefix);
		/// Check tradional roles
		bool is_op() const;
		bool is_halfop() const;
		bool is_voice() const;
	public:
		/// Comparing users
		friend bool operator==(User& user1, User& user2);
		friend bool operator<(User& user1, User& user2);
	signals:
		void onChangeFullNick(const QString&);
	private:
		/// Ctor
		User(const QString& fullnick);
	private:
		void set_nick(const QString& nick);
	private:
		QString _fullnick;
		QString _nick;
		char _prefix;
		quint8 _roles;
	};

} // namespace irc

#endif /* !COM_USER_HH */
