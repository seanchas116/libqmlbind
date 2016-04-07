QT += widgets qml quick

TARGET = qmlbind
TEMPLATE = lib
CONFIG += c++11
QMAKE_CFLAGS += "-std=c99"
VERSION = 0.1.0

DEFINES += QMLBIND_LIBRARY

INCLUDEPATH += $$PWD/include

SOURCES += \
    src/api_application.cpp \
    src/api_engine.cpp \
    src/api_iterator.cpp \
    src/api_value.cpp \
    src/metaobject.cpp \
    src/wrapper.cpp \
    src/api_string.cpp \
    src/api_component.cpp \
    src/typeregisterer.cpp \
    src/signalemitter.cpp \
    src/api_signal_emitter.cpp \
    src/engine.cpp \
    src/api_plugin.cpp \
    src/api_metaclass.cpp \
    src/metaclass.cpp

PUBLIC_HEADERS += \
    include/qmlbind/application.h \
    include/qmlbind/engine.h \
    include/qmlbind/iterator.h \
    include/qmlbind/qmlbind_global.h \
    include/qmlbind/value.h \
    include/qmlbind/string.h \
    include/qmlbind/component.h \
    include/qmlbind.h \
    include/qmlbind/metaclass.h \
    include/qmlbind/signal_emitter.h \
    include/qmlbind/plugin.h \

HEADERS = $$PUBLIC_HEADERS \
    src/metaobject.h \
    src/wrapper.h \
    src/typeregisterer.h \
    src/metaclass.h \
    src/signalemitter.h \
    src/engine.h

macx {
    QMAKE_SONAME_PREFIX = @rpath
}

unix {
    isEmpty(INSTALL_PREFIX) {
        INSTALL_PREFIX=/usr
    }

    for(header, PUBLIC_HEADERS) {
       path = $${INSTALL_PREFIX}/$${dirname(header)}
       eval(headers_$${path}.files += $$header)
       eval(headers_$${path}.path = $$path)
       eval(INSTALLS *= headers_$${path})
    }

    target.path = $${INSTALL_PREFIX}/lib
    INSTALLS += target
}
