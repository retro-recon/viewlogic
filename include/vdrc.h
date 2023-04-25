/*
 * $Log
 */

#include "vllib.h"
#include "viewbase.h"

typedef struct vdrc *vdrcID;
typedef struct vdrcError *vdrcErrorID;

#define vdrcTestAUTO_ASSIGN (-1)

typedef enum {vdrcEVERY_OCCURRENCE, vdrcNO_REPEATS} vdrcTraversalFlagT;

/*\Header vdrcObjTypeT -- Enumeration for Viewbase objects

DESCRIPTION
     This specifies Viewbase objects, as recognized by DRC.  Note
     that groups and attributes are not in this list.

SEE ALSO
     vdrcN_OBJ_TYPES
*/
typedef enum {
    vdrcNET, vdrcSPN, vdrcSCH, vdrcCOM, vdrcPIN, vdrcSYM
} vdrcObjTypeT;

/*\Docpage vdrcN_OBJ_TYPES -- Constant for the ordinality of vdrcObjTypeT
*/
#define vdrcN_OBJ_TYPES 6

#if 0
typedef struct {
    char *block_name;
    int sheet_number;
} vbNameNumberT;
#endif

typedef struct {
    char *block_name;
    int sheet_number;
} vdrcNameNumberT;

typedef enum {vdrcScopeDESIGN, vdrcScopeLEVEL, vdrcScopeSHEET} vdrcScopeT;

extern vlPreferencesID vdrcPreferences vlARGS((vdrcID));
extern vlBoolT vdrcPrefModified vlARGS((vdrcID, const char *));
extern vlPreferencesID vdrcErrPreferences vlARGS((vdrcID));
extern GROUPS *vdrcTopLevelGroup vlARGS((vdrcID));
extern vdrcID vdrcCreate vlARGS((const char *, vlVoidProcT, vlPointerT, int *, char **));
extern vlLoopT vdrcForAllHierPins vlARGS((const char *, NETS *, vlLoopProcT, vlPointerT));
extern void vdrcReCheck vlARGS((vdrcID, vlSymTableID));
extern void vdrcReadDesign vlARGS((vdrcID));
extern void vdrcAddDesignTest vlARGS((vdrcID, vlVoidProcT, vlPointerT));
extern void vdrcAddObjTest vlARGS((vdrcID, vdrcObjTypeT, vlVoidProcT, vlPointerT));
extern void vdrcAddUpdateTest vlARGS((vdrcID, vlVoidProcT, vlPointerT));
extern void vdrcAddPrefsTest vlARGS((vdrcID, vlVoidProcT, vlPointerT));
extern void vdrcAddTerminate vlARGS((vdrcID, vlVoidProcT, vlPointerT));
extern vdrcScopeT vdrcGetScope vlARGS((vdrcID));
extern void vdrcAddEndOfTest vlARGS((vdrcID, vlVoidProcT, vlPointerT));
extern vlBoolT vdrcReadSheet vlARGS((vdrcID, const char *, int));
extern void vdrcReadSymbol vlARGS((vdrcID, const char *, int));
extern void vdrcErrorClear vlARGS((vdrcID, vdrcErrorID, vlPointerT, vdrcObjTypeT));
extern void vdrcReport vlARGS((vdrcID, vdrcErrorID, vlPointerT, vdrcObjTypeT, const char *));
extern void vdrcAddReport vlARGS((vdrcID, vlPointerT, vdrcObjTypeT, const char *));
extern void vdrcReportErr vlARGS((vdrcID, vlErrID));
extern const char *vdrcGroupName vlARGS((vdrcID));
extern const char *vdrcGroupPath vlARGS((vdrcID, GROUPS *));
extern GROUPS *vdrcFlat vlARGS((vdrcID));
extern void vdrcDestroy vlARGS((vdrcID));
extern const char *vdrcPrimaryDir vlARGS((vdrcID));
extern vlBoolT vdrcGroupInDir vlARGS((vdrcID, GROUPS *, const char *));
extern vdrcErrorID vdrcErrorCreate vlARGS((vdrcID, const char *, int, vlErrSeverityT, const char *));
extern void vdrcPrefDirty vlARGS((vdrcID));
extern void vdrcErrDirty vlARGS((vdrcID));
extern SYMBOLS *vdrcIgspnown vlARGS((SYMPINS *spn));

extern void vdrcUserInit vlARGS((vdrcID, int *, char **));

#define vdrcTIME_OP(msg, op) do { \
    long TO_t1, TO_t2; \
    vrFprintf (stderr, "%s...\n", msg); \
    vrFflush (stderr); \
    vsTimer (vsHUNDS, &TO_t1); \
    op; \
    vsTimer (vsHUNDS, &TO_t2); \
    vrFprintf (stderr, "...%s done, %g seconds\n", \
               msg, ((double) (TO_t2 - TO_t1)) / 100.0); \
} while (0)


typedef enum {vdrcNOTE, vdrcWARNING, vdrcERROR, vdrcDISABLED} vdrcSeverityT;
extern vlTypeSpecT vdrcSeverityTS;
