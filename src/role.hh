/*!
 * \file role.hh
 * \author shaoner
 * \brief An IRC channel role helper
 */

#ifndef COM_ROLE_HH
# define COM_ROLE_HH

# include <QHash>
# include <QDebug>

namespace com
{

	/*!
	 * \class Role
	 * \brief This class dynamicly handles IRC channel roles
	 */
	class Role
	{
	public:
		static Role* get();
		static void reset();
	public:
		quint8 highest(quint8 role);
		char to_prefix(quint8 role);
		quint8 from_prefix(char prefix);
		char from_mode(char mode);
		void add(char mode, char prefix, quint8 role);
	private:
		static Role* _instance;
	private:
		Role();
	private:
		QHash<char, char> _supportedPrefixes;
		QHash<char, quint8> _supportedRoles;
	};

	inline quint8
	uint8_msb(quint8 role)
	{
		role |= role >> 1;
		role |= role >> 2;
		role |= role >> 4;
		return role - (role >> 1);
	}

} // namespace com

#endif /* !COM_ROLE_HH */
