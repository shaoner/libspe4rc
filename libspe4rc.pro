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
HEADERS += \
	src/client.hh \
	src/command-event.hh \
	src/connector.hh \
    src/event.hh \
	src/irc-error.hh \
    src/message.hh \
    src/parser.hh \
    src/raw-event.hh \
	src/role.hh \
	src/user.hh \
	src/user-list.hh

SOURCES += \
	src/client.cc \
	src/connector.cc \
    src/message.cc \
    src/parser.cc \
	src/role.cc \
	src/user.cc \
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
