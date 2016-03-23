QT += widgets qml quick core-private

TARGET = qmlbind
TEMPLATE = lib
CONFIG += c++11
DEFINES += QMLBIND_LIBRARY

INCLUDEPATH += $$PWD/include

SOURCES += \
    src/api_application.cpp \
    src/api_engine.cpp \
    src/api_iterator.cpp \
    src/api_value.cpp \
    src/metaobject.cpp \
    src/api_metaobject.cpp \
    src/wrapper.cpp \
    src/api_string.cpp \
    src/api_component.cpp \
    src/typeregisterer.cpp \
    src/api_register.cpp \
    src/exporter.cpp \
    src/api_exporter.cpp \
    src/interface.cpp \
    src/backref.cpp \
    src/signalemitter.cpp \
    src/api_signal_emitter.cpp \
    src/engine.cpp \
    src/api_plugin.cpp

PUBLIC_HEADERS += \
    include/qmlbind/application.h \
    include/qmlbind/engine.h \
    include/qmlbind/iterator.h \
    include/qmlbind/qmlbind_global.h \
    include/qmlbind/value.h \
    include/qmlbind/metaobject.h \
    include/qmlbind/string.h \
    include/qmlbind/component.h \
    include/qmlbind.h \
    include/qmlbind/register.h \
    include/qmlbind/exporter.h \
    include/qmlbind/signal_emitter.h \
    include/qmlbind/plugin.h \

PRIVATE_HEADERS += \
    src/metaobject.h \
    src/wrapper.h \
    src/typeregisterer.h \
    src/util.h \
    src/exporter.h \
    src/interface.h \
    src/backref.h \
    src/signalemitter.h \
    src/engine.h

HEADERS = $$PUBLIC_HEADERS $$PRIVATE_HEADERS

macx {
    QMAKE_SONAME_PREFIX = @rpath
}

unix {
    for(header, PUBLIC_HEADERS) {
       path = $${INSTALL_PREFIX}/usr/$${dirname(header)}
       eval(headers_$${path}.files += $$header)
       eval(headers_$${path}.path = $$path)
       eval(INSTALLS *= headers_$${path})
    }

    target.path = /usr/lib
    INSTALLS += target
}
