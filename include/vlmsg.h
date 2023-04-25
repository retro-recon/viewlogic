/*
 * $Id: vlmsg.h,v 1.10.9.1 1995/10/17 20:40:17 cway Stab $
 *
 * Public header file for Message Files
 *
 * Copyright 1991 by Viewlogic Systems, Inc.
 */

#ifndef vlMsg_H
#define vlMsg_H

typedef struct vlMsgFileT *vlMsgFileID;

typedef struct vlMsgStringT {
    int StrSize;
    char *Str;
} vlMsgStringT;

extern vlMsgFileID vlMsgFile ();
extern vlMsgFileID vlMsgFileOpen vlARG5(const char *,
                                        const char *,
                                        const char *,
                                        const char *,
                                        const char *);
extern const char *vlMsgGetFilename vlARG1(vlMsgFileID);
extern void vlMsgFileClose vlARG1(vlMsgFileID);
extern int vlMsgGenerate vlVaARG4(vlMsgFileID, int, vlIntProcT, vlPointerT);
extern int vlMsgGenerateVa vlARG5(vlMsgFileID, int, vlIntProcT, vlPointerT, vlVaListT);
extern int vlMsgText vlARG4(vlMsgFileID, int, vlIntProcT, vlPointerT);

extern char *vlMsgAlloc vlVaARG2(vlMsgFileID, int);
extern const char *vlMsgStatic vlVaARG2(vlMsgFileID, int);
extern const char *vlMsgStaticVa vlARG3(vlMsgFileID, int, vlVaListT);
extern int vlMsgBuffer vlVaARG4(vlMsgFileID, int, char *, int);

extern int vlMsgCopyToBuffer vlARG2(vlMsgStringT *, char *);
extern int vlMsgCopyAlloc vlARG2(char **, char *);

/* this one is for testing purposes only */
extern void vlMsgDisplayCacheResults ();

#endif /* vlMsg_H */
