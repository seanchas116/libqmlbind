#include "qmlbind/string.h"
#include <QByteArray>
#include <QList>

extern "C" {

// Only implement constData() here, as there's probably no meaningful usecase which includes modifying
// the internal data representation without needing a copy afterwards anyway.
const char *qmlbind_string_get_chars(const qmlbind_string *self)
{
    return self->constData();
}

int qmlbind_string_get_length(const qmlbind_string *self)
{
    return self->size();
}

void qmlbind_string_release(qmlbind_string *self)
{
    delete self;
}

}
