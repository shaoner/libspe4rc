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
	void onNotice(UserEvent* event);
	void onRaw(RawEvent* event);
	void onJoin(ChannelEvent* event);
	void onPart(ChannelEvent* event);
};


#endif /* !SIMPLE_CLIENT_HH */
