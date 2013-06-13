#include <simple_client.hh>

SimpleClient::SimpleClient()
{
	Client* c = new Client("shao2", "shao22", "user", "Im the boss");
	connect(c, SIGNAL(onNotice(UserEvent*)), this, SLOT(onNotice(UserEvent*)));
	connect(c, SIGNAL(onRaw(RawEvent*)), this, SLOT(onRaw(RawEvent*)));
	connect(c, SIGNAL(onJoin(ChannelEvent*)), this, SLOT(onJoin(ChannelEvent*)));
	connect(c, SIGNAL(onPart(ChannelEvent*)), this, SLOT(onPart(ChannelEvent*)));
	c->start("irc.locklab.fr", 6667);
}

void
SimpleClient::onNotice(UserEvent* event)
{
	qDebug() << "* [Notice from " << event->nick()
			 << " to " << event->target() << "]: "
			 << event->args()[0];
}

void
SimpleClient::onRaw(RawEvent* event)
{
	qDebug() << "* [" << event->raw() << "]: " << event->rawmsg();
}

void
SimpleClient::onJoin(ChannelEvent* event)
{
	qDebug() << "* " << event->nick()
			 << " has joined " << event->channel()
			 << " ( " << event->args()[0] << " )";
}

void
SimpleClient::onPart(ChannelEvent* event)
{
	qDebug() << "* " << event->nick()
			 << " has left " << event->channel()
			 << " ( " << event->args()[0] << " )";
}

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  SimpleClient sc;
  return a.exec();
}
