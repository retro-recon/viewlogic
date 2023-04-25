/*  $Id: vlmag.h,v 1.3.4.1 1995/10/17 20:42:13 cway Stab $
 */


#ifndef vlmag_H
#define vlmag_H

/* keep all of these in sync! */

typedef enum {
    vlMagUNSET = -1,
    vlMagATTO,
    vlMagFEMTO,
    vlMagPICO,
    vlMagNANO,
    vlMagMICRO,
    vlMagMILLI,
    vlMagNONE,
    vlMagKILO,
    vlMagMEGA,
    vlMagGIGA,
    vlMagTERA
} vlMagT;

#ifdef vlmagDEFINING_TYPESPEC
static const char *asMagChoices[] = {
    "Atto",
    "Femto",
    "Pico",
    "Nano",
    "Micro",
    "Milli",
    "None",
    "Kilo",
    "Mega",
    "Giga",
    "Tera"
};
#endif

#ifdef vlmagDEFINING_CONVERSIONS
static const char *mag2abbrev[] = {
    "a",
    "f",
    "p",
    "n",
    "u",
    "m",
    "",
    "k",
    "M",
    "G",
    "T"
};

#if 0
static const char *mag2longname[] = {
    "atto",
    "femto",
    "pico",
    "nano",
    "micro",
    "milli",
    "",
    "kilo",
    "mega",
    "giga",
    "tera"
};
#endif

static short mag2exponent[] = {
    -18,
    -15,
    -12,
    -9,
    -6,
    -3,
    0,
    3,
    6,
    9,
    12
};

static float mag2value[] = {
    1e-18,
    1e-15,
    1e-12,
    1e-9,
    1e-6,
    1e-3,
    1,
    1e+3,
    1e+6,
    1e+9,
    1e+12
};
#endif

#endif
