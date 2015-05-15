#-------------------------------------------------
#
# Project created by QtCreator 2015-05-16T02:03:07
#
#-------------------------------------------------

QT       += core gui

TARGET = testplugin
TEMPLATE = lib
CONFIG += plugin

SOURCES += testplugin.cpp

HEADERS += testplugin.h
DISTFILES += testplugin.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}
