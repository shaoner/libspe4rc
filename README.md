Libspe4rc v0.2.1a
=======

Libspe4rc (pronunced libspea-rc) is a library that can be used to build an IRC client.
The main idea is to handle *only* the IRC protocol inside the library.
How you want to display the IRC data is up to you! ;)

Notes:
* This library is the first part of a simple Qt IRC Client (spe4k) that has not been published yet.
* It is still incomplete: lot of events not finished, but usable.

## Build

### Requirements

* qt >= 4.8
* qmake >= 2.01a

### Compiling for Linux

<pre>
qmake-qt4 -r -spec linux-g++
make
</pre>

### Cross compiling for Windows

Requires:
* mingw32-qmake-qt4
* mingw32-gcc-c++

<pre>
mingw-qmake-qt4 libspe4rc.pro -r
make
</pre>

## How to use it?

```c++

class IrcHandler
{
	IrcHandler()
	{
		Client* client = new Client("shaoner", "shaoner`", "shao", "WE DO NOT BREAK THE USERSPACE Mauro!");
		connect(client, SIGNAL(onJoin(ChannelEvent*), this, SLOT(on_join(ChannelEvent*)));
        client->start("irc.spe4k.com", 6667);
	}

	// on join event listener
   	void on_join(ChannelEvent* event)
   	{
		qDebug() << "Hello " << event->client()->nickname();
		qDebug() << "* " << event->nick() << " has joined " << event->channel();
   	}
};
// ...
```

## License

LGPL

## Authors

shaoner <shaoner@gmail.com>
