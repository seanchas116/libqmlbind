#include "exporter.h"
#include "interface.h"
#include <stdexcept>
#include <QVector>
#include <QDebug>

namespace QmlBind {

Exporter::Exporter(const char *className, qmlbind_client_class *classObject, QSharedPointer<Interface> interface) :
    mClassObject(classObject),
    mInterface(interface)
{
    mBuilder.setClassName(className);
}

static QByteArray methodSignature(const char *name, int arity)
{
    QByteArray sig;
    sig += name;
    sig += "(";
    for (int i = 0; i < arity; ++i) {
        if (i != 0) {
            sig += ",";
        }
        sig += "QJSValue";
    }
    sig += ")";
    return sig;
}



void Exporter::addMethod(const char *name, int arity)
{
    QMetaMethodBuilder method = mBuilder.addMethod(methodSignature(name, arity), "QJSValue");

    Method methodInfo;
    methodInfo.arity = arity;
    methodInfo.name = name;

    mMethodMap[method.index()] = methodInfo;
}

void Exporter::addSignal(const char *name, const QList<QByteArray> &args)
{
    QMetaMethodBuilder method = mBuilder.addSignal(methodSignature(name, args.size()));
    method.setParameterNames(args);

    mSignalIndexMap[name] = method.index();
}

void Exporter::addProperty(const char *name, const char *notifier)
{
    if (!mSignalIndexMap.contains(notifier)) {
        qWarning() << "signal" << notifier << "not yet added";
    }
    QMetaPropertyBuilder property = mBuilder.addProperty(name, "QJSValue", mSignalIndexMap[notifier]);

    property.setReadable(true);
    property.setWritable(true);

    Property propertyInfo;
    propertyInfo.name = name;

    mPropertyMap[property.index()] = propertyInfo;
}

} // namespace QmlBind
