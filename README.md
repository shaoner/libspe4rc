Libspe4rc v0.5.0
=======

Libspe4rc (pronunced libspea-R-C) is a library that can be used to build an IRC client.
The main idea is to handle *only* the IRC protocol inside the library.
How you want to use and display the IRC data is up to you! ;)

Notes:
* This library is the first part of a simple Qt IRC Client (spe4k) that has not been published yet.
* It is still incomplete, but usable.

## Build

### Requirements

* qt >= 4.8
* qmake >= 2.01a

### Compiling for Linux

<pre>
qmake-qt4 -r -spec linux-g++
make
</pre>

### Cross compiling for Windows 32bits

Requires:
* mingw32-qmake-qt4
* mingw32-gcc-c++

<pre>
mingw-qmake-qt4 libspe4rc.pro -r
make
</pre>

### Cross compiling for Windows 64bits

Requires:
* mingw64-qmake-qt4
* mingw64-gcc-c++

<pre>
mingw-qmake-qt4 libspe4rc.pro -r
make
</pre>


## How to use it?

```c++

class MyIrcClient : public QObject
{

	Q_OBJECT

	MyIrcClient()
	{
	    // Init a session

		Client client = Session("spe4k")
			   		  	.hostname("irc.spe4k.com"),
					   	.port(6667)
						.password("")
						.nickname("shaoner")
						.altnickname("shaoner1")
						.altnickname("shaoner2")
						.altnickname("shaoner3")
						.user("shaoner")
						.realname("we do not break userspace MAURO")
		// Attach to some event listeners
		connect(client, SIGNAL(onJoin(CommandEvent&, const QString&)), this, SLOT(on_join(CommandEvent& event, const QString&)));
		connect(client, SIGNAL(onKick(CommandEvent&, const QString&, const QString&, const QString&)),
				this, SLOT(on_kick(CommandEvent& event, const QString&, const QString&, const QString&)));
        client.start();
		// ...
	}

	// on join event listener
   	void on_join(CommandEvent& event, const QString& channel)
   	{
		qDebug() << "You can access the associated client session through event.client()";
		qDebug() << "Hello " << event.client().nickname();
		qDebug() << "* " << event.nick() << " has joined " << channel;
   	}

	void on_kick(CommandEvent& event, const QString& channel, const QString& target, const QString& reason)
	{
		qDebug() << target << " has been kicked by " << event.nick() << "( reason: " << reason << " )";
	}
};
// ...
```

## License

LGPL

## Authors

shaoner <shaoner@gmail.com>
