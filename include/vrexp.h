/*
 *  $Revision: 1.11.4.2 $  $Date: 1996/02/07 14:58:07 $
 *
 *  Portable math expressions.
 *
 *  Copyright (c) 1991,1994 by Viewlogic Systems, Inc.
 */


#ifndef __HAVE_VRLOG10_INCLUDE__
#define __HAVE_VRLOG10_INCLUDE__

/* The Watcom compiler (and probably other) generates lots of warnings
 * when these preprocessor symbols are used but not defined.  Define
 * them if not defined for those compilers.
 */
#if (vlCOMP_WC)
#ifndef u3b
#define u3b     0
#endif
#ifndef u3b5
#define u3b5    0
#endif
#ifndef pdp11
#define pdp11   0
#endif
#ifndef vax
#define vax     0
#endif
#ifndef gcos
#define gcos    0
#endif
#endif

#define M_LOG2_10       3.32192809488736218171
#define M_LOG2          0.301029995663981198017467

#ifndef M_LOG10E
/* these constants are ala Knuth &/or UNIX /usr/include/math.h */
#define M_E             2.7182818284590452354
#define M_LOG2E         1.4426950408889634074
#define M_LOG10E        0.43429448190325182765
#define M_LN2           0.69314718055994530942
#define M_LN10          2.3025850929940456840179914546843642076011
#define M_PI            3.14159265358979323846264338327950288419716939937510
#define M_PI_2          1.57079632679489661923
#define M_PI_4          0.78539816339744830962
#define M_1_PI          0.31830988618379067154
#define M_2_PI          0.63661977236758134308
#define M_2_SQRTPI      1.12837916709551257390
#define M_SQRT2         1.41421356237309504880
#define M_SQRT1_2       0.70710678118654752440
#endif

/* now define MAXFLOAT separately from the above */
#ifndef MAXFLOAT

#ifdef sun
#define MAXFLOAT        ((float)3.40282346638528860e+38)
#ifndef HUGE
#define HUGE    99.e999         /* IEEE infinity */
#endif
#else

#if u3b || u3b5
#define MAXFLOAT        ((float)3.40282346638528860e+38)
#endif
#if pdp11 || vax
#define MAXFLOAT        ((float)1.701411733192644299e+38)
#endif
#if gcos
#define MAXFLOAT        ((float)1.7014118219281863150e+38)
#endif
#ifdef mips
#define MAXFLOAT        ((float)3.40282346638528860e+38)
#endif

#ifndef MAXFLOAT
#define MAXFLOAT        ((float)3.40282346638528860e+38)
#endif
#ifndef HUGE
#define HUGE    MAXFLOAT
#endif

#endif /* else !defined (sun) */

/* MAXFLOAT WILL be defined at this point */
/* #define MAXFLOAT ((float)1.701411733192644299e+38) */
#endif  /* MAXFLOAT not defined */

#if (vlOS_SUNOS4)

#define vrExp10(d) exp10(d)
#define vrExp2(d) exp2(d)

#else
                        /* ln(10) */
#define vrExp10(d) exp(M_LN10*(d))
#define vrExp2(d) exp(M_LN2*(d))

#endif


#if vlOS_HPUX
#define vrFinite(y) (1)
#else
#define vrFinite(x) finite(x)
#endif

#endif
