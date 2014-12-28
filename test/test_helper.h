#pragma once

#include <QByteArray>
#include <QString>
#include <ostream>

inline std::ostream &operator<<(std::ostream &stream, const QByteArray &ba)
{
    return stream << ba.data();
}

inline std::ostream &operator<<(std::ostream &stream, const QString &str)
{
    return stream << str.toUtf8();
}
