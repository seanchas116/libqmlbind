#pragma once

#include <QVector>
#include <QSharedPointer>

namespace QmlBind {

class MetaObject;

class TypeRegisterer
{
public:
    static TypeRegisterer &instance();
    int registerType(const std::shared_ptr<const MetaObject> &metaObject, const char *uri, int versionMajor, int versionMinor, const char *qmlName);

private:
    typedef void (*CreationCallback)(void *);
    template <int Count, int Offset = 0> struct CreationCallbacksSetter;

    TypeRegisterer();
    template <int Index> static void create(void *memory);
    void registerType(const std::shared_ptr<const MetaObject> &metaObject, CreationCallback create, const char *uri, int versionMajor, int versionMinor, const char *qmlName);

    QVector<std::shared_ptr<const MetaObject> >  mMetaObjects;
    QVector<CreationCallback> mCreationCallbacks;
};

} // namespace QmlBind
