/*
 * $Id: vsfileio.h,v 1.5.9.1 1995/10/17 20:40:57 cway Stab $
 *
 * System defines and includes needed for low level (Level 1) file io
 * Peter Colby- May 1991
 *
 * Copyright 1991 by Viewlogic Systems, Inc.
 */

#ifndef vsFILEIO_H
#define vsFILEIO_H

#if (vlCOMP_HC || vlCOMP_BC || vlCOMP_MC || vlCOMP_WC)
#include <io.h>
#endif

#include <fcntl.h>

#if (vlCOMP_LC)
#define S_IEXEC 0
#endif

#if (vlCOMP_MC || vlCOMP_HC || vlCOMP_BC || vlCOMP_WC)
#include <sys\stat.h>
#ifndef O_RAW
#define O_RAW O_BINARY
#endif
#endif
 
#if (vlOS_UNIX)
#include <sys/file.h>
#include <sys/stat.h>
#ifndef O_RAW
#define O_RAW 0
#endif
#endif

#if (vlOS_VMS)
#include <file.h>
#include <stat.h>
#ifndef O_RAW
#define O_RAW 0
#endif
#endif

/* define dummies for DOS of all the standard UNIX permission bits */

#if (vlCOMP_HC || vlCOMP_LC || vlCOMP_MC || vlCOMP_BC)
#define S_IRWXU  (S_IREAD | S_IWRITE | S_IEXEC)
#define S_IRUSR  S_IREAD
#define S_IWUSR  S_IWRITE
#define S_IXUSR  S_IEXEC
#define S_IRWXG  0
#define S_IRGRP  0
#define S_IWGRP  0
#define S_IXGRP  0
#define S_IRWXO  0
#define S_IROTH  0
#define S_IWOTH  0
#define S_IXOTH  0
#endif

#define S_IBOTH S_IWRITE | S_IREAD

#endif /* vsFILEIO_H */
