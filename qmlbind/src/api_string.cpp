#include "qmlbind/string.h"
#include <QByteArray>
#include <QList>

extern "C" {

char *qmlbind_string_get_chars(qmlbind_string *self)
{
    return str->data();
}

int qmlbind_string_get_length(qmlbind_string *self)
{
    return self->size();
}

void qmlbind_string_release(qmlbind_string *self)
{
    delete self;
}

}
