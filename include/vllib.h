/*
 *  $Revision: 2.128.1.2 $  $Date    : 94/01/05 18:33:15 $
 *
 *  The vllib library master header file.
 *
 *  Copyright (c) 1984,1994 by Viewlogic Systems, Inc.
 */


#ifndef vlLIB_H
#define vlLIB_H

#ifndef vlDEFS_H
#include "vldefs.h"
#endif

#ifndef vlVARGS_H
#include "vlvargs.h"
#endif

#ifndef vsLIB_H
#include "vslib.h"
#endif

#ifndef vlMsg_H
#include "vlmsg.h"
#endif

#ifndef vlERR_H
#include "vlerr.h"
#endif

#ifndef vlEXCEPT_H
#include "vlexcept.h"
#endif

#if vlOS_WIN32
extern void vlpcErrYell vlARGS((char* msg));
extern void vlpcExit vlARGS((int code));
extern void vlpcAbort vlARGS((int code));
#endif

#include <limits.h>


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

/*\Section vllib -- Portability & Reusability Library

                         MASTER SECTION INDEX

-------------------------------------------------------------------------------

615 banners -- routines for generating the WORKVIEW copyright banner

     vlBannerStrWV - Generate the WORKVIEW copyright banner
     vlBannerStr - Generate a facility's VIEWlogic copyright banner
     vlBanner - print a facility's VIEWlogic copyright banner on stdout

-------------------------------------------------------------------------------

619 BusNotation -- Routines for parsing bus strings

     vlBusExpandStatus - get execution status
     vlBusExpandRepsep - replace default token separators (delimiters)
     vlBusExpandCopy - make a copy of an expansion structure
     vlBusExpandFrame - test to see if string contains frame segment(s)
     vlBusExpandWidth - get the number of substrings in a bus string
     vlBusExpandFree - release a bus structure (not normally used)
     vlBusExpand - expand a bus string into sub-strings
     vlBusExpandSubset - test if one string is a subset of another

-------------------------------------------------------------------------------

628 vlCell -- ROutines for handling a dynamic list of objects.

     vlCellNew -- create a new cell structure
     vlCellFLSave  -- save cell on free list
     vlCellFLFree  -- frees the memory used by the cell free list
     vlCellFound   -- determine if there is a cell pointing to item
     vlCellAdd -- add a cell to list of cells, given an item
     vlCellRemove -- remove cell that points to an item from list
     vlCellFree -- Free a list of cells and their items
     vlCellStrFree -- Free a list of cells and their string items
     vlCellFind -- looks for an item in a list of cells

-------------------------------------------------------------------------------

829 vlCvt -- Conversion of decimal, hexadecimal, octal, binary, etc.

     vlCvtStrBin -- convert to binary
     vlCvtDecBin -- convert decimal to binary
     vlCvtHexBin -- convert hex to binary
     vlCvtOctBin -- convert octal to binary
     vlCvtIsBinary -- convert binary to binary
     vlCvtBinOct -- convert binary to octal
     vlCvtBinHex -- convert binary to hex
     vlCvtBinDec -- convert binary to decimal
     vlCvtTimeStr -- convert a time value to a string
     vlCvtTime -- convert seconds in long to time in ints
     vlCvtDtostr -- formatting doubles into strings in various ways.
     vlCvtUstrtod -- reading strings with units notation into doubles
     vlCvtIntStr -- convert integer to string
     vlCvtLongStr -- convert long integer to string
     vlCvtFloatStr -- convert floating point number to string
     vlCvtUpc -- convert character to upper case
     vlCvtLoc -- convert character to lower case
     vlCvtStrInt -- convert ASCII string to integer

-------------------------------------------------------------------------------

637 vlDlist -- Doubly linked lists

     vlDlistAddHead -- Add a new element to the beginning of a list
     vlDlistAddTail -- Add a new element to the end of a list
     vlDlistRemHead -- Delete the first element of a list and return it
     vlDlistRemTail -- Delete the last element of a list and return it
     vlDlistHead -- Return the first element of a list
     vlDlistTail -- Return the first element of a list
     vlDlistEmpty -- Return TRUE if the list is empty
     vlDlistSize -- Return the number of elements in a list
     vlDlistSearchFor -- Search for an element in a list
     vlDlistSearchForKey -- Search with user-defined equality test
     vlDlistDelElement -- Delete an element in the list
     vlDlistCurElement -- return the current element
     vlDlistCurCell -- return the current cell
     vlDlistSetCurrent -- Set the current cell
     vlDlistNxtElement -- set current to next element and return it
     vlDlistPreElement -- set current to previous element and return it
     vlDlistNxtCell -- set current to next cell and return it
     vlDlistPreCell -- set current to previous cell and return it
     vlDlistCurFirst -- Is current cell the head of the list?
     vlDlistCurLast -- Is current cell the tail of the list?
     vlDlistDelCurrent -- Delete the current cell
     vlDlistInsBefore -- Insert element before current cell
     vlDlistInsAfter -- Insert element after current cell
     vlDlistLoop -- Iterate through a list
     vlDlistReverseLoop -- Iterate through a list in reverse order
     vlDlistLoop2 -- Iterate through a list with 2 arguments
     vlDlistLoop3 -- Iterate through a list with 3 arguments
     vlDlistMovhh -- Move head of from_list to head of to_list
     vlDlistMovht -- move head of from_list to tail of to_list
     vlDlistMovth -- Move tail of from_list to head of to_list
     vlDlistFreeList -- Free a list
     vlDlistDestroyList -- Free a list and its elements
     vlDlistPurge -- Clear out internal free lists
     vlDlistMoveAll -- Move all elements of source to destination
     vlDlistVerifyList -- Sanity check for list structures

-------------------------------------------------------------------------------

672 vlDufs -- DOS <==> UNIX transparent ASCII file sharing

     vlDufsFgetc - DOS/UNIX transparent version of vrFgetc
     vlDufsFgets - DOS/UNIX transparent version of vrFgets
     vlDufsFgetline - reads a line of text, regardless of size

-------------------------------------------------------------------------------

776 vlDufsB -- Portable binary files for DOS/UNIX compatibility

     vlDufsBFopen -- Open a portable binary file
     vlDufsBSetup -- Setup a stdio file as a portable binary file
     vlDufsBFclose -- Close a portable binary file
     vlDufsBFtell -- return the current position of a binary file
     vlDufsBFseek -- set the current position of the binary file
     vlDufsBRewind -- position the binary file at the beginning
     vlDufsBGetFD -- get the file descriptor of the binary file
     vlDufsBWriteString -- Write a string to a portable binary file
     vlDufsBReadByte -- Read bytes from a binary file
     vlDufsBReadString -- Read a string from a binary file
     vlDufsBReadShort -- Read shorts from a binary file
     vlDufsBReadShortUnsigned -- Read unsigned shorts from a binary file
     vlDufsBReadInt -- Read ints from a binary file
     vlDufsBReadIntUnsigned -- Read unsigned ints from a binary file
     vlDufsBReadEnum -- Read enums from a binary file
     vlDufsBReadLong -- Read longs from a binary file
     vlDufsBReadLongUnsigned -- Read unsigned longs from a binary file
     vlDufsBReadFloat -- Read floats from a binary file
     vlDufsBReadDouble -- Read doubles from a binary file
     vlDufsBWriteByte -- Write bytes to a binary file
     vlDufsBWriteShort -- Write shorts to a binary file
     vlDufsBWriteInt -- Write ints to a binary file
     vlDufsBWriteEnum -- Write enums to a binary file
     vlDufsBWriteLong -- Write longs to a binary file
     vlDufsBWriteFloat -- Write floats to a binary file
     vlDufsBWriteDouble -- Write doubles to a binary file

-------------------------------------------------------------------------------

870 vlErr -- Error Handling

     vlErrOut -- output error
     vlErrOutBuild -- output error
     vlErrOutBuildVa -- output error
     vlErrOut2 -- output error (alternate for vlErrOut)
     vlErrOut3 -- output error (alternate for vlErrOut)
     vlErrReport -- output error
     vlErrReportBuild -- output error
     vlErrReportBuildVa -- output error
     vlErrReport2 -- output error
     vlErrYell -- report something on stderr
     vlErrCreate - create an error object
     vlErrCreate2 - create an error object
     vlErrCopy -- copy an error object
     vlErrDestroy - nuke an error object
     vlErrBuild - build an error object
     vlErrBuildVa - for use with vlErrReport (varargs version)
     vlErrLocationAttribute - return location string for attribute
     vlErrLocationUid - return location string for Viewdraw object
     vlErrLocationDesign - return location string for design
     vlErrLocationLine - return location string for file, line
     vlErrLocationFile - return location string for file
     vlErrLocationWave - return location string for waveform
     vlErrLocationMessage - return location string for message
     vlErrLocationRoutine - return location string for function call
     vlErrAppend -- append one error message to another
     vlErrApp -- get the application name of an error report
     vlErrText -- get the text of an error report
     vlErrLocation -- get the location of an error report
     vlErrSeverity -- get the severity of an error report
     vlErrNum -- get the message number of an error report
     vlErrLoop -- loop through all individual errors in a stacked object
     vlErrSeverityToString - get string representation of severity
     vlErrStringToSeverity - get severity from string representatino
     vlErrSeverityToChar - char representation of severity
     vlErrCharToSeverity - get severity from char representatino
     vlErrStreamCreate - create a message stream
     vlErrStreamDestroy - destroy a message stream
     vlErrStreamAdd - add a message to a stream
     vlErrStreamCount - how many messages are in a stream
     vlErrStreamGetAlert - get the alert box associated with a stream
     vlErrStreamSetAlert - set the alert box associated with a stream
     vlErrStreamBaddest - return the highest severity in stream
     vlErrStreamSummary - get types & counts of all messages in stream
     vlErrStreamExitCode - get the appropriate exit code
     vlErrInit -- initialize the error routines
     vlErrString - get the error report as a string
     vlErrSaveOnlyNewestFiles -- delete according to timestamp

-------------------------------------------------------------------------------

864 vlEx -- Exception Handling

     vlExThrow -- signal subroutine failure
     vlExThrow2 -- signal subroutine failure
     vlExThrowBuild -- signal subroutine failure
     vlExTagString -- return string representing exception type
     vlExDbg -- dummy function for debugging exceptions

-------------------------------------------------------------------------------

609 vlFl -- Routines for handling floating point numbers

     vlFlTrunc -- truncates a floating point number
     vlFlRound -- rounds a floating point number
     vlFlSqrt -- calculate square root of a number
     vlFlCos -- Compute the cosine of a number in degrees
     vlFlSin -- Compute the sine of a number in degrees

-------------------------------------------------------------------------------

680 vlList -- Singly and doubly linked lists

     vlListSins -- insert element into a singly linked list
     vlListSdel -- delete element from singly linked list
     vlListDins -- insert element into a doubly linked list
     vlListDdel -- delete element from doubly linked list
     vlListPrev -- get previous element in a list
     vlListLast -- get the last element in a list
     vlListSize -- counts the number of elements in a list
     vlListFree -- free the elements of a list

-------------------------------------------------------------------------------

770 vlMask -- Macros to help deal with masks

     vlMaskTURN_ON -- Turn on the specified bit in the mask
     vlMaskTURN_OFF -- Turn off the specified bit in the mask
     vlMaskSET -- Set the specified bit in the mask to on or off
     vlMaskGET -- Is specified bit in mask on?
     vlMaskTOGGLE -- Change specified bit in the mask

-------------------------------------------------------------------------------

848 vlMem -- Memory Management Functions

     vlMemMALLOC -- Allocate dynamic memory
     vlMemCALLOC -- Allocate and clear elements of memory
     vlMemREALLOC -- Change size of memory block.
     vlMemAlloca -- Conditionalized stack memory allocation.
     vlMemFreea -- Conditionalized stack memory allocation.
     vlMemALLOCA -- Conditionalized stack memory allocation.
     vlMemCpy -- copy a block of memory
     vlMemMove -- copy a block of memory
     vlMemOutV -- Function to free memory needed for allocation
     vlMemRchr -- search backwards in memory for a character
     vlMemMalloc -- Allocate dynamic memory with "identifier".
     vlMemCalloc -- Allocate and clear elements of memory with "identifier".
     vlMemRealloc -- Change size of memory block with "identifier".
     vlMemFree -- Free a block of dynamic memory.

-------------------------------------------------------------------------------

676 vlMemFl -- Centralized freelist support

     vlMemFlAlloc -- Allocate a block using the freelist
     vlMemFlFree -- Free a block to the freelist
     vlMemFlPurge -- Purge all memory held in freelists

-------------------------------------------------------------------------------

918 vlMsg -- Message Files

     vlMsgGenerateVa - the "real" vlMsgGenerate.
     vlMsgFileOpen - Open a specific message file.
     vlMsgFile -- returns the fileid for the vllib message file
     vlMsgGetFilename - Translate a FileID to a file name
     vlMsgFileClose - Close an open message file.
     vlMsgGenerate - Generate a printable message with converted data.
     vlMsgText - Get the raw text of a message with no data conversion.
     vlMsgAlloc - Place a generated message into a dynamic buffer.
     vlMsgStatic - Place a generated message into a static buffer.
     vlMsgBuffer - Place a generated message into a user managed buffer.
     vlMsgCopyToBuffer - Sample output function for vlMsgGenerate.
     vlMsgCopyAlloc - Sample output function for vlMsgGenerate.
     msgcomp -- message file compiler

-------------------------------------------------------------------------------

689 vlOldMsg -- Message Handling using the Workview message file

     vlMsgGet -- get a message given a message number
     vlMsgBuild - build a message from the Workview message file
     vlMsgBuildVa - build a msg out of msg file (varargs version)
     vlMsgOpen  -- open the Workview message file
     vlMsgClose -- close the Workview message file

-------------------------------------------------------------------------------

766 vlOnExit

     vlOnExitAdd -- Add a routine to be called on termination
     vlOnExitRemove -- Remove a routine from the termination list
     vlOnExitCall -- Call all the handlers and free them.

-------------------------------------------------------------------------------

695 vlPoint --  Collection of routines for handling points.

     vlPointNew -- allocate a list of points
     vlPointFree -- Free a list of points
     vlPointAdd -- add a point to a list given coordinates
     vlPointCopy -- copy a list of points
     vlPointDist -- calculate distance between two points
     vlPointSort -- sort points lower-left to upper-right

-------------------------------------------------------------------------------

704 vlPref -- Preferences

     vlPrefCreate -- Create a preference sub-database.
     vlPrefDestroy -- Destroy a preference sub-database.
     vlPrefAdd -- Add a new preference.
     vlPrefVal -- Get a preference value.
     vlPrefTypespec -- Get the type of a preference
     vlPrefDefault -- Get a preferences default.
     vlPrefChanged -- See if a preference has changed.
     vlPrefSetval -- Change a preference to a new value.
     vlPrefRevert -- Revert a preference value.
     vlPrefParse -- Parse the command line.
     vlPrefUsage -- Parse the command line for -usage, -help, or -?
     vlPrefForEachOption -- Loop through every preference option

-------------------------------------------------------------------------------

717 vlPrint -- ANSI formatted output with extensions

     vlSprintf - Full ANSI-C "safe" vrSprintf function with extensions
     vlSprintfVa - varargs version of vlSprintf
     vlSprintfStatic - ANSI-C "safe" vrSprintf into static buffer
     vlSprintfStaticVa - varargs version of vlSprintfStatic
     vlSprintfAlloc - ANSI "safe" vrSprintf into allocated buffer
     vlSprintfAllocVa - varargs version of vlSprintfAlloc

-------------------------------------------------------------------------------

702 ProcedureRoutines

     vlDummyProc  -- dummy routine which does nothing

-------------------------------------------------------------------------------

722 vlQ - Queue Manipulation

     vlQLifo -- create a LIFO queue
     vlQFifo -- create a FIFO queue
     vlQFree -- vrFree a queue
     vlQAdd -- add an element to the queue
     vlQTop -- get top element of a queue
     vlQPop -- get top element of the queue and remove it
     vlQSize --number of items currently in the queue

-------------------------------------------------------------------------------

932 vlRegexp -- Regular Expressions

     vlRegexpCompile - compile a regular expression
     vlRegexpDestroy - destroy a regular expression
     vlRegexpExec - match a regexp against a string
     vlRegexpReplace - perform substitutions after a regexp match
     vlRegexpGetMatchAlloc - return substring matching Nth subexpression
     vlRegexpGetMatch - return substring matching Nth subexpression

-------------------------------------------------------------------------------

982 vlRtc -- Run Time Type Checking

     vlRtcMsg -- Return string describing a type checking failure
     vlRtcDECLARE_TYPE -- Declare a static debugging type string
     vlRtcDECLARE_TYPE_GLOBAL -- Declare a global debugging type string
     vlRtcTYPE_DECLARATION -- Declare the type field of a structure
     vlRtcSET_TYPE -- Set the type field of a typed structure
     vlRtcSET_FREE -- Set the type field to "Free"
     vlRtcTYPE_CHECK -- check that a structure is of expected type
     vlRtcCREATE -- Allocate a structure and set its type field
     vlRtcDESTROY -- Clear a structures type field and free it

-------------------------------------------------------------------------------

730 vlSpFmt -- Sprintf format parsing.

     vlSpFmtParse -- Parse a vrSprintf style format string.
     vlSpFmtDescIs -- Identifies the token descriptor
     vlSpFmtArgIs -- Returns a bit mask describing the conversion
     vlSpFmtOrigStr -- Returns a pointer to the original format string
     vlSpFmtDescStr -- Returns a pointer to the current descriptor
     vlSpFmtArgFlags -- Return the conversion flags
     vlSpFmtArgConv -- Return the conversion specifier
     vlSpFmtArgPosition -- Return the position of argument in the list
     vlSpFmtArgWidth -- Minimum field width for the converted argument
     vlSpFmtArgPrecision -- Numerical precision of the argument

-------------------------------------------------------------------------------

803 vlStr - Functions for manipulating strings

     vlStrncpyNullTerm -- vrStrncpy will ensured NULL termination
     vlStrLoc -- lowercase a string
     vlStrUpc -- uppercase a string
     vlStrIcmp  -- string compare case insensitive
     vlStrNicmp  -- string compare n characters case insensitive
     vlStrBlk -- skip blanks (white space)
     vlStrBrk -- find break character in string
     vlStrIsnum  -- determines whether string is valid number
     vlStrCat -- concatenate two strings in static buffer
     vlStrCatAlloc -- concatenate two strings into a new buffer
     vlStrChr -- find the first occurence of char in string
     vlStrCpy -- copy a string into an allocated buffer
     vlStrCpy1 -- copy a string into an allocated string buffer
     vlStrEqu -- are two strings equal?
     vlStrIequ -- are two strings equal - case insensitive?
     vlStrIindex -- Find String in array of strings - case insensitive
     vlStrIndex -- Find String in array of strings
     vlStrIMat -- are two strings equal with wildcards - case insensitive?
     vlStrMat -- are two strings equal with wildcards?
     vlStrRch  -- find the last occurence of char in string
     vlStrTok -- get a token from a string
     vlStrTrim -- trim leading and trailing spaces from string
     vlStrLex -- vrStrtok with separate delim & skip lists
     vlStrUnlexdelim -- "push" back delimiter token for vlStrLex
     vlStrAlloc -- Allocate memory for a string
     vlStrFree -- Free memory for a string
     vlStrTerminate -- Destroy all string memory
     vlStrAlloca -- allocate a string on the stack
     vlStrFreea -- Free a string allocated by vlStrAlloca

-------------------------------------------------------------------------------

741 vlStrCvt -- Literal String Handling

     vlStrCvtChrset -- Identify character set used for literal strings.
     vlStrCvtFromLiteral -- Convert literal ASCII to 8 bit characters.
     vlStrCvtToAscii -- Convert binary char string to printable ASCII.

-------------------------------------------------------------------------------

745 vlSym -- Hash Symbol Tables

     vlSymCreate -- Create a symbol table.
     vlSymResize -- Resize a hash table to have a new number of buckets.
     vlSymDynamic -- Make a hash table grow dynamically.
     vlSymNotFoundValue -- Set the value returned on failure.
     vlSymDestroy -- Destroy a symbol table.
     vlSymClear -- Clear a symbol table.
     vlSymClearAddr -- Clear a symbol table.
     vlSymStore -- Store a new value for a symbol.
     vlSymFetch -- Fetch the value of a symbol.
     vlSymFetchAddr -- Fetch the address of the value of a symbol.
     vlSymRemove -- Remove the value of a symbol.
     vlSymLoop -- Loop through all symbol-value pairs in the table.
     vlSymLoopAddr -- Loop through all symbol-value pairs in the table.
     vlSymStHash -- Hash a string into an integer.
     vlSymStIhash -- Hash a string into an integer - case insensitive.
     vlSymStCpy -- Copy a string.
     vlSymStFree -- Free a string.
     vlSymPtrHash -- Hash a pointer into an unsigned int.
     vlSymPtrCmp -- Compare two pointers for equality.
     vlSymReturn -- Return the pointer argument.
     vlSymDummy -- Dummy for passing as free routine to vlSymCreate.
     vlSymDump -- Print a histogram of the symbol table to stdout.
     vlSymStrDump -- Print a histogram of a table with string keys.

-------------------------------------------------------------------------------

939 vlType -- Type specification system.

     vlTypeDataT -- Union for specifying typespec data.
     vlTypeBaseT -- Structure for specifying common typespecs info.
     vlTypeSpecT -- Structure for describing data types.
     vlTypeMAKE_PTR -- Make a typespec for a simple pointer type.
     vlTypeMAKE_PTR1 -- Make a typespec for a pointer type.
     vlTypeMAKE_PTR2 -- Make a typespec for a complex pointer type.
     vlTypeMAKE_PTR3 -- Make a typespec for a way-complex pointer type.
     vlTypeMAKE_PTR4 -- Make a typespec for a parsable pointer type
     vlTypeMAKE_ENUM -- Make an enum typespec from a string array.
     vlTypeMAKE_ENUM2 -- Make an enum typespec with two choices.
     vlTypeMAKE_ENUM3 -- Make an enum typespec with three choices.
     vlTypeMAKE_ENUM4 -- Make an enum typespec with four choices.
     vlTypeMAKE_ENUM5 -- Make an enum typespec with five choices.
     vlTypeMAKE_ENUM6 -- Make an enum typespec with six choices.
     vlTypeMAKE_ENUM7 -- Make an enum typespec with seven choices.
     vlTypeMAKE_ENUM8 -- Make an enum typespec with eight choices.
     vlTypeMAKE_ENUM9 -- Make an enum typespec with nine choices.
     vlTypeMAKE_ENUM10 -- Make an enum typespec with nine choices.
     vlTypeMAKE_MASK -- Make an mask typespec from a string array.
     vlTypeMAKE_MASK2 -- Make an mask typespec with two choices.
     vlTypeMAKE_MASK3 -- Make an mask typespec with three choices.
     vlTypeMAKE_MASK4 -- Make an mask typespec with four choices.
     vlTypeMAKE_MASK5 -- Make an mask typespec with five choices.
     vlTypeMAKE_MASK6 -- Make an mask typespec with six choices.
     vlTypeMAKE_MASK7 -- Make an mask typespec with seven choices.
     vlTypeMAKE_MASK8 -- Make an mask typespec with eight choices.
     vlTypeMAKE_MASK9 -- Make an mask typespec with nine choices.
     vlTypeMAKE_MASK10 -- Make an mask typespec with nine choices.
     vlTypeMAKE_INT -- Create an integer typespec.
     vlTypeMAKE_FLOAT -- Create a floating point typespec.
     vlTypeMAKE_STRING -- Make a string datatype with a check routine.
     vlTypeOUTPUT -- Call a routine with printed rep. of typespec data.
     vlTypeCONVERT -- Convert a string into data for a typespec.
     vlTypeIS_CONVERTIBLE -- Determine if a typespec is convertible.
     vlTypeIS_POINTER -- Determine if a typespec's rep. is a pointer.
     vlTypeNAME -- Get the name of a typespec.
     vlTypeEQUAL -- Determine if two typedata objects are equal.
     vlTypeCOPY -- Copy typespec data.
     vlTypeFREE -- Free typespec data.
     vlTypeConvert -- Convert data of one typespec to another
     vlTypeAddConverter -- Register a type converter between 2 typespecs
     vlTypeCreateEnum -- Dynamically create an enum typespec

-------------------------------------------------------------------------------

863 vlVa -- varargs interface.

-------------------------------------------------------------------------------

595 vllib -- Portability & Reusability Library

*/

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

extern vlIntProcT vlCleanupProcV;
extern vlIntProcT vlMemOutV;

/*\Docpage vlCONCAT_TOKEN -- preprocessor token concatenation

DESCRIPTION
     Concatentate two tokens using evil preprocessor tricks.  This
     is really an evil thing to do, and may only work with Unix and
     Ansi compilers, but is sometimes very useful in macros.

EXAMPLE
     vlCONCAT_TOKEN (Yo,Mama) --> YoMama

CAUTIONS    
     Do not put any extra whitespace inside the parens when calling this
     macro, otherwise it won't work.

SYNOPSIS
     vlCONCAT_TOKEN (token1,token2) --> token1token2
*/
#ifdef __STDC__
#define vlCONCAT_TOKEN(a, b) a##b
#else
#    if (vlCOMP_BC || vlCOMP_MC)
#       define vlCONCAT_TOKEN(a, b) a##b
#    else
#       define vlCONCAT_TOKEN(a, b) a/**/b
#    endif
#endif

/*\Docpage vlASSERT -- debugging assert statement
 *
 * DESCRIPTION
 *      If "exp" is FALSE, print out "string" to stderr, print out the
 *      current C filename and line number, and exit.  This should be
 *      used to verify sanity of data structures, validity of input
 *      arguments, etc.  It should *not* be used to verify user input,
 *      because assertion failures cause program termination and core dump.
 *
 *      Assertions are turned off (compile into nothing) when
 *      vlENV_DEBUG is 0.  This macro should be used only to
 *      perform time-consuming or redundant checks, and should
 *      definitely not be used for subroutine pre-condition
 *      validation.  See CAUTIONS.
 *
 * CAUTIONS
 *      Do not use side effects in "exp", because they won't occur when
 *      debugging is off.
 *
 * SYNOPSIS
 *      vlASSERT (exp, string);
 *         vlBoolT exp;
 *         char *string;
 * 
 * SEE ALSO
 *      vlASSERT1
 */
#if vlENV_DEBUG
#define vlASSERT(exp, string) \
    if (! (exp)) {\
        vlCleanup ();\
        vrFprintf (stderr, (char *)"ASSERTION FAILED: %s, line %d: %s\n",\
                 __FILE__, __LINE__, string);\
        vlAbort (TRUE);\
    }

/*\Docpage vlASSERT1 -- debugging assert statement with arg
 *
 * DESCRIPTION
 *      If "exp" is FALSE, print out "string" to stderr, print out the
 *      current C filename and line number, and exit. 
 *      p1 is formatted into "string", printf-style.
 *      This should be used to verify sanity of data structures,
 *      validity of input arguments, etc.  It should *not* be used
 *      to verify user input, because assertion failures cause
 *      program termination and core dump.
 *
 *      Assertions are turned off (compile into nothing) when
 *      vlENV_DEBUG is 0.  This macro should be used only to
 *      perform time-consuming or redundant checks, and should
 *      definitely not be used for subroutine pre-condition
 *      validation.  See CAUTIONS.
 *
 * CAUTIONS
 *      Do not use side effects in "exp", because they won't occur when
 *      debugging is off.
 *
 * SYNOPSIS
 *      vlASSERT1 (exp, string, p1);
 *         vlBoolT exp;
 *         char *string;
 *         ??? p1;    |* should match formatter in string *|
 *
 * SEE ALSO
 *      vlASSERT
 */
#define vlASSERT1(exp, string, p1) \
    if (! (exp)) {\
        vlCleanup ();\
        vrFprintf (stderr, (char *)"ASSERTION FAILED: %s, line %d: ",\
                 __FILE__, __LINE__);\
        vrFprintf (stderr, (char *)string, p1);\
        vrFprintf (stderr, (char *)"\n");\
        vlAbort (TRUE);\
    }
#else
#define vlASSERT(exp, string) /* nothing */
#define vlASSERT1(exp, string, p1)
#endif

#ifndef vlMEMORY_H
#include "vlmemory.h"
#endif

#ifndef vlSTR_H
#include "vlstr.h"
#endif

#ifndef vlmag_h
#include "vlmag.h"
#endif

#ifndef vlCVT_H
#include "vlcvt.h"
#endif

#ifndef vlDLIST_H
#include "vldlist.h"
#endif

#ifndef vlDUFS_H
#include "vldufs.h"
#endif

/*\Docpage vlRCS_C -- Declare a global character string for an RCS ID

DESCRIPTION
     Used for declaring an rcs ident string as a global variable.
     If you use this macro instead of declaring the character string
     yourself, we'll be able to exclude these strings from an executable
     during a build.  vlRCS_C and vlRCS_H are identical, but we can
     turn them off selectively for C and H files if we want to.

SEE ALSO
     vlRCS_H
*/

/* RCS tagging macro */
#if (!vlOS_UNIX || !vlENV_DEBUG)
#   define vlRCS_TAG(x) enum { rcs_tag=0 }
#   define vlRCS_H(var, x) enum { var=0 }
#   define vlRCS_C(var, x) enum { var=0 }
#else
#   define vlRCS_TAG(x) static const char *rcs_tag = x

/*
 * Get ready, and hold your breath.  The following macro is used to
 * define a static string variable that may never be referenced, but
 * will fool GCC into thinking that it is referenced, because it is part
 * of a self referential static structure!  If we just do
 *      static char *var = x;
 * then gcc will warn that we're never referencing it.  So we just put
 * it into a self referential structure!  If we make it a global, like
 * in vlRCS_C above, then it will cause multiple definition errors
 * when linking.  Thank god for sick minds.
 *                                          -Josh, 1/11/90
 */
#   define vlRCS_H(var, x) \
        static struct var { \
            struct var *self; \
            char *rcs_id; \
        } var = {&var, x}

#   define vlRCS_C(var, x) const char *var = x
#endif /* (!vlOS_UNIX || !vlENV_DEBUG) */

/******************************************************************/

/*\Docpage vlStatBufDECLARE -- declare an expandable static buffer

DESCRIPTION
     Declares a static buffer of a given type, and an integer counter
     indicating how big the buffer is.

SEE ALSO
     vlStatBufEXPAND

SYNOPSIS
     vlStatBufDECLARE (buf_type, buf_var, max_var)
*/
#define vlStatBufDECLARE(buf_type, buf_var, max_var)                          \
    static int max_var = 0;                                                   \
    static buf_type *buf_var = NULL

/*\Docpage vlStatBufEXPAND -- Expand a static buffer to a given size

DESCRIPTION
     Expands "buf_var", if necessary, so that "needed" elements of
     type "buf_type" are available.  The number of elements currently
     allocated is held in "max_var".

CAUTION
     The buffer MUST HAVE BEEN DECLARED via vlStatBufDECLARE

EXAMPLE
     This example shows how you might write code to gather characters
     from stdin into a buffer that grows to meet the size requirements
     of the input data:

     {
         int c, size = 0;
         vlStatBufDECLARE (char, buf, buflen);

         while ((c = getchar ()) != EOF) {
             size++;
             vlStatBufEXPAND (char, buf, buflen, size + 1);
             buf[size - 1] = c;
         }
         buf[size] = '\0';             
     }

     That implementation grows the buffer using "realloc" by one character
     each time a new one is read in.  Another implementation will double
     the buffer size each time, which is more efficient:

         while ((c = getchar ()) != EOF) {
             size++;
             if (buflen < size + 1)
                 vlStatBufEXPAND (char, buf, buflen, 2 * (size + 1));
             buf[size - 1] = c;
         }

SYNOPSIS
     vlStatBufEXPAND (buf_type, buf_var, max_var, int needed);
*/
#define vlStatBufEXPAND(buf_type, buf_var, max_var, needed)                   \
   do {                                                                       \
    if (needed > max_var) {                                                   \
        max_var = needed;                                                     \
        if (buf_var != NULL)                                                  \
            vlOnExitRemove (vlMemFree, (vlPointerT) buf_var);                 \
        buf_var = (buf_type *) vlMemRealloc (buf_var,                         \
                                             max_var * sizeof (buf_type),     \
                                             "vlStaticBuffer");               \
        vlOnExitAdd (vlMemFree, (vlPointerT) buf_var);                        \
    } /* if */                                                                \
   } while (0) /* So the macro can parse correctly as an if-clause itself */

/*\Docpage vlBUFEXPAND -- Expand a dynamic buffer to a given size

DESCRIPTION
     Expands "buf_var", if necessary, so that "needed" elements of
     type "buf_type" are available.  The number of elements currently
     allocated is held in "max_var". Both buf_var and max_var are expected
     to be local variables, declared on the stack. If an expandable static
     buffer is desired, use vlStatBufDECLARE to delcare it and
     vlStatBufEXPAND to expand it.

EXAMPLE
     This example shows how you might write code to gather characters
     from stdin into a buffer that grows to meet the size requirements
     of the input data:

     {
         int c, size = 0;
         char *buf = NULL;
         int buflen = 0;

         while ((c = getchar ()) != EOF) {
             size++;
             vlBUFEXPAND (char, buf, buflen, size + 1);
             buf[size - 1] = c;
         }
         buf[size] = '\0';             
     }

     That implementation grows the buffer using "realloc" by one character
     each time a new one is read in.  Another implementation will double
     the buffer size each time, which is more efficient:

         while ((c = getchar ()) != EOF) {
             size++;
             if (buflen < size + 1)
                 vlBUFEXPAND (char, buf, buflen, 2 * (size + 1));
             buf[size - 1] = c;
         }

SYNOPSIS
     vlBUFEXPAND (buf_type, buf_var, max_var, int needed);
*/

#define vlBUFEXPAND(buf_type, buf_var, max_var, needed)                       \
    if (needed > max_var) {                                                   \
        max_var = needed;                                                     \
        buf_var = (buf_type *) vlMemREALLOC (buf_var,                         \
                                             max_var * sizeof (buf_type));    \
    } /* if */                                                                \
    else /* So the macro can parse correctly as an if-clause itself */

/*\Docpage vlDufsGetchar  -- get a character from stdin
 *
 * DESCRIPTION
 *     Gets a character portably from stdin;
 *     identical to vlFgetc(stdin)
 *
 * RETURNS
 *     The character gotten
 *
 * SYNOPSIS
 *     char vlDufsGetchar ();
 */

#define vlDufsGetchar() vlDufsFgetc(stdin)
/* vlDufsGetchar calls should be given an empty set of paren's */

#ifndef vlMask_H
#include "vlmask.h"
#endif

#ifndef vlRtc_H
#include "vlrtc.h"
#endif

/* Math macros */

#ifdef MAX
#undef MAX
#endif
#ifdef MIN
#undef MIN
#endif

#ifndef ABS
#define ABS(x)                ((x)<0?-(x):(x))
#endif
#define SIGN(x)               ((x)<0?-1:((x)>0?1:0))
#define MAX(a,b)              ((a)>(b)?(a):(b))
#define MIN(a,b)              ((a)<=(b)?(a):(b))

/* ------------------------- MISCELLANEOUS ------------------------ */

/* A leapyear is one divisible by 4 but not by 100 EXCEPT that one
   divisible by 400 IS a leapyear.  pjs */
#define vlLEAPYEAR(x) (((((x)%4)==0)&&((x)%100!=0))||(((x)%400)==0))

#ifdef PI
#  define vlPI PI
#else
#  ifdef _PI
#    define vlPI _PI
#  else
#    define vlPI 3.14159265358979323846
#  endif
#endif

/* --------------------------- BANNER SIZES ------------------------- */

#define vlBANNER_SIZE 255

/* -------------------------- MESSAGE HANDLER ----------------------- */

#define vlStrSIZE 128
#define STR_SIZE vlStrSIZE
#define vlMOST_STR 16000
#define vlSTR_FNAME "wv50.msg"
#define vlCACHEBLK 16

/* -------------------- TOKEN STRUCTURES ETC. ----------------------- */

#define vlLEXER_NONE_FOUND -3
#define vlNO_KEYWORD 0

typedef struct keywords {
   struct keywords *next;
   char            *word;
   int             min_chars_to_recognize;
   int             keyword_number;
   } vlKeywordT;


/* -------------------- STRING EXPANSION STRUCTURE ETC.------------------- */

#define vlBusExpandOK      0   /* no errors encountered */
#define vlBusExpandBRACKET 1   /* nested brackets or closing bracket missing */
#define vlBusExpandCHAR    2   /* illegal character within brackets */
#define vlBusExpandSYNTAX  3   /* illegal syntax within brackets */
#define vlBusExpandDIGIT   4   /* illegal digit for specified radix */
#define vlBusExpandRANGE   5   /* illegal range for specified radix */
#define vlBusExpandINC     6   /* illegal increment specified (zero) */
#define vlBusExpandNULLPTR 7   /* argument pointer is NULL */
#define vlBusExpandBUFLEN  8   /* return buffer too small */
#define vlBusExpandMAXNAM 32   /* struct space to reserve for name string */

typedef struct vecrec {
    char            *nexttok;           /* next TOKEN to parse */
    vlBoolT         repeater;           /* is this a repeat vector? */
    vlBoolT         in_repeater;        /* will we be repeated? */
    char            *cptr;              /* NAME (if too big for cstr) */
    char             cstr[vlBusExpandMAXNAM];/* NAME (if small enough) */
    int              prefix;            /* set if NAME preceeds bit #'s */
    int              radix;             /* radix of bit #'s (2,8,10,16...) */
    int              increment;         /* bit increment (0 if no bit #'s) */
    int              lzeros;            /* field width if leading zeros */
    int              first;             /* first bit number */
    int              last;              /* last bit number */
    int              current;           /* current bit number */
    int              done;              /* set when current == last */
    struct vecrec   *next;              /* for multi-dimensional tokens */
    /*struct vecrec   *top_repeater;       vector at the begining of the
                                           repeat sequence*/
    struct vecrec   *next_repeat_token; /* next token in the repeat sequence */
    /*int              repeat_status;     denotes if begin/end of repeat
                                           sequence */
    int              n_pass;            /* Number of passes left to go */

    struct vecrec   *repeat_tok;        /* list of repeating vectors */
    struct vecrec   *cur_tok;           /* where we are now in list */
    int              total_passes;      /* total number of passes needed */

} vlVecRecT;

/* CRITICAL SECTION CODE HANDLING */


/* These are internal defines for the final macros */
/* The HP uses longs, all others uses ints for the masks */
/* I haven't looked into this for the PC yet - AAK */
#if vlOS_HPUX
#define vl_ALLSIGNALS (~(0L))
#define vl_SIGTYPE long
#else
#define vl_ALLSIGNALS (~(0))
#define vl_SIGTYPE int
#endif
/*\Docpage vlCRITICAL -- protect critical code from signal interruption
 *
 * DESCRIPTION
 *      Code located within a CRITICAL block is protected from being
 *      stopped by signals like ^C.
 *
 * EXAMPLE
 *      vlBoolT error = FALSE;
 *      vlCRITICAL {
 *          ...
 *          if (something_bad_happens)
 *              error = TRUE;
 *          ...
 *      } vlEND_CRITICAL;
 *      if (error)
 *          vlExThrow (...); // or return or whatever
 *
 * CAUTIONS
 *      A critical block MUST end with vlEND_CRITICAL.   You cannot
 *      leave such a block by means of a `goto' or a `return';
 *      exceptions (vlExThrow) are fine.
 *
 * NOTES
 *     The signal mask is returned to its prior value on exit; thus, 
 *     vlCRITICAL sections may be nested.
 */

#define vlCRITICAL { vl_SIGTYPE vl_SigMask = sigsetmask (vl_ALLSIGNALS); \
                     vlExUNWIND_PROTECT

/*\Docpage vlEND_CRITICAL -- end a vlCRITICAL section
 *
 * DESCRIPTION
 *      See vlCRITICAL
 */

#define vlEND_CRITICAL vlExCLEANUP sigsetmask (vl_SigMask); \
                       vlExEND_UNWIND; }

#define vlCANCEL_CRITICAL sigsetmask (vl_SigMask)


/* -------------------- POINT STRUCTURES ----------------------- */

typedef struct point {
    struct point *next;     /* pointer to next point in list */
    int x;                  /* X coordinate of point */
    int y;                  /* Y coordinate of point */
} vlPointT,*vlPointPtrT;


/* -------------------- LIST STRUCTURE ----------------------- */

typedef struct le
    {
    struct le *next;	/* pointer to next element in list */
    struct le *prev;	/* pointer to previous element in list */
    } *vlLePtrT;

typedef int (*vlListFuncPtrT) vlARG2(vlPointerT, vlPointerT);
typedef void (*vlListFreeFuncT) vlARG1(vlPointerT);

/* -------------------- CELL STRUCTURE ----------------------- */

typedef struct cell
{
    struct cell *next;		/* pointer to next cell in list */
    struct le *item;			/* pointer to the item */
} vlCellT,*vlCellPtrT;


/* -------------------- QUEUE STRUCTURE ----------------------- */

typedef vlCellPtrT vlQPtrT;

/* ------------------------ function prototypes -------------------- */

extern void vlCleanup vlARG1(void);
extern void vlF_NORETURN vlAbort vlARG1(int) vlF_NORETURN_GCC_CHANGES_SUK;
extern double vlFlCos vlARG1(int);
extern double vlFlSin vlARG1(int);
extern double vlFlTrunc vlARG2(double, int);
extern int vlFlRound vlARG1(double);
extern double vlFlSqrt vlARG1(double);
extern void vlBannerStrWV vlARG1(char *);
extern void vlBannerStr vlARG3(char *, const char *, const char *);
extern void vlBanner vlARG2(const char *, const char *);
extern char *vlCurrentBannerV;
extern char *vlCurrentNameV;

extern vlCellPtrT vlCellNew vlARG1(void);
extern void vlCellFLSave vlARG1(vlCellPtrT);
extern void vlCellFLFree vlARG1(void);
extern int vlCellFound vlARG2(vlLePtrT, vlCellPtrT);
extern vlCellPtrT vlCellAdd vlARG2(vlLePtrT, vlCellPtrT);
extern vlCellPtrT vlCellRemove vlARG2(vlLePtrT, vlCellPtrT);
extern void vlCellFree vlARG1(vlCellPtrT);
extern void vlCellStrFree vlARG1(vlCellPtrT);
extern void vlCellFreeGeneral vlARG2(vlCellPtrT, vlListFreeFuncT);
extern vlCellPtrT vlCellFind vlARG2(vlLePtrT, vlCellPtrT);
extern int vlDufsFgetc vlARG1(FILE *);
extern char *vlDufsFgets vlARG3(char *, int, FILE *);
extern const char *vlDufsFgetline vlARG1(FILE *);
extern int vlDufsFseek vlARGS((FILE *, long, int));
extern long vsFtime vlARG1(char *);
#if vlHW_PC
#define vsFGMtime vsFtime
#else
extern long vsFGMtime vlARG1(char *);
#endif
extern int vsFexists vlARG1(char *);
extern int vsFnotport vlARG1(char *);
extern vlLePtrT vlListSins vlARG3(vlLePtrT, vlLePtrT, vlLePtrT);
extern vlLePtrT vlListSdel vlARG2(vlLePtrT, vlLePtrT);
extern vlLePtrT vlListDins vlARG3(vlLePtrT, vlLePtrT, vlLePtrT);
extern vlLePtrT vlListDdel vlARG2(vlLePtrT, vlLePtrT);
extern vlLePtrT vlListPrev vlARG2(vlLePtrT, vlLePtrT);
extern vlLePtrT vlListLast vlARG1(vlLePtrT);
extern vlLePtrT vlListSsort vlARG2(vlLePtrT, vlListFuncPtrT);
extern vlLePtrT vlListDsort vlARG2(vlLePtrT, vlListFuncPtrT);
extern unsigned int vlListSize vlARG1(vlLePtrT);
extern int vlMem_FastLfree vlARG1(vlLePtrT);
extern int vlMem_DbgLfree vlARG1(vlLePtrT);
extern const char *vlMsgBuild vlVaARG1(int);
extern const char *vlMsgBuildVa vlARG2(int, vlVaListT);
extern int vlMsgGet vlARG2(int, vlStringPtrT);
extern int vlMsgOpen vlARG1(char *);
extern void vlMsgClose vlARG1(void);
extern vlPointPtrT vlPointNew vlARG1(unsigned int);
extern void vlPointFree vlARG1(vlPointPtrT);
extern vlPointPtrT vlPointAdd vlARG3(int, int, vlPointPtrT);
extern vlPointPtrT vlPointCopy vlARG1(vlPointPtrT);
extern double vlPointDist vlARG2(vlPointPtrT, vlPointPtrT);
extern void vlPointSort vlARG1(vlPointPtrT);
extern int vlDummyProc vlARG1(void);
extern vlQPtrT vlQLifo vlARG1(void);
extern vlQPtrT vlQFifo vlARG1(void);
extern int vlQFree vlARG1(vlQPtrT);
extern int vlQAdd vlARG2(vlQPtrT, vlLePtrT);
extern vlLePtrT vlQTop vlARG1(vlQPtrT);
extern vlLePtrT vlQPop vlARG1(vlQPtrT);
extern long vlQSize vlARG1(vlQPtrT);
extern int vlBusExpandStatus vlARG1(void);
extern void vlBusExpandRepsep vlARG1(char *);
extern vlVecRecT *vlBusExpandCopy vlARG1(vlVecRecT *);
extern int vlBusExpandFrame vlARG1(char *);
extern unsigned int vlBusExpandWidth vlARG1(char *);
extern void vlBusExpandFree vlARG1(vlVecRecT *);
extern vlVecRecT *vlBusExpand vlARG4(vlVecRecT *, char *, char *, int);
extern int vlBusExpandSubset vlARG2(char *, char *);
extern char *vlMem_FastStcpy vlARG1(const char *);
extern char *vlMem_DbgStcpy vlARG1(const char *);
extern int vlTklex vlARG6(vlFilePtrT, char[], int, char[], char[], vlKeywordT *);
extern void vlListFree vlARG1(vlLePtrT);
extern void vlListFreeGeneral vlARG2 (vlLePtrT, vlListFreeFuncT);

/**/
extern const char *vlSprintfStaticVa vlARG2(const char *, vlVaListT);
extern const char *vlSprintfStatic vlVaARG1(const char *)
#if __GNUC__
    __attribute__ ((format (printf, 1, 2)))
#endif
    ;
extern int vlSprintf vlVaARG3(char *, int, const char *)
#if __GNUC__
    __attribute__ ((format (printf, 3, 4)))
#endif
    ;
extern int vlSprintf2 vlVaARG4(char *, int, int *, const char *)
#if __GNUC__
    __attribute__ ((format (printf, 4, 5)))
#endif
    ;
extern char *vlSprintfAlloc vlVaARG1(const char *)
#if __GNUC__
    __attribute__ ((format (printf, 1, 2)))
#endif
    ;
extern char *vlSprintfAllocVa vlARG2(const char *, vlVaListT);
extern int vlSprintfVa vlARG4(char *, int, const char *, vlVaListT);
extern int vlSprintfVa2 vlARG5(char *, int, int *, const char *, vlVaListT);
/**/

extern vlPointerT vlMemFlAlloc vlARGS((size_t, const char *));
extern void vlMemFlFree vlARGS((vlPointerT, size_t));
extern void vlMemFlPurge vlARGS((void));

extern void vlOnExitAdd vlARGS((vlVoidProcT, vlPointerT));
extern void vlOnExitAdd2 vlARGS((vlVoidProcT));
extern void vlOnExitRemove vlARGS((vlVoidProcT, vlPointerT));
extern void vlOnExitRemove2 vlARGS((vlVoidProcT));
extern void vlOnExitCall vlARGS((void));
extern void vlOnExitSetOrder vlARGS ((vlVoidProcT, int));
extern void vlF_NORETURN vlExit vlARG1(int) vlF_NORETURN_GCC_CHANGES_SUK;
extern void vlF_NORETURN vlGoodbye vlARGS((void)) vlF_NORETURN_GCC_CHANGES_SUK;


/* Here is some stuff that that Bob Davis wanted to add */
/* so I stck it here, it's as good a place as any */
#define vlBIG_ENDIAN 0
#define vlLITTLE_ENDIAN 1
/* These rare breeds have different word than byte order.
 * The pdp11 used to be one of these I 'tink.
 */
#define vlBIG_LITTLE_ENDIAN 2
#define vlLITTLE_BIG_ENDIAN 3

#if (vlHW_SUN3 | vlHW_SUN4 | vlHW_RIOS | vlHW_HP9000 | vlOS_IRIX)
#define vlBYTE_ORDER vlBIG_ENDIAN
#else
#if (vlHW_ALPHA | vlHW_PMAX | vlHW_PC | vlHW_INTEL386 | vlHW_SUN386 | vlHW_NECPC)
#define vlBYTE_ORDER vlLITTLE_ENDIAN
#else
#if 0
#define vlBYTE_ORDER vlBIG_LITTLE_ENDIAN
#else
#if 0
#define vlBYTE_ORDER vlLITTLE_BIG_ENDIAN
#endif
#endif
#endif
#endif

/* Compilers &/or platforms which support "long long"'s as 64 bit
 * quantities sign up here.
 */
#if (vlCOMP_GC || vlOS_SOLARIS || vlHW_ALPHA || vlOS_IRIX)
#define vlLONGLONG 1
#else
#define vlLONGLONG 0
#endif

extern const char *vlCompatibleVersionV;
extern const char *vlCurrentVersionV;

/* the bus merge stuff that is here for a lack of better place */
#include "vlsigpub.h"


/*****************************************************************************/
/*                          Metafile defines.                                */
/*****************************************************************************/

/*
 * ADT for the metafile context.
 */
typedef struct vlMetaCntxS *vlMetaCntxID;

/*
 * C doesn't allow passing type keywords as function arguments, thus we have
 * to invent our own.  Don't start this enum at 0, because the
 * vlMetafileRegisterProc function will not be able to detect the terminating
 * NULL for the variable number of arguments.
 */
typedef enum
{
    vlMetaTypeDOUBLE    = 1,        /* Corresponds to: double           */
    vlMetaTypeSTRING    = 2,        /* Corresponds to: vlStringPtrT     */
    vlMetaTypeVARDOUBLE = 3         /* Corresponds to: double           */
} vlMetaTypeT;


/*
 * Token values accepted by the vlMetafileRegisterProc(man) function.  See the
 * vlMetafile man page for examples of their use.
 */
#define vlMetaDfltTOKENS    -1      /* Use the default token number         */
#define vlMetaVarTOKENS     -2      /* Use the variable number of tokens.   */
#define vlMetaNoTOKENS      -3      /* No tokens defined                    */


/*
 * Typedef for a metafile record handler.
 */
typedef vlPointerT (*vlMetafileProcT) vlARGS((int *, vlUnsignedIntT,
                                              double *, vlUnsignedIntT,
                                              vlStringPtrT *, vlUnsignedIntT,
                                              unsigned long, vlStringPtrT,
                                              vlPointerT));

extern vlMetaCntxID vlMetafileCntxCreate vlARGS((vlCStringPtrT));
extern void vlMetafileCntxFree vlARGS((vlMetaCntxID));
extern vlMetaCntxID vlMetafileCntxCopy vlARGS((vlMetaCntxID));
extern vlCStringPtrT vlMetafileCntxGetName vlARGS((vlMetaCntxID));
extern void vlMetafileRegisterProc vlVaARG4(vlMetaCntxID, int,
                                            vlMetafileProcT, int);
extern void vlMetafileRead vlARGS((vlMetaCntxID, vlCStringPtrT, vlPointerT));
extern vlPointerT vlMetafileReadRecord vlARGS((vlMetaCntxID, vlStrBufID,
                                               FILE *, vlBoolT *,
                                               vlPointerT));
extern vlPointerT vlMetafileReadRecord2 vlARGS((vlMetaCntxID, vlStrBufID,
                                               vlStringProcT, vlPointerT,
                                               vlBoolT *,
                                               vlPointerT));


/****************************************************************************/
/*                          Byte block defines                              */
/****************************************************************************/

/*
 * ADT for an arbitrarily large byte block.
 */
typedef struct vlByteBlock *vlByteBlockID;


extern vlByteBlockID vlByteBlockCreate vlARGS ((vlCStringPtrT, unsigned long));
extern vlByteBlockID vlByteBlockCopy vlARGS ((vlByteBlockID));
extern void vlByteBlockFree vlARGS ((vlByteBlockID));
extern unsigned int vlByteBlockGetSize vlARGS ((vlByteBlockID));
extern vlCStringPtrT vlByteBlockGetData vlARGS ((vlByteBlockID));

typedef struct vlFreelist *vlFreelistID;
extern vlFreelistID vlMemFlCreate vlARGS((int, const char *));
extern void vlMemFlDestroy vlARGS((vlFreelistID));
extern vlPointerT vlMemFlAlloc2 vlARGS((vlFreelistID));
extern void vlMemFlFree2 vlARGS((vlFreelistID, vlPointerT));

#endif /* vlLIB_H */
