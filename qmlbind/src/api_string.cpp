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

int qmlbind_string_list_get_length(qmlbind_string_list *list)
{
    return list->size();
}

char *qmlbind_string_list_get(qmlbind_string_list *list, int index)
{
    return (*list)[index].data();
}

void qmlbind_string_list_delete(qmlbind_string_list *list)
{
    delete list;
}

}
