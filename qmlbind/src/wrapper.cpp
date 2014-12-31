#include "wrapper.h"
#include "metaobject.h"

namespace QmlBind {

Wrapper::Wrapper(const MetaObject *metaObject, void *handle) :
    mMetaObject(metaObject),
    mHandle(handle)
{
}

Wrapper::~Wrapper()
{
    mMetaObject->interface()->handlers().delete_object(mHandle);
}

const QMetaObject *Wrapper::metaObject() const
{
    return mMetaObject;
}

int Wrapper::qt_metacall(QMetaObject::Call call, int index, void **argv)
{
    return mMetaObject->metaCall(this, call, index, argv);
}

void *Wrapper::handle() const
{
    return mHandle;
}

} // namespace QmlBind
