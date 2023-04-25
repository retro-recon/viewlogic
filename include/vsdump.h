/*
 * $Id: vsdump.h,v 1.10.1.1 1995/10/17 20:44:25 cway Stab $
 */

#ifndef vsDUMP_H
#define vsDUMP_H

#if (vlOS_SUNOS4 || vlOS_HPUX || vlOS_ULTRIX)
#define vsDumpENABLED  0
#endif
#if (vlOS_SUNOS4)
#define vsDumpENABLED_FOR_GRAPHICS 0
#endif

/* Parameters to vsDumpCallOnRead, vsDumpCallOnWrite */
typedef enum {
    vsDumpCALL_BEFORE,
    vsDumpCALL_AFTER,
    vsDumpCALL_BEFORE_AND_AFTER
} vsDumpCallSequenceT;
typedef vlBoolT (* vsDumpActionProcT) vlARGS((vlPointerT, vsDumpCallSequenceT));

extern vlBoolT vsDumpWrite vlARGS((const char *, const char *));
extern vlBoolT vsDumpRead vlARGS((const char *, const char *));

#if vsDumpENABLED

extern void vsDumpCallOnWrite vlARGS((vsDumpActionProcT, vlPointerT, vsDumpCallSequenceT));
extern void vsDumpCallOnRead vlARGS((vsDumpActionProcT, vlPointerT, vsDumpCallSequenceT));

#else /* vsDumpENABLED */

#define vsDumpCallOnWrite(a,b,c)
#define vsDumpCallOnRead(a,b,c)

#endif /* vsDumpENABLED */

#endif /* vsDUMP_H */
