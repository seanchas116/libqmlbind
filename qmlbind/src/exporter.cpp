#include "exporter.h"
#include "interface.h"
#include <stdexcept>
#include <QVector>

namespace QmlBind {

Exporter::Exporter(const char *className, const Backref &classRef) :
    mClassRef(classRef)
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



QMetaMethodBuilder Exporter::addMethod(const Backref &methodRef, const char *name, int arity)
{
    QMetaMethodBuilder method = mBuilder.addMethod(methodSignature(name, arity), "QJSValue");

    Method methodInfo;
    methodInfo.arity = arity;
    methodInfo.method = methodRef;

    mMethodMap[method.index()] = methodInfo;

    return method;
}

QMetaMethodBuilder Exporter::addSignal(const char *name, const QList<QByteArray> &args)
{
    QMetaMethodBuilder method = mBuilder.addSignal(methodSignature(name, args.size()));
    method.setParameterNames(args);

    mSignalIndexMap[name] = method.index();

    return method;
}

QMetaPropertyBuilder Exporter::addProperty(const Backref &getter, const Backref &setter, const char *name, int notifySignalIndex)
{
    QMetaPropertyBuilder property = mBuilder.addProperty(name, "QJSValue", notifySignalIndex);

    property.setReadable(true);
    property.setWritable(true);

    Property propertyInfo;
    propertyInfo.getter = getter;
    propertyInfo.setter = setter;

    mPropertyMap[property.index()] = propertyInfo;

    return property;
}

} // namespace QmlBind
