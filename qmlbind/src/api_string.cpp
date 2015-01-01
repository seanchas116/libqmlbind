#include "qmlbind/string.h"
#include <QByteArray>
#include <QList>

extern "C" {

char *qmlbind_string_get_chars(qmlbind_string str)
{
    return str->data();
}

int qmlbind_string_get_length(qmlbind_string str)
{
    return str->size();
}

void qmlbind_string_delete(qmlbind_string str)
{
    delete str;
}

}
