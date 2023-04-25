/*
 * $Id: vsos.h,v 1.31.3.1 1995/10/17 20:43:33 cway Stab $
 *
 * System or Compiler standard includes and defines
 *
 * Peter Colby - May 1991
 *
 * Copyright 1991, 1994 by Viewlogic Systems, Inc.
 */

#ifndef vsOS_H
#define vsOS_H

#ifndef vlPLATFORM_H
#include "vplatfrm.h"
#endif

#ifdef vsNEED_WINDOWS_H
#if (vlOS_WIN32)
#include <windows.h>
#endif
#endif

#ifndef vsPROTODEFS_H
#include "vsprotod.h"
#endif

#if vlCOMP_LC
typedef unsigned long time_t;
typedef unsigned int size_t;
#ifdef isspace
#undef isspace
#endif
#endif

#if (vlCOMP_BC || vlCOMP_HC || vlCOMP_MC || vlCOMP_WC || vlCOMP_GCPLPL)
#include <stdio.h>
#else
#ifndef NULL
#include <stdio.h>
#endif
#endif

#if vlOS_UNIX
#include <unistd.h>
#if vlHW_SUN4 && !vlOS_SYSVR4
#include <vfork.h>
#endif
#include <sys/ioctl.h>
#if vlOS_SYSVR4
#include <sys/filio.h>
#endif
#ifdef MIN
#undef MIN
#endif
#ifdef MAX
#undef MAX
#endif
#include <sys/param.h>
#include <pwd.h>
#include <sys/types.h>
#if vlOS_AIX || vlOS_PCUNIX || vlOS_SYSVR4
#include <time.h>
#endif
#include <sys/time.h>
#else
#include <time.h>
#if (vlOS_VMS || vlCOMP_HC)
#include <types.h>
#endif
#if (vlCOMP_MC || vlCOMP_BC || vlCOMP_WC)
#include <sys\types.h>
#endif
#endif

#include <limits.h>

/*
 * We're looking for ANSI or ANSI-ish things here,
 * the motivation being that if compilers provide
 * ANSI-isms, we should use them.
 *
 * So far, the ANSI compilers we have are:
 *    GCC, MC 6.0, HC 1.62
 *
 * vlHAVE_STDLIB_H, vlHAVE_STRING_H, vlHAVE_STDARG_H are used below,
 * vlHAVE_STDARG_H is also used in "vlvargs.h".
 */

#if defined(__STDC__) || vlOS_VMS || vlCOMP_CPP || vlCOMP_BC || vlOS_SYSVR4 || vlOS_OSF || vlCOMP_HC || vlCOMP_MC || vlCOMP_WC || vlCOMP_GCPLPL
#define vlHAVE_STDLIB_H 1
#define vlHAVE_STDARG_H 1
#define vlHAVE_STRING_H 1

/*
 * Define _INC_VARARGS so varargs.h doesn't get included (this may happen with
 * some of the "standard" header files from OVI, like vcs_user.h).
 */
#if vlCOMP_MC
#define _INC_VARARGS    1
#endif

#else
#if vlOS_SUNOS4 || vlOS_HPUX || vlOS_AIX30
#define vlHAVE_STDLIB_H 1 /* only valid for SunOS 4.1 and higher */
#define vlHAVE_STDARG_H 0
#define vlHAVE_STRING_H 1
#else
#if vlOS_ULTRIX
#define vlHAVE_STDLIB_H 1
#define vlHAVE_STDARG_H 0
#define vlHAVE_STRING_H 1
#else
#if (vlOS_386)
#define vlHAVE_STDLIB_H 1
#define vlHAVE_STDARG_H 1
#define vlHAVE_STRING_H 1
#else
#if (vlOS_286)
#define vlHAVE_STDLIB_H 1
#define vlHAVE_STDARG_H 0
#define vlHAVE_STRING_H 0
#else
/* #if vlOS_SYSV */
#define vlHAVE_STDLIB_H 0
#define vlHAVE_STDARG_H 0
#define vlHAVE_STRING_H 1
#endif
#endif
#endif
#endif
#endif

/* This is just for kicks, an alternative to <stdarg.h> for testing */

#if vlOS_ULTRIX || vlOS_AIX30 || vlOS_SUN4 || vlCOMP_GC || vlOS_VMS || vlOS_SYSVR4 || vlOS_OSF
#define vlHAVE_VARARGS_H 1
#endif

#if vlCOMP_AC || vlCOMP_GCPLPL
#define vlHAVE_STDARG_H 1
#endif

#if vlHAVE_STDLIB_H
#include <stdlib.h>
#endif

#if vlHAVE_STDARG_H
#include <stdarg.h>
#else
#include <varargs.h>
#endif

#if vlOS_SUNOS4 && !vlCOMP_GCPLPL
#include "vsfndecl.h"
#endif

/*
 * SunOS 4 does't come with prototypes, so we had to add them in "vlstring.h".
 */
#if vlOS_SUNOS4 && vlCOMP_PROTO && !vlCOMP_GCPLPL && (!__GNUC__ || !__GNUC_MINOR__ || __GNUC_MINOR__ < 5)
#include "vlstring.h"
#else
#if vlHAVE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif
#endif

#ifndef isascii
#include <ctype.h>
#endif

/*
  Include math.h, but only if it has not yet been included.  This
  is determined by looking for a symbol DOMAIN or HUGE on lattice,
  AIX, and VMS.  Other compilers have an idempotent math.h.
*/
#if vlCOMP_LC || vlOS_AIX || vlOS_PCUNIX || vlOS_SYSVR4
#ifndef DOMAIN				    /* first define in \lc\math.h */
#include <math.h>
#endif
#else
#if vlOS_VMS
#ifndef HUGE
#include <math.h>
#endif
#else
#include <math.h>
#endif
#endif

#if (vlCOMP_MC || vlCOMP_BC || vlCOMP_WC)
#include <malloc.h>
/* BC's malloc.h #includes alloc.h, too. */
#endif

#if (vlOS_SUNOS4 || vlOS_SYSVR4)
#include <alloca.h>
#endif

#if !vlOS_AIX30
#if vlOS_UNIX
#if vlOS_AIX || vlOS_PCUNIX
 extern vlPointerT calloc vlARG2(size_t, size_t);
 extern vlPointerT realloc vlARG2(vlPointerT, size_t);
 extern vlPointerT malloc vlARG1(size_t);
#else
#include <malloc.h>
#endif /* else */
#endif /* vlOS_UNIX */
#endif /* !vlOS_AIX30 */

#if (vlCOMP_GCPLPL)
#else
#ifndef vsFILEIO_H
#include "vsfileio.h"
#endif
#endif

#ifndef NOT_NEED
#ifndef vsNETWORK_H
#include "vsnetwrk.h"
#endif

#include <errno.h>
#include <signal.h>

#if vlOS_UNIX
#include <grp.h>
#else
#if (vlHW_PC || (vlHW_MIPS && vlOS_NT))    /* Temp. for MIPS && NT */
struct  group {
    char    *gr_name;
    char    *gr_passwd;
    int     gr_gid;
    char    **gr_mem;
};
#endif
#endif
#endif
#if (!vlGRAF_MSWINDOWS)
#include <setjmp.h>
#endif

#if vlOS_OSF
#include <values.h>
#endif

#ifndef __GNUC__
#define __GNUC__        0
#endif

#ifndef __BORLANDC__
#define __BORLANDC__    0
#endif

#if vlOS_SUNOS4
typedef void (* vsSigHandlerProcT) vlARGS((int sig, int code, struct sigcontext *scp, char *addr));
#else
typedef void (* vsSigHandlerProcT) vlARGS((int sig));
#endif

#endif /* vsOS_H */
