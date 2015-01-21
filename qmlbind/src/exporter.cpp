#include "exporter.h"
#include <stdexcept>
#include <QVector>

namespace QmlBind {

Exporter::Exporter(const char *className, qmlbind_class_handle classHandle, qmlbind_interface_handlers handlers) :
    mClassHandle(classHandle),
    mHandlers(handlers)
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



QMetaMethodBuilder Exporter::addMethod(qmlbind_method_handle handle, const char *name, int arity)
{
    QMetaMethodBuilder method = mBuilder.addMethod(methodSignature(name, arity), "QJSValue");

    Method methodInfo;
    methodInfo.arity = arity;
    methodInfo.handle = handle;

    mMethodMap[method.index()] = methodInfo;

    return method;
}

QMetaMethodBuilder Exporter::addSignal(const char *name, const QList<QByteArray> &args)
{
    QMetaMethodBuilder method = mBuilder.addSignal(methodSignature(name, args.size()));
    method.setParameterNames(args);
    return method;
}

QMetaPropertyBuilder Exporter::addProperty(qmlbind_getter_handle getterHandle, qmlbind_setter_handle setterHandle, const char *name, int notifySignalIndex)
{
    QMetaPropertyBuilder property = mBuilder.addProperty(name, "QJSValue", notifySignalIndex);

    property.setReadable(true);
    property.setWritable(true);

    Property propertyInfo;
    propertyInfo.getterHandle = getterHandle;
    propertyInfo.setterHandle = setterHandle;

    mPropertyMap[property.index()] = propertyInfo;

    return property;
}

qmlbind_class_handle Exporter::classHandle() const
{
    return mClassHandle;
}

const QMetaObjectBuilder &Exporter::metaObjectBuilder() const
{
    return mBuilder;
}

qmlbind_interface_handlers Exporter::handlers() const
{
    return mHandlers;
}

QHash<int, Exporter::Method> Exporter::methodMap() const
{
    return mMethodMap;
}

QHash<int, Exporter::Property> Exporter::propertyMap() const
{
    return mPropertyMap;
}

} // namespace QmlBind
