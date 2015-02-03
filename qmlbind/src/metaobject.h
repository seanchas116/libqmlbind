#pragma once

#include "qmlbind/qmlbind_global.h"
#include "exporter.h"
#include <QScopedPointer>
#include <QSharedPointer>
#include <private/qobject_p.h>

namespace QmlBind {

class Exporter;
class Wrapper;

class MetaObject : public QMetaObject
{
public:
    MetaObject(const QSharedPointer<const Exporter> &exporter);
    ~MetaObject();

    QSharedPointer<const Exporter> exporter() const { return mExporter; }
    int metaCall(QObject *object, Call call, int index, void **argv) const;

private:

    QSharedPointer<const Exporter> mExporter;
    QScopedPointer<QMetaObject, QScopedPointerPodDeleter> mPrototype;
};

} // namespace QmlBind
