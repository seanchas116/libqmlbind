#pragma once

#include "qmlbind/qmlbind_global.h"
#include <QObject>
#include <QSharedPointer>

namespace QmlBind {

class MetaObject;

class Wrapper : public QObject
{
public:
    Wrapper(const QSharedPointer<const MetaObject> &metaObject, qmlbind_object_handle handle);
    ~Wrapper();

    const QMetaObject *metaObject() const Q_DECL_OVERRIDE;
    int qt_metacall(QMetaObject::Call call, int index, void **argv) Q_DECL_OVERRIDE;

    qmlbind_object_handle handle() const;

private:

    QSharedPointer<const MetaObject> mMetaObject;
    qmlbind_object_handle mHandle;
};

} // namespace QmlBind
