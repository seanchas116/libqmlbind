#pragma once

#include "qmlbind/qmlbind_global.h"
#include <QSharedPointer>

namespace QmlBind {

class Backref
{
public:
    Backref();
    Backref(qmlbind_client_object *object, const std::shared_ptr<Interface> &interface);
    Backref(const Backref &other);
    ~Backref();

    Backref &operator=(const Backref &other);

    qmlbind_client_object *backref() const { return mBackref; }
    std::shared_ptr<Interface> interface() const { return mInterface; }

private:
    void retain();
    void release();

    qmlbind_client_object *mBackref;
    std::shared_ptr<Interface> mInterface;
};

} // namespace QmlBind
