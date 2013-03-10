#-------------------------------------------------
#
# SPE4K
#
#-------------------------------------------------

QT += core network

TEMPLATE = lib

# Target
TARGET = spe4rc
CONFIG += staticlib
# Temporary files
OBJECTS_DIR = ./build/objs
MOC_DIR = ./build/src

# Sources
INCLUDEPATH += src
HEADERS += src/channel-event.hh \
    src/common.hh \
    src/event.hh \
    src/event-processor.hh \
    src/message.hh \
    src/parser.hh \
    src/protocol.hh \
    src/raw-event.hh \
    src/server-event.hh \
    src/session.hh \
    src/user-event.hh

SOURCES += src/parser.cc \
    src/session.cc \
    src/protocol.cc \
    src/message.cc \
    src/event-processor.cc \
    src/event.cc \
    src/user-event.cc \
    src/channel-event.cc \
    src/server-event.cc \
    src/raw-event.cc

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
