#-------------------------------------------------
#
# SPE4K
#
#-------------------------------------------------

QT += core network

TEMPLATE = lib

# Target
TARGET = spe4rc
CONFIG += sharedlib
# Temporary files
OBJECTS_DIR = ./build/objs
MOC_DIR = ./build/src

# Sources
INCLUDEPATH += src
HEADERS += src/channel-event.hh \
	src/client.hh \
	src/command-event.hh \
	src/connector.hh \
    src/event.hh \
    src/message.hh \
    src/parser.hh \
    src/raw-event.hh \
	src/role.hh \
    src/server-event.hh \
	src/user.hh \
    src/user-event.hh \
	src/user-list.hh

SOURCES += src/channel-event.cc \
	src/client.cc \
	src/command-event.cc \
	src/connector.cc \
    src/event.cc \
    src/message.cc \
    src/parser.cc \
    src/raw-event.cc \
	src/role.cc \
    src/server-event.cc \
	src/user.cc \
    src/user-event.cc \
	src/user-list.cc

doc.depends = $(SOURCES)
doc.commands = doxygen Doxyfile

QMAKE_EXTRA_TARGETS += doc

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
