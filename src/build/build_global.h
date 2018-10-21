#ifndef BUILD_GLOBAL_H
#define BUILD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BUILD_LIBRARY)
#  define BUILDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BUILDSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BUILD_GLOBAL_H
