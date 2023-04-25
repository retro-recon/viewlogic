/*
 *  $Id: vlexcept.h,v 5.25.3.1 1995/10/17 20:42:49 cway Stab $
 *
 *  Exception handling.  PLEASE see the manpage on "vlEx".
 *
 *  Copyright (c) 1989,1992 by Viewlogic Systems, Inc.
 */


#ifndef vlEXCEPT_H
#define vlEXCEPT_H

#include "vlerr.h"

/*
 * These are the functions you can call.
 */
extern void vlF_NORETURN vlExThrow  vlARGS((long tag, vlErrID err))
    vlF_NORETURN_GCC_CHANGES_SUK;
extern void vlF_NORETURN vlExThrow2  vlARGS((long tag, const char *app, int severity, const char *text))
    vlF_NORETURN_GCC_CHANGES_SUK;
extern void vlF_NORETURN vlExThrowBuild  vlVaARG4(long tag, const char *location, vlMsgFileID msgfile, int msgnum)
    vlF_NORETURN_GCC_CHANGES_SUK;
extern const char *vlExTagString  vlARGS((long));
extern void vlExPrecond vlVaARG4( int, vlCStringPtrT, vlMsgFileID, int );
/* Borland C++ 3.1, High-C (1.73), and Microsoft C 7.00 all support setjmp
 * and longjmp.  Old Catch and Throw stuff deleted - 11/5/92.
 */

#include <setjmp.h>
#define JMPBUF jmp_buf

/*
 * Definition of internal structure.  This is necessary
 * because of the fact that `setjmp (jmpbuf)' must be used in
 * a macro and not a function.
 * Don't use this knowledge.
 */
typedef struct vlExFrame {
    long tag; /* NEED 32 bits for this.  See tag definitions below */
    JMPBUF jmpbuf;
    struct vlExFrame *next;
} *vlExFramePtrT;

/*
 * The following type is really used only as a placeholder. The actual
 * structure sigcontext is never defined. We need to do this however, 
 * because otherwise gcc would complain.
 */
typedef struct sigcontext *     vlSigCntxID;

/*
 * Prototypes of internal routines used in the macro definitions.
 * Don't call these functions!
 */
extern void vlExInit  vlARGS((int *, char **));
extern void vlEx_PreCond  vlVaARG3(const char *, vlMsgFileID, int);
extern void vlEx_PostCond  vlVaARG3(const char *, vlMsgFileID, int);
#if vlENV_DEBUG
extern void vlExDbg  vlARGS((void));
#else
#  define vlExDbg()  /* nada */
#endif

/*
 * Global variables used to store information during a throw.
 * These should be used ONLY within the exception clause of a
 * catcher and are INVALID outside that clause.
 */
extern long vlExTagV;           /* the thrown tag */
extern vlErrID vlExErrV;        /* the thrown error */
extern struct vlExFrame *vlEx_StackV;
extern int vlEx_CatchLevelsV;

/*
 * Lattice C setjmp/longjmp takes jmpbuf *, other compilers take jmpbuf.
 * Note that vlEx_SETJMP takes a vlExFramePtrT,
 * but vlEx_LONGJMP takes a jmpbuf (jmpbuf *).
 *
 * Windows doesn't support setjmp and longjmp but have a similar construct
 * using Catch and Throw, which also take pointers to the buffer instead
 * of the buffer itself.  
 */
#if vlCOMP_LC
#define vlEx_SETJMP(frame_ptr)       setjmp (&((frame_ptr)->jmpbuf))
#define vlEx_LONGJMP(jmpbuf, x)      longjmp (&(jmpbuf), x)
#else
#define vlEx_SETJMP(frame_ptr)       setjmp ((frame_ptr)->jmpbuf)
#define vlEx_LONGJMP(jmpbuf, x)      longjmp (jmpbuf, x)
#endif

/*
 * Possible tags to throw with & masks to catch with
 * (yes I know in baseball you don't catch with a mask, but here you do).
 * If a new tag is added here, don't forget to add it to vlExString().
 */
#define vlExPRE_COND       0x00000001 /* failed pre-condition */
#define vlExPOST_COND      0x00000002 /* failed post-condition */
#define vlExFAILURE        0x00000002 /* can't fulfill contract - same as POST_COND */
#define vlExFAIL           0x00000002 /* same as FAILURE, but less typing */
#define vlExANY_SUBR       0x0000000f /* any subroutine contract-related */
  
/* #define vlExOUT_OF_MEMORY // memory exhausted -- unused */
/* #define vlExABORT         // iot instruction, see abort(3) -- unused */
/* #define vlExINTERRUPT     // interrupt (Ctrl-C) -- unused */

#define vlExBUS            0x00000040 /* bus error */
#define vlExSEGV           0x00000080 /* segmentation violation */
#define vlExFPE            0x00000100 /* floating point exception */
#define vlExANY_SYSTEM     0x0000fff0 /* any system signal */

#define vlExUSER1          0x00010000 /* user defined 1 */
#define vlExUSER2          0x00020000
#define vlExUSER3          0x00040000
#define vlExUSER4          0x00080000
#define vlExUSER5          0x00100000
#define vlExUSER6          0x00200000
#define vlExUSER7          0x00400000
#define vlExUSER8          0x00800000
#define vlExANY_USER       0x00ff0000 /* any user defined */

/*
 * For ViewScript's internal use only.
 */
#define vlExVSCM_BREAK     0x01000000 /* ViewScript's internal */
#define vlExVSCM_CONTINUE  0x02000000 /* ViewScript's internal */
#define vlExVSCM_RETURN    0x04000000 /* ViewScript's internal */

#define vlExSAVE_N_RESTORE 0x10000000

/*
 * Any exception except vlExPRE_COND - you shouldn't be
 * catching that but if you do, you must name it explicitly.
 */
#define vlExANY (vlExPOST_COND | vlExANY_SYSTEM | vlExANY_USER)
/*
 * Only Core should use this one.  What you really want is to use
 * vlExUNWIND_PROTECT!
 */
#define vlExANY_AND_ALL    0xffffffff /* any, any type of exception, really. */

/*
 * This macro is obsoleted by the macro vlVOLATILE.
 */
#ifdef volatile 
#define vlExVOLATILE(var)       &var
#else
#define vlExVOLATILE(var)
#endif

/*
 * Things common between vlExCATCH and vlExUNWIND_PROTECT.
 * Basically setup catch stack and call setjmp.
 */
#define vlEx_COMMON(ttag)  \
    /* whether or not this code resulted in a throw */\
    vlVOLATILE (int, vlEx_Caught, FALSE);\
    /* where to reset vlEx_StackV if we don't catch - */\
    /* we _could_ use vlEx_StackV->next here instead. */\
    struct vlExFrame *vlEx_LastFramePtrV = vlEx_StackV;\
    struct vlExFrame vlEx_ThisFrameV;\
    vlEx_ThisFrameV.tag = ttag;\
    vlEx_ThisFrameV.next = vlEx_StackV;\
    vlEx_StackV = &vlEx_ThisFrameV;\
    if (! vlEx_SETJMP (&vlEx_ThisFrameV))

/*
 * Catch form.
 */
#define vlExCATCH(ttag)  {\
                           vlErrID previous = vlExErrV;\
                           vlEx_COMMON (ttag)\
                           {
#define vlExEXCEPTION      }\
                           else {\
                               vlEx_Caught = TRUE;\
                               vlExDbg ();
#define vlExEND_CATCH          if (vlExErrV != NULL) {\
                                   vlErrDestroyTop (&vlExErrV, previous);\
                               }\
                               vlExTagV = 0L;\
                           }\
                           /* These are already equal if we caught. */\
                           /* They aren't if we didn't.             */\
                           vlEx_StackV = vlEx_LastFramePtrV;\
                         }

/*
 * Cleanup-without-catching-on-any-throw form.
 * DO_CLEANUP is only executed if there is a Throw.
 */
#define vlExCLEANUP_ON_SIGNAL  vlExCATCH (vlExANY_AND_ALL)
#define vlExDO_CLEANUP         vlExEXCEPTION
#define vlExEND_CLEANUP        vlExRESIGNAL; vlExEND_CATCH

/*
 * Unwind-protect form.
 * CLEANUP is executed whether or not there is a Throw.
 */
#define vlExUNWIND_PROTECT  {\
                              vlEx_COMMON (vlExANY_AND_ALL)\
                              {
#define vlExCLEANUP           }\
                              else {\
                                  vlEx_Caught = TRUE;\
                                  vlExDbg ();\
                              }
#define vlExEND_UNWIND        if (vlEx_Caught) vlExRESIGNAL;\
                              /* Don't need to worry about freeing  */\
                              /* vlExErrV here, because we only do  */\
                              /* that if we catch, and if we caught */\
                              /* we would have RESIGNAL'd by now.   */\
                              /* These are already equal if we caught. */\
                              /* But, we didn't...                     */\
                              vlEx_StackV = vlEx_LastFramePtrV;\
                            }

/*
 * Alternate one-liner (code-goes-within-the-macro) forms.
 */
#define vlExIF(code, handler) \
    vlExCATCH (vlExFAILURE) {code;} vlExEXCEPTION {handler;} vlExEND_CATCH
#define vlExCATCH2(tag, code, handler) \
    vlExCATCH (tag) {code;} vlExEXCEPTION {handler;} vlExEND_CATCH
#define vlExCLEANUP_ON_SIGNAL2(code, handler) \
    vlExCLEANUP_ON_SIGNAL {code;} vlExDO_CLEANUP {handler;} vlExEND_CLEANUP
#define vlExUNWIND_PROTECT2(code, cleanup) \
    vlExUNWIND_PROTECT {code;} vlExCLEANUP {cleanup;} vlExEND_UNWIND

/*
 * This throws the same exception that was just caught.
 */
#define vlExRESIGNAL            vlExThrow (vlExTagV, vlExErrV)

/*
 * Compatibility macros.
 */
#define vlExDECLARE_PROTECT  /* nada */
#define vlExPROTECT          vlExCATCH (vlExFAILURE)
#define vlExEND_PROTECT      vlExEND_CATCH
#define vlExRAISE(str)  vlExThrow2 (vlExFAILURE, "vcore", vlErrERROR, str)

/*
 * Routine contract verification macros.
 */
#if vlENV_DEBUG
#  define vlPRE_COND(expr, parmlist) \
      {if (!(expr)) vlEx_PreCond parmlist;}
#  define vlPOST_COND(expr, parmlist) \
      {if (!(expr)) vlEx_PostCond parmlist;}
#else
#  define vlPRE_COND(expr, parmlist)  /* nada */
#  define vlPOST_COND(expr, parmlist)  /* nada */
#endif

#endif /* vlEXCEPT_H */
