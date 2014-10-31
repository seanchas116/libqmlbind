TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

QMAKE_CFLAGS += "-std=c89"

LIBS += -L$$PWD/../src/ -lqmlbind
INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src
