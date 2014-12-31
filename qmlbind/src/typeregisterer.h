#pragma once

#include <QVector>
#include <QScopedPointer>

namespace QmlBind {

class MetaObject;

class TypeRegisterer
{
public:
    static TypeRegisterer *instance();
    int registerType(MetaObject *metaObject, const char *uri, int versionMajor, int versionMinor, const char *qmlName);

private:
    typedef void (*CreationCallback)(void *);
    template <int Count, int Offset = 0> struct CreationCallbacksSetter;

    TypeRegisterer();
    template <int Index> static void create(void *memory);
    void registerType(MetaObject *metaObject, CreationCallback create, const char *uri, int versionMajor, int versionMinor, const char *qmlName);

    QVector<MetaObject *> mMetaObjects;
    QVector<CreationCallback> mCreationCallbacks;
};

} // namespace QmlBind
