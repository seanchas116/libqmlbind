#pragma once

#include <QSharedPointer>

namespace QmlBind {

template <typename T>
QSharedPointer<T> *newSharedPointer(T *ptr)
{
    return new QSharedPointer<T>(ptr);
}

}
