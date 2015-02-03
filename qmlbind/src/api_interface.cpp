#include "qmlbind/interface.h"
#include "util.h"
#include "interface.h"

using namespace QmlBind;

extern "C" {

qmlbind_interface qmlbind_interface_new(qmlbind_interface_handlers handlers)
{
    return newSharedPointer(new Interface(handlers));
}

void qmlbind_interface_release(qmlbind_interface interface)
{
    delete interface;
}

}
