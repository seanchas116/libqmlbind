#pragma once

#include "qmlbind/qmlbind_global.h"
#include "classinfo.h"
#include <QMetaObject>
#include <QHash>
#include <QVector>

namespace QmlBind {

class Wrapper;
class SignalEmitter;

class MetaObject : public QMetaObject, public std::enable_shared_from_this<MetaObject>
{
public:
    MetaObject(const QByteArray &className, const QList<MethodInfo> &methods, const QList<PropertyInfo> &properties,
               qmlbind_client_class *classObject, qmlbind_client_callbacks callbacks);

    Wrapper *newWrapper(qmlbind_client_object *object) const;
    Wrapper *newObject(void *memory) const;

    // needed because indexOfSignal() needs the full normalized signal signature, not only the name.
    int indexOfSignalName(const char *name) const;

    int metaCall(QObject *object, Call call, int index, void **argv) const;

private:
    void setupData(const QByteArray &className);

    QVector<uint8_t> mStringData;
    QVector<uint> mMetadata;

    QList<MethodInfo> mMethods;
    QList<PropertyInfo> mProperties;
    QHash<QByteArray, int> mSignalIndexMap;

    qmlbind_client_class *mClassObject;
    qmlbind_client_callbacks mCallbacks;
};

} // namespace QmlBind
