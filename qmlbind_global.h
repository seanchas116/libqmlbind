#ifndef QMLBIND_GLOBAL_H
#define QMLBIND_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QMLBIND_LIBRARY)
#  define QMLBINDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QMLBINDSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QMLBIND_GLOBAL_H
