#include "qmlbind/interface.h"
#include <private/qmetaobjectbuilder_p.h>
#include <private/qobject_p.h>
#include "interface.h"

using namespace QmlBind;

extern "C" {

qmlbind_interface qmlbind_interface_new(qmlbind_class_handle classHandle, const char *className, qmlbind_interface_handlers handlers)
{
    return new Interface(className, classHandle, handlers);
}

void qmlbind_interface_delete(qmlbind_interface interface)
{
    delete interface;
}

int qmlbind_interface_add_method(
    qmlbind_interface interface,
    qmlbind_method_handle handle,
    const char *name,
    int arity
)
{
    return interface->addMethod(handle, name, arity).index();
}

int qmlbind_interface_add_signal(
    qmlbind_interface interface,
    const char *name,
    int arity
)
{
    return interface->addSignal(name, arity).index();
}

int qmlbind_interface_add_property(
    qmlbind_interface interface,
    qmlbind_getter_handle getterHandle,
    qmlbind_setter_handle setterHandle,
    const char *name,
    int notifierSignalIndex
)
{
    return interface->addProperty(getterHandle, setterHandle, name, notifierSignalIndex).index();
}

}
