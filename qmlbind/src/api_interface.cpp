#include "qmlbind/interface.h"
#include <private/qmetaobjectbuilder_p.h>
#include <private/qobject_p.h>
#include "interface.h"

using namespace QmlBind;

extern "C" {

qmlbind_interface *qmlbind_interface_new(const char *className, qmlbind_interface_handlers handlers)
{
    return new Interface(className, handlers);
}

void qmlbind_interface_delete(qmlbind_interface *exporter)
{
    delete exporter;
}

int qmlbind_interface_add_method(
    qmlbind_interface *exporter,
    void *handle,
    const char *name,
    int arity
)
{
    return exporter->addMethod(handle, name, arity).index();
}

int qmlbind_interface_add_signal(
    qmlbind_interface *exporter,
    const char *name,
    int arity
)
{
    return exporter->addSignal(name, arity).index();
}

int qmlbind_interface_add_property(
    qmlbind_interface *exporter,
    void *getterHandle,
    void *setterHandle,
    const char *name,
    int notifierSignalIndex
)
{
    return exporter->addProperty(getterHandle, setterHandle, name, notifierSignalIndex).index();
}

}
