#include "functionwrapper.h"
#include <QVector>

namespace QmlBind {

FunctionWrapper::FunctionWrapper(
        qmlbind_value (*callback)(qmlbind_function_data,int, qmlbind_value *),
        qmlbind_function_data data,
        void (*deleteData)(qmlbind_function_data)) :
    mCallback(callback),
    mData(data),
    mDeleteData(deleteData)
{
}

FunctionWrapper::~FunctionWrapper()
{
    mDeleteData(mData);
}

QJSValue FunctionWrapper::call(const QJSValue &args)
{
    int length = args.property("length").toInt();
    QVector<QJSValue *> values;
    values.reserve(length);

    for (int i = 0; i < length; ++i) {
        values << new QJSValue(args.property(i));
    }

    QJSValue *resultPtr = mCallback(mData, length, values.data());

    for (int i = 0; i < length; ++i) {
        delete values[i];
    }

    QJSValue result = *resultPtr;
    delete resultPtr;

    return result;
}

}
