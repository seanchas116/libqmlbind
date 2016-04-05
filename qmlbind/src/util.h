#pragma once

#include <QSharedPointer>

namespace QmlBind {

template <typename T>
std::shared_ptr<T> *newSharedPointer(T *ptr)
{
    return new std::shared_ptr<T>(ptr);
}

}
