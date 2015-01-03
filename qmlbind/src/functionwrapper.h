#pragma once

#include "qmlbind/qmlbind_global.h"
#include <QObject>
#include <QJSValue>

namespace QmlBind {

class FunctionWrapper : public QObject
{
    Q_OBJECT
public:
    explicit FunctionWrapper(qmlbind_value (*callback)(qmlbind_function_data data, int argc, qmlbind_value *argv),
                             qmlbind_function_data data,
                             void (*deleteData)(qmlbind_function_data data));
    ~FunctionWrapper();

    Q_INVOKABLE QJSValue call(const QJSValue &args);

private:

    qmlbind_value (*mCallback)(qmlbind_function_data, int, qmlbind_value *);
    qmlbind_function_data mData;
    void (*mDeleteData)(qmlbind_function_data);
};

}
