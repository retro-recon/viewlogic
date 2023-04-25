/*  $Revision: 2.55.3.1 $  $Date: 1995/10/17 20:43:29 $
 *
 *  Portable system library header file.
 *
 *  Copyright (c) 1986,1994 by Viewlogic Systems, Inc.
 */

/*\Section vslib -- Portability library
 */

#ifndef vsLIB_H
#define vsLIB_H

#ifndef vlLIB_H
#include "vllib.h"
#endif

#ifndef vlREGEXP_H
#include "vlregexp.h"
#endif

#include "vsdump.h"

/* Return Codes */
#define vsSUCCESS       0               /* Successful completion    */
#define vsINTERNAL      1               /* Internal error    */
#define vsINVPRM        2               /* Invalid parameter    */
#define vsINSDSK        3               /* Insufficient disk space  */
#define vsNEXIST        4               /* Item does not exist  */
#define vsEXISTS        5               /* Item already exists  */
#define vsNOPEN         6               /* Unable to open a file    */
#define vsNOACCESS      7               /* Unable to access the file    */

/* Return Codes For Loop Procedure */
#define vsSTART        -1               /* used to step through WDIR */
#define vsSTOP          0               /* Stop looping */
#define vsLOOP          1               /* Continue looping */

/* Attribute Values */
#define vsSECS          0               /* Seconds since January 1, 1970    */
#define vsHUNDS         1               /* Hundreths of seconds this month  */
#define vsDIR           2               /* File type is directory   */
#define vsFILE          3               /* File type is normal  */
#define vsBOTH          4               /* File type is either  */

/* String Buffer Sizes */
#if (!vlOS_UNIX && !vlOS_VMS && !vlOS_NT)
#define vsSIZEDEV       3               /* Maximum device specifier size */
#define vsSIZESPEC      65              /* Maximum file specifier size  */
#define vsSIZEPATH      65              /* Maximum path specifier size  */
#define vsSIZEFILE      9               /* Maximum file name size   */
#define vsSIZEEXT       4               /* Maximum extension size   */
#define vsSIZELOG       129             /* Buffer size for environment vars */
#endif

#if (vlOS_NT)
#define vsSIZEDEV    3                  /* Maximum device specifier size */
#define vsSIZESPEC  255                 /* Maximum file specifier size  */
#define vsSIZEPATH  255                 /* Maximum path specifier size  */
#define vsSIZEFILE  255                 /* Maximum file name size   */
#define vsSIZEEXT   255                 /* Maximum extension size   */
#define vsSIZELOG   255                 /* Buffer size for environment vars */
#endif

#if vlOS_VMS
#define vsSIZEDEV       255             /* Maximum device specifier size */
#define vsSIZESPEC      255             /* Maximum file specifier size  */
#define vsSIZEPATH      255             /* Maximum path specifier size  */
#define vsSIZEFILE      40              /* Maximum file name size   */
#define vsSIZEEXT       40              /* Maximum extension size   */
#define vsSIZELOG       255             /* Buffer size for environment vars */
#endif

#if vlOS_UNIX
#define vsSIZEDEV       1               /* Maximum device specifier size */
#define vsSIZESPEC      256             /* Maximum file specifier size  */
#define vsSIZEPATH      256             /* Maximum path specifier size  */
#define vsSIZELOG       2048            /* Buffer size for environment vars */
#if vlOS_SYSVR3
#define vsSIZEFILE      15              /* Maximum file name size   */
#define vsSIZEEXT       15              /* Maximum extension size   */
#define vsSYSVSIZEFILE  15              /* Maximum file name size   */
#define vsSYSVSIZEEXT   15              /* Maximum extension size   */
#else
#define vsSIZEFILE      256             /* Maximum file name size   */
#define vsSIZEEXT       256             /* Maximum extension size   */
#endif
#endif

#ifndef vsSYSVSIZEFILE
#define vsSYSVSIZEFILE  256             /* Maximum file name size   */
#define vsSYSVSIZEEXT   256             /* Maximum extension size   */
#endif

/* Macro for getting the environment variable WDIR (or WV$DIR) */
/* Define the actual environment variable for the current OS   */
#if vlOS_VMS
#define vsWDIR "WV$DIR"
#else
#define vsWDIR "WDIR"
#endif

/* vsCoreDump is here only to make it easy to find for portability reasons */
extern void vlF_NORETURN vsCoreDump vlARGS((void)) vlF_NORETURN_GCC_CHANGES_SUK;

extern int vsAppend vlARG2(char *, char *);
extern int vsConvPath vlARG2(vlCStringPtrT, vlStringPtrT);
extern int vsCopy vlARG2(const char *, const char *);
extern int vsCreate vlARG2(char *, int);
extern int vsCreateWithPath vlARG2(vlCStringPtrT, int);
extern int vsDelete vlARG2(const char *, int);
extern int vsDnpath vlARG2(vlStringPtrT, vlCStringPtrT);
extern int vsExists vlARG2(vlCStringPtrT, int);
extern int vsExists2 vlARG3(vlCStringPtrT, int, vlStringPtrT);
extern int vsGetdef vlARG1(char *);
extern int vsSetdef vlARG1(vlStringPtrT);
extern int vsGetini vlARG2(const char *, char *);
extern vlBoolT vsSetexedir vlARG1(const char *);
extern const char *vsExeDir vlARGS((void));
extern void vsLoopwdirs vlARGS((vlIntProcT));
extern vlLoopT vsLoopWdirs2 vlARGS((vlLoopProcT, vlPointerT));
extern vlLoopT vsWdirLoopSrchdirs2 vlARGS((vlLoopProcT proc, vlPointerT arg));
extern void vsWdirSetCompatibleVersion vlARGS((const char *version_string));
extern const char *vsStepWdirs vlARG2(int, int);
extern vlStringPtrT vsStepWdirsAlloc vlARG2(int, int);
extern const char *vsStepWdirsForName vlARG3(vlCStringPtrT, int, int);
extern vlStringPtrT vsStepWdirsForNameAlloc vlARG3(vlCStringPtrT, int, int);
extern int vsSrchExeDir vlARGS((char *, char *, char *, int, char *));
extern int vsSrchdirs vlARG3(const char *, int, char *);
extern int vsSrchwdirs vlARG3(const char *, int, char *);
extern int vsFindExeInPath vlARGS ((const char *, char *));
extern void vsResetWdirCache vlARGS ((void));
extern int vsInfo vlARG4(vlCStringPtrT, long *, long *, int *);
extern int vsDirForEachFile vlARGS((vlCStringPtrT, vlCStringPtrT, int,
                                    vlLoopProcT, vlPointerT));
extern int vsLoop vlARG3(char *, int, vlIntProcT);
extern int vsLoop2 vlARG4(char *, int, vlIntProcT, vlPointerT);
extern int vsLoopRegexp vlARG5(vlCStringPtrT, int, vlRegexpID, vlIntProcT,
                               vlPointerT);
extern int vsMakeExtValid vlARG1(char *);
extern int vsMakeValid vlARG1(char *);
extern int vsMerge vlARG5(char *, vlCStringPtrT, vlCStringPtrT,
                                  vlCStringPtrT, vlCStringPtrT);
extern int vsParse vlARG5(const char *, char *, char *, char *, char *);
extern void vsParseEx vlARG5(const char *, char *, char *, char *, char *);
extern int vsParse2 vlARG4(const char *, char *, char *, char *);
extern void vsPutenv vlARG2(char *, char *);
extern int vsRename vlARG2(char *, char *);
extern int vsRelPath vlARG1(char *);
extern int vsRelPath2 vlARG2(const char *, char *);
extern int vsTimer vlARG2(int, long *);
extern int vsTrnlog vlARG2(const char *, char *);
extern int vsUnique vlARG1(char *);
extern int vsUppath vlARG2(char *, char *);
extern vlBoolT vsValidFile vlARGS((char *));
extern int vsMakeValidFile vlARGS((char *));
extern vlBoolT vsValidExt vlARGS((char *));
extern int vsMakeValidExt vlARGS((char *));
extern vlBoolT vsValidSpec vlARGS((char *));
extern int vsMakeValidSpec vlARGS((char *));
extern int vsXfer vlARG2(FILE *, FILE *);
extern int vsGetport();
extern char *vsGetorigin();
extern int vsSetorigin vlARG1(char *);
extern int vsAbsPath vlARG1(vlStringPtrT);
extern int vsRelPath vlARG1(vlStringPtrT);
extern int vsAbsPath2 vlARG2(vlCStringPtrT, vlStringPtrT);
extern int vsAbsSysPath2 vlARG2(vlCStringPtrT, vlStringPtrT);
extern void vsSleepMs vlARGS((int));
extern void vsSleepSec vlARGS((int));
extern int vsGetUserId vlARGS(());
extern char *vsGetHostName vlARGS(());
extern const char *vsGetHardwarePlatform vlARGS((void));
extern vlCStringPtrT vsGetTerminalName vlARGS(( void ));
extern vlCStringPtrT vsGetPwdName vlARGS(( unsigned long uid ));
extern vlCStringPtrT vsGetLoginName vlARGS(( void ));

#if (vlOS_PCDOS || vlOS_286 || vlOS_386)
extern int vsWaitxms vlARG1(int);                /** KSM 7-23-90 **/
extern int vsWait1ms vlARG1(int);                /** KSM 7-23-90 **/
extern short int vsReadtmr();                    /** KSM 7-23-90 **/
extern int vsPeek vlARG4(int, int, char *, int);
extern int vsWait5xus vlARG1(int);               /** KSM 8-23-90 **/
extern int vsWait5us vlARG1(int);                /** KSM 8-23-90 **/
#if vlOS_386
extern int _386peek vlARG4(int,int,void *,int);   /** KSM 7-23-90 **/
#endif
#endif

#if vlOS_VMS
extern void vsInitp (/* FILEPARSE * */);
#else
extern void vsInitp vlARG1(char *);
#endif

#include "vsfile.h"

#if vlOS_WIN32
vlBoolT vsIsOSNT(void);
#endif

#endif /* vsLIB_H */
