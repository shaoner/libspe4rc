#include <simple_client.hh>

SimpleClient::SimpleClient()
{
	Client* c = new Client("richard", "stallman", "I'm a gnu");
	c->add_altnickname("richie");
	c->add_altnickname("emacs");
	connect(c, SIGNAL(onNotice(CommandEvent&, const QString&, const QString&)),
			this, SLOT(onNotice(CommandEvent&, const QString&, const QString&)));
	connect(c, SIGNAL(onRaw(RawEvent&)),
			this, SLOT(onRaw(RawEvent&)));
	connect(c, SIGNAL(onJoin(CommandEvent&, const QString&)),
			this, SLOT(onJoin(CommandEvent&, const QString&)));
	connect(c, SIGNAL(onPart(CommandEvent&, const QString&, const QString&)), this, SLOT(onPart(CommandEvent&, const QString&, const QString&)));
	c->start("127.0.0.1", 6667);
}

void
SimpleClient::onNotice(CommandEvent& event, const QString& target, const QString& msg)
{
	qDebug() << "* [Notice from " << event.nick()
			 << " to " << target << "]: "
			 << msg;
}

void
SimpleClient::onRaw(RawEvent& event)
{
	qDebug() << "* [" << event.raw() << "]: " << event.msg();
}

void
SimpleClient::onJoin(CommandEvent& event, const QString& channel)
{
	qDebug() << "* " << event.nick()
			 << "@" << event.user()
			 << "!" << event.host()
			 << " has joined " << channel;
}

void
SimpleClient::onPart(CommandEvent& event, const QString& channel, const QString& reason)
{
	qDebug() << "* " << event.nick()
 			 << "@" << event.user()
			 << "!" << event.host()
			 << " has left " << channel
			 << " ( " << reason << " )";
}

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
  SimpleClient sc;
  return a.exec();
}
