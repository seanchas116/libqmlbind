#include "wrapper.h"
#include "metaobject.h"
#include "exporter.h"

namespace QmlBind {

Wrapper::Wrapper(const QSharedPointer<const MetaObject> &metaObject, const Backref &ref) :
    mMetaObject(metaObject),
    mRef(ref)
{
}

const QMetaObject *Wrapper::metaObject() const
{
    return mMetaObject.data();
}

int Wrapper::qt_metacall(QMetaObject::Call call, int index, void **argv)
{
    return mMetaObject->metaCall(this, call, index, argv);
}

} // namespace QmlBind
