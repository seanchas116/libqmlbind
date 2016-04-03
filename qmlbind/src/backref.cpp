#include "backref.h"
#include "interface.h"

namespace QmlBind {

Backref::Backref()
{
}

Backref::Backref(qmlbind_backref *backref, const QSharedPointer<Interface> &interface) :
    mBackref(backref),
    mInterface(interface)
{
    retain();
}

Backref::Backref(const Backref &other) :
    mBackref(other.mBackref),
    mInterface(other.mInterface)
{
    retain();
}

Backref::~Backref()
{
    release();
}

Backref &Backref::operator=(const Backref &other)
{
    release();
    mInterface = other.mInterface;
    mBackref = other.mBackref;
    retain();

    return *this;
}

void Backref::retain()
{
    if (mInterface) {
        mInterface->retainObject(mBackref);
    }
}

void Backref::release()
{
    if (mInterface) {
        mInterface->releaseObject(mBackref);
    }
}

} // namespace QmlBind

