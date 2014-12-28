#include "qmlbind/string.h"
#include <QByteArray>
#include <QList>

extern "C" {

char *qmlbind_string_get(qmlbind_string *str)
{
    return str->data();
}

void qmlbind_string_delete(qmlbind_string *str)
{
    delete str;
}

}
