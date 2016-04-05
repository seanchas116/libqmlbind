#include "wrapper.h"
#include "metaobject.h"

namespace QmlBind {

Wrapper::Wrapper(const std::shared_ptr<const MetaObject> &metaObject, Interface&& interface) :
    mMetaObject(metaObject),
    mInterface(interface)
{
}

const QMetaObject *Wrapper::metaObject() const
{
    return mMetaObject.get();
}

int Wrapper::qt_metacall(QMetaObject::Call call, int index, void **argv)
{
    return mMetaObject->metaCall(this, call, index, argv);
}

} // namespace QmlBind
