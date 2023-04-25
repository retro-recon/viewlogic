/*
 * $Id: vlregexp.h,v 3.2.13.1 1995/10/17 20:40:21 cway Stab $
 *
 * Regular expression support.
 * This is a MODIFIED version of regexp.h
 * written by Henry Spencer @ U of Toronto in 1986.
 *
 * Caveat:  these are V8 regexp routines, not the System V ones.
 */


#ifndef vlREGEXP_H
#define vlREGEXP_H

/*
 * If you change this number, you are a bonehead;
 * this limit is inherent in the specification.
 * Who can tell the diff between \1 and \10 ?  Not these routines!
 */
#define vlRegexpNSUBEXP	10
typedef struct vlRegexpInfo {
	const char *startp[vlRegexpNSUBEXP];
	const char *endp[vlRegexpNSUBEXP];
} vlRegexpInfoT;

typedef struct vlRegexp {
	char regstart;		/* Internal use only. */
	char reganch;		/* Internal use only. */
	char *regmust;		/* Internal use only. */
	int regmlen;		/* Internal use only. */
	char program[1];	/* Unwarranted chumminess with compiler. */
} vlRegexpT, *vlRegexpID;

extern vlRegexpT *vlRegexpCompile vlARGS((const char *));
extern void vlRegexpDestroy vlARGS((vlRegexpT *));
extern int vlRegexpExec vlARGS((vlRegexpT *, vlRegexpInfoT *, const char *));
extern void vlRegexpReplace vlARGS((vlRegexpT *, vlRegexpInfoT *, char *, char *));
extern char *vlRegexpGetMatchAlloc vlARGS((vlRegexpInfoT *, int));
extern int vlRegexpGetMatch vlARGS((vlRegexpInfoT *, int, char *, int));

#endif /* vlREGEXP_H */
