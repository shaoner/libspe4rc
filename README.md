Libspe4rc v0.1.0
=======

Libspe4rc (pronunced libsp-i-rc) is a library that can be used to build an IRC client.
I need it to be as simple as possible and customizable.
The main idea is to handle the display outside of the library.

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
mingw-qmake-qt4 spe4k.pro -r
make
</pre>

## How to use it?

<pre>
class NoticeDisplay : UserEvent
{
        bool notify()
        {
                qDebug() << "* Notice from " << senderNick() << ": " << message();
                return false;
        }
}

// ...

  com::Session* client = new com::Session();
  client->nickname("spe4rc");
  client->altnickname("spe4rc_");
  client->username("spe4rc");
  client->realname("My Libspe4rc client");
  client->hostname("irc.spe4k.com");
  client->port(6667);
  NoticeDisplay nd;
  client->add_notifier(com::ON_NOTICE, &nd);
  client->start();
</pre>

## License

LGPL

## Authors

shaoner <shaoner@gmail.com>
