/*
 * $Id: vsprotod.h,v 1.14.3.2 1996/01/26 21:55:29 gwu Stab $
 *
 * Defines for generating platform independant function prototypes
 *
 * Peter Colby - May 1991
 *
 * Copyright 1991, 1994 by Viewlogic Systems, Inc.
 */


#ifndef vsPROTODEFS_H
#define vsPROTODEFS_H

#if vlCOMP_PROTO
#define vlARGS(a)                  a
#define vlARG1(a1)                 (a1)
#define vlARG2(a1,a2)              (a1,a2)
#define vlARG3(a1,a2,a3)           (a1,a2,a3)
#define vlARG4(a1,a2,a3,a4)        (a1,a2,a3,a4)
#define vlARG5(a1,a2,a3,a4,a5)     (a1,a2,a3,a4,a5)
#define vlARG6(a1,a2,a3,a4,a5,a6)  (a1,a2,a3,a4,a5,a6)
#define vlARG7(a1,a2,a3,a4,a5,a6,a7) (a1,a2,a3,a4,a5,a6,a7)
#define vlARG8(a1,a2,a3,a4,a5,a6,a7,a8) (a1,a2,a3,a4,a5,a6,a7,a8)
#define vlARG9(a1,a2,a3,a4,a5,a6,a7,a8,a9) (a1,a2,a3,a4,a5,a6,a7,a8,a9)
#define vlARG10(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10) (a1,a2,a3,a4,a5,a6,a7,a8,a9,a10)
#define vlARG11(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11) (a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11)
#define vlARG12(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12) (a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12)
#define vlARG13(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13) (a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13)
#define vlARG14(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14) (a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14)
#define vlARG15(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15) (a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15)

#else
#define vlARGS(a)                  ()
#define vlARG1(a1)                 ()
#define vlARG2(a1,a2)              ()
#define vlARG3(a1,a2,a3)           ()
#define vlARG4(a1,a2,a3,a4)        ()
#define vlARG5(a1,a2,a3,a4,a5)     ()
#define vlARG6(a1,a2,a3,a4,a5,a6)  ()
#define vlARG7(a1,a2,a3,a4,a5,a6,a7) ()
#define vlARG8(a1,a2,a3,a4,a5,a6,a7,a8) ()
#define vlARG9(a1,a2,a3,a4,a5,a6,a7,a8,a9) ()
#define vlARG10(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10) ()
#define vlARG11(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11) ()
#define vlARG12(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12) ()
#define vlARG13(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13) ()
#define vlARG14(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14) ()
#define vlARG15(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15) ()
#endif

/*\Docpage vlVOLATILE -- macro for declaring a volatile automatic variable
 *
 * SYNOPSIS
 *      vlVOLATILE(var_type, var_name, initial_value);
 *
 * DESCRIPTION
 *      Users of vlExCATCH, vlExUNWIND_PROTECT, et. al., need to be
 *      use this macro.
 *
 *      Non-volatile automatic variables might be clobbered by an
 *      exception (vlExThrow).  If the variable can be referenced
 *      after catching an exception, then the variable must be
 *      declared volatile.  Use this macro to do it, so that the
 *      functionality is portable to non-ANSI compilers.
 *
 * EXAMPLE
 *      vlVOLATILE(vlBoolT, error_occurred, FALSE);
 */
/*
 * Likewise, Lattice and Unix compilers barf on "volatile" and "const".
 */
#if (vlCOMP_LC || vlCOMP_UC) && !defined(__STDC__)
#define volatile
#define const
#define vlVOLATILE(type, var, ini) \
    type var = ini; \
    type *vlCONCAT_TOKEN (var,_vlExVPtr) = &var
#else
#define vlVOLATILE(type, var, ini) type volatile var = ini
#endif

/* Definition of 'const' must come before these typedefs */

/*
 * Lattice C and most Unix compilers don't do "void *".
 */
#if (vlCOMP_LC || (vlCOMP_UC && !vlOS_ULTRIX) || vlCOMP_CPP) && !defined(__STDC__)
typedef char *vlPointerT;
typedef const char *vlConstPtrT;
#else
typedef void *vlPointerT;
typedef const void *vlConstPtrT;
#endif


/*
 * An attempt to define specific integer sizes.  I hope I get these right!
 * They shouldn't be used unless you know what you're doing!
 */
typedef short   vlInt16T;

#if vlOS_PCDOS
typedef long    vlInt32T;
#else
typedef int     vlInt32T;
#endif


/*
 * See also vlint64.h.
 */
#if vlCOMP_GC || vlCOMP_GCPLPL
typedef long long _vlInt64T;
#define _vlInt64MIN               LONG_LONG_MIN
#define _vlInt64MAX               LONG_LONG_MAX
#else
#if vlOS_SOLARIS
typedef long long _vlInt64T;
#define _vlInt64MIN               LLONG_MIN
#define _vlInt64MAX               LLONG_MAX
#else
#if vlHW_ALPHA
typedef long    _vlInt64T;
#define _vlInt64MIN               LONG_MIN
#define _vlInt64MAX               LONG_MAX
#else
#if vlCOMP_MC
typedef __int64 _vlInt64T;
#define _vlInt64MIN               _I64_MIN
#define _vlInt64MAX               _I64_MAX
#else
#if (vlHW_MIPS && vlOS_SYSVR4)
typedef long long _vlInt64T;
#define _vlInt64MIN               LONGLONG_MIN
#define _vlInt64MAX               LONGLONG_MAX
#else
#endif
#endif
#endif
#endif
#endif

/*********************** G C C Special Stuff ***************************/

/* These macros take advantage of some odd GCC features. */

/*\Docpage vlF_NOSIDEEFFECTS -- marks a function is not having side effects
 * 
 * DESCRIPTION
 *      Marks A function as not having side effects, so GCC can do some common
 *      subexpresion elimination. It is ignored by all other compilers.
 *      It must be placed in the function prototype (you do use prototypes,
 *      don't you?), following the return type--including any *'s. (See
 *      example.)
 *
 * EXAMPLE
 *      extern int * vlF_NOSIDEEFFECTS myFunc (int);
 *
 * CAUTIONS
 *      There are restrictions on what functions may be marked this way.
 *      Note that GCC will not warn against improper use of this macro.
 *      - It must not modify globals
 *      - It must not do I/O
 *      - It must not dereference any pointer parameters
 */

#if vlCOMP_GC
#  define vlF_NOSIDEEFFECTS const
#else
#  define vlF_NOSIDEEFFECTS
#endif

/*\Docpage vlF_NORETURN - indicates that a function won't return
 *
 * DESCRIPTION
 *      Notes that a function will not return.  GCC uses this information
 *      when warning about possible control flow problems, For example, in
 *      this code:
 *
 *            void vlF_NORETURN report_an_error ()
 *            {
 *                vlExThrow(...);
 *            }
 *
 *            int check (x)
 *               int x;
 *            {
 *               if (x < MAX)
 *                  return x;
 *               else
 *                  report_an_error ();
 *                  / note: no return statement here /
 *            }
 *
 *      GCC will warn of a missing return UNLESS report_an_error is marked as
 *      vlF_NORETURN. Other compilers ignore this macro.
 *
 *      Typically a NORETURN function will exit or throw an exception.  The
 *      return type should be void--nothing else makes sense.
 *
 * EXAMPLE
 *      extern void vlF_NORETURN myFunc (int);
 */

/*
 * Gnu C as of version 2.5 changed the semantics of
 * "extern volatile void vlExThrow()" and we started getting all sorts of
 * warnings.  Ah, I love compiler changes...
 */
#if vlCOMP_GC
#  if !__GNUC_MINOR__ || (__GNUC__ == 2 &&  __GNUC_MINOR__ < 5)
#    define vlF_NORETURN volatile
#    define vlF_NORETURN_GCC_CHANGES_SUK
#  else
#    define vlF_NORETURN
#    define vlF_NORETURN_GCC_CHANGES_SUK __attribute__ ((noreturn))
#  endif
#else
#  define vlF_NORETURN
#  define vlF_NORETURN_GCC_CHANGES_SUK
#endif

/*\Docpage vlF_LIKEPRINTF -- Enables format string vs. parameter checking
 *
 * DESCRIPTION
 *      Indicates that a function takes a printf-like format string, and
 *      enables GCC to do some consistency checking. All other compilers
 *      ignore this macro.
 *
 * SYNOPSIS
 *      vlF_LIKEPRINTF (formatloc, paramloc);
 *         int formatloc; // location of format string in param list
 *         int paramloc;  // location of first parameter in param list
 *
 * EXAMPLE
 *      extern int vlSprintf (char *, int, const char *, ...)
 *             vlF_LIKEPRINTF (3, 4);
 *
 *      The formatloc parameter indicates where in the parameter list the
 *      format string is (starting with 1).  The paramloc parameter indicates
 *      where the parameters to be formatted begin. A 0 disables some of the
 *      checks.
 */

#if vlCOMP_GC
#  define vlF_LIKEPRINTF(a,b) \
    __attribute__ ((format (printf, a, b)))
#else
#  define vlF_LIKEPRINTF(a,b)
#endif

/*\Docpage vlF_INLINE - declare a funciton `inline'
 *
 * DESCRIPTION
 *      The following description is taken from the GCC CC help file
 *      describing the inline functionality:
 *
 *      "By declaring a function `inline', you can direct GNU CC to integrate
 *      that function's code into the code for its callers.  This makes
 *      execution faster by eliminating the function-call overhead; in
 *      addition, if any of the actual argument values are constant, their
 *      known values may permit simplifications at compile time so that not
 *      all of the inline function's code needs to be included.  Inlining of
 *      functions is an optimization and it really "works" only in optimizing
 *      compilation. If you don't use `-O', no function is really inline."
 *
 *      Please refer to the compiler documentation on the specific behavior of
 *      inlined functions.
 *
 * EXAMPLE
 *     vlF_INLINE void myFunc (int);
 */

#if vlCOMP_GC
#  define vlF_INLINE inline
#else
#  define vlF_INLINE
#  define inline
#endif

#endif /* vsPROTODEFS_H */
