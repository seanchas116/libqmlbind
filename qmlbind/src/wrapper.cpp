#include "wrapper.h"
#include "metaobject.h"
#include <private/qobject_p.h>

namespace QmlBind {

Wrapper::Wrapper(MetaObject *metaObject, void *handle, void (*deleteHandle)(void *)) :
    mMetaObject(metaObject),
    mHandle(handle),
    mDeleteHandle(deleteHandle)
{
}

Wrapper::~Wrapper()
{
    mDeleteHandle(mHandle);
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
