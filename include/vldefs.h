/*
 * $Id: vldefs.h,v 2.40.8.2 1996/01/26 21:21:47 gwu Stab $
 *
 * General purpose definitions and typedefs.
 *
 * Copyright (c) 1984,1993 by Viewlogic Systems, Inc.
 */


#ifndef vlDEFS_H
#define vlDEFS_H

#ifndef vsOS_H
#include "vsos.h"
#endif

/* Exit status codes */
#if vlOS_VMS
#define vlEXIT_SUCCESS 1
#define vlEXIT_WARNING 0
#define vlEXIT_ERROR 2
#define vlEXIT_FATAL 4
#define vlCHECKEXITCODE(c) \
   vlASSERT1 ((c >= 0 && c <= 4), "Bad exit code: %d\n", c)
#else
#define vlEXIT_SUCCESS 0
#define vlEXIT_WARNING 1
#define vlEXIT_ERROR 2
#define vlEXIT_FATAL 3
#define vlCHECKEXITCODE(c) \
   vlASSERT1 ((c >= 0 && c <= 3), "Bad exit code: %d\n", c)
#endif

/* for compatibility */
#define vsEX_SUCCESS vlEXIT_SUCCESS
#define vsEX_WARNING vlEXIT_WARNING
#define vsEX_ERROR   vlEXIT_ERROR
#define vsEX_FATAL   vlEXIT_FATAL

#ifndef vlVARGS_H
#include "vlvargs.h"
#endif

#ifndef vrLIB_H
#include "vrlib.h"
#endif

/* TYPEDEFs */

typedef char *vlStringPtrT;                /* Pointer to character string  */
typedef const char *vlCStringPtrT;         /* Ptr to const string          */
typedef int vlCoordinateT;                 /* Coordinate value             */
typedef char vlBitT;                       /* Flag or bit value            */
typedef unsigned int vlBoolT;              /* Bigger but faster boolean    */
typedef unsigned long vlMaskT;             /* Mask value for up to 32 flags*/
typedef char vlByteIntT;                   /* Single byte integer          */
typedef unsigned int vlUnsignedIntT;       /* unsigned integer             */
typedef FILE *vlFilePtrT;                  /* File pointer                 */

/*\Docpage vlIntProcT -- integer procedure pointer typedef
 * 
 * DESCRIPTION
 *      Typedef for pointer to function returning int.
 *      Parameters are not prototyped.
 */
typedef int (*vlIntProcT) ();
/*\Docpage vlBoolProcT -- vlBoolT procedure pointer typedef
 *
 * DESCRIPTION
 *      Typedef for pointer to function returning vlBoolT.
 *      Parameters are not prototyped.
 */
typedef vlBoolT (*vlBoolProcT) ();
/*\Docpage vlVoidProcT -- void procedure pointer typedef
 *
 * DESCRIPTION
 *      Typedef for pointer to function returning void.
 *      Parameters are not prototyped.
 */
typedef void (*vlVoidProcT) ();
/*\Docpage vlPointerProcT -- vlPointerT procedure pointer typedef
 *
 * DESCRIPTION
 *      Typedef for pointer to function returning vlPointerT.
 *      Parameters are not prototyped.
 */
typedef vlPointerT (*vlPointerProcT) ();
/*\Docpage vlStringProcT -- string procedure pointer typedef
 *
 * DESCRIPTION
 *      Typedef for pointer to function returning char *.
 *      Its parameters are not prototyped.
 */
typedef char * (*vlStringProcT) ();

/*----------------------------------------------------------------------
 * Typedefs for function pointer types required for ANSI or POSIX functions.
 */

/*\Docpage vlQsortProcT -- procedure pointer typedef
 *
 * DESCRIPTION
 *      Typedef for pointer to comparison function used by vrQsort.
 *
 * SYNOPSIS
 *      typedef int (*vlQsortProcT) (const void *, const void *);
 */
typedef int (*vlQsortProcT) vlARGS((const void *, const void *));
/*\Docpage vlBsearchProcT -- procedure pointer typedef
 *
 * DESCRIPTION
 *      Typedef for pointer to comparison function used by vrBsearch.
 *
 * SYNOPSIS
 *      typedef int (*vlBsearchProcT) (const void *, const void *);
 */
typedef int (*vlBsearchProcT) vlARGS((const void *, const void *));

#define vlNULL_PROC ((vlVoidProcT) vlDummyProc)

/*\Docpage vlLoopT -- Enum used by iterator procedures
 *
 * DESCRIPTION
 *      A loop action procedure returns vlLoopSTOP to stop looping,
 *      or vlLoopCONTINUE to continue looping.
 */
typedef enum {
    vlLoopSTOP = 0,
    vlLoopCONTINUE = 1
} vlLoopT;

/*\Docpage vlLoopProcT -- action procedure pointer typedef
 * 
 * DESCRIPTION
 *      Typedef for pointer to function returning vlLoopT.
 *      Its parameters are not prototyped.
 */
typedef vlLoopT (*vlLoopProcT) ();

/* Constants */
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif


/* Numerical macros
 *
 * Note that <limits.h> has already been included by "vsos.h".
 */

/*\Docpage vlLIMIT_TO_SHORT -- limit int value to range of short int
 * 
 * DESCRIPTION
 *      If the value lies outside the range [SHRT_MIN..SHRT_MAX], then
 *      it is limited to that range.  Otherwise it is untouched.
 *      That is,
 * 
 *          if      (z < SHRT_MIN) z = SHRT_MIN;
 *          else if (z > SHRT_MAX) z = SHRT_MAX;
 * 
 */
#define vlLIMIT_TO_SHORT(z) \
    do { \
        if      (z < SHRT_MIN) z = SHRT_MIN; \
        else if (z > SHRT_MAX) z = SHRT_MAX; \
    } while (0)


/* Bogus macros
 *
 * The functionality of these macros should be superseded by the
 * definitions found in <limits.h>.  That is, vlLINFINITY should be
 * replaced by INT_MAX or LONG_MAX, whichever is appropriate.
 */

#define vlINFINITY 32767
#if (vlHW_ALPHA && vlOS_OSF)
#define vlLINFINITY MAXLONG
#else
#if (vlHW_MIPS && vlOS_SYSVR4)
#define vlLINFINITY LONG_MAX
#else
#define vlLINFINITY 2147483647l
#endif
#endif

#if (vlCOMP_VC)
# define vlFINFINITY 10E+37
# define vlDINFINITY 10E+37
#else
/* # if !vlOS_AIX30 */
#  define vlFINFINITY ((float)3.40282346638528860e+38)
#  define vlDINFINITY 1.797693134862315708e+308
/* # endif */
#endif

#ifdef UINT_MAX
#define vlUINT_MAX UINT_MAX
#else
#if vlOS_286 || vlOS_WINDOWS
#define vlUINT_MAX 0xFFFFU
#else
#define vlUINT_MAX 0xFFFFFFFFUL
#endif
#endif

#define vlLONG_BITS 32

/* End of bogus macros */


#define vlCharCOMMENT '|'
#define vlCharWILDCARD '*'
#define vlCharBACKSLASH '\\'
#define vlCharNEWLINE '\n'
#define vlCharNULL '\0'
#define vlCharPERIOD '.'
#define vlCharEQUAL '='
#define vlCharSPACE ' '
#define vlCharDOLLAR '$'
#define vlCharCOLON ':'
#define vlCharESC 27
#define vlCharBELL 7
#define vlCharLF 10
#define vlCharCR 13
#define vlCharZERO '0'
#define vlStrMAX 512
#define vlLINESIZE 80

/* Get index defines */
#define vlStrAMBIGUOUS -2
#define vlStrNOT_FOUND -1

#endif /* vlDEFS_H */
