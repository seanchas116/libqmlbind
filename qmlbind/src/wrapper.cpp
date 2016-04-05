#include "wrapper.h"
#include "metaobject.h"

namespace QmlBind {

Wrapper::Wrapper(const std::shared_ptr<const MetaObject> &metaObject, const Backref &ref) :
    mMetaObject(metaObject),
    mRef(ref)
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
