/*
 * $Id: vlstr.h,v 1.35.3.1 1995/10/17 20:43:22 cway Stab $
 *
 * Defines and externals for the vlStr package
 *
 * Peter Colby - May 1991
 *
 * Copyright 1991, Viewlogic Systems, Inc.
 */

#ifndef vlSTR_H
#define vlSTR_H

#include "vlmemory.h"
/* find out the on-stack allocation availability */

/*\Docpage vlStrBufID -- String buffer data type

DESCRIPTION
     This data structure contains an expandable string buffer,
     which can be appended to without regard to overflow.

SEE ALSO
     vlStrBufCreate, vlStrBufDestroy, vlStrBufAppend, vlStrBufAppendChar,
     vlStrBufAppendN, vlStrBufAppendStrings, vlStrBufClear, vlStrBufRemoveN,
     vlStrBufString, vlStrBufLength
*/
typedef struct vlStrBuf *vlStrBufID;

/*\Docpage vlStrMaskT -- Flags that can be passed to vlStrBufUntokQuote

DESCRIPTION
     These include: vlStrNO_FLAGS (default actions), vlStrDOLLAR (xlate
     $ to $$) and vlStrDELIMITED (if there are break characters in the
     string, surround the string with double-quotes).
*/
typedef vlMaskT vlStrMaskT;
#define vlStrNO_FLAGS       ((vlStrMaskT) 0)
#define vlStrDOLLAR         ((vlStrMaskT) 1)
#define vlStrDELIMITED      ((vlStrMaskT) 2)


extern vlBoolT  vlStrIsnum      vlARG1(const char *);
extern char    *vlStrBlk        vlARG1(const char *);
extern char    *vlStrBrk        vlARG2(const char *, const char *);
extern char    *vlStrCat        vlARG2(const char *, const char *);
extern char    *vlStrCatAlloc   vlARG2(const char *, const char *);
extern char    *vlStrChr        vlARG2(const char *, int);
extern vlBoolT  vlStrEqu        vlARG2(const char *, const char *);
extern vlBoolT  vlStrIequ       vlARG2(const char *, const char *);
extern int      vlStrIcmp       vlARG2(const char *, const char *);
extern int      vlStrIndex     vlARG3(const char *, const char **, int);
extern int      vlStrIindex    vlARG3(const char *, const char **, int);
extern char    *vlStrLoc        vlARG1(char *);
extern vlBoolT  vlStrIMat       vlARG2(const char *, const char *);
extern vlBoolT  vlStrMat        vlARG2(const char *, const char *);
extern int      vlStrNicmp      vlARG3(const char *, const char *, int);
extern char    *vlStrRch        vlARG2(const char *, int);
extern char    *vlStrSearch     vlARG2(const char *, const char *);
extern char    *vlStrISearch    vlARG2(const char *, const char *);
extern char    *vlStrTok       vlARG4(const char *, char *, int, const char *);
extern char    *vlStrTrim       vlARG1(char *);
extern char    *vlStrTrimAlloc  vlARG1(vlCStringPtrT);
extern char    *vlStrUpc        vlARG1(char *);
extern char    *vlStrLex        vlARG5(const char *, char *, size_t,
                                       const char *, const char *);
extern int      vlStrUnlexdelim vlARG3(const char *, int, const char *);
extern char    *vlStrCpy        vlARG1(const char *);
extern char    *vlStrOldCopy    vlARG1(const char *);
extern char    *vlStrAlloc      vlARG1(int);
extern void     vlStrFree       vlARG1(char *);
extern void     vlStrTerminate  vlARGS((void));
extern char    *vlStrncpyNullTerm vlARGS((char *, const char *, int));
extern char *vlStrBufTokQuote vlARGS((const char *, vlStrBufID, const char *));
extern char *vlStrBufTok vlARGS((const char *, vlStrBufID, const char *));
extern char *vlStrTokQuote vlARGS((const char *, char *, int, const char *));
extern void vlStrBufUntokQuote vlARGS((const char *, vlStrBufID, vlStrMaskT, const char *));

/*\Docpage vlStrWHITESPACE -- macro to return a string containing whitespace

DESCRIPTION
    Contains space, newline, and tab.  For use with vlStrTok, vlStrBrk, etc.
*/
#define vlStrWHITESPACE vlStrWhitespaceV
extern const char vlStrWhitespaceV[];

/*\Docpage vlStrWILDCARD -- macro to return a string containing a wildcard

DESCRIPTION
    "*"
*/
#define vlStrWILDCARD vlStrWildcardV
extern const char vlStrWildcardV[];

extern void vlStrBufAppend vlARGS((vlStrBufID, const char *));
extern void vlStrBufAppendStrings vlVaARG1 (vlStrBufID);
extern void vlStrBufAppendN vlARGS((vlStrBufID, const char *, unsigned int));
extern void vlStrBufAppendChar vlARGS((vlStrBufID, int));
extern int vlStrBufLength vlARGS((vlStrBufID));
extern const char *vlStrBufString vlARGS((vlStrBufID));
extern void vlStrBufClear vlARGS((vlStrBufID));
extern vlStrBufID vlStrBufCreate vlARGS((int));
extern void vlStrBufDestroy vlARGS((vlStrBufID));
extern void vlStrBufRemoveN vlARGS((vlStrBufID, int));

/*\Docpage vlStrAlloca -- allocate a string on the stack

DESCRIPTION
    This function is identical to vlStrAlloc except that the string will
    be allocated on the stack if the platform supports alloca

CAUTION
    vlStrFreea MUST be used to free the string.

SEE ALSO
    vlStrAlloc, vlStrFreea, vlStrCpya

SYNOPSIS
    char *vlStrAlloca(size)
        int size;
*/

/*\Docpage vlStrCpya -- copy a string onto the stack

DESCRIPTION
    This function is identical to vlStrCpy except that the string will
    be allocated onto the stack if the platform supports alloca

CAUTION
    vlStrFreea MUST be used to free the string.
    This macro may evaluate its arguments more than once.

SEE ALSO
    vlStrAlloca, vlStrFreea, vlStrCata2, vlStrCata3, vlStrCata4

SYNOPSIS
    char *vlStrCpya(str)
        char *str;
*/

/*\Docpage vlStrCata2 -- concatenate 2 strings on the stack

DESCRIPTION
    This function is identical to vlStrCatAlloc except that the string will
    be allocated onto the stack if the platform supports alloca

CAUTION
    vlStrFreea MUST be used to free the string.

SEE ALSO
    vlStrAlloca, vlStrFreea, vlStrCata3, vlStrCata4

SYNOPSIS
    char *vlStrCata2 (char *str1, char *str2)
*/

/*\Docpage vlStrCata3 -- concatenate 3 strings on the stack

DESCRIPTION
    This function is similar to vlStrCata2, but it concatenates
    3 strings instead of 2.  Note that you cannot vlStrCata3 based
    on vlStrCata2, because you would have to ensure that the
    intermediate strings got freed.

CAUTION
    vlStrFreea MUST be used to free the string.

SEE ALSO
    vlStrAlloca, vlStrFreea, vlStrCata2, vlStrCata4

SYNOPSIS
    char *vlStrCata3 (char *str1, char *str2, char *str3)
*/

/*\Docpage vlStrCata4 -- concatenate 4 strings on the stack

DESCRIPTION
    This function is similar to vlStrCata2, but it concatenates
    4 strings instead of 2.  Note that you cannot vlStrCata4 based
    on vlStrCata2, because you would have to ensure that the
    intermediate strings got freed.

CAUTION
    vlStrFreea MUST be used to free the string.

SEE ALSO
    vlStrAlloca, vlStrFreea, vlStrCata2, vlStrCata3

SYNOPSIS
    char *vlStrCata4 (char *str1, char *str2, char *str3, char *str4)

*/

/*\Docpage vlStrFreea -- Free a string allocated by vlStrAlloca

DESCRIPTION
    This function is identical to vlStrFree except that the string MUST
    have been allocated on the stack with vlStrAlloca.

CAUTION
    Only do this for strings allocated via vlStrAlloca

SEE ALSO
    vlStrAlloca, vlStrFree

SYNOPSIS
    void vlStrFreea(str)
        char *str;
*/

#if vlMemHAS_ALLOCA
# define vlStrAlloca(size) ((char *) alloca(size))
# define vlStrCpya(str) (vrStrcpy ((char *) alloca (strlen (str) + 1), str))
# define vlStrFreea(str)
#else
# define vlStrAlloca(size) vlStrAlloc(size)
# define vlStrCpya(str) vlStrCpy (str)
# define vlStrFreea(str) vlStrFree(str)
#endif
    
#define vlStrCata2(s1, s2) \
    (vrStrcat (vrStrcpy (vlStrAlloca (strlen (s1) + strlen (s2) + 1), \
                         s1), \
               s2))
#define vlStrCata3(s1, s2, s3) \
    (vrStrcat (vrStrcat (vrStrcpy (vlStrAlloca (strlen (s1) + \
                                                strlen (s2) + \
                                                strlen (s3) + 1), \
                                   s1), \
                         s2), \
               s3))
#define vlStrCata4(s1, s2, s3, s4) \
    (vrStrcat (vrStrcat (vrStrcat (vrStrcpy (vlStrAlloca (strlen (s1) + \
                                                          strlen (s2) + \
                                                          strlen (s3) + \
                                                          strlen (s4) + 1), \
                                             s1), \
                                   s2), \
                         s3), \
               s4))
                         
#endif

