#include "qmlbind/metaobject.h"
#include "metaobject.h"

using namespace QmlBind;

extern "C" {

qmlbind_metaobject *qmlbind_metaobject_new(const qmlbind_metaclass *metaclass)
{
    return new std::shared_ptr<MetaObject>(new MetaObject(*metaclass));
}

void qmlbind_metaobject_release(qmlbind_metaobject *metaobject)
{
    delete metaobject;
}

}
