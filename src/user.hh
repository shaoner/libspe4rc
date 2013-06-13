#ifndef COM_USER_HH
# define COM_USER_HH

# include <QString>
# include <QDebug>

namespace com
{

	enum UserRole
	{
		ROLE_NORMAL = 1,
		ROLE_VOICE = 2,
		ROLE_HALFOP = 4,
		ROLE_OP = 5,
		ROLE_OTHER = 6
	};

	class User
	{
	public:
		/// Ctor
		User(const QString& fullnick);
	public:
		static UserRole char_to_role(char c);
	public:
		const QString& fullnick() const;
		const QString& nick() const;
		UserRole roles() const;
		void add_role(UserRole role);
		bool is_op();
		bool is_halfop();
		bool is_voice();
	public:
		friend bool operator==(User& user1, User& user2);
		friend bool operator<(User& user1, User& user2);
	private:
		QString _fullnick;
		QString _nick;
		UserRole _roles;
	};

} // namespace com

#endif /* !COM_USER_HH */
