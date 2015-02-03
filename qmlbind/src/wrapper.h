#pragma once

#include "qmlbind/qmlbind_global.h"
#include "backref.h"
#include <QObject>
#include <QSharedPointer>

namespace QmlBind {

class MetaObject;

class Wrapper : public QObject
{
public:
    Wrapper(const QSharedPointer<const MetaObject> &metaObject, const Backref &ref);

    const QMetaObject *metaObject() const Q_DECL_OVERRIDE;
    int qt_metacall(QMetaObject::Call call, int index, void **argv) Q_DECL_OVERRIDE;

    Backref backref() { return mRef; }

private:

    QSharedPointer<const MetaObject> mMetaObject;
    Backref mRef;
};

} // namespace QmlBind
