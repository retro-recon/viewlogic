/* ------------------------------------------------------------------------ *\
 * $Id: vldufs.h,v 1.3.9.1 1995/10/17 20:40:03 cway Stab $
 * Public header for portable binary files
 *
 * Copyright (c) 1991 by Viewlogic Systems, Inc.
 * ---- change log ----
 */


#ifndef vlDUFSB_H
#define vlDUFSB_H

/* Public datatypes */

typedef struct vlDufsBFileDesc *vlDufsBID;
#define vlDufsBSTRMAX 255

/* ========================================================================= */
/* These are PRIVATE to the vlDufsB package - PLEASE do not use */

typedef enum {
    vlDufsBByte = 0,
    vlDufsBShort,
    vlDufsBInt,
    vlDufsBEnum,
    vlDufsBLong,
    vlDufsBFloat,
    vlDufsBDouble,
    vlDufsBString
} vlDufsBDataT;

int vlDufsBRead vlARG5(vlDufsBID, vlPointerT, int, vlDufsBDataT, vlBoolT);
int vlDufsBWrite vlARG4(vlDufsBID, vlPointerT, int, int);

/* ========================================================================= */
/* Public interfaces */

vlDufsBID vlDufsBFopen vlARG2(const char *, const char *);
vlDufsBID vlDufsBSetup vlARG2(FILE *, char *);
void vlDufsBFclose vlARG1(vlDufsBID);
long vlDufsBFtell vlARG1(vlDufsBID);
int vlDufsBFseek vlARG3(vlDufsBID, long, int);
void vlDufsBRewind vlARG1(vlDufsBID);
FILE *vlDufsBGetFD vlARG1(vlDufsBID);

int vlDufsBWriteString vlARG2(vlDufsBID, char *);

/*\Docpage vlDufsBReadByte -- Read bytes from a binary file
 *
 * DESCRIPTION
 *
 * vlDufsBReadByte reads a bunch of 8 bit bytes from a binary file
 *
 * RETURNS
 *
 * Number of bytes read
 *
 * ERROR INDICATIONS
 *
 *   o If the value returned != nitems, there was a file system error and errno
 *     should be checked for the actual error.
 *   o If the Binary file ID (vlDufsBID) is invalid, a PRE_COND exception is
 *     posted with the error "vlDufsB_E_INVALID_BID".
 *
 * SYNOPSIS
 *
 * int vlDufsBReadByte(bid, buf, nitems)
 *     vlDufsBID bid;  |* id of the binary file to read from *|
 *     vlPointerT buf; |* buffer to place the data into *|
 *     int nitems;     |* number of bytes to read *|
 */

#define vlDufsBReadByte(id, buf, cnt)\
    vlDufsBRead(id, (vlPointerT) (buf), cnt, vlDufsBByte, FALSE)

/*\Docpage vlDufsBReadString -- Read a string from a binary file
 *
 * DESCRIPTION
 *
 * vlDufsBReadString reads a NUL terminated string from the binary file.
 * The buffer must be able to hold at LEAST vlDufsBSTRMAX + 1 characters.
 *
 * RETURNS
 *
 *   0 if the read failed
 *   1 if the string was read
 *
 * ERROR INDICATIONS
 *
 *   o If the value returned = 0, there was a file system error and errno
 *     should be checked for the actual error.
 *   o If the Binary file ID (vlDufsBID) is invalid, a PRE_COND exception is
 *     posted with the error "vlDufsB_E_INVALID_BID".
 *
 * SYNOPSIS
 *
 * int vlDufsBReadByte(bid, buf)
 *     vlDufsBID bid;  |* id of the binary file to read from *|
 *     vlPointerT buf; |* buffer to place the string into *|
 */

#define vlDufsBReadString(id, buf)\
    vlDufsBRead(id, (vlPointerT) (buf), 1, vlDufsBString, FALSE)

/*\Docpage vlDufsBReadShort -- Read shorts from a binary file
 *
 * DESCRIPTION
 *
 * vlDufsBReadShort reads a bunch of shorts from a binary file.
 *
 * If the byte ordering of shorts in the file differs from the byte ordering
 * of shorts on the native machine, each short read will be byte-swapped.
 *
 * Differences in the size of a short between the creating machine and the
 * reading machine are handled as follows:
 *   o If the short of the creator is SMALLER than the short of
 *     the reader, the shorts read are sign extended.
 *   o If the short of the creator is LARGER than the short of
 *     the reader, the "extra" Most Significant Bytes (of the short in the
 *     file) MUST be filled with only with sign bits or an exception will
 *     occur.
 *
 * RETURNS
 *
 *   Returns the number of shorts actually read
 *
 * ERROR INDICATIONS
 *
 *   o If the value returned < nitems, there was a file system error and errno
 *     should be checked for the actual error.
 *   o If the precision (number of significant bytes) of a short in the file
 *     exceeds the precision of the short for the current machine, a POST_COND
 *     exception is posted with the error "vlDufsB_E_PREC_EXCEEDED"
 *   o If the Binary file ID (vlDufsBID) is invalid, a PRE_COND exception is
 *     posted with the error "vlDufsB_E_INVALID_BID".
 *
 * SYNOPSIS
 *
 * int vlDufsBReadShort(bid, buf, nitems)
 *     vlDufsBID bid;  |* id of the binary file to read from *|
 *     vlPointerT buf; |* buffer to place the data into *|
 *     int nitems;     |* number of shorts to read *|
 */

#define vlDufsBReadShort(id, buf, cnt)\
    vlDufsBRead(id, (vlPointerT) (buf), cnt, vlDufsBShort, TRUE)

/*\Docpage vlDufsBReadShortUnsigned -- Read unsigned shorts from a binary file
 *
 * DESCRIPTION
 *
 * vlDufsBReadShortUnsigned reads a bunch of unsigned shorts from a binary
 * file.
 *
 * If the byte ordering of shorts in the file differs from the byte ordering
 * of shorts on the native machine, each short read will be byte-swapped.
 *
 * Differences in the size of a short between the creating machine and the
 * reading machine are handled as follows:
 *   o If the short of the creator is SMALLER than the short of
 *     the reader, the unsigned shorts read are padded with leading zeros.
 *   o If the short of the creator is LARGER than the short of
 *     the reader, the "extra" Most Significant Bytes (of the unsigned short
 *     in the file) MUST be filled with only with zeros or an exception will
 *     occur.
 *
 * RETURNS
 *
 *   Returns the number of unsigned shorts actually read
 *
 * ERROR INDICATIONS
 *
 *   o If the value returned < nitems, there was a file system error and errno
 *     should be checked for the actual error.
 *   o If the precision (number of significant bytes) of a short in the file
 *     exceeds the precision of the short for the current machine, a POST_COND
 *     exception is posted with the error "vlDufsB_E_PREC_EXCEEDED"
 *   o If the Binary file ID (vlDufsBID) is invalid, a PRE_COND exception is
 *     posted with the error "vlDufsB_E_INVALID_BID".
 *
 * SYNOPSIS
 *
 * int vlDufsBReadShortUnsigned(bid, buf, nitems)
 *     vlDufsBID bid;  |* id of the binary file to read from *|
 *     vlPointerT buf; |* buffer to place the data into *|
 *     int nitems;     |* number of shorts to read *|
 */

#define vlDufsBReadShortUnsigned(id, buf, cnt)\
    vlDufsBRead(id, (vlPointerT) (buf), cnt, vlDufsBShort, FALSE)

/*\Docpage vlDufsBReadInt -- Read ints from a binary file
 *
 * DESCRIPTION
 *
 * vlDufsBReadInt reads a bunch of ints from a binary file.
 *
 * If the byte ordering of ints in the file differs from the byte ordering
 * of ints on the native machine, each int read will be byte-swapped.
 *
 * Differences in the size of a int between the creating machine and the
 * reading machine are handled as follows:
 *   o If the int of the creator is SMALLER than the int of
 *     the reader, the ints read are sign extended.
 *   o If the int of the creator is LARGER than the int of
 *     the reader, the "extra" Most Significant Bytes (of the int in the
 *     file) MUST be filled with only with sign bits or an exception will
 *     occur.
 *
 * RETURNS
 *
 *   Returns the number of ints actually read
 *
 * ERROR INDICATIONS
 *
 *   o If the value returned < nitems, there was a file system error and errno
 *     should be checked for the actual error.
 *   o If the precision (number of significant bytes) of a int in the file
 *     exceeds the precision of the int for the current machine, a POST_COND
 *     exception is posted with the error "vlDufsB_E_PREC_EXCEEDED"
 *   o If the Binary file ID (vlDufsBID) is invalid, a PRE_COND exception is
 *     posted with the error "vlDufsB_E_INVALID_BID".
 *
 * SYNOPSIS
 *
 * int vlDufsBReadInt(bid, buf, nitems)
 *     vlDufsBID bid;  |* id of the binary file to read from *|
 *     vlPointerT buf; |* buffer to place the data into *|
 *     int nitems;     |* number of ints to read *|
 */

#define vlDufsBReadInt(id, buf, cnt)\
    vlDufsBRead(id, (vlPointerT) (buf), cnt, vlDufsBInt, TRUE)

/*\Docpage vlDufsBReadIntUnsigned -- Read unsigned ints from a binary file
 *
 * DESCRIPTION
 *
 * vlDufsBReadIntUnsigned reads a bunch of unsigned ints from a binary
 * file.
 *
 * If the byte ordering of ints in the file differs from the byte ordering
 * of ints on the native machine, each int read will be byte-swapped.
 *
 * Differences in the size of a int between the creating machine and the
 * reading machine are handled as follows:
 *   o If the int of the creator is SMALLER than the int of
 *     the reader, the unsigned ints read are padded with leading zeros.
 *   o If the int of the creator is LARGER than the int of
 *     the reader, the "extra" Most Significant Bytes (of the unsigned int
 *     in the file) MUST be filled with only with zeros or an exception will
 *     occur.
 *
 * RETURNS
 *
 *   Returns the number of unsigned ints actually read
 *
 * ERROR INDICATIONS
 *
 *   o If the value returned < nitems, there was a file system error and errno
 *     should be checked for the actual error.
 *   o If the precision (number of significant bytes) of a int in the file
 *     exceeds the precision of the int for the current machine, a POST_COND
 *     exception is posted with the error "vlDufsB_E_PREC_EXCEEDED"
 *   o If the Binary file ID (vlDufsBID) is invalid, a PRE_COND exception is
 *     posted with the error "vlDufsB_E_INVALID_BID".
 *
 * SYNOPSIS
 *
 * int vlDufsBReadIntUnsigned(bid, buf, nitems)
 *     vlDufsBID bid;  |* id of the binary file to read from *|
 *     vlPointerT buf; |* buffer to place the data into *|
 *     int nitems;     |* number of ints to read *|
 */

#define vlDufsBReadIntUnsigned(id, buf, cnt)\
    vlDufsBRead(id, (vlPointerT) (buf), cnt, vlDufsBInt, FALSE)

/*\Docpage vlDufsBReadEnum -- Read enums from a binary file
 *
 * DESCRIPTION
 *
 * vlDufsBReadEnum reads a bunch of enums from a binary file.
 *
 * If the byte ordering of enums in the file differs from the byte ordering
 * of enums on the native machine, each enum read will be byte-swapped.
 *
 * Differences in the size of a enum between the creating machine and the
 * reading machine are handled as follows:
 *   o If the enum of the creator is SMALLER than the enum of
 *     the reader, the enums read are sign extended.
 *   o If the enum of the creator is LARGER than the enum of
 *     the reader, the "extra" Most Significant Bytes (of the enum in the
 *     file) MUST be filled with only with sign bits or an exception will
 *     occur.
 *
 * RETURNS
 *
 *   Returns the number of enums actually read
 *
 * ERROR INDICATIONS
 *
 *   o If the value returned < nitems, there was a file system error and errno
 *     should be checked for the actual error.
 *   o If the precision (number of significant bytes) of a enum in the file
 *     exceeds the precision of the enum for the current machine, a POST_COND
 *     exception is posted with the error "vlDufsB_E_PREC_EXCEEDED"
 *   o If the Binary file ID (vlDufsBID) is invalid, a PRE_COND exception is
 *     posted with the error "vlDufsB_E_INVALID_BID".
 *
 * SYNOPSIS
 *
 * int vlDufsBReadEnum(bid, buf, nitems)
 *     vlDufsBID bid;  |* id of the binary file to read from *|
 *     vlPointerT buf; |* buffer to place the data into *|
 *     int nitems;     |* number of enums to read *|
 */

#define vlDufsBReadEnum(id, buf, cnt)\
    vlDufsBRead(id, (vlPointerT) (buf), cnt, vlDufsBEnum, TRUE)

/*\Docpage vlDufsBReadLong -- Read longs from a binary file
 *
 * DESCRIPTION
 *
 * vlDufsBReadLong reads a bunch of longs from a binary file.
 *
 * If the byte ordering of longs in the file differs from the byte ordering
 * of longs on the native machine, each long read will be byte-swapped.
 *
 * Differences in the size of a long between the creating machine and the
 * reading machine are handled as follows:
 *   o If the long of the creator is SMALLER than the long of
 *     the reader, the longs read are sign extended.
 *   o If the long of the creator is LARGER than the long of
 *     the reader, the "extra" Most Significant Bytes (of the long in the
 *     file) MUST be filled with only with sign bits or an exception will
 *     occur.
 *
 * RETURNS
 *
 *   Returns the number of longs actually read
 *
 * ERROR INDICATIONS
 *
 *   o If the value returned < nitems, there was a file system error and errno
 *     should be checked for the actual error.
 *   o If the precision (number of significant bytes) of a long in the file
 *     exceeds the precision of the long for the current machine, a POST_COND
 *     exception is posted with the error "vlDufsB_E_PREC_EXCEEDED"
 *   o If the Binary file ID (vlDufsBID) is invalid, a PRE_COND exception is
 *     posted with the error "vlDufsB_E_INVALID_BID".
 *
 * SYNOPSIS
 *
 * int vlDufsBReadLong(bid, buf, nitems)
 *     vlDufsBID bid;  |* id of the binary file to read from *|
 *     vlPointerT buf; |* buffer to place the data into *|
 *     int nitems;     |* number of longs to read *|
 */

#define vlDufsBReadLong(id, buf, cnt)\
    vlDufsBRead(id, (vlPointerT) (buf), cnt, vlDufsBLong, TRUE)

/*\Docpage vlDufsBReadLongUnsigned -- Read unsigned longs from a binary file
 *
 * DESCRIPTION
 *
 * vlDufsBReadLongUnsigned reads a bunch of unsigned longs from a binary
 * file.
 *
 * If the byte ordering of longs in the file differs from the byte ordering
 * of longs on the native machine, each long read will be byte-swapped.
 *
 * Differences in the size of a long between the creating machine and the
 * reading machine are handled as follows:
 *   o If the long of the creator is SMALLER than the long of
 *     the reader, the unsigned longs read are padded with leading zeros.
 *   o If the long of the creator is LARGER than the long of
 *     the reader, the "extra" Most Significant Bytes (of the unsigned long
 *     in the file) MUST be filled with only with zeros or an exception will
 *     occur.
 *
 * RETURNS
 *
 *   Returns the number of unsigned longs actually read
 *
 * ERROR INDICATIONS
 *
 *   o If the value returned < nitems, there was a file system error and errno
 *     should be checked for the actual error.
 *   o If the precision (number of significant bytes) of a long in the file
 *     exceeds the precision of the long for the current machine, a POST_COND
 *     exception is posted with the error "vlDufsB_E_PREC_EXCEEDED"
 *   o If the Binary file ID (vlDufsBID) is invalid, a PRE_COND exception is
 *     posted with the error "vlDufsB_E_INVALID_BID".
 *
 * SYNOPSIS
 *
 * int vlDufsBReadLongUnsigned(bid, buf, nitems)
 *     vlDufsBID bid;  |* id of the binary file to read from *|
 *     vlPointerT buf; |* buffer to place the data into *|
 *     int nitems;     |* number of longs to read *|
 */

#define vlDufsBReadLongUnsigned(id, buf, cnt)\
    vlDufsBRead(id, (vlPointerT) (buf), cnt, vlDufsBLong, FALSE)

/*\Docpage vlDufsBReadFloat -- Read floats from a binary file
 *
 * DESCRIPTION
 *
 * vlDufsBReadFloat reads a bunch of floats from a binary file.
 *
 * If the byte ordering of floats in the file differs from the byte ordering
 * of floats on the native machine, each float read will be byte-swapped.
 *
 * RETURNS
 *
 *   Returns the number of floats actually read
 *
 * ERROR INDICATIONS
 *
 *   o If the value returned < nitems, there was a file system error and errno
 *     should be checked for the actual error.
 *   o If the Binary file ID (vlDufsBID) is invalid, a PRE_COND exception is
 *     posted with the error "vlDufsB_E_INVALID_BID".
 *
 * SYNOPSIS
 *
 * int vlDufsBReadFloat(bid, buf, nitems)
 *     vlDufsBID bid;  |* id of the binary file to read from *|
 *     vlPointerT buf; |* buffer to place the data into *|
 *     int nitems;     |* number of floats to read *|
 */

#define vlDufsBReadFloat(id, buf, cnt)\
    vlDufsBRead(id, (vlPointerT) (buf), cnt, vlDufsBFloat, TRUE)

/*\Docpage vlDufsBReadDouble -- Read doubles from a binary file
 *
 * DESCRIPTION
 *
 * vlDufsBReadDouble reads a bunch of doubles from a binary file.
 *
 * If the byte ordering of doubles in the file differs from the byte ordering
 * of doubles on the native machine, each double read will be byte-swapped.
 *
 * RETURNS
 *
 *   Returns the number of doubles actually read
 *
 * ERROR INDICATIONS
 *
 *   o If the value returned < nitems, there was a file system error and errno
 *     should be checked for the actual error.
 *   o If the Binary file ID (vlDufsBID) is invalid, a PRE_COND exception is
 *     posted with the error "vlDufsB_E_INVALID_BID".
 *
 * SYNOPSIS
 *
 * int vlDufsBReadDouble(bid, buf, nitems)
 *     vlDufsBID bid;  |* id of the binary file to read from *|
 *     vlPointerT buf; |* buffer to place the data into *|
 *     int nitems;     |* number of doubles to read *|
 */

#define vlDufsBReadDouble(id, buf, cnt)\
    vlDufsBRead(id, (vlPointerT) (buf), cnt, vlDufsBDouble, TRUE)

/*\Docpage vlDufsBWriteByte -- Write bytes to a binary file
 *
 * DESCRIPTION
 *
 * vlDufsBWriteByte writes a bunch of 8 bit bytes to a binary file.
 *
 * RETURNS
 *
 *   Returns the number of bytes actually written
 *
 * ERROR INDICATIONS
 *
 *   o If the value returned < nitems, there was a file system error and errno
 *     should be checked for the actual error.
 *   o If the Binary file ID (vlDufsBID) is invalid, a PRE_COND exception is
 *     posted with the error "vlDufsB_E_INVALID_BID".
 *
 * SYNOPSIS
 *
 * int vlDufsBWriteByte(bid, buf, nitems)
 *     vlDufsBID bid;  |* id of the binary file to write to *|
 *     vlPointerT buf; |* buffer to write the data from *|
 *     int nitems;     |* number of bytes to write *|
 */

#define vlDufsBWriteByte(id, buf, cnt)\
    vlDufsBWrite(id, (vlPointerT) (buf), cnt, 1)

/*\Docpage vlDufsBWriteShort -- Write shorts to a binary file
 *
 * DESCRIPTION
 *
 * vlDufsBWriteShort writes a bunch of shorts to a binary file.
 *
 * RETURNS
 *
 *   Returns the number of shorts actually written
 *
 * ERROR INDICATIONS
 *
 *   o If the value returned < nitems, there was a file system error and errno
 *     should be checked for the actual error.
 *   o If the Binary file ID (vlDufsBID) is invalid, a PRE_COND exception is
 *     posted with the error "vlDufsB_E_INVALID_BID".
 *
 * SYNOPSIS
 *
 * int vlDufsBWriteShort(bid, buf, nitems)
 *     vlDufsBID bid;  |* id of the binary file to write to *|
 *     vlPointerT buf; |* buffer to write the data from *|
 *     int nitems;     |* number of shorts to write *|
 */

#define vlDufsBWriteShort(id, buf, cnt)\
    vlDufsBWrite(id, (vlPointerT) (buf), cnt, sizeof(short))

/*\Docpage vlDufsBWriteInt -- Write ints to a binary file
 *
 * DESCRIPTION
 *
 * vlDufsBWriteInt writes a bunch of ints to a binary file.
 *
 * RETURNS
 *
 *   Returns the number of ints actually written
 *
 * ERROR INDICATIONS
 *
 *   o If the value returned < nitems, there was a file system error and errno
 *     should be checked for the actual error.
 *   o If the Binary file ID (vlDufsBID) is invalid, a PRE_COND exception is
 *     posted with the error "vlDufsB_E_INVALID_BID".
 *
 * SYNOPSIS
 *
 * int vlDufsBWriteInt(bid, buf, nitems)
 *     vlDufsBID bid;  |* id of the binary file to write to *|
 *     vlPointerT buf; |* buffer to write the data from *|
 *     int nitems;     |* number of ints to write *|
 */

#define vlDufsBWriteInt(id, buf, cnt)\
    vlDufsBWrite(id, (vlPointerT) (buf), cnt, sizeof(int))

/*\Docpage vlDufsBWriteEnum -- Write enums to a binary file
 *
 * DESCRIPTION
 *
 * vlDufsBWriteEnum writes a bunch of enums to a binary file.
 *
 * RETURNS
 *
 *   Returns the number of enums actually written
 *
 * ERROR INDICATIONS
 *
 *   o If the value returned < nitems, there was a file system error and errno
 *     should be checked for the actual error.
 *   o If the Binary file ID (vlDufsBID) is invalid, a PRE_COND exception is
 *     posted with the error "vlDufsB_E_INVALID_BID".
 *
 * SYNOPSIS
 *
 * int vlDufsBWriteEnum(bid, buf, nitems)
 *     vlDufsBID bid;  |* id of the binary file to write to *|
 *     vlPointerT buf; |* buffer to write the data from *|
 *     int nitems;     |* number of enums to write *|
 */

#define vlDufsBWriteEnum(id, buf, cnt)\
    vlDufsBWrite(id, (vlPointerT) (buf), cnt, sizeof(int))

/*\Docpage vlDufsBWriteLong -- Write longs to a binary file
 *
 * DESCRIPTION
 *
 * vlDufsBWriteLong writes a bunch of longs to a binary file.
 *
 * RETURNS
 *
 *   Returns the number of longs actually written
 *
 * ERROR INDICATIONS
 *
 *   o If the value returned < nitems, there was a file system error and errno
 *     should be checked for the actual error.
 *   o If the Binary file ID (vlDufsBID) is invalid, a PRE_COND exception is
 *     posted with the error "vlDufsB_E_INVALID_BID".
 *
 * SYNOPSIS
 *
 * int vlDufsBWriteLong(bid, buf, nitems)
 *     vlDufsBID bid;  |* id of the binary file to write to *|
 *     vlPointerT buf; |* buffer to write the data from *|
 *     int nitems;     |* number of longs to write *|
 */

#define vlDufsBWriteLong(id, buf, cnt)\
    vlDufsBWrite(id, (vlPointerT) (buf), cnt, sizeof(long))

/*\Docpage vlDufsBWriteFloat -- Write floats to a binary file
 *
 * DESCRIPTION
 *
 * vlDufsBWriteFloat writes a bunch of floats to a binary file.
 *
 * RETURNS
 *
 *   Returns the number of floats actually written
 *
 * ERROR INDICATIONS
 *
 *   o If the value returned < nitems, there was a file system error and errno
 *     should be checked for the actual error.
 *   o If the Binary file ID (vlDufsBID) is invalid, a PRE_COND exception is
 *     posted with the error "vlDufsB_E_INVALID_BID".
 *
 * SYNOPSIS
 *
 * int vlDufsBWriteFloat(bid, buf, nitems)
 *     vlDufsBID bid;  |* id of the binary file to write to *|
 *     vlPointerT buf; |* buffer to write the data from *|
 *     int nitems;     |* number of floats to write *|
 */

#define vlDufsBWriteFloat(id, buf, cnt)\
    vlDufsBWrite(id, (vlPointerT) (buf), cnt, sizeof(float))

/*\Docpage vlDufsBWriteDouble -- Write doubles to a binary file
 *
 * DESCRIPTION
 *
 * vlDufsBWriteDouble writes a bunch of doubles to a binary file.
 *
 * RETURNS
 *
 *   Returns the number of doubles actually written
 *
 * ERROR INDICATIONS
 *
 *   o If the value returned < nitems, there was a file system error and errno
 *     should be checked for the actual error.
 *   o If the Binary file ID (vlDufsBID) is invalid, a PRE_COND exception is
 *     posted with the error "vlDufsB_E_INVALID_BID".
 *
 * SYNOPSIS
 *
 * int vlDufsBWriteDouble(bid, buf, nitems)
 *     vlDufsBID bid;  |* id of the binary file to write to *|
 *     vlPointerT buf; |* buffer to write the data from *|
 *     int nitems;     |* number of doubles to write *|
 */

#define vlDufsBWriteDouble(id, buf, cnt)\
    vlDufsBWrite(id, (vlPointerT) (buf), cnt, sizeof(double))

#endif
