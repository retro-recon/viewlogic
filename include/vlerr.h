/*
 * $Id: vlerr.h,v 5.30.4.1 1995/10/17 20:42:04 cway Stab $
 *
 * Error Handling header.
 *
 * Copyright (c) 1991 by Viewlogic Systems, Inc.
 */


#ifndef vlERR_H
#define vlERR_H

#ifndef vlVARGS_H
#include "vlvargs.h"
#endif

/**********************************************************************/
/*\Docpage vlErrSeverityT -- Error severity enum type
 *
 * DESCRIPTION
 *      This type is used as a parameter to some vlErr routines, and
 *      describes the severity or intensity of an error condition.
 *      The available severities and their meanings are:
 *
 *          vlErrSTATUS   -- some status about what is going on
 *          vlErrNOTE     -- informational text only; no problem
 *          vlErrWARNING  -- something may be wrong, maybe not
 *          vlErrERROR    -- something is definitely wrong
 *          vlErrFATAL    -- we cannot possibly recover; NO RETURN
 *          vlErrINTERNAL -- something internal is screwy; NO RETURN
 *          vlErrDISABLED -- we won't do anything except log this
 */
/*
 * vlErrERROR is explicitly set to zero; accidents will happen,
 * someone will no doubt use a zero sometime...
 *
 * I'm not so sure anymore that the above was a good motivation.
 * With the vcPickEnum facility, enumerated types appear in a
 * picklist in ascending order, and this one looks really bogus.
 * Nota Bene:  once this is changed, *everything* needs to be
 * recompiled!
 */
typedef enum {
    vlErrSTATUS = 1,
    vlErrNOTE = 2,
    vlErrWARNING = 3,
    vlErrERROR = 0,
    vlErrFATAL = 4,
    vlErrINTERNAL = 5,
    vlErrDISABLED = 6
} vlErrSeverityT;

#define vlErrISSEVERITYCHAR(c)\
  ((c) == 'D' || (c) == 'S' || (c) == 'I' || (c) == 'W' || \
   (c) == 'E' || (c) == 'F' || (c) == 'Z')

/**********************************************************************/
/*\Docpage vlErrContextT -- Error context enum type
 *
 * DESCRIPTION
 *      This type is needed for a call to vlErrString to describe
 *      how vlErrString formats the report.  See vlErrString(man)
 *      for more details.
 */
typedef enum {
    vlErrSTDERR = 0,
    vlErrSTATUS_LINE = 1,
    vlErrALERT_BOX = 2,
    vlErrLOG_FILE = 3
} vlErrContextT;

#include "vltype.h"

/*
 * Types.
 */
typedef struct vlErrStream *vlErrStreamID;
typedef struct vlErr       *vlErrID;
extern vlVoidProcT  vlErrOutFuncV;

/*
 * Prototypes.
 */
extern void vlErrOut vlARGS((vlErrStreamID stream, vlErrID err));
extern void vlErrOutBuild vlVaARG4(vlErrStreamID stream, const char *location, vlMsgFileID msgfile, int msgnum);
extern void vlErrOutBuildVa vlARGS((vlErrStreamID stream, const char *location, vlMsgFileID msgfile, int msgnum, vlVaListT args));
extern void vlErrOut2 vlARGS((const char *app, vlErrSeverityT severity, const char *text));
extern void vlErrOut3 vlARGS((const char *location, const char *app, vlErrSeverityT severity, const char *text));
extern void vlErrReport vlARGS((vlErrStreamID stream, vlErrID err));
extern void vlErrReportBuild vlVaARG4(vlErrStreamID stream, const char *location, vlMsgFileID msgfile, int msgnum);
extern void vlErrReportBuildVa vlARGS((vlErrStreamID stream, const char *location, vlMsgFileID msgfile, int msgnum, vlVaListT args));
extern void vlErrReport2 vlARGS((const char *app, vlErrSeverityT severity, const char *text));
extern vlErrID vlErrCreate vlARGS((const char *location, const char *app, int num, vlErrSeverityT severity, const char *help_node, const char *text));
extern vlErrID vlErrCreate2 vlARGS((const char *app, vlErrSeverityT severity, const char *text));
extern void vlErrDestroy vlARGS((vlErrID report));
extern void vlErrDestroyTop vlARGS((vlErrID *, vlErrID));
extern vlErrID vlErrCopy vlARGS((vlErrID report));
extern vlErrID vlErrAppend vlARGS((vlErrID report, vlErrID sub_report));
extern void vlErrAppendText vlARGS((vlErrID report, const char *more_text));
extern vlErrID vlErrBuild vlVaARG3(const char *location, vlMsgFileID msgfile, int msgnum);
extern vlErrID vlErrBuildVa vlARGS((const char *location, vlMsgFileID msgfile, int msgnum, vlVaListT args));

extern vlErrID vlErrCreateFromString vlARGS((const char *report));
extern vlLoopT vlErrReadErrorFile vlARGS((FILE *pf, vlLoopProcT action_proc, vlPointerT data));

extern const char *vlErrString vlARGS((vlErrID err, vlErrContextT context));
extern char *vlErrStringAlloc vlARGS((vlErrID err, vlErrContextT context));
extern const char *vlErrApp vlARGS((vlErrID err));
extern const char *vlErrLocation vlARGS((vlErrID err));
extern const char *vlErrText vlARGS((vlErrID err));
extern int vlErrNum vlARGS((vlErrID err));
extern vlErrSeverityT vlErrSeverity vlARGS((vlErrID err));
extern vlLoopT vlErrLoop vlARGS((vlErrID err, vlLoopProcT actionproc, vlPointerT arg));
extern vlLoopT vlErrLoop2 vlARGS((vlErrID err, vlLoopProcT actionproc, vlPointerT arg1, vlPointerT arg2));

extern const char *vlErrSeverityToString vlARGS((vlErrSeverityT severity));
extern vlErrSeverityT vlErrStringToSeverity vlARGS((const char *str));
extern int vlErrSeverityToChar vlARGS((vlErrSeverityT severity));
extern vlErrSeverityT vlErrCharToSeverity vlARGS((int c));

extern vlErrStreamID vlErrStreamCreate vlARGS((void));
extern void vlErrStreamDestroy vlARGS((vlErrStreamID));
extern int vlErrStreamCount vlARGS((vlErrStreamID));
extern vlErrID vlErrStreamError vlARGS((vlErrStreamID, int));
extern vlErrSeverityT vlErrStreamBaddest vlARGS((vlErrStreamID));
extern void vlErrStreamSummary vlARGS((vlErrStreamID, int *, int *, int *, int *));
extern int vlErrStreamExitCode vlARGS((vlErrStreamID));

extern const char *vlErrLocationLine vlARGS((const char *, int));
extern const char *vlErrLocationFile vlARGS((const char *));
extern const char *vlErrLocationMessage vlARGS((const char *, int, int));
extern const char *vlErrLocationRoutine vlARGS((const char *));

/********************  PRIVATE!  PRIVATE!  PRIVATE!  ********************
 *
 * The stuff which follows is for internal use only!
 * If questioned, I will disavow all knowledge of it.
 */

/*
 * These are the possible actions that can be taken when an error
 * condition is encountered.  This list MUST STAY IN SYNC with
 * the list of strings in "vlerrcfg.c".
 */
typedef enum {
    statusLine = 0,
    alertBox = 1,
    disabled = 2
} vlErrActionT;
extern vlErrActionT vlErrActionV[];

/*
 * These are the possible styles of error reporting.
 */
typedef enum {
    vlErrTERSE = 0,
    vlErrVERBOSE = 1
} vlErrStyleT;
extern vlErrStyleT vlErrStyleV[];

extern void vlErrInit vlARGS((int *argcp, char **argv));
extern void vlErrGetPrefs vlARGS((void));
extern void vlErrFatal vlARGS((vlErrID));
extern void vlErrYell vlVaARG1(const char *format);
extern vlPointerT vlErrStreamGetAlert vlARGS((vlErrStreamID));
extern void vlErrStreamSetAlert vlARGS((vlErrStreamID, vlPointerT));
extern void vlErrStreamAdd vlARGS((vlErrStreamID, vlErrID));

extern void vlErrLogSetArgv0 vlARGS((char *argv0));
extern void vlErrLogKeepFiles vlARGS((int num_to_keep));
extern void vlErrLogOpenFile vlARGS((void));
extern void vlErrLogEnable vlARGS((vlBoolT yes_or_no));
extern vlBoolT vlErrLogIsEnabled vlARGS ((void));
extern void vlErrLog vlARGS((vlErrID err));
extern void vlErrSaveOnlyNewestFiles vlARGS((const char *wildcard, int files_to_be_kept));

extern const char *vlErr_String vlARGS((vlErrID err, vlErrStyleT output_style));

#endif
