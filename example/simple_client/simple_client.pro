#-------------------------------------------------
#
# Project created by QtCreator 2013-02-23T19:16:35
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = simple_client
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += simple_client.hh
SOURCES += simple_client.cc

LIBS += -L$$OUT_PWD/../../ -lspe4rc

INCLUDEPATH += $$PWD/../../src
DEPENDPATH += $$PWD/../../

#win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libspe4rc/release/spe4rc.lib
#else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../libspe4rc/debug/spe4rc.lib
#else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../../libspe4rc.so
