#pragma once

#include "qmlbind/qmlbind_global.h"
#include <QSharedPointer>

namespace QmlBind {

class Backref
{
public:
    Backref();
    Backref(qmlbind_backref *backref, const QSharedPointer<Interface> &interface);
    Backref(const Backref &other);
    ~Backref();

    Backref &operator=(const Backref &other);

    qmlbind_backref *backref() const { return mBackref; }
    QSharedPointer<Interface> interface() const { return mInterface; }

private:
    void retain();
    void release();

    qmlbind_backref *mBackref;
    QSharedPointer<Interface> mInterface;
};

} // namespace QmlBind
