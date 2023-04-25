/*
 * $Id: vlvargs.h,v 1.21.8.1 1995/10/17 20:40:39 cway Stab $
 *
 * Copyright (c) 1990 by Viewlogic Systems, Inc.
 */

/**********************************************************************/
/*\Section vlVa -- varargs interface.
 *
 * DESCRIPTION
 *      The vlVa macros are a portable interface for defining
 *      functions which take a variable number of arguments.
 *
 *      functype func vlVaARG_DECL1(p1type, p1)
 *          defines a function `func', which has one named argument
 *          `p1', of type `p1type', plus a variable number of other
 *          arguments.  There are also macros for functions with
 *          more fixed parameters, vlVaARG_DECL2, 3, 4 and 5.
 *
 *      vlVaListT arglist;
 *          is the type of the variable `arglist', used to traverse
 *          the list of arguments.  There should need to be only
 *          one variable of this type.
 *
 *      vlVaSTART (pvar, parmN)
 *          is used to initialize pvar to the beginning of the
 *          list.  `parmN' is the last named parameter prior to
 *          the variable number of arguments.
 *
 *      vlVaARG (pvar, type)
 *          returns the next element of the `pvar' list, as the
 *          specified type.  It is up to the routine to know what
 *          type the next element is supposed to be.
 *
 *      vlVaEND (pvar)
 *          ends processing of the list.  You must call this to
 *          finish up.
 *
 * IMPORTANT
 *      A function which takes a variable-length list of
 *      arguments as a parameter is different from a function
 *      which takes a variable number of arguments; mixture of
 *      the two will probably result in fatal run-time errors.
 *      Let the buyer beware.  If a function has taken a variable
 *      number of arguments as "in" parameters, and wishes to
 *      call another function with the parameters remaining in
 *      the list (such as vprintf), it should be defined with
 *      vlVaARG_DECL1, and the function it passes the remainder
 *      of the list to should be defined normally, taking a
 *      parameter of type vlVaListT.  Such a function should be
 *      named with a suffix of Va.  Therefore, vlMsgBuild takes a
 *      variable number of arguments, whereas vlMsgBuildVa takes
 *      an argument which is a variable-length list.
 *
 * PROTOTYPING
 *      A function which is defined using vlVaARG_DECL1 should be
 *      prototyped using vlVaARG1.
 *
 * NAMING CONVENTIONS
 *      A function which takes a variable number of arguments may
 *      have any name, whereas a function which takes an argument
 *      list should do so as its last parameter and have a suffix
 *      of `Va'.  That is, vlErrBuild takes a variable number of
 *      arguments, and vlErrBuildVa takes an argument list.
 *
 * EXAMPLES
 *      // prototypes
 *      extern void vlErrOutBuild vlVaARG4(vlErrStreamID stream,
 *                                         const char * location,
 *                                         vlMsgFileID msg_file,
 *                                         int msg_number);
 *      extern void vlErrOutBuildVa vlARGS((vlErrStreamID stream,
 *                                         const char * location,
 *                                         vlMsgFileID msg_file,
 *                                         int msg_number,
 *                                         vlVaListT args));
 *
 *      // function definitions
 *      void vlErrOutBuild vlVaARG_DECL4(vlErrStreamID, stream,
 *                                       const char *, location,
 *                                       vlMsgFileID, msg_file,
 *                                       int, msg_number)
 *      {
 *          vlVaListT args;
 *
 *          vlVaSTART (args, msg_number);
 *          vlErrOutBuildVa (stream, location, msg_file,
 *                           msg_number, args);
 *          vlVaEND (args);
 *      }
 *
 *      void vlErrOutBuildVa(stream, location, msg_file, msg_num, args)
 *          vlErrStreamID stream;
 *          const char *location;
 *          vlMsgFileID msg_file;
 *          int msg_num;
 *          vlVaListT args;
 *      {
 *          // NOTE: do not use vlVaSTART or vlVaEND here
 *          while () {
 *             ...
 *             // Determine what type of variable is coming next, then
 *             some_var = vlVaARG (args, some_type);
 *             ...
 *          }
 *      }
 */

#ifndef vlVARGS_H
#define vlVARGS_H

#ifndef vsOS_H
#include "vsos.h"
#endif

/*
 * True ANSI varargs through <stdarg.h>
 * (tested under High-C, MS C, GCC, Ultrix).
 *
 * We could use __STDC__ here to decide on whether to
 * use <stdarg.h> or <varargs.h>, but the stand was taken
 * in "vldefs.h" that we should whatever ANSI-isms
 * compilers are providing.  Also, a particular vendor may
 * have both <stdarg.h> and <varargs.h>, only one of which
 * may actually work correctly (this was the case with Ultrix).
 *
 * HACK_ALERT - varargs code is broken by GCC 1.36 optimizer
 * and MC 6.0 optimizer!  Don't optimize there!
 *
 * HACK_ALERT - found a bug in Ultrix preprocessor (cc v2.0)
 * here using "vlmsg.c".  We now use <varargs.h> instead.
 */
#if vlHAVE_STDARG_H

/*
#define vlVaDECLARE1(functype, func, p1type, p1) \
    functype func(p1type p1, ...)
*/
#define vlVaARG_DECL1(p1type, p1) \
    (p1type p1, ...)
#define vlVaARG_DECL2(p1type, p1, p2type, p2) \
    (p1type p1, p2type p2, ...)
#define vlVaARG_DECL3(p1type, p1, p2type, p2, p3type, p3) \
    (p1type p1, p2type p2, p3type p3, ...)
#define vlVaARG_DECL4(p1type, p1, p2type, p2, p3type, p3, p4type, p4) \
    (p1type p1, p2type p2, p3type p3, p4type p4, ...)
#define vlVaARG_DECL5(p1type,p1,p2type,p2,p3type,p3,p4type,p4,p5type,p5) \
    (p1type p1, p2type p2, p3type p3, p4type p4, p5type p5, ...)
#define vlVaARG_DECL6(p1type,p1,p2type,p2,p3type,p3,p4type,p4,p5type,p5,p6type,p6) \
    (p1type p1, p2type p2, p3type p3, p4type p4, p5type p5, p6type p6, ...)
#define vlVaSTART(argsvar, preceeding_parm) \
    va_start (argsvar, preceeding_parm)

#define vlVaARG1(a)             (a, ...)
#define vlVaARG2(a, b)          (a, b, ...)
#define vlVaARG3(a, b, c)       (a, b, c, ...)
#define vlVaARG4(a, b, c, d)    (a, b, c, d, ...)
#define vlVaARG5(a, b, c, d, e) (a, b, c, d, e, ...)
#define vlVaARG6(a, b, c, d, e, f) (a, b, c, d, e, f, ...)

/*
 * Traditional Unix (non-ANSI) varargs through <varargs.h>
 * (tested under Sun CC, GCC, Ultrix C).
 */
#else /* vlHAVE_STDARG_H */

/*
#define vlVaDECLARE1(functype, func, p1type, p1) \
    functype func(p1, va_alist)\
        p1type p1;\
        va_dcl
*/
#define vlVaARG_DECL1(p1type, p1) \
    (p1, va_alist)\
        p1type p1;\
        va_dcl
#define vlVaARG_DECL2(p1type, p1, p2type, p2) \
    (p1, p2, va_alist)\
        p1type p1;\
        p2type p2;\
        va_dcl
#define vlVaARG_DECL3(p1type, p1, p2type, p2, p3type, p3) \
    (p1, p2, p3, va_alist)\
        p1type p1;\
        p2type p2;\
        p3type p3;\
        va_dcl
#define vlVaARG_DECL4(p1type, p1, p2type, p2, p3type, p3, p4type, p4) \
    (p1, p2, p3, p4, va_alist)\
        p1type p1;\
        p2type p2;\
        p3type p3;\
        p4type p4;\
        va_dcl
#define vlVaARG_DECL5(p1type,p1,p2type,p2,p3type,p3,p4type,p4,p5type,p5) \
    (p1, p2, p3, p4, p5, va_alist)\
        p1type p1;\
        p2type p2;\
        p3type p3;\
        p4type p4;\
        p5type p5;\
        va_dcl
#define vlVaARG_DECL6(p1type,p1,p2type,p2,p3type,p3,p4type,p4,p5type,p5,p6type,p6) \
    (p1, p2, p3, p4, p5, p6, va_alist)\
        p1type p1;\
        p2type p2;\
        p3type p3;\
        p4type p4;\
        p5type p5;\
        p6type p6;\
        va_dcl
#define vlVaSTART(argsvar, preceeding_parm) \
    va_start (argsvar)

#define vlVaARG1(a)             ()
#define vlVaARG2(a, b)          ()
#define vlVaARG3(a, b, c)       ()
#define vlVaARG4(a, b, c, d)    ()
#define vlVaARG5(a, b, c, d, e) ()
#define vlVaARG6(a, b, c, d, e, f) ()

#endif /* vlHAVE_STDARG_H */

/*
 * Macros common to both.
 */
typedef va_list vlVaListT;
#define vlVaARG(argsvar, ptype)   va_arg (argsvar, ptype)
#define vlVaEND(argsvar)          va_end (argsvar)

/* Macro for use in assigning value to vlVaListT variable. */
#if (vlCOMP_WC)
#define vlVaASSIGNVaList(l, r)    (l)[0] = (r)[0]
#else
#define vlVaASSIGNVaList(l, r)    l = r
#endif

#endif /* vlVARGS_H */
