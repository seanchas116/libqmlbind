#include "qmlbind/metaclass.h"
#include "metaclass.h"
#include "metaobject.h"
#include "typeregisterer.h"

using namespace QmlBind;

extern "C" {

qmlbind_metaclass *qmlbind_metaclass_new(qmlbind_client_class *classObject, const char *className, qmlbind_client_callbacks callbacks)
{
    return new MetaClass(className, classObject, callbacks);
}

void qmlbind_metaclass_add_method(
    qmlbind_metaclass *self,
    const char *name,
    int arity
)
{
    self->addMethod(name, arity);
}

void qmlbind_metaclass_add_signal(
    qmlbind_metaclass *self,
    const char *name,
    int arity,
    const char *const *params
)
{
    QList<QByteArray> paramList;
    for (int i = 0; i < arity; ++i) {
        paramList << params[i];
    }
    self->addSignal(name, paramList);
}

void qmlbind_metaclass_add_property(qmlbind_metaclass *self,
    const char *name,
    const char *notifierSignal
)
{
    self->addProperty(name, notifierSignal);
}

void qmlbind_metaclass_release(qmlbind_metaclass *self)
{
    delete self;
}

int qmlbind_metaclass_register(
    qmlbind_metaclass *self,
    const char *uri,
    int versionMajor, int versionMinor,
    const char *qmlName)
{
    return TypeRegisterer::instance().registerType(self->createMetaObject(), uri, versionMajor, versionMinor, qmlName);
}

}
