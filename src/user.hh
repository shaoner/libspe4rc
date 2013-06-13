#ifndef COM_USER_HH
# define COM_USER_HH

# include <QString>

namespace com
{

	class User
	{
	public:
		/// Ctor
		User(const QString& nick, const QString& prefix = "");
		User(const QString& nick, QChar prefix);
	public:
		static User* create(const QString& fullname);
	public:
		const QString& nick() const;
		const QString& prefix() const;
		bool is_op();
		bool is_halfop();
		bool is_voice();
	public:
		bool operator==(User* user) const;
		bool operator<(User* user) const;
	private:
		QString _nick;
		QString _lowerNick;
		QString _prefix;
	};

} // namespace com

#endif /* !COM_USER_HH */
