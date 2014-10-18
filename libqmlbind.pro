#-------------------------------------------------
#
# Project created by QtCreator 2014-10-18T14:55:19
#
#-------------------------------------------------

QT       += widgets qml quick

TARGET = qmlbind
TEMPLATE = lib

DEFINES += QMLBIND_LIBRARY

SOURCES += value.cpp

HEADERS += value.h \
    qmlexport_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
