#include "qmlbind/exporter.h"
#include "exporter.h"
#include "metaobject.h"
#include <private/qmetaobjectbuilder_p.h>
#include <private/qobject_p.h>

using namespace QmlBind;

extern "C" {

qmlbind_exporter *qmlbind_exporter_new(qmlbind_client_class *classObject, const char *className, qmlbind_client_callbacks callbacks)
{
    return new Exporter(className, classObject, callbacks);
}

void qmlbind_exporter_add_method(
    qmlbind_exporter *self,
    const char *name,
    int arity
)
{
    self->addMethod(name, arity);
}

void qmlbind_exporter_add_signal(
    qmlbind_exporter *self,
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

void qmlbind_exporter_add_property(qmlbind_exporter *self,
    const char *name,
    const char *notifierSignal
)
{
    self->addProperty(name, notifierSignal);
}

void qmlbind_exporter_release(qmlbind_exporter *self)
{
    delete self;
}

}
