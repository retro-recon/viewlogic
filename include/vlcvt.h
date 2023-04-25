/*
 * $Id: vlcvt.h,v 1.12.4.1 1995/10/17 20:42:25 cway Stab $
 *
 * Header for conversion functions and macros
 *
 * Peter Colby - June 1991
 *
 * Copyright 1991, Viewlogic Systems, Inc
 */

#ifndef vlCVT_H
#define vlCVT_H

#ifndef vlmag_H
#include "vlmag.h"
#endif

/* type/defines for vlCvtDtostr & vlCvtUstrtod */

#if (!vlCOMP_LC)
typedef enum {
    vlCvtNotaAMBIGUOUS = (-2),
    vlCvtNotaUNDEFINED = (-1),
    vlCvtNotaDECIMAL,
    vlCvtNotaSCIENTIFIC,
    vlCvtNotaENGINEERING,
    vlCvtNotaUNITS
} vlCvtNOTATION;
#else
#define vlCvtNotaAMBIGUOUS          (-2)
#define vlCvtNotaUNDEFINED          (-1)
#define vlCvtNotaDECIMAL            0
#define vlCvtNotaSCIENTIFIC         1
#define vlCvtNotaENGINEERING        2
#define vlCvtNotaUNITS              3
typedef int vlCvtNOTATION;
#endif

/* for use with vlCvtDformat* */
#define vlCvtMAGNITUDE (1L<<0)
#define vlCvtNORMALIZE (1L<<1)
#define vlCvtTRUNC     (1L<<2)
#define vlCvtFIXED     (1L<<3)
/* NOTA BENE: change vllmCvt flags in "vllm.h" if you add any flags here */

   /* char CONVERSION MACROS */

/*\Docpage vlCvtUpc -- convert character to upper case 

DESCRIPTION 

     Converts a character to upper case  

RETURNS 

     c = upper cased character 

SYNOPSIS 

     c = vlCvtUpc(ch); 

     char c;                upper cased character 
     char ch;               input character 
*/
#define vlCvtUpc(c)           (vrIslower(((int)(c))&0xff)?((c)-('a'-'A')):(c))

/*\Docpage vlCvtLoc -- convert character to lower case 

DESCRIPTION 

     Converts a character to lower case  

RETURNS 

     c = lower cased character 

SYNOPSIS 

     c = vlCvtLoc(ch); 

     char c;                lower cased character 
     char ch;               input character 
*/
#define vlCvtLoc(c)           (vrIsupper(((int)(c))&0xff)?((c)+('a'-'A')):(c))

/*\Docpage vlCvtStrInt -- convert ASCII string to integer 

DESCRIPTION 

     Converts a string representation of an integer into a real integer. Stops
     the conversion without warning if a non-numeric character is encountered.

RETURNS 

     i = integer

SYNOPSIS 

     i = vlCvtStrInt(s); 

     char *s;               NUL terminated string
     int i;                 integer returned.
*/
#define vlCvtStrInt(s)	          vrAtoi(s)

/*\Docpage vlCvtStrLong -- convert ASCII string to long 

DESCRIPTION 

     Converts a string representation of an integer into a long. Stops
     the conversion without warning if a non-numeric character is encountered.

RETURNS 

     i = long

SYNOPSIS 

     i = vlCvtStrlong(s); 

     char *s;               NUL terminated string
     long i;                 integer returned.
*/
#define vlCvtStrLong(s)	          vrAtol(s)

extern int vlCvtStrBin vlARG2(char *, char *);
extern int vlCvtDecBin vlARG2(char *, char *);
extern int vlCvtHexBin vlARG2(char *, char *);
extern int vlCvtOctBin vlARG2(char *, char *);
extern int vlCvtIsBinary vlARG1(char *);
extern int vlCvtBinOct vlARG3(char *, char *, int);
extern int vlCvtBinHex vlARG3(char *, char *, int);
extern int vlCvtBinDec vlARG3(char *, char *, int);
extern char *vlCvtTimeStr vlARG1(long);
extern int vlCvtTime vlARG7(long, int *, int *, int *, int *, int *, int *);
extern char *vlCvtIntStr vlARG1(int);
extern char *vlCvtLongStr vlARG1(long);
extern char *vlCvtFloatStr vlARG1(double);
extern const char *vlCvtDtostr vlARG4(double, vlCvtNOTATION, int, double);
extern void vlCvtDformatStrBuf vlARGS((vlStrBufID strbuf, double value, int ndigits, vlMagT mag, unsigned long flags));
extern const char *vlCvtDformatStatic vlARGS((double value, int ndigits, vlMagT mag, unsigned long flags));
extern double vlCvtUstrtod vlARG2(const char *, char **);
extern double vlCvtUstrtod2 vlARGS((const char *str, char **end_ptr, vlMagT default_mag, const char *units));
extern vlMagT vlCvtUstrtomag vlARGS((const char *mag_str));
extern long vlCvtUHexTol vlARG2(const char *, char **);

#endif
