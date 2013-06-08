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
	src/connector.hh \
    src/event.hh \
    src/message.hh \
    src/parser.hh \
    src/raw-event.hh \
    src/server-event.hh \
    src/user-event.hh

SOURCES += src/channel-event.cc \
	src/client.cc \
	src/connector.cc \
    src/event.cc \
    src/message.cc \
    src/parser.cc \
    src/raw-event.cc \
    src/server-event.cc \
    src/user-event.cc

doc.depends = $(SOURCES)
doc.commands = doxygen Doxyfile
#(cat Doxyfile; echo "INPUT = $?") | doxygen -
QMAKE_EXTRA_TARGETS += doc

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
