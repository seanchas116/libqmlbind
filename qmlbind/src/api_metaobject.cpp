#include "qmlbind/metaobject.h"
#include "metaobject.h"

using namespace QmlBind;

extern "C" {

qmlbind_metaobject *qmlbind_metaobject_new(qmlbind_interface *interface)
{
    return new MetaObject(interface);
}

void qmlbind_metaobject_delete(qmlbind_metaobject *metaobject)
{
    delete metaobject;
}

}
