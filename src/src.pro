QT += widgets qml quick

TARGET = qmlbind
TEMPLATE = lib

DEFINES += QMLBIND_LIBRARY

SOURCES += value.cpp \
    iterator.cpp \
    object.cpp \
    util.cpp

HEADERS += value.h \
    qmlbind_global.h \
    iterator.h \
    object.h \
    util_p.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
