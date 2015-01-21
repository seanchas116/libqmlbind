#include "typeregisterer.h"
#include "metaobject.h"
#include "wrapper.h"
#include <QVector>
#include <QtQml>

#define MAX_CALLBACK_COUNT 256

namespace QmlBind {

template <int Index>
void TypeRegisterer::create(void *memory)
{
    const QSharedPointer<const MetaObject> &metaobj = TypeRegisterer::instance().mMetaObjects[Index];
    const Exporter *exporter = metaobj->exporter().data();
    qmlbind_object_handle handle = exporter->handlers().new_object(exporter->classHandle());

    new (memory) Wrapper(metaobj, handle);
}

// statically generates callback array

template <int Count, int Offset>
struct TypeRegisterer::CreationCallbacksSetter
{
    void set(TypeRegisterer *self)
    {
        CreationCallbacksSetter<Count / 2, Offset>().set(self);
        CreationCallbacksSetter<Count - Count / 2, Offset + Count / 2>().set(self);
    }
};

template <int Offset>
struct TypeRegisterer::CreationCallbacksSetter<1, Offset>
{
    void set(TypeRegisterer *self)
    {
        self->mCreationCallbacks[Offset] = create<Offset>;
    }
};

TypeRegisterer::TypeRegisterer() :
    mCreationCallbacks(MAX_CALLBACK_COUNT)
{
    CreationCallbacksSetter<MAX_CALLBACK_COUNT>().set(this);
}

int TypeRegisterer::registerType(const QSharedPointer<const MetaObject> &metaObject, const char *uri, int versionMajor, int versionMinor, const char *qmlName)
{
    int index = mMetaObjects.size();
    if (MAX_CALLBACK_COUNT <= index) {
        qWarning() << "Cannot register QML types more than" << MAX_CALLBACK_COUNT;
        return false;
    }
    mMetaObjects << metaObject;

    CreationCallback create = mCreationCallbacks[index];

    registerType(metaObject, create, uri, versionMajor, versionMinor, qmlName);

    return true;
}

void TypeRegisterer::registerType(const QSharedPointer<const MetaObject> &metaObject, CreationCallback create, const char *uri, int versionMajor, int versionMinor, const char *qmlName)
{
    QByteArray className;
    className += metaObject->className();
    className += "*";

    QByteArray listName;
    listName += "QQmlListProperty<";
    listName += metaObject->className();
    listName += ">";

    QQmlPrivate::RegisterType type = {
        0,
        qRegisterNormalizedMetaType<Wrapper *>(className),
        qRegisterNormalizedMetaType<QQmlListProperty<Wrapper> >(listName),
        sizeof(Wrapper), create,
        QString(),

        uri, versionMajor, versionMinor, qmlName, metaObject.data(),

        0, 0,

        QQmlPrivate::StaticCastSelector<Wrapper,QQmlParserStatus>::cast(),
        QQmlPrivate::StaticCastSelector<Wrapper,QQmlPropertyValueSource>::cast(),
        QQmlPrivate::StaticCastSelector<Wrapper,QQmlPropertyValueInterceptor>::cast(),

        0, 0,

        0,
        0
    };

    QQmlPrivate::qmlregister(QQmlPrivate::TypeRegistration, &type);
}

TypeRegisterer &TypeRegisterer::instance()
{
    static TypeRegisterer *i = 0;
    if (!i) {
        i = new TypeRegisterer();
    }
    return *i;
}

} // namespace QmlBind
