#ifndef COM_USER_HH
# define COM_USER_HH

# include <QString>
# include <QDebug>

# include <role.hh>

namespace com
{

	class UserList;

    class User : public QObject
	{
		Q_OBJECT
	public:
		/// Dtor
		~User();
	public:
		void change_nick(const QString& nick);
		const QString& fullnick() const;
		const QString& nick() const;
		quint8 roles() const;
		void add_prefix(char prefix);
		void del_prefix(char prefix);
		bool is_op() const;
		bool is_halfop() const;
		bool is_voice() const;
	public:
		friend bool operator==(User& user1, User& user2);
		friend bool operator<(User& user1, User& user2);
	signals:
		void onChangeNick(User*, const QString&);
		void onChangeFullNick(const QString&);
	private:
		/// Ctor
		User(const QString& fullnick);
		void set_nick(const QString& nick);
		friend UserList;
	private:
		QString _fullnick;
		QString _nick;
		char _prefix;
		quint8 _roles;
	};

} // namespace com

#endif /* !COM_USER_HH */
