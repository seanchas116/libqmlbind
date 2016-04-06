#include "qmlbind/metaobject.h"
#include "metaobject.h"

using namespace QmlBind;

extern "C" {

void qmlbind_metaobject_release(qmlbind_metaobject *metaobject)
{
    delete metaobject;
}

}
