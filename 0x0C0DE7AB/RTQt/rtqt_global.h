#ifndef RTQT_GLOBAL_H
#define RTQT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(RTQT_LIBRARY)
#  define RTQTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define RTQTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // RTQT_GLOBAL_H
