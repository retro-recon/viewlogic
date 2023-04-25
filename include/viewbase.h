/*
*
*   Name: VIEWBASE.H
*
*   Facility: VIEWBASE
* 
*   Functional Description: 
*       Defines types and declarations for the routines in
*       VIEWBASE.LIB.  This file is a concatenation of the
*       header files IWIR.H, ACCESS.H, IPA.H, MISC.H, and IXEVAL.H
*       IWOAT.H.
*       
*   Environment:
*       DOS, VMS, UNIX
*     
*   Modified by: 
*   Who     Version     When        What
*   MPC     1.00        01/87       Original coding.
*   MPC     3.40        05/89       Added prototype macros
*   WAB     5.01        01/92       Added iwoat.h to end of file.
*   
*   Copyright (c) 1987 by Viewlogic Systems, Inc.
*
*/

/* if not defined, then function prototyping is enabled */
#ifndef COMP_PROTO
#define COMP_PROTO      1       /* Compiler supports function prototypes */
#endif

#ifndef vlARG1                    /* Create prototype macros */
# if COMP_PROTO
#  define vlARG1(a)                 (a)
#  define vlARG2(a,b)               (a,b)
#  define vlARG3(a,b,c)             (a,b,c)
#  define vlARG4(a,b,c,d)           (a,b,c,d)
#  define vlARG5(a,b,c,d,e)         (a,b,c,d,e)
#  define vlARG6(a,b,c,d,e,f)       (a,b,c,d,e,f)
#  define vlARG7(a,b,c,d,e,f,g)     (a,b,c,d,e,f,g)
#  define vlARG8(a,b,c,d,e,f,g,h)   (a,b,c,d,e,f,g,h)
# else
#  define vlARG1(a)                 ()
#  define vlARG2(a,b)               ()
#  define vlARG3(a,b,c)             ()
#  define vlARG4(a,b,c,d)           ()
#  define vlARG5(a,b,c,d,e)         ()
#  define vlARG6(a,b,c,d,e,f)       ()
#  define vlARG7(a,b,c,d,e,f,g)     ()
#  define vlARG8(a,b,c,d,e,f,g,h)   ()
# endif
#endif


/**  
*
*   Name:   IWIR.H
* 
*   Facility:  VIEWBASE
*
*   Functional Description: 
*       Defines the types and declarations of the WIR file reader.
*   
*   Author:  
*       Lorne Cooper -- July, 1986
*    
*   Modified by:
*   Who    Version When        What
*   LJC    0.01    7/20/86     Original Coding.
*   JRM    0.02    10/14/86    Added coding conventions.
*   MPC    0.10    11/10/86    Added group Symbol and Schematic sheets.
*   WAB    4.10    10/31/90    Added definitions for directory types.	
*   SMW    4.10    07/07/91    Added refsym sympin component.  Specific to the
*                              VIEWGEN compiler switch.
*
*   Copyright (c) 1986 by Viewlogic Systems, Inc.
*
**/

/* Definitions for Directory Types */
#define ID_PRIMARY      0
#define ID_WRITABLE     1
#define ID_READONLY     6
#define ID_MEGAFILE     11
#define ID_NONE         -1

/* Definitions for Data Structure Types */
#define VB_PINS         1
#define VB_NETS         2
#define VB_COMPONENTS   3
#define VB_SCHEMATICS   4
#define VB_SYMPINS      5
#define VB_SYMBOLS      6
#define VB_GROUPS       7
#define VB_ATTRIBUTES   8
#define VB_LIBS         9
#define VB_HETERO_SYMSETS         10
#define VB_HETERO_SYMS  11
#define VB_HETERO_PINS  12
#define VB_UNUSABLE     13


/* Definitions for Component symtype's */
#define UNKNOWN_TYPE   -1
#define MODULE_TYPE     0
#define COMPOSITE_TYPE  1
#define PIN_TYPE        2
#define PLD_TYPE        3
#define PLDCOMP_TYPE    4

/* Types of nets ... Pins have a corresponding field that is always > 0 */
#define LOCAL_NET       0
#define GLOBAL_NET     -1

/* Bit masks for Error Reporting Routines */
#define INFO            1
#define WARNING         2
#define ERROR           4
#define NOINC           8   /* don't increment count (for 2 part msgs) */

/* Database flatten options */
#define DB_FLATTEN      0
#define UPDATE_GLOBALS  1

#ifndef vlSymTAB_H
typedef struct symtable *vlSymTableID;
#endif
typedef vlSymTableID NET_TABLE_ID;
typedef vlSymTableID GRP_TABLE_ID;
typedef vlSymTableID COM_TABLE_ID;
GRP_TABLE_ID Igrp_table;


typedef struct libsxxx
{
    int            otype;
    void           *vfplib;
    char           *name;    /* Path name */
    struct libsxxx *next;
} LIBS;
 
typedef enum
{
    VBERR_NO_ERROR = 0,
    VBERR_UNUSABLE_OID,
    VBERR_INVALID_OBJECTTYPE,
    VBERR_READ_ONLY,
    VBERR_OBJECT_ALREADY_EXISTS,
    VBERR_INVALID_NAME,
    VBERR_ILLEGAL_OPERATION,
    VBERR_NAME_IN_USE,
    VBERR_UNUSABLE_PORT_OID,
    VBERR_INVALID_PORT_TYPE,
    VBERR_PORT_ALREADY_ATTACHED,
    VBERR_SCALAR_BUNDLE_ATTACHMENT,
    VBERR_CROSS_VIEW_OPERATION,
    VBERR_UNUSABLE_PORTINST_OID,
    VBERR_INVALID_PORTINST_TYPE,
    VBERR_PORTINST_ALREADY_ATTACHED,
    VBERR_PORT_NOT_ATTACHED,
    VBERR_PORTINST_NOT_ATTACHED,
    VBERR_UNUSABLE_DESCRIBER_OID,
    VBERR_INVALID_DESCRIBER_TYPE,
    VBERR_INVALID_SHEETNUM,
    VBERR_DESCRIBER_RECURSION,
    VBERR_INVALID_DIRECTION,
    VBERR_INVALID_VALUE,
    VBERR_INTERNAL_SYSTEM_ERROR,
    VBERR_INVALID_OWNER,
    VBERR_INCORRECT_PORTINST_COUNT,
    VBERR_INST_ALPHA_ORDER,
    VBERR_INST_DUPLICATE_NAMES,
    VBERR_NET_ALPHA_ORDER,
    VBERR_NET_DUPLICATE_NAMES,
    VBERR_PROP_ALPHA_ORDER,
    VBERR_LIB_OPEN_FAILED,
    VBERR_LIB_ALREADY_OPEN,
    VBERR_OBJECT_NOT_FOUND,
    VBERR_DISK_FULL,
    VBERR_INVALID_ACCESSMODE,
    VBERR_MAX_ERROR
} vbErrorT;
typedef struct vbobjxxx
{
    int otype;
} VBOBJECT;

/* Structure Definitions */

/* --- ATTRIBUTES --- */
typedef struct attsxxx {
    int                 otype;      /* Object type */
    struct vbobjxxx     *owner;     /* Owner */
    char                *name;      /* Attribute name */
    char                *value;     /* Attribute value */
    struct attsxxx      *next;      /* Next attribute */
} 
ATTRIBUTES;

/* --- PINS --- 
*   The size of the PINS structure is key to the total database size, 
*   and is about 40% of the database.
*
*   The pins off the component are defined as an array.  The first pin
*   record in the array (pins[0]) has a pointer to the owning component 
*   (in the pins[0].atts field).  The component pins are in array 1 through 
*   "numpins", ("numpins" is found in the symbol record).  This in-elegance
*   is added for the sake of great gain in storage efficiency ... 
*   otherwise, each pin must have an "owner_component" field (4 bytes).
*
*   The pins off a net are on a ring to eliminate the "owner_net" back 
*   pointer (4 bytes).  The "next" pointer of the last pin-off-the-net 
*   points back to the net record.  The net "type" field distinguishes 
*   the net record from the pin record.  (The pin "ordernum" field ranges 
*   1 ... "numpins", while the net "type" field is GLOBAL_NET or LOCAL_NET.)
*/
typedef struct pinsxxx {
    int                 otype;      /* Object type */
    short int           ordernum;   /* Ordinal pin number */
    ATTRIBUTES          *atts;      /* Pin attributes */
    struct pinsxxx      *netpin;    /* Next pin the same net */
    void                *tag;       /* User tag */
} 
PINS;

/* --- NETS --- */
typedef struct netsxxx {
    int                 otype;      /* Object type */
    short int           type;       /* Global or Local Net */
    char                *name;      /* Workview assigned label */
    ATTRIBUTES          *atts;      /* Net attributes */
    PINS                *pins;      /* Pins on this net (ring) */
    struct groupxxx     *owner;     /* Owner group of this net */
    struct netsxxx      *next;      /* Next net on this group */
    void                *tag;       /* User tag */
} 
NETS;

/* --- COMPONENTS --- */
typedef struct compxxx {
    int                 otype;      /* Object type */
    char                *name;      /* Workview assigned label */
    ATTRIBUTES          *atts;      /* Component attributes */
    PINS                *pins;      /* Array of instance pins (PINORDER'd) */
    struct schemxxx     *sheet;     /* Schematic sheet instantiated on */
    struct symbxxx      *symbol;    /* Symbol representation */
    struct compxxx      *next;      /* Next component on this sheet */
    void                *tag;       /* User tag */
} 
COMPONENTS;

/* --- SCHEMATICS --- */
typedef struct schemxxx {
    int                 otype;      /* Object type */
    short int           sheetnum;   /* Schematic sheet number */
    ATTRIBUTES          *atts;      /* Schematic attributes */
    COMPONENTS          *comp;      /* Components on this sheet */
    COMPONENTS          *lastcomp;  /* Last component in comp list */
    struct groupxxx     *owner;     /* Owner group of this schem sheet */
    struct schemxxx     *next;      /* Next schematic sheet in group */
    void                *tag;       /* User tag */
    COM_TABLE_ID        com_table;  /* This schematic's com table */
}
SCHEMATICS;

/* --- SYMPINS --- */
typedef struct sympinxxx {
    int                 otype;      /* Object type */
    struct symbxxx      *owner;     /* Owner symbol */
    char                *name;          /* User assigned label */
    ATTRIBUTES          *atts;          /* Symbol pin attributes */
    NETS                *internalnet;   /* Net that connects to this pin */
    struct sympinxxx    *next;          /* Next symbol pin (in PINORDER) */
    void                *tag;           /* User tag */
    char                *refsym;        /* Symbol name SMW 11/1/90 */
}
SYMPINS;

/* --- SYMBOLS --- */
typedef struct symbxxx {
    int                 otype;      /* Object type */
    short int           sheetnum;   /* Symbol sheet number */
    ATTRIBUTES          *atts;      /* Symbol attributes */
    SYMPINS             *pins;      /* Symbol pins in PINORDER order */
    short int           symtype;    /* Module, composite, pin, etc. */
    short int           numpins;    /* Number of pins on symbol */
    struct groupxxx     *owner;     /* Owner group of this symbol */
    struct symbxxx      *next;      /* If more than 1 symbol representation */
    void                *tag;       /* User tag */
} 
SYMBOLS;

/* --- GROUPS --- */
typedef struct groupxxx {
    int                 otype;      /* Object type */
    LIBS                *owner;     /* Owner library */
    char                *name;      /* Group name */
    SCHEMATICS          *sheets;    /* Group schematic sheets */
    SYMBOLS             *symbols;   /* Group symbols */
    NETS                *nets;      /* Group nets */
    NETS                *lastnet;   /* Last net in nets list */
    struct groupxxx     *next;      /* Next group (NULL if top_proj) */
    void                *tag;       /* User tag */
    NET_TABLE_ID        net_table;  /* This group's net table */
}
GROUPS;

/*
*    Hetero Data Structures.
*/

typedef struct hetero_syms
{
    int                   otype;         /* VB_HETERO_SYMS */
    GROUPS                *grpp;         /* Pointer to corres part grp */
    char                  *sym_name;     /* Partial hetero grp name */
    struct hetero_syms    *next;
} HETERO_SYMS;

typedef struct hetero_pins
{
    int                   otype;         /* VB_HETERO_PINS */
    SYMPINS               *spnp;         /* Pointer to corres part sympin */
    char                  *pin_name;     /* Name of pin */
    char                  *pin_dir;      /* Pin direction string */
    struct hetero_pins    *next;
} HETERO_PINS;

typedef struct hetero_symsets
{
    int                   otype;         /* VB_HETERO_SYMSETS */
    char                  *hetero_name;  /* Combined symbol name */
    HETERO_SYMS           *hetero_syms;  /* List of partial symbols */
    HETERO_PINS           *hetero_pins;  /* Pinorder - name, direction */
    GROUPS                *grpp;         /* Combined group */
    int                   done;          /* Combining done for the set */
    struct hetero_symsets *next;
} HETERO_SYMSETS;

HETERO_SYMSETS *Ihetset;
 

/*
*   To assist in maintainance and readability, the following convention
*   for declaring pointers to the wir structures is offered.
*
*       ATTRIBUTES  *attp;          pointer to attribute
*       PINS        *pinp;          pointer to component pin
*       NETS        *netp;          pointer to net
*       COMPONENTS  *comp;          pointer to component
*       SCHEMATICS  *schp;          pointer to schematic
*       SYMPINS     *spnp;          pointer to symbol pin
*       SYMBOLS     *symp;          pointer to symbol
*       GROUPS      *grpp;          pointer to group
*/

extern GROUPS       *iw1level vlARG1(char *);
extern GROUPS       *iw1sheet vlARG2(char *, int);
extern GROUPS       *iw1sht1lev vlARG2(char *, int);
extern void          iwmsgwv vlARG2(int, char *);
extern COMPONENTS   *iwallcomp vlARG2(GROUPS *, COMPONENTS *);
extern char         *iwalloc vlARG1(unsigned int);
extern int           iwrecache vlARG1(void);
extern int           iwenablecache vlARG1(int);
extern int           iwchktime vlARG1(void);
extern void          iwcleanup vlARG1(void);
extern int           iwexpbus vlARG1(void);
extern void          iwfinish vlARG1(void);
extern GROUPS       *iwflat vlARG2(GROUPS *, unsigned int);
extern FILE         *iwfopen vlARG2(char *, char *);
extern FILE         *iwvarfopen vlARG1(char *);
extern void          iwfree vlARG1(char *);
extern void          iwreplacegblnet vlARG2(NETS *, NETS *);
extern void          iwdelgblnet vlARG2(NETS *, GROUPS *);
extern void          iwaddgblnet vlARG2(NETS *, GROUPS *);
extern void          iwgbldel vlARG2(NETS *, GROUPS *);
extern void          iwgblfree vlARG1(void);
extern GROUPS       *iwgblgrp vlARG2(NETS *, GROUPS *);
extern void          iwgblinit vlARG1(void);
extern NETS         *iwgblnet vlARG1(NETS *);
extern int           iwgblren vlARG1(GROUPS *);
extern GROUPS       *iwgetgrp vlARG1(GROUPS *);
extern char         *iwgetlevel vlARG1(ATTRIBUTES *);
extern GROUPS       *iwgroup vlARG1(char *);
extern int           iwinit vlARG1(void);
extern void          iwmsgclose vlARG1(void);
extern int           iwmsgcount vlARG1(int);
extern void          iwmsginc vlARG1(int);
extern void          iwmsgout (/* variable number of arguments */);
extern void          iwmsghndlr (/* variable number of arguments */);
extern char          *iwmsggen (/* variable number of arguments */);
extern void          iwregmsgdflt vlARG1(void);
extern void          iwmsgsetup vlARG3(int, FILE *, char *);
extern void          iwopenmsg vlARG1(char *);
extern void          iwsetini vlARG1(char *);
extern void          iwsetlevel vlARG1(char *);
extern int           iwsortpins vlARG2(SYMBOLS *, char *);
extern void          iwsrchmsg vlARG1(char *);
extern void          iwsrchwir vlARG1(char *);
extern void          iwstatline vlARG2(char *, int);
extern void          iwstatln vlARG1(FILE *);
extern void          iwstatmode vlARG1(int);
extern void          iwstatus vlARG3(char *, int, int);
extern int           iwsysatt vlARG1(char *);
extern void          iwufts vlARG3(char *, int, char *);
extern void          iwupdate vlARG1(char *);
extern void          iwupdat2 vlARG3(int, const char **, int *);
extern void          iwusedisk vlARG1(void);
extern void          iwusehash vlARG1(void);
extern char         *iwversion vlARG1(void);
extern char         *iggrplnm vlARG1(GROUPS *);
extern char         *iggrpnam vlARG1(GROUPS *);
extern int           iglibdir vlARG1(char *);
extern int           igdirnxt vlARG1(void);
extern int           igdirtyp vlARG1(void);
extern char         *igdirnam vlARG1(void);
extern char         *iwparselib vlARG1(char *);
extern char         *iwparsename vlARG1(char *);
extern int           iwsettag vlARG3(void *, int, void *);
extern void         *iwgettag vlARG3(void *, int, int *);
extern void         iwdeltag vlARG4(void *, int, void (* deltagfunc) (void *, void *), void *);
extern void         iwregmsghndlr vlARG2(void (*outfunc) (void *, char *), void *);
extern int           iwnstrbrk vlARG2(char *, char *);
extern char         *iwstrtok vlARG3(int, char *, char *);
extern int           iwallupc vlARG1(char *);
extern void          iwhetero vlARG1 (void);
extern void          iwcombine_hetero vlARG1 (int);
extern void          iwnochk_writable vlARG1 (int);

/* PUBLIC ROUTINES -- TO MODIFY VIEWBASE DATA STRUCTURES */
extern LIBS       *imclib    vlARG2(char *, vbErrorT *);
extern GROUPS     *imclibgrp vlARG3(LIBS *, char *, vbErrorT *);
extern SYMBOLS    *imcgrpsym vlARG3(GROUPS *, char *, vbErrorT *);
extern SCHEMATICS *imcgrpsch vlARG3(GROUPS *, int, vbErrorT *);
extern void        imsobjnam vlARG3(VBOBJECT *, char *, vbErrorT *);
extern void        imsnetnam vlARG3(NETS *, char *, vbErrorT *);
extern void        imscomnam vlARG3(COMPONENTS *, char *, vbErrorT *);
extern void        imsattnam vlARG3(ATTRIBUTES *, char *, vbErrorT *);
extern void        imanetspn vlARG3(NETS *, SYMPINS *, vbErrorT *);
extern void        imanetpin vlARG3(NETS *, PINS *, vbErrorT *);
extern void        imdnetspn vlARG3(NETS *, SYMPINS *, vbErrorT *);
extern void        imdnetpin vlARG3(NETS *, PINS *, vbErrorT *);
extern COMPONENTS *imcgrpcom vlARG6(GROUPS *, int, SYMBOLS *, SYMBOLS *, char *, vbErrorT *);
extern NETS       *imcgrpnet vlARG4(GROUPS *, SYMBOLS *, char *, vbErrorT *);
extern SYMPINS    *imcsymspn vlARG5(SYMBOLS *, char *, int, char *, vbErrorT *);
extern void        imsnettyp vlARG3(NETS *, int, vbErrorT *);
extern ATTRIBUTES *imcobjatt vlARG3(VBOBJECT *, char *, vbErrorT *);
extern ATTRIBUTES *imcobjdupatt vlARG3(VBOBJECT *, char *, vbErrorT *);
extern void        imsattval vlARG3(ATTRIBUTES *, char *, vbErrorT *);

extern void        imdgrp    vlARG2 (GROUPS *, vbErrorT *);
extern void        imdschcom vlARG3 (SCHEMATICS *, COMPONENTS *, vbErrorT *);


/* PUBLIC ROUTINES -- MISC TO PURGE/SAVE/DESTROY LIB/VIEW */
extern void        imwlibsave vlARG2(LIBS *, vbErrorT *);
extern void        imwgrpsave vlARG2(GROUPS *, vbErrorT *);
extern void        imwlibpurge vlARG2(LIBS *, vbErrorT *);
extern void        imwgrppurge vlARG2(GROUPS *, vbErrorT *);
extern void        imwobjdestroy vlARG2(VBOBJECT *, vbErrorT *);

/* PUBLIC ROUTINES -- TO CHECK VIEWBASE DATA STRUCTURES */
extern int         iwcheck vlARG1(vbErrorT *);
extern int         iwcheckgrp vlARG2(GROUPS *, vbErrorT *);

/* NON-PUBLIC ROUTINES -- TO CHECK VIEWBASE DATA STRUCTURES */
extern int         i_check_otype     vlARG3(VBOBJECT *, int, vbErrorT *);
extern int         i_check_att       vlARG3(ATTRIBUTES *,VBOBJECT *,vbErrorT *);
extern int         i_check_owner     vlARG3(VBOBJECT *, VBOBJECT *, vbErrorT *);
extern int         i_check_name      vlARG2(char *, vbErrorT *);
extern int         i_check_spnnet    vlARG2(SYMPINS *, vbErrorT *);
extern int         i_check_comspncnt vlARG2(COMPONENTS *, vbErrorT *);
extern int         i_check_pinspn    vlARG2(PINS *, vbErrorT *);
extern int         i_check_comnames  vlARG2(COMPONENTS *, vbErrorT *);
extern int         i_check_netnames  vlARG2(NETS *, vbErrorT *);
extern int         i_check_attnames  vlARG2(ATTRIBUTES *, vbErrorT *);
extern int         i_check_spnnames  vlARG2(SYMPINS *, vbErrorT *);
extern int         i_check_writable  vlARG2(VBOBJECT *, vbErrorT *);
extern int         i_check_direction vlARG1(char *);
extern int         i_check_recgrp    vlARG3(GROUPS *, GROUPS *, int *);
extern int         i_check_usable    vlARG1(VBOBJECT *);

/* PUBLIC ROUTINES -- MISCELLANEOUS */
extern LIBS       *iggrpown  vlARG1(GROUPS *);
extern char       *iglibnam  vlARG1(LIBS *);
extern ATTRIBUTES *igobjatt  vlARG1(VBOBJECT *);
extern int         igobjtyp  vlARG1(VBOBJECT *);
extern SYMBOLS    *igspnown  vlARG1(SYMPINS *);
extern VBOBJECT   *igattown  vlARG1(ATTRIBUTES *);
extern char       *igobjnam  vlARG1(VBOBJECT *);
extern LIBS       *iwgetlibs  vlARG1(LIBS *);
extern LIBS       *iwlibopen vlARG3(char *, char *, vbErrorT *);


/* NON-PUBLIC ROUTINES -- MISCELLANEOUS */
extern void        iwaddlibs         vlARG1(void);
extern void        sort_obj_atts     vlARG1(VBOBJECT *);
extern vbErrorT    iwgrpwrite        vlARG1(GROUPS *);

/*
*
*   Name: ACCESS.H
*
*   Facility: VIEWBASE
* 
*   Functional Description: 
*
*       External declarations and macro definitions for VIEWBASE
*       Database Access Routines.
*
*   Author:  
*       Brian Kelly         -- November, 1986
*
*   Modified by: 
*   Who            Version  When      What
*   BKK            0.90     12/01/86  Original Coding
*   MPC            0.91     01/06/87  Added NULL pointer protection.
*   MPC            1.31     09/19/87  Added extern def for ignetspn().
*   MPC            1.40     10/12/87  Modified Null Test to work with High-C.
*   MPC            3.49     08/04/89  Added #undef NULL, #define NULL 0L
*   
*   Copyright (c) 1986 by Viewlogic Systems, Inc.
*
*/

/* ---------------------------------------------------------------------
*
*   Naming conventions for macros:
*
*   Character:  1   = i (reserved letter for GPI routines)
*               2   = f (find), g (get)
*               3-5 = structure
*               6-8 = field
*
*   Structure and field acronyms:
*
*      grp  =  GROUPS *      (ptr to group struct)
*      sym  =  SYMBOLS *     (ptr to symbol struct)
*      sch  =  SCHEMATICS *  (ptr to schematic struct)
*      com  =  COMPONENTS *  (ptr to component struct)
*      net  =  NETS *        (ptr to net struct)
*      spn  =  SYMPINS *     (ptr to symbol pin struct)
*      pin  =  PINS *        (ptr to component pin struct)
*      att  =  ATTRIBUTES *  (ptr to attribute struct)
*      sat  =  ATTRIBUTES *  (ptr to component/symbol attribute)
*      pat  =  ATTRIBUTES *  (ptr to component/symbol pin attribute)
*      pth  =  char *        (ptr to hierarchical path name)
*      typ  =  integer       (net or symbol type)
*      nam  =  char *        (ptr to name)
*      val  =  char *        (ptr to value)
*      ord  =  integer       (pin order number)
*      num  =  integer       (pin/sheet number)
*      own  =  <pointer>     (ptr to owner of structure)
*      sht  =  integer       (sheet number)
*      nxt  =  <pointer>     (ptr to next structure in linked list)
*      nnx  =  NETS *        (ptr to next pin in pins-off-net list)
*      cnx  =  PINS *        (ptr to next pin in pins-off-component list)
*
* --------------------------------------------------------------------- */

/* the following redefinition is required to make the macros work */
/* with High-C and Vax-C, (where NULL is defined as ((void *) 0) ) */

#if !(vlHW_MIPS && vlOS_SYSVR4)
#ifdef NULL
# undef NULL
# define NULL 0L
#endif
#endif


/* --- NULL pointer test macros --- */
#define NTP(ptr,field) (((ptr) == NULL)? (NULL): (field))
#define NTI(ptr,field) (((ptr) == NULL)? (0):    (field))

/* --- GROUPS macros --- */
#define igfullnam(p) NTP((p),(p)->name)     /* Get group name */
#define iggrpnet(p) NTP((p),(p)->nets)     /* Get first group net */
#define iggrpsym(p) NTP((p),(p)->symbols)  /* Get first group symbol */
#define iggrpsch(p) NTP((p),(p)->sheets)   /* Get first group schematic */

/* --- NETS macros --- */
#define ignetnam(p) NTP((p),(p)->name)     /* Get net name */
#define ignettyp(p) NTI((p),(p)->type)     /* Get net type */
#define ignetatt(p) NTP((p),(p)->atts)     /* Get first net attribute */
#define ignetown(p) NTP((p),(p)->owner)    /* Get owner group of net */
#define ignetnxt(p) NTP((p),(p)->next)     /* Get next net */

/* --- SYMBOL macros --- */
#define igsymsht(p) NTI((p),(p)->sheetnum) /* Get symbol sheet number */
#define igsymtyp(p) NTI((p),(p)->symtype)  /* Get symbol type */
#define igsymatt(p) NTP((p),(p)->atts)     /* Get first symbol attribute */
#define igsymspn(p) NTP((p),(p)->pins)     /* Get first symbol pin */
#define igsymnum(p) NTI((p),(p)->numpins)  /* Get number of symbol pins */
#define igsymown(p) NTP((p),(p)->owner)    /* Get owner group of symbol */
#define igsymnxt(p) NTP((p),(p)->next)     /* Get next symbol */

/* --- SCHEMATIC macros --- */
#define igschsht(p) NTI((p),(p)->sheetnum) /* Get schematic sheet number */
#define igschcom(p) NTP((p),(p)->comp)     /* Get first schematic component */
#define igschatt(p) NTP((p),(p)->atts)     /* Get first schematic attribute */
#define igschown(p) NTP((p),(p)->owner)    /* Get schematic's owner group */
#define igschnxt(p) NTP((p),(p)->next)     /* Get next schematic */

/* --- COMPONENT macros --- */
#define igcomuid(p) NTP((p),(p)->name)     /* Get component unique id */
#define igcomatt(p) NTP((p),(p)->atts)     /* Get first component attribute */
#define igcomsym(p) NTP((p),(p)->symbol)   /* Get component's reference sym */
#define igcomown(p) NTP((p),(p)->sheet)    /* Get component's owner schem */
#define igcomnxt(p) NTP((p),(p)->next)     /* Get next component */

/* --- SYMBOL PIN macros --- */
#define igspnnam(p) NTP((p),(p)->name)     /* Get symbol pin name */
#define igspnatt(p) NTP((p),(p)->atts)     /* Get first sym pin attribute */
#define igspnnxt(p) NTP((p),(p)->next)     /* Get next symbol pin */
#define igspnnet(p) NTP((p),(p)->internalnet) /* Get internal net off pin */

/* --- COMPONENT PIN macros --- */
#define igpinord(p) NTI((p),(p)->ordernum) /* Get ordinal number of pin */
#define igpinatt(p) NTP((p),(p)->atts)     /* Get first pin attribute */

/* --- ATTRIBUTE macros --- */
#define igattnam(p) NTP((p),(p)->name)     /* Get attribute name */
#define igattval(p) NTP((p),(p)->value)    /* Get attribute value */
#define igattnxt(p) NTP((p),(p)->next)     /* Get next attribute */

/* --- CHECK-vlPointerT macro --- */
#define ICHKPTR(p)  { if ((p) == NULL) iwmsgwv(ERROR, "Unexpected NULL pointer"); }

/* Function Prototypes */

extern ATTRIBUTES   *ifattatt vlARG2(char *, ATTRIBUTES *);
extern ATTRIBUTES   *ifupattatt vlARG2(char *, ATTRIBUTES *);
extern COMPONENTS   *ifcomcom vlARG2(char *, COMPONENTS *);
extern COMPONENTS   *ifcompth vlARG2(char *, GROUPS *);
extern ATTRIBUTES   *ifcospat vlARG2(char *, PINS *);
extern ATTRIBUTES   *ifcossat vlARG2(char *, COMPONENTS *);
extern GROUPS       *ifgrpgrp vlARG1(char *);
extern NETS         *ifnetnet vlARG2(char *, NETS *);
extern NETS         *ifupnetnet vlARG2(char *, NETS *);
extern NETS         *ifnetpth vlARG2(char *, GROUPS *);
extern PINS         *ifpinpin vlARG2(int, PINS *);
extern SCHEMATICS   *ifschsch vlARG2(int, SCHEMATICS *);
extern SYMPINS      *ifspnspn vlARG2(char *, SYMPINS *);
extern SYMBOLS      *ifsymsym vlARG2(int, SYMBOLS *);
extern char         *igcomnam vlARG1(COMPONENTS *);
extern PINS         *igcompin vlARG1(COMPONENTS *);
extern ATTRIBUTES   *igcospat vlARG2(PINS *, ATTRIBUTES *);
extern ATTRIBUTES   *igcossat vlARG2(COMPONENTS *, ATTRIBUTES *);
extern COMPONENTS   *iggrpcom vlARG2(GROUPS *, COMPONENTS *);
extern PINS         *ignetpin vlARG1(NETS *);
extern SYMPINS      *ignetspn vlARG1(NETS *);
extern PINS         *igpincnx vlARG1(PINS *);
extern NETS         *igpinnet vlARG1(PINS *);
extern PINS         *igpinnnx vlARG1(PINS *);
extern COMPONENTS   *igpinown vlARG1(PINS *);
extern SYMPINS      *igpinspn vlARG1(PINS *);

/*
*
*   Name: IPA.H
*
*   Facility: VIEWBASE
* 
*   Functional Description: 
*       Macro definitions and external declarations for the
*       Parameterized Attribute routines.
*
*   Author:  
*       Matt Chapman         -- Sept, 1986
*
*   Modified by: 
*   Who     Version     When        What
*   MPC     3.47        07/28/89    Added #defines for ipsetsrch().
*   MPC     4.00        01/09/90    Added externs for ipsets...().
*   
*   Copyright (c) 1986 by Viewlogic Systems, Inc.
*
*/

/* status return codes */
#define IP_SUCCESS      0   /* successful completion of routine */
#define IP_INC          1   /* level incremented to far */
#define IP_DEC          2   /* level decremented to far */
#define IP_DUPVAR       3   /* attempted to load a duplicate variable */
#define IP_NOVAR        4   /* undefined variable(s) encountered */
#define IP_SIZE         5   /* insufficient space to perform expansion */
#define IP_VARDEF       6   /* attribute is a variable definition */
#define IP_VARREF       7   /* string contains variable reference(s) */
#define IP_RECURSE      8   /* recursive definition encountered */
#define IP_NONAME       9   /* tried to add a NULL value to the var table */
#define IP_FILERR      10   /* couldn't find the specified file */
#define IP_NOTINIT     11   /* ipinit has not been called */

/* ipsets...() options */
#define IP_SKIP         0   /* skip this search */
#define IP_PRIMARY      1   /* search primary definitions */
#define IP_DESIGN       2   /* search design definitions */
#define IP_DEFAULT      3   /* search default definitions */
#define IP_TOPDOWN      4   /* search design top-to-bottom */
#define IP_BOTTOMUP     5   /* search design bottom-to-top */

/* Function Prototypes */

extern int           ipaddatt vlARG1(ATTRIBUTES *);
extern int           ipadddef vlARG2(char *, char *);
extern int           ipaddlist vlARG1(ATTRIBUTES *);
extern int           ipaddvardefs vlARG1(COMPONENTS *);
extern int           ipdeldef vlARG1(char *);
extern int           ipdelvardefs vlARG1(void);
extern void          ipdmptbl vlARG1(void);
extern int           ipevaluate vlARG3(char *, char *, int);
extern int           ipexpand vlARG3(char *, char *, int);
extern void          ipfinfile vlARG1(void);
extern void          ipfinish vlARG1(void);
extern int           ipgetlev vlARG1(void);
extern char         *ipgetmsg vlARG1(int);
extern char         *ipgetvar vlARG1(char *);
extern int           ipincfile vlARG1(char *);
extern int           ipinit vlARG1(GROUPS *);
extern int           ippoplev vlARG1(void);
extern int           ippushlev vlARG1(void);
extern void          ipsetsdir vlARG1(int);
extern void          ipsetsord vlARG3(int, int, int);
extern int           ipvardef vlARG1(char *);
extern int           ipvarref vlARG1(char *);
extern ATTRIBUTES   *iaaddatt vlARG3(ATTRIBUTES *, char *, char *);
extern ATTRIBUTES   *iadelatt vlARG2(ATTRIBUTES *, ATTRIBUTES *); 
extern int           iaaddpatt vlARG1(ATTRIBUTES *);

/*
*
*   Name: MISC.H
*
*   Facility: VIEWBASE
* 
*   Functional Description: 
*       External declarations and definitions for miscellaneous
*       VIEWBASE routines.
*
*   Author:  
*       Matt Chapman            -- Jan, 1987
*
*   Modified by: 
*   Who     Version     When        What
*   MPC     1.30        09/20/87    Made inaddmem() and insetmem() char *.
*   
*   Copyright (c) 1987 by Viewlogic Systems, Inc.
*
*/

extern char         *idate vlARG1(void);
extern char         *iday vlARG1(void);
extern void          iemsclose vlARG1(void);
extern void          iemsinit vlARG1(void);
extern char         *inaddmem vlARG3(int, char *, int);
extern char         *inanymem vlARG1(int);
extern int           indelmem vlARG2(int, char *);
extern int           indelset vlARG1(int);
extern char         *insetmem vlARG2(int, char *);
extern void          iprintf (/* variable number of arguments */);
extern void          iprintfend vlARG1(void);
extern void          iprintfinit vlARG3(int, char *, char *);
extern void          iprintfsetbuf vlARG1(unsigned int);
extern char         *itime vlARG1(void);
/*
*
*   Name: IXEVAL.H
*
*   Facility: VIEWBASE
* 
*   Functional Description: 
*       This is the header file for the generic expression evaluator.
*       Two evaluation functions are provided: ixevaluate() and
*       ixeval().
*
*   Author:  
*       Brian Kelley        -- Nov, 1986
*
*   Modified by: 
*   Who     Version     When        What
*   
*   
*   Copyright (c) 1986 by Viewlogic Systems, Inc.
*
*/


#define IX_CONST       -7   /** illegal constant in expression    **/
#define IX_QUOTES      -6   /** mismatched quotations             **/
#define IX_PARENS      -5   /** mismatched parenthesis            **/
#define IX_IOP         -4   /** illegal operand types             **/
#define IX_UOP         -3   /** undefined operator                **/
#define IX_BUFLEN      -2   /** char string buffer to short       **/
#define IX_UNDEFINED   -1   /** undefined error                   **/
#define IX_EXPRESS      0   /** expression                        **/

#define IX_BOOLEAN      1   /** Boolean result           (btoken) **/
#define IX_CHAR         2   /** Character                (ctoken) **/
#define IX_NUMBER       3   /** Integer constants        (ntoken) **/
#define IX_STRING       4   /** Character string         (stoken) **/
#define IX_REAL         5   /** Real number              (rtoken) **/
#define IX_MEMORY       6   /** Memory location          (mtoken) **/
#define IX_SCIEN        7   /** Scientific Notation      (rtoken) **/

#define IX_STRLEN     512   /** Record string buffer length       **/

typedef struct ixrec {
    int type;                       /* token type or error code */
    union {
        int     btoken;             /* boolean */
        char    ctoken;             /* character */
        long    ntoken;             /* integer number   */
        char    stoken[IX_STRLEN];  /* character string */
        double  rtoken;             /* real/scientific notation number */
        char   *mtoken;             /* memory */
    } value;
} IXPREC;


/* Function Prototypes */

extern IXPREC       *ixalloc vlARG1(void);
extern IXPREC       *ixbinary vlARG3(IXPREC *, IXPREC *, IXPREC *);
extern IXPREC       *ixclassify vlARG2(int, IXPREC *);
extern int           ixepriority vlARG1(char *);
extern int           ixeval vlARG1(IXPREC *);
extern int           ixevaluate vlARG3(char *, char *, int);
extern void          ixformat vlARG2(int, char *);
extern void          ixfree vlARG1(IXPREC *);
extern char         *ixgetmsg vlARG1(int);
extern IXPREC       *ixunary vlARG2(IXPREC *, IXPREC *);

/*
*
*   Name: ICONTEXT.H
*
*   Facility: VIEWBASE (internal)
* 
*   Functional Description: 
*       Header file for the context (walk flat) routines.
*     
*   Author:  
*       Matt Chapman            -- May, 1987
*
*   Modified by: 
*   Who     Version     When        What
*   
*   
*   Copyright (c) 1987 by Viewlogic Systems, Inc.
*
*/

#define ICMAXBUF     1024       /* length of name buffer */
#define ICGBL_ENABLE    1       /* enable global net processing */
#define ICGBL_NET       2       /* currently processing a global net */
#define ICGBL_FIRST     4       /* current global is the first occurance */

#define icvarfirst(c) ((c) == '@')
#define icvarchar(c)  (isalpha(c) || isdigit(c) || icvarfirst(c) || (c=='_'))

typedef struct gblnet {
    NETS            *netp;      /* processed global net */
    struct gblnet   *next;      /* next net */
}
GBLNET;

typedef struct cstack {
    GROUPS          *cgrp;      /* current group at this level */
    COMPONENTS      *ccom;      /* current comp at this level */
    COMPONENTS      *save;      /* temporary location for current comp */
    PINS            *cpin;      /* current pin at this level */
    NETS            *cnet;      /* current net at this level */
    int              done;      /* nets done on this level */
    struct cstack   *next;      /* next stack struct */
}
CSTACK;

typedef struct context {
    CSTACK          *stack;     /* context stack */
    GBLNET          *gnets;     /* processed global nets */
    int              status;    /* status for global net processing */
    ATTRIBUTES      *attp;      /* place holder for hier. attrib. */
    char            *namebuf;   /* space for context name and p.a. eval. */
}
CONTEXT;

/* Function Prototypes */

extern COMPONENTS   *icallcom vlARG1(CONTEXT *);
extern NETS         *icallnet vlARG1(CONTEXT *);
extern PINS         *icallpin vlARG2(CONTEXT *, NETS *);
extern CONTEXT      *iccpyctx vlARG1(CONTEXT *);
extern void          icdeldef vlARG1(void);
extern void          icdelstk vlARG1(CONTEXT *);
extern ATTRIBUTES   *iceval vlARG2(CONTEXT *, ATTRIBUTES *);
extern ATTRIBUTES   *icfcomat vlARG4(CONTEXT *, COMPONENTS *, char *, int);
extern char         *icfindef vlARG2(int, char *);
extern ATTRIBUTES   *icfnetat vlARG4(CONTEXT *, NETS *, char *, int);
extern ATTRIBUTES   *icfpinat vlARG4(CONTEXT *, PINS *, char *, int);
extern void          icfree vlARG1(CONTEXT *);
extern ATTRIBUTES   *icgcomat vlARG3(CONTEXT *, COMPONENTS *, int);
extern NETS         *icgetgbl vlARG2(CONTEXT *, NETS *);
extern char         *icgetvar vlARG2(CONTEXT *, char *);
extern ATTRIBUTES   *icgnetat vlARG3(CONTEXT *, NETS *, int);
extern ATTRIBUTES   *icgpinat vlARG3(CONTEXT *, PINS *, int);
extern CONTEXT      *icinit vlARG2(GROUPS *, int);
extern int           icloadef vlARG1(char *);
extern ATTRIBUTES   *icmakatt vlARG3(CONTEXT *, char *, char *);
extern int           icnewgbl vlARG2(CONTEXT *, NETS *);
extern int           icomposite vlARG1(COMPONENTS *);
extern char         *icontext vlARG2(CONTEXT *, char *);
extern CSTACK       *icpop vlARG1(CONTEXT *);
extern void          icpush vlARG2(CONTEXT *, GROUPS *);
extern void          icrecadd vlARG1(char *);
extern void          icrecdel vlARG1(char *);
extern void          icrecfin vlARG1(void);
extern void          icrecinit vlARG1(void);
extern int           icrecsea vlARG1(char *);
extern NETS         *icsubnet vlARG2(CONTEXT *, NETS *);
extern NETS         *icsupnet vlARG2(CONTEXT *, NETS *);
extern NETS         *ictopnet vlARG2(CONTEXT *, NETS *);
extern int           icvarref vlARG1(char *);

/*
*
*   Name: MODIFY.H
*
*   Facility: VIEWBASE  (internal)
* 
*   Functional Description: 
*       Provides function prototype for the add and delete routine.
*       
*     
*   Author:  
*       Matt Chapman            -- Sept, 1988
*
*   Modified by: 
*   Who     Version     When        What
*   
*   
*   Copyright (c) 1987 by Viewlogic Systems, Inc.
*
*/

extern ATTRIBUTES  *iaattnam vlARG2(ATTRIBUTES *, char *);
extern ATTRIBUTES  *iaattval vlARG2(ATTRIBUTES *, char *);
extern COMPONENTS  *iacomatt vlARG2(COMPONENTS *, ATTRIBUTES *);
extern COMPONENTS  *iacomnam vlARG2(COMPONENTS *, char *);
extern COMPONENTS  *iacomsym vlARG2(COMPONENTS *, SYMBOLS *);
extern COMPONENTS  *iacomuid vlARG2(COMPONENTS *, char *);
extern GROUPS      *iagrpnam vlARG2(GROUPS *, char *);
extern GROUPS      *iagrpnet vlARG2(GROUPS *, NETS *);
extern GROUPS      *iagrpsch vlARG2(GROUPS *, SCHEMATICS *);
extern GROUPS      *iagrpsym vlARG2(GROUPS *, SYMBOLS *);
extern NETS        *ianetatt vlARG2(NETS *, ATTRIBUTES *);
extern NETS        *ianetnam vlARG2(NETS *, char *);
extern NETS        *ianetpin vlARG2(NETS *, PINS *);
extern NETS        *ianettyp vlARG2(NETS *, int);
extern PINS        *iapinatt vlARG2(PINS *, ATTRIBUTES *);
extern SCHEMATICS  *iaschatt vlARG2(SCHEMATICS *, ATTRIBUTES *);
extern SCHEMATICS  *iaschcom vlARG2(SCHEMATICS *, COMPONENTS *);
extern SCHEMATICS  *iaschsht vlARG2(SCHEMATICS *, int);
extern SYMPINS     *iaspnatt vlARG2(SYMPINS *, ATTRIBUTES *);
extern SYMPINS     *iaspnnam vlARG2(SYMPINS *, char *);
extern SYMPINS     *iaspnnet vlARG2(SYMPINS *, NETS *);
extern SYMBOLS     *iasymatt vlARG2(SYMBOLS *, ATTRIBUTES *);
extern SYMBOLS     *iasymnum vlARG2(SYMBOLS *, int);
extern SYMBOLS     *iasymsht vlARG2(SYMBOLS *, int);
extern SYMBOLS     *iasymspn vlARG2(SYMBOLS *, SYMPINS *);
extern SYMBOLS     *iasymtyp vlARG2(SYMBOLS *, int);
extern ATTRIBUTES  *idcomatt vlARG2(COMPONENTS *, ATTRIBUTES *);
extern NETS        *idgrpnet vlARG2(GROUPS *, NETS *);
extern SCHEMATICS  *idgrpsch vlARG2(GROUPS *, SCHEMATICS *);
extern SYMBOLS     *idgrpsym vlARG2(GROUPS *, SYMBOLS *);
extern ATTRIBUTES  *idnetatt vlARG2(NETS *, ATTRIBUTES *);
extern PINS        *idnetpin vlARG2(NETS *, PINS *);
extern ATTRIBUTES  *idpinatt vlARG2(PINS *, ATTRIBUTES *);
extern ATTRIBUTES  *idschatt vlARG2(SCHEMATICS *, ATTRIBUTES *);
extern COMPONENTS  *idschcom vlARG2(SCHEMATICS *, COMPONENTS *);
extern ATTRIBUTES  *idspnatt vlARG2(SYMPINS *, ATTRIBUTES *);
extern ATTRIBUTES  *idsymatt vlARG2(SYMBOLS *, ATTRIBUTES *);
extern SYMPINS     *idsymspn vlARG2(SYMBOLS *, SYMPINS *);
extern ATTRIBUTES  *iwdelatt vlARG2(ATTRIBUTES *, ATTRIBUTES *);
extern void         iwfratt vlARG1(ATTRIBUTES *);
extern void         iwfrcom vlARG1(COMPONENTS *);
extern void         iwfrgrp vlARG1(GROUPS *);
extern void         iwfrnet vlARG1(NETS *);
extern void         iwfrpin vlARG1(PINS *);
extern void         iwfrsch vlARG1(SCHEMATICS *);
extern void         iwfrspn vlARG1(SYMPINS *);
extern void         iwfrsym vlARG1(SYMBOLS *);
extern void         iwinitflist vlARG1(void);
extern ATTRIBUTES  *iwmakatt vlARG1(void);
extern COMPONENTS  *iwmakcom vlARG1(void);
extern GROUPS      *iwmakgrp vlARG1(void);
extern NETS        *iwmaknet vlARG1(void);
extern PINS        *iwmakpin vlARG1(int);
extern SCHEMATICS  *iwmaksch vlARG1(void);
extern SYMPINS     *iwmakspn vlARG1(void);
extern SYMBOLS     *iwmaksym vlARG1(void);
extern SYMBOLS     *iwrdsym vlARG1(char *);
extern int          iwsortpins vlARG2(SYMBOLS *, char *);

/* IWOAT.H - Occurrence Attribute Routines

Facility: Viewbase 

Functional Description: 

Environment:
   DOS 2.0
   VAX/VMS
   UNIX

Author:  Wayne Bailey

Modified By:
Who       When       Why
----------------------------------------------------------------------------
WAB    12 Oct 90    Initiial Implementation
ASM    20 Mar 91    Added IWOAT

Copyright (C) 1985 by Viewlogic Systems, Inc.
*/


/* status return codes */
#define IW_LOWESTCODE  -4  /* lowest return code                       */
#define IW_ORPHANOATS  -4  /* orphan oats may have been loaded         */
#define IW_NOBACKUP    -3  /* no backup done while killing orphan oats */
#define IW_NOOAT       -2  /* encountered no OAT file specification    */
#define IW_EMPTY       -1  /* no occurrences in OAT file               */
#define IW_SUCCESS      0  /* successful completion of routine         */
#define IW_DUPOAT       1  /* attempted to load a duplicate variable   */
#define IW_LOWESTERROR  2  /* lowest return code that is an error      */
#define IW_NOFILE       2  /* couldn't find the specified file         */
#define IW_BADPARAM     3  /* parameter is a NULL pointer              */
#define IW_BADFNAME     4  /* bad specified OAT file name              */
#define IW_BADFILE      5  /* bad oat file format                      */
#define IW_NOSPACE      6  /* no more space for loading oat files      */
#define IW_ERROR        7  /* error while loading an OAT file          */
#define IW_INTERROR     8  /* internal coding error                    */
#define IW_HIGHESTCODE  8  /* highest return code                      */

/*-----------------------------------------------------------------------*/
/*  Definitions for back-annotation records                              */
/*-----------------------------------------------------------------------*/

#define OComp 2
#define OPin  4
#define ONet  8

/*-----------------------------------------------------------------------*/
/* External routine declarations.                                        */
/*-----------------------------------------------------------------------*/

extern int         iwloadoat vlARG2(char *, char *);
extern int         iwoat     vlARG3(GROUPS *, int, char *);

extern ATTRIBUTES *igcomoat  vlARG1(char *);
extern ATTRIBUTES *igpinoat  vlARG1(char *);
extern ATTRIBUTES *ignetoat  vlARG1(char *);

extern ATTRIBUTES *igopsatt  vlARG4(char *, PINS *, int *, ATTRIBUTES *);
extern ATTRIBUTES *igocsatt  vlARG4(char *, COMPONENTS *, int *, ATTRIBUTES *);
extern ATTRIBUTES *igonatt   vlARG4(char *, NETS *, int *, ATTRIBUTES *);

extern ATTRIBUTES *ifocsatt  vlARG4(char *, char *, COMPONENTS *, int *);
extern ATTRIBUTES *ifopsatt  vlARG4(char *, char *, PINS *, int *);
extern ATTRIBUTES *ifonatt   vlARG4(char *, char *, NETS *, int *);

