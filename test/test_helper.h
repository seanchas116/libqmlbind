#pragma once

#include <QByteArray>
#include <QString>
#include <ostream>
#include <catch.hpp>

#define DESCRIBE(what) SECTION(what)
#define CONTEXT(what) SECTION(what)
#define IT(what) SECTION(what)

inline std::ostream &operator<<(std::ostream &stream, const QByteArray &ba)
{
    return stream << ba.data();
}

inline std::ostream &operator<<(std::ostream &stream, const QString &str)
{
    return stream << str.toUtf8();
}
