/*
 *  $Revision: 1.43.3.3 $  $Date: 1996/03/07 19:03:49 $
 *
 *  Header file for the "local" version of ANSI-C and POSIX runtime functions.
 *
 *  Copyright (c) 1991,1994 by Viewlogic Systems, Inc.
 */


/*\Section vrlib - Viewlogic's runtime library.
 *
 * DESCRIPTION
 *      Vrlib contains all the runtime functions supported for portable code.
 *
 *      Local manpages only exist for a limited number of functions. If you
 *      can't find a "vr" manpage for a function "vrFunction" then try the
 *      manpage for "function" instead.
 *
 *      The current "approved" available vr functions are listed here, if you
 *      need access to any of the "less portable" functions you should be able
 *      to see exactly what is available by looking at the vrlib.h header.
 *
 *      List of approved vr functions: (runtime name => vrlib name)
 *      =======================================================================
 *
 *        abs        => vrAbs            acos        => vrAcos
 *        anint      -> vrAnint          asin        => vrAsin
 *        atan       => vrAtan           atan2       => vrAtan2
 *        atof       => vrAtof           atoi        => vrAtoi
 *        atol       => vrAtol           bcopy       => vrMemmove
 *        bsearch    => vrBsearch        bzero       => vrBzero
 *        ceil       => vrCeil           close       => vrClose
 *        cos        => vrCos            creat       => vrCreat
 *        dup        => vrDup            ecvt        => vrEcvt
 *        errno      => vrErrno          exp         => vrExp
 *        fabs       => vrFabs           fclose      => vrFclose
 *        fcvt       => vrFcvt           fdopen      => vrFdopen
 *        feof       => vrFeof           fflush      => vrFflush
 *        fgetc      => vrFgetc          fgets       => vrFgets
 *        floor      => vrFloor          fopen       => vrFopen
 *        fprintf    => vrFprintf        fputc       => vrFputc
 *        fputs      => vrFputs          fread       => vrFread
 *        fscanf     => vrFscanf         fseek       => vrFseek
 *        ftell      => vrFtell          fwrite      => vrFwrite
 *        getc       => vrGetc           getchar     => vrGetchar
 *        getenv     => vrGetenv         gets        => vrGets
 *        isalnum    => vrIsalnum        isalpha     => vrIsalpha
 *        isascii    => vrIsascii
 *        isatty     => vrIsatty         iscntrl     => vrIscntrl
 *        isdigit    => vrIsdigit        isgraph     => vrIsgraph
 *        islower    => vrIslower        isprint     => vrIsprint
 *        ispunct    => vrIspunct        isspace     => vrIsspace
 *        isupper    => vrIsupper        isxdigit    => vrIsxdigit
 *        log        => vrLog            lseek       => vrLseek
 *        lstat      => vrLStat
 *        memchr     => vrMemchr         memcpy      => vrMemcpy
 *        memcmp     => vrMemcmp         memmove     => vrMemmove
 *        memset     => vrMemset         modf        => vrModf
 *        open       => vrOpen           pow         => vrPow
 *        printf     => vrPrintf         putc        => vrPutc
 *        putchar    => vrPutchar        putenv      => vrPutenv
 *        puts       => vrPuts           qsort       => vrQsort
 *        read       => vrRead           rewind      => vrRewind
 *        scanf      => vrScanf          setbuf      => vrSetbuf
 *        sin        => vrSin            sprintf     => vrSprintf
 *        sqrt       => vrSqrt           sscanf      => vrSscanf
 *        stat       => vrStat           statfs      => vrStatfs
 *        strbrk     => vrStrbrk
 *        strcasecmp => vrStrcasecmp     strcat      => vrStrcat
 *        strchr     => vrStrchr         strcmp      => vrStrcmp
 *        strcpy     => vrStrcpy         strcspn     => vrStrcspn
 *        strdup     => vrStrdup         stricmp     => vrStricmp
 *        strlen     => vrStrlen         strncasecmp => vrStrncasecmp
 *        strncat    => vrStrncat        strncmp     => vrStrncmp
 *        strncpy    => vrStrncpy        strnicmp    => vrStrnicmp
 *        strrchr    => vrStrrchr        strstr      => vrStrstr
 *        strtod     => vrStrtod         strtok      => vrStrtok
 *        strtol     => vrStrtol         system      => vrSystem
 *        tan        => vrTan            tolower     => vrTolower
 *        toupper    => vrToupper        umask       => vrUmask
 *        ungetc     => vrUngetc         unlink      => vrUnlink
 *        vfprintf   => vrVfprintf       write       => vrWrite
 */

#ifndef vrLIB_H
#define vrLIB_H

#if 0   /* (vlGRAF_MSWINDOWS) */
#define vrUSE_VRMALLOC  1
#else
#define vrUSE_VRMALLOC  0
#endif

#if vrUSE_VRMALLOC
#include "vrmalloc.h"
#else
#define vrCalloc        calloc
#define vrFree          free
#define vrMalloc        malloc
#define vrRealloc       realloc
#endif

#if (vlCOMP_BC || vlCOMP_MC || vlCOMP_WC)
#include <process.h>    /* For getpid macro */
#endif

#if 0
#ifdef _INC_WINDOWS             /* BigWin's version of windows.h */
#define vlUSE_WINAPI_CALLS  1
#else
#ifdef __WINDOWS_H              /* Borland C's version of windows.h */
#define vlUSE_WINAPI_CALLS  1
#else
#ifdef _WINDOWS_                /* Microsoft C's (NT) version of windows.h */
#define vlUSE_WINAPI_CALLS  1
#else
#define vlUSE_WINAPI_CALLS  0
#endif
#endif
#endif
#else
#define vlUSE_WINAPI_CALLS  0
#endif

#if (vlCOMP_HC || vlCOMP_MC)
#define vr_Name(n, _n)   _n
#else
#define vr_Name(n, _n)   n
#endif

#if vlUSE_WINAPI_CALLS

#define vrClose         _lclose
#define vrCreat         _lcreat
#define vrLseek         _llseek
#define vrOpen          _lopen
#define vrRead          _lread
#define vrStrcat        lstrcat
#define vrStrcpy        lstrcpy
#define vrStrcmp        lstrcmp
/* #define vrStricmp       lstrcmpi <This is done below>*/
#define vrStrlen        lstrlen
#define vrWrite         _lwrite

#else

#define vrClose         vr_Name (close, _close)
#define vrCreat         creat
#define vrLseek         lseek
#define vrOpen          vr_Name (open, _open)
#define vrRead          read
#define vrStrcat        strcat
#define vrStrcpy        strcpy
#define vrStrcmp        strcmp
#if vlHW_SUN
#define vrStrlen(s)     ((unsigned int)strlen(s))
#else
#define vrStrlen        strlen
#endif
#define vrWrite         write

#endif

#include "vrexp.h"

#define vrAbort          abort
#if (vlCOMP_HC) /* Bug in High-C 1.73 */
#define vrAbs(i)    (((i) < 0) ? -(i) : (i))
#else
#define vrAbs            abs
#endif
#define vrAccept         accept
#define vrAcos           acos
#if (vlOS_HPUX | vlOS_ULTRIX | vlOS_AIX | vlOS_OSF | vlCOMP_HC | vlCOMP_MC | \
     vlOS_NT | vlOS_SOLARIS | vlOS_IRIX)
#define vrAnint(x)       (((x) < 0.0) ? vrCeil((x) - 0.5) : vrFloor((x) + 0.5))
#define vrNint(x)        (((x) < 0.0) ? ((int) ((x) - 0.5)) :               \
                                        ((int) ((x) + 0.5)))
#else
#define vrAnint          anint
#define vrNint           nint
#endif
#define vrAsin           asin
#define vrAtan           atan
#define vrAtan2          atan2
#define vrAtof           atof
#define vrAtoi           atoi
#define vrAtol           atol
#define vrBcmp           bcmp
#define vrBcopy          bcopy
#define vrBind           bind
#define vrBsearch        bsearch
#if vlOS_SOLARIS
#define vrBzero(p, len)  memset (p, 0, len)
#else
#define vrBzero          bzero
#endif
#define vrCeil           ceil
#define vrChdir          vr_Name (chdir, _chdir)
#define vrChdrive        _chdrive
#if (!vlCOMP_HC && !vlCOMP_MC)
#define vrClosedir       closedir
#endif
#define vrConnect        connect
#define vrCos            cos
#define vrCtime          ctime
#define vrDup            dup
#if (vlOS_UNIX || vlCOMP_MC || vlCOMP_BC || vlCOMP_WC)
#define vrEcvt           ecvt
#else
#if (vlCOMP_HC)
extern char *vrEcvt vlARG4(double, int, int *, int *);
#endif
#endif
#if ((vlOS_386 || vlOS_BIGWIN) && !vlCOMP_WC)
#define vrEnviron _environ
#else
#if (!vlCOMP_MC && !vlCOMP_WC)
extern char **environ;
#endif
#define vrEnviron environ
#endif
#define vrErrno          errno
#define vrExecve         execve
#define vrExecvp         execvp
#if vlOS_WIN32
#define vrExit           vlpcExit
#else
#define vrExit           exit
#endif
#define vrExp            exp
#define vrFabs           fabs
#define vrFclose         fclose
#define vrFcntl          fcntl
#if (vlOS_UNIX || vlCOMP_MC || vlCOMP_WC)
#define vrFcvt           fcvt
#else
#if (vlCOMP_HC)
extern char *vrFcvt vlARG4(double, int, int *, int *);
#endif
#endif
#define vrFdopen         fdopen
#define vrFeof           feof
#define vrFflush         fflush
#define vrFgetc          fgetc
#define vrFgets          fgets
#define vrFloor          floor
#define vrFopen          fopen
#define vrFork           fork
#if vlHW_PMAX
extern vrFprintf vlVaARG2(FILE *, const char *);
#else
#define vrFprintf        fprintf
#endif
#define vrFputc          fputc
#define vrFputs          fputs
#define vrFread          fread
#define vrFscanf         fscanf
#define vrFseek          fseek
#define vrFtell          ftell
#define vrFtime          ftime
#define vrFwrite         fwrite
#define vrGetc           getc
#define vrGetchar        getchar
#define vrGetcwd         vr_Name (getcwd, _getcwd)
#if (vlCOMP_BC)
#define vrGetdcwd        _getdcwd
#endif
#define vrGetdtablesize  getdtablesize
#if (vlGRAF_MSWINDOWS && vlOS_BIGWIN)
extern char *vrGetenv vlARGS((char *));
#else
#define vrGetenv         getenv
#endif
#if (vlOS_UNIX)
#define vrGetgid         getgid
#else
#if (vlHW_PC)
extern int vrGetgid vlARG1(void);
#endif
#endif
#if (vlOS_UNIX)
#define vrGetgrgid       getgrgid
#else
#if (vlHW_PC)
extern struct group *vrGetgrgid vlARG1(int);
#endif
#endif
#define vrGethostbyaddr  gethostbyaddr
#define vrGethostbyname  gethostbyname
#define vrGethostname    gethostname
#if (vlCOMP_BC)
extern int vrGethostname(char *, int);
#endif
#if (vlCOMP_MC)
#define vrGetpid         _getpid
#else
#define vrGetpid         getpid
#endif
#define vrGetpwuid       getpwuid
#define vrGets           gets
#define vrGetservbyname  getservbyname
#define vrGetsockname    getsockname
#define vrGettimeofday   gettimeofday
#if (vlOS_SUNOS4 || vlOS_SOLARIS)
extern int vrGettimeofday vlARGS ((struct timeval *t, struct timezone *));
#endif
#define vrGetuid         getuid
#define vrGetwd          getwd
#define vrGmtime         gmtime
#define vrIndex          strchr
#define vrInet_addr      inet_addr
#define vrInet_ntoa      inet_ntoa
#define vrIoctl          ioctl
#define vrIsalnum        isalnum
#define vrIsalpha        isalpha
#define vrIsascii        isascii
#define vrIsatty         isatty
#define vrIscntrl        iscntrl
#define vrIsdigit        isdigit
#define vrIsgraph        isgraph
#define vrIslower        islower
#define vrIsprint        isprint
#define vrIspunct        ispunct
#define vrIsspace        isspace
#define vrIsupper        isupper
#define vrIsxdigit       isxdigit
#define vrKill           kill
#define vrListen         listen
#define vrLocaltime      localtime
#define vrLog            log
#define vrLongjmp        longjmp
#define vrMemchr         memchr
#define vrMemcmp         memcmp
#define vrMemcpy         memcpy
#if vlHW_SUN && !vlOS_SYSVR4
#define vrMemmove(d,s,n) bcopy (s, d, n)
#else
#define vrMemmove        memmove
#endif
#define vrMemset         memset
#define vrMkdir          vr_Name (mkdir, _mkdir)
#define vrMknod          mknod
#if (vlOS_ULTRIX || vlOS_OSF)
extern char *mktemp vlARGS((char *template));
#endif
#define vrMktemp         vr_Name (mktemp, _mktemp)
#define vrModf           modf
#if (!vlCOMP_HC && !vlCOMP_MC)
#define vrOpendir        opendir
#endif
#define vrPerror         perror
#define vrPow            pow
#define vrPrintf         printf
#define vrPutc           putc
#define vrPutchar        putchar
#if (vlGRAF_MSWINDOWS && vlOS_BIGWIN)
extern int vrPutenv vlARGS((char *));
#else
#define vrPutenv         putenv
#endif
#define vrPuts           puts
#if (vlCOMP_HC)
#define vrQsort(array, n, size, proc) \
do { \
    if (n != 0) \
        qsort (array, n, size, proc); \
} while (0)
#else
#define vrQsort          qsort
#endif
#define vrRand           rand
#if (!vlCOMP_HC && !vlCOMP_MC)
#define vrReaddir        readdir
#endif
#define vrRecvfrom       recvfrom
#define vrRename         rename
#define vrRewind         rewind
#define vrRindex         strrchr
#define vrRmdir          vr_Name (rmdir, _rmdir)
#define vrScanf          scanf
#define vrSelect         select
#define vrSend           send
#define vrSendto         sendto
#define vrSetbuf         setbuf
#define vrSetjmp         setjmp
#define vrSetpgrp        setpgrp
#define vrSetsockopt     setsockopt
#define vrShutdown       shutdown
#define vrSignal         signal
#define vrSin            sin
#define vrSleep          sleep
#define vrSocket         socket
#define vrSprintf        sprintf
#define vrSqrt           sqrt
#define vrSrand          srand
#define vrSscanf         sscanf
#define vrStat           stat
#if vlOS_SYSVR4
#define vrStatfs         statvfs
#else
#define vrStatfs         statfs
#endif
#define vrLStat          lstat
#define vrStrbrk         strbrk
#if (vlOS_SUNOS4 || vlOS_ULTRIX || vlOS_HPUX || vlOS_LINUX)
#define vrStrcasecmp     strcasecmp
#else
#if !(vlOS_AIX30 || vlOS_SYSVR4 || vlOS_OSF)
#define vrStrcasecmp     stricmp
#else
#define vrStrcasecmp     vlStrIcmp
#endif
#endif
#define vrStrchr         strchr
#define vrStrcspn        strcspn
#define vrStrdup         strdup
#if (vlOS_SUNOS4 || vlOS_ULTRIX || vlOS_HPUX || vlOS_LINUX)
#define vrStricmp        strcasecmp
#else
#if !(vlOS_AIX30 || vlOS_SYSVR4 || vlOS_OSF)
#if vlUSE_WINAPI_CALLS
#define vrStricmp        lstrcmpi
#else
#define vrStricmp        stricmp
#endif
#else
#define vrStricmp        vlStrIcmp
#endif
#endif
#if (vlOS_SUNOS4 || vlOS_ULTRIX || vlOS_HPUX || vlOS_LINUX)
#define vrStrncasecmp    strncasecmp
#else
#if !(vlOS_AIX30 || vlOS_SYSVR4 || vlOS_OSF)
#define vrStrncasecmp    strnicmp
#else
#define vrStrncasecmp    vlStrNicmp
#endif
#endif
#define vrStrncat        strncat
#define vrStrncmp        strncmp
#define vrStrncpy        strncpy
#if (vlOS_SUNOS4 || vlOS_ULTRIX || vlOS_HPUX || vlOS_LINUX)
#define vrStrnicmp       strncasecmp
#else
#if !(vlOS_AIX30 || vlOS_SYSVR4 || vlOS_OSF)
#define vrStrnicmp       strnicmp
#else
#define vrStrnicmp       vlStrNicmp
#endif
#endif
#define vrStrrchr        strrchr

#if vlCOMP_HC
/* This fixes a bug in High-C 1.7. Be sure to check again for a fix
 * in later versions! */
#define vrStrstr(src, sub) ((((char *)src) == NULL || \
                              *((char *)src) == '\0') ? NULL : \
                                 strstr (src, sub))
#else
#define vrStrstr         strstr
#endif 

#define vrStrtod         strtod
#if (vlCOMP_HC)
extern char *vrStrtok vlARGS((char *, const char *));
extern long vrStrtol vlARGS((const char *, char **, int));
#else
#define vrStrtok         strtok
#define vrStrtol         strtol
#endif
#define vrSys_errlist    sys_errlist
#define vrSys_nerr       sys_nerr
#define vrSystem         system
#define vrTan            tan
#define vrTime           time
#define vrTmpnam         tmpnam
#define vrTolower        tolower
#define vrToupper        toupper
#define vrUmask          umask
#define vrUngetc         ungetc
#define vrUnlink         unlink
#define vrUtime          vr_Name (utime, _utime)
#define vrVfprintf       vfprintf

/* We should use these, too. */
/*
#define vrStdin          stdin
#define vrStdout         stdout
#define vrStderr         stderr
*/

#endif
