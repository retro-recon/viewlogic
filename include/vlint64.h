#ifndef vlINT64_H
#define vlINT64_H

/* 
 * WARNING!  
 * The following preprocessor symbol has been defined for
 * conditional compilation only on those platforms which provide
 * 64-bit integers. We cannot use vlLONGLONG here because it depends
 * on whether GCC is used, but we want to be able to switch compilers
 * for the vlint64.c module.  
 */
/* BD adds vlCOMP_MC -- all recent revs of Microsoft C on all windows
 * and NT platforms, have an __int64 type for native 64 bit support.
 */
#define HAVE_NATIVE_64BIT  (vlOS_SOLARIS || (vlHW_SUN4 && vlCOMP_GC)|| vlHW_ALPHA || vlOS_LINUX || vlCOMP_MC || (vlHW_MIPS && vlOS_SYSVR4))


/*\Section vlInt64 - 64 bit integer arithmetic
 *
 * DESCRIPTION
 *   This package of routines allows for the portable manipulation
 *   of 64 bit numbers. The type vlInt64T is used for this purpose.
 *
 *   The operations provided are listed below. Note that vlInt64T
 *   should be treated as an ADT, i.e., only the operations below
 *   should be used on these objects.
 */
#if HAVE_NATIVE_64BIT
typedef _vlInt64T  vlInt64T;
#else
typedef union _vlint64tag
{
#if defined (INSIDE_VLINT64_C)
    _vlInt64T       num;               /* this is for real computation */
#endif
    unsigned long   word [2];          /* this is for debugging        */
    double          dword;             /* this is to ensure alignment  */
} vlInt64T;
#endif


#if HAVE_NATIVE_64BIT
/*\Docpage vlInt64Add - 64 bit addition
 *
 *   vlInt64T vlInt64Add (x, y)
 *               vlInt64T x, y;
 */
#define vlInt64Add(x, y)         ((x) + (y))
/*\Docpage vlInt64Sub - 64 bit subtraction
 *
 *   vlInt64T vlInt64Sub (x, y)
 *               vlInt64T x, y;
 */
#define vlInt64Sub(x, y)         ((x) - (y))
/*\Docpage vlInt64Mul - 64 bit multiplication
 *
 *   vlInt64T vlInt64Mul (x, y)
 *               vlInt64T x, y;
 */
#define vlInt64Mul(x, y)         ((x) * (y))
/*\Docpage vlInt64Div - 64 bit division
 *
 *   vlInt64T vlInt64Div (x, y)
 *               vlInt64T x, y;
 */
#define vlInt64Div(x, y)         ((x) / (y))
/*\Docpage vlInt64Mod - 64 bit modulo
 *
 *   vlInt64T vlInt64Mod (x, y)
 *               vlInt64T x, y;
 */
#define vlInt64Mod(x, y)         ((x) % (y))
/*\Docpage vlInt64Neg - 64 bit negation
 *
 *   vlInt64T vlInt64Neg (x)
 *               vlInt64T x;
 */
#define vlInt64Neg(x)            (- (x))
/*\Docpage vlInt64Abs - 64 bit absolute value
 *
 *   vlInt64T vlInt64Abs (x)
 *               vlInt64T x;
 */
#define vlInt64Abs(x)            ((x) >= 0 ? (x) : - (x))

/*\Docpage vlInt64Eq - 64 bit equality
 *
 *   vlBoolTT vlInt64Eq (x, y)
 *               vlInt64T x, y;
 */
#define vlInt64Eq(x, y)          ((x) == (y))
/*\Docpage vlInt64Lt - 64 bit less than
 *
 *   vlBoolT vlInt64Lt (x, y)
 *               vlInt64T x, y;
 */
#define vlInt64Lt(x, y)          ((x) < (y))
/*\Docpage vlInt64Le - 64 bit less than or equal
 *
 *   vlBoolT vlInt64Le (x, y)
 *               vlInt64T x, y;
 */
#define vlInt64Le(x, y)          ((x) <= (y))
/*\Docpage vlInt64Gt - 64 bit greater than
 *
 *   vlBoolT vlInt64Gt (x, y)
 *               vlInt64T x, y;
 */
#define vlInt64Gt(x, y)          ((x) > (y))
/*\Docpage vlInt64Ge - 64 bit greater than or equal
 *
 *   vlBoolT vlInt64Ge (x, y)
 *               vlInt64T x, y;
 */
#define vlInt64Ge(x, y)          ((x) >= (y))

/*\Docpage vlInt64And - 64 bit bitwise and
 *
 *   vlInt64T vlInt64And (x, y)
 *               vlInt64T x, y;
 */
#define vlInt64And(x, y)         ((x) & (y))
/*\Docpage vlInt64Or - 64 bit bitwise or
 *
 *   vlInt64T vlInt64Or (x, y)
 *               vlInt64T x, y;
 */
#define vlInt64Or(x, y)          ((x) | (y))
/*\Docpage vlInt64Xor - 64 bit bitwise xor
 *
 *   vlInt64T vlInt64Xor (x, y)
 *               vlInt64T x, y;
 */
#define vlInt64Xor(x, y)         ((x) ^ (y))
/*\Docpage vlInt64Not - 64 bit bitwise not
 *
 *   vlInt64T vlInt64Not (x)
 *               vlInt64T x;
 */
#define vlInt64Not(x)            (~ (x))

/*\Docpage vlInt64Inc - 64 bit increment (++)
 *
 *   vlInt64T vlInt64Inc (x)
 *               vlInt64T x; (modified)
 */
#define vlInt64Inc(x)            (++(x))
/*\Docpage vlInt64Dec - 64 bit decrement (--)
 *
 *   vlInt64T vlInt64Not (x)
 *               vlInt64T x; (modified)
 */
#define vlInt64Dec(x)            (--(x))

/*\Docpage vlInt64CvtFromLong - long to 64 bit conversion
 *
 *   vlInt64T vlInt64CvtFromLong (x)
 *               long x;
 */
#define vlInt64CvtFromLong(x)    ((vlInt64T) (x))
/*\Docpage vlInt64CvtToLong - 64 bit to long conversion
 *
 *   long vlInt64CvtToLong (x)
 *               vlInt64T x;
 */
#define vlInt64CvtToLong(x)      ((long) (x))
/*\Docpage vlInt64CvtFromDouble - double to 64 bit conversion
 *
 *   vlInt64T vlInt64CvtFromDouble (x)
 *               double x;
 */
#define vlInt64CvtFromDouble(x)  ((vlInt64T) (x))
/*\Docpage vlInt64CvtToDouble - 64 bit to double conversion
 *
 *   double vlInt64CvtToDouble (x)
 *               vlInt64T x;
 */
#define vlInt64CvtToDouble(x)    ((double) (x))

/*\Docpage vlInt64Zero - 64 bit zero constant
 */
#define vlInt64Zero              vlInt64CvtFromLong (0)
/*\Docpage vlInt64One - 64 bit one constant
 */
#define vlInt64One               vlInt64CvtFromLong (1)
/*\Docpage vlInt64MIN - 64 bit minimum value constant
 */
#define vlInt64MIN               vlInt64CvtFromLong (_vlInt64MIN)      
/*\Docpage vlInt64MAX - 64 bit maximum value constant
 */
#define vlInt64MAX               vlInt64CvtFromLong (_vlInt64MAX)


#else /* HAVE_NATIVE_64BIT */


extern vlInt64T vlInt64Add                        vlARG2(vlInt64T, vlInt64T);
extern vlInt64T vlInt64Sub                        vlARG2(vlInt64T, vlInt64T);
extern vlInt64T vlInt64Mul                        vlARG2(vlInt64T, vlInt64T);
extern vlInt64T vlInt64Div                        vlARG2(vlInt64T, vlInt64T);
extern vlInt64T vlInt64Mod                        vlARG2(vlInt64T, vlInt64T);
extern vlInt64T vlInt64Neg                        vlARG1(vlInt64T);
extern vlInt64T vlInt64Abs                        vlARG1(vlInt64T);

extern vlBoolT  vlInt64Eq                         vlARG2(vlInt64T, vlInt64T);
extern vlBoolT  vlInt64Lt                         vlARG2(vlInt64T, vlInt64T);
extern vlBoolT  vlInt64Le                         vlARG2(vlInt64T, vlInt64T);
extern vlBoolT  vlInt64Gt                         vlARG2(vlInt64T, vlInt64T);
extern vlBoolT  vlInt64Ge                         vlARG2(vlInt64T, vlInt64T);

extern vlInt64T vlInt64And                        vlARG2(vlInt64T, vlInt64T);
extern vlInt64T vlInt64Or                         vlARG2(vlInt64T, vlInt64T);
extern vlInt64T vlInt64Xor                        vlARG2(vlInt64T, vlInt64T);
extern vlInt64T vlInt64Not                        vlARG1(vlInt64T);

#define vlInt64Inc(x)            vlInt64Inc_ (&(x))
#define vlInt64Dec(x)            vlInt64Dec_ (&(x))

extern vlInt64T vlInt64Inc_                       vlARG1(vlInt64T *);
extern vlInt64T vlInt64Dec_                       vlARG1(vlInt64T *);

extern vlInt64T vlInt64CvtFromLong                vlARG1(long);
extern long     vlInt64CvtToLong                  vlARG1(vlInt64T);
extern vlInt64T vlInt64CvtFromDouble              vlARG1(double);
extern double   vlInt64CvtToDouble                vlARG1(vlInt64T);

extern vlInt64T vlInt64Zero;
extern vlInt64T vlInt64One;
extern vlInt64T vlInt64MIN;
extern vlInt64T vlInt64MAX;


#endif /* HAVE_NATIVE_64BIT */


/*\Docpage vlInt64IsZero - 64 bit zero test
 *
 *   vlBoolT vlInt64IsZero (x)
 *               vlInt64T x;
 */
#define vlInt64IsZero(x)         vlInt64Eq (x, vlInt64Zero)
/*\Docpage vlInt64IsOne - 64 bit one test
 *
 *   vlBoolT vlInt64IsOne (x)
 *               vlInt64T x;
 */
#define vlInt64IsOne(x)          vlInt64Eq (x, vlInt64One)
/*\Docpage vlInt64Positive - 64 bit positive test
 *
 *   vlBoolT vlInt64Positive (x)
 *               vlInt64T x;
 */
#define vlInt64Positive(x)       vlInt64Gt (x, vlInt64Zero)
/*\Docpage vlInt64NonNegative - 64 bit non-negative test
 *
 *   vlBoolT vlInt64NonNegative (x)
 *               vlInt64T x;
 */
#define vlInt64NonNegative(x)    vlInt64Ge (x, vlInt64Zero)
/*\Docpage vlInt64Negative - 64 bit negative test
 *
 *   vlBoolT vlInt64Negative (x)
 *               vlInt64T x;
 */
#define vlInt64Negative(x)       vlInt64Lt (x, vlInt64Zero)
/*\Docpage vlInt64NonPositive - 64 bit non positive test
 *
 *   vlBoolT vlInt64NonPositive (x)
 *               vlInt64T x;
 */
#define vlInt64NonPositive(x)    vlInt64Le (x, vlInt64Zero)

extern vlInt64T vlInt64Pow vlARGS((vlInt64T, vlInt64T));

typedef struct {
    vlInt64T imin, imax;
} vlTypeRangeInt64T;


extern vlInt64T vlInt64CvtFromStr                 vlARG3(const char *, 
                                                         const char **, int);
extern const char *vlInt64CvtToStr                vlARG2(vlInt64T, int);
typedef vlMaskT vlInt64OutT;

#define vlInt64OutUNSIGNED            0x0001
#define vlInt64OutISUNSIGNED(m)       ((m) & 0x0001)

#define vlInt64OutUPPERCASE           0x0002
#define vlInt64OutISUPPERCASE(m)      ((m) & 0x0002)

#define vlInt64OutRIGHTJUST           0x0000
#define vlInt64OutLEFTJUST            0x0010
#define vlInt64OutZEROPAD             0x0020
#define vlInt64OutJUSTIFY(m)          ((m) & 0x00f0)

#define vlInt64OutOPTSIGN             0x0000
#define vlInt64OutFORCESIGN           0x0100
#define vlInt64OutFORCESIGNSPACE      0x0200
#define vlInt64OutSIGN(m)             ((m) & 0x0700)

#define vlInt64OutALT                 0x0800
#define vlInt64OutISALT(m)            ((m) & 0x0800)

#define vlInt64OutDEFAULT             0x0000

extern const char *vlInt64CvtToStrEx vlARGS ((vlInt64T,
                                       int, int, int, vlInt64OutT));

extern vlTypeRangeInt64T vlInt64FullRange;

#endif /* vlINT64_H */


