#include "object.h"
#include "metaobject.h"
#include <private/qobject_p.h>

namespace QmlBind {

Object::Object(MetaObject *metaObject, void *handle, void (*deleteHandle)(void *)) :
    mMetaObject(metaObject),
    mHandle(handle),
    mDeleteHandle(deleteHandle)
{
}

Object::~Object()
{
    mDeleteHandle(mHandle);
}

const QMetaObject *Object::metaObject() const
{
    return mMetaObject;
}

int Object::qt_metacall(QMetaObject::Call call, int index, void **argv)
{
    return mMetaObject->metaCall(this, call, index, argv);
}

void *Object::handle() const
{
    return mHandle;
}

} // namespace QmlBind
