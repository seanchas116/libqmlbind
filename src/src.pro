QT += widgets qml quick

TARGET = qmlbind
TEMPLATE = lib

DEFINES += QMLBIND_LIBRARY

SOURCES += value.cpp \
    iterator.cpp \
    object.cpp \
    util.cpp \
    engine.cpp \
    application.cpp

HEADERS += value.h \
    qmlbind_global.h \
    iterator.h \
    object.h \
    util_p.h \
    engine.h \
    value_p.h \
    application.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

QMAKE_CXXFLAGS += "-std=c++03 -Wno-mismatched-tags"
