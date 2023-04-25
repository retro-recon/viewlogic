#ifndef SIGPUB_H
#define SIGPUB_H

#include "vllib.h"

extern char * vlRemPinFromSigAtt vlARG3(char *,char *,char *);
extern char * vlMergePinToSigAtt vlARG4(char *,char *,char *,int);
extern int vlFillSigNc vlARG5(int,char *,char *,char *,char *);
extern int vlSigNcStat vlARG1(char *);

#define vlSigISNOTSIGNC 1
#define vlSigISSIGNAL 2
#define vlSigISNC 3
#define vlSigISBADLYFORMED 4

#define vlPAULS_SIZE 127
#define vlSEXSIZE 256

/* these are for compatibility from the days before these were moved here */
/* some of these don't really need to be public but I don't want to */
/* mess with it at this late date */
#define vpbRemPinFromSigAtt vlRemPinFromSigAtt
#define vpbMergePinToSigAtt vlMergePinToSigAtt
#define vpbFillSigNc        vlFillSigNc
#define vpbSigNcStat        vlSigNcStat
#define vpbSigISNOTSIGNC    vlSigISNOTSIGNC
#define vpbSigISSIGNAL      vlSigISSIGNAL
#define vpbSigISNC          vlSigISNC
#define vpbSigISBADLYFORMED vlSigISBADLYFORMED
#define PAULS_SIZE vlPAULS_SIZE
#define SEXSIZE vlSEXSIZE

#endif
