#pragma once

#include "qmlbind/qmlbind_global.h"
#include <QObject>

namespace QmlBind {

class MetaObject;

class Object : public QObject
{
public:
    Object(MetaObject *metaObject, void *handle, void (*deleteHandle)(void *));
    ~Object();

    const QMetaObject *metaObject() const Q_DECL_OVERRIDE;
    int qt_metacall(QMetaObject::Call call, int index, void **argv) Q_DECL_OVERRIDE;

    void *handle() const;

private:

    const MetaObject *mMetaObject;
    void *mHandle;
    void (*mDeleteHandle)(void *);
};

} // namespace QmlBind
