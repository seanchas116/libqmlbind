#include "qmlbind/iterator.h"
#include <QJSValueIterator>

qmlbind_iterator *qmlbind_iterator_new(const qmlbind_value *object)
{
    return new QJSValueIterator(*object);
}

void qmlbind_iterator_release(qmlbind_iterator *self)
{
    delete self;
}

qmlbind_string *qmlbind_iterator_get_key(const qmlbind_iterator *self)
{
    return new QByteArray(self->name().toUtf8());
}

qmlbind_value *qmlbind_iterator_get_value(const qmlbind_iterator *self)
{
    return new QJSValue(self->value());
}

void qmlbind_iterator_next(qmlbind_iterator *self)
{
    self->next();
}

int qmlbind_iterator_has_next(const qmlbind_iterator *self)
{
    return self->hasNext();
}
