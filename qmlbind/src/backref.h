#pragma once

#include "qmlbind/qmlbind_global.h"
#include <QSharedPointer>

namespace QmlBind {

class Backref
{
public:
    Backref();
    Backref(qmlbind_backref *backref, const std::shared_ptr<Interface> &interface);
    Backref(const Backref &other);
    ~Backref();

    Backref &operator=(const Backref &other);

    qmlbind_backref *backref() const { return mBackref; }
    std::shared_ptr<Interface> interface() const { return mInterface; }

private:
    void retain();
    void release();

    qmlbind_backref *mBackref;
    std::shared_ptr<Interface> mInterface;
};

} // namespace QmlBind
