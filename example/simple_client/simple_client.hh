#ifndef SIMPLE_CLIENT_HH
# define SIMPLE_CLIENT_HH

# include <QtCore/QCoreApplication>
# include <QtDebug>
# include <client.hh>

using namespace com;

class SimpleClient : public QObject
{
	Q_OBJECT

public:
	SimpleClient();
public slots:
	void onNotice(CommandEvent& event, const QString& target, const QString& msg);
	void onRaw(RawEvent& event);
	void onJoin(CommandEvent& event, const QString& channel);
	void onPart(CommandEvent& event, const QString& channel, const QString& reason);
};


#endif /* !SIMPLE_CLIENT_HH */
