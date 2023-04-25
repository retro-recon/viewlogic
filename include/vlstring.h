/*
 * $Id: vlstring.h,v 1.18.7.1 1995/10/17 20:40:33 cway Stab $
 *
 * These definitions were "borrowed" from the pmax stdio.h and string.h
 * files, and are currently only used for gcc (pre-2.5.8), to
 * eliminate warnings about undefined standard functions, but they
 * should work on any platform.
 */

#ifndef vlSTRING_H
#define vlSTRING_H

#ifndef vlWLDEFS_H
#include "vldefs.h"
#endif

#ifndef vlVARGS_H
#include "vlvargs.h"
#endif

extern char
	*strcat vlARGS ((char *, const char *)),	
	*strchr vlARGS ((const char *, int)),
	*strcpy vlARGS ((char *, const char *)),
	*strerror vlARGS ((int)),		
	*strncat vlARGS ((char *, const char *, size_t)),
	*strncpy vlARGS ((char *, const char *, size_t)),
	*strpbrk vlARGS ((const char *, const char *)),	
	*strrchr vlARGS ((const char *, int)),
	*strstr vlARGS ((const char *, const char *)),
	*strtok vlARGS ((char *, const char *));	

extern int
        toupper vlARGS ((int)),
        tolower vlARGS ((int)),
	strcoll vlARGS ((const char *, const char *)),
        strcasecmp vlARGS ((const char *, const char *)),
        strncasecmp vlARGS ((const char *, const char *, int)),
	strcmp vlARGS ((const char *, const char *)),
	strncmp vlARGS ((const char *, const char *, size_t));

extern long strtol vlARGS ((const char *, char **, int));

extern size_t
	strcspn vlARGS ((const char *, const char *)),
	strlen vlARGS ((const char *)),
	strspn vlARGS ((const char *, const char *)),
	strxfrm vlARGS ((char *, const char *, size_t __maxsize));

#ifndef clearerr
extern void	clearerr vlARGS ((FILE *)); 
#endif
extern int      putenv vlARGS((char *));
extern int	fclose vlARGS ((FILE *));
extern int	fflush vlARGS ((FILE *));
extern int	fgetc vlARGS ((FILE *));
extern char *	fgets vlARGS ((char *, int , FILE *));
extern size_t	fread vlARGS ((vlPointerT , size_t ,
			size_t , FILE *)); 
extern int	fseek vlARGS ((FILE *, long , int));
extern long	ftell vlARGS ((FILE *));
extern char *	gets vlARGS ((char *));	
extern int	getw vlARGS ((FILE *));
extern int	pclose vlARGS ((FILE *));
extern int	putw vlARGS ((int , FILE *));
extern int	rename vlARGS ((const char *, const char *));
extern FILE *	fdopen vlARGS ((int , const char *));
extern FILE *	fopen vlARGS ((char *, const char *));
extern void	perror vlARGS ((const char *));

#if (vlHW_SUN4 && vlCOMP_AC)   /*****************  Conrad 9-2--91 */

extern int      rewind vlARG1 (FILE *);
extern char *  vsprintf vlARG3 (char *, const char *, va_list);
extern int	fputc vlARG2 (char , FILE *);
extern FILE	*fdopen  vlARG2 (int, const char *);
extern FILE	*popen  vlARG2 (const char *, const char *);
extern FILE     *freopen  vlARG3 (const char *, const char *, FILE *);
extern char	*tempnam  vlARG2 (const char *, const char *);
extern char	*vsprintf  vlARG3 (char *, const char *, void *);
extern char     *sprintf  vlARGS ((char *, const char *, ...));
extern char *	memchr  vlARG3 (const char *, int, int);
extern char *	memcpy  vlARG3 (char *, const char *, int);
extern char *	memset  vlARG3 (char *, int, int);
extern int	scanf  vlARGS ((const char *, ...));
extern int	sscanf  vlARGS ((const char *, const char *, ...));
extern int	vfprintf  vlARG3 (FILE *, const char *, void *);
extern int	vprintf  vlARG2 (const char *, void *);
extern int 	memcmp  vlARG3 (const char *, const char *, int);
extern int      fprintf  vlARGS ((FILE *, const char *, ...));
extern int      fputs  vlARG2 (const char *, FILE *);
extern int      fscanf  vlARGS ((FILE *, const char *, ...));
extern int      printf  vlARGS ((const char *, ...));
extern int      puts  vlARG1 (const char *);
extern int      remove  vlARG1 (const char *);
extern size_t   fwrite  vlARG4 (const void *, size_t, size_t, FILE *);
extern void *	memmove  vlARG3 (void *, const void *, size_t);

#else /* vlHW_SUN4 && vlCOMP_AC */

extern void	rewind vlARGS ((FILE *));
extern int	vsprintf vlARGS ((char *, const char *, va_list));
extern int	fprintf vlARGS ((FILE *, char *, ...));
extern int	fputc vlARGS ((int , FILE *));
extern int	fputs vlARGS ((char *, FILE *));
extern FILE *	freopen vlARGS ((char *, char *, FILE *));
extern int	fscanf vlARGS ((FILE *, char *, ...));
extern size_t	fwrite vlARGS ((vlPointerT , size_t ,
			size_t , FILE *));
extern FILE  *	popen vlARGS ((char *, char *));
extern int	printf vlARGS ((char *, ...));	
extern int	puts vlARGS ((char *));	
extern int	remove vlARGS ((char *));
extern int	scanf vlARGS ((char *, ...));	
extern int	sscanf vlARGS ((char *, char *, ...));
extern char *	tempnam vlARGS ((char *, char *));
extern int	vfprintf vlARGS ((FILE *, char *, va_list));
extern int	vprintf vlARGS ((char *, va_list));

extern vlPointerT memchr vlARGS ((const vlPointerT , int , size_t));
extern vlPointerT memmove vlARGS ((vlPointerT , const vlPointerT , size_t));
extern vlPointerT memset vlARGS ((vlPointerT , int , size_t));

#endif /* vlHW_SUN4 && vlCOMP_AC */

extern void	setbuf vlARGS ((FILE *, char *));
extern int	setvbuf vlARGS ((FILE *, char *,
			int , size_t));
extern FILE *	tmpfile vlARGS ((void));	
extern char *	tmpnam vlARGS ((char *));
extern int	ungetc vlARGS ((int , FILE *));

/* quiet warnings from using `getc' macro */
#if vlOS_SUNOS4 && vlCOMP_GC
extern int      _filbuf vlARGS((FILE *));
extern int      _flsbuf vlARGS((unsigned char, FILE *));
#endif

#endif /* vlSTRING_H */
