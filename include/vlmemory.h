/*
 * $Id: vlmemory.h,v 1.21.3.2 1996/01/26 21:59:33 gwu Stab $
 *
 * Header file for all the vlMem... memory management functions.
 *
 * Peter Colby, March 1991
 *
 * Copyright 1991 by Viewlogic Systems, Inc.
 */

#ifndef vlMEMORY_H
#define vlMEMORY_H

/*---------------------------------------------------------------------------*/
/*\Section vlMem -- Memory Management Functions

DYNAMIC MEMORY MANAGEMENT FUNCTIONS
    vlMemMALLOC  -- Allocate dynamic memory.
    vlMemMalloc  -- Allocate dynamic memory with "identifier".
    vlMemCALLOC  -- Allocate and clear elements of memory.
    vlMemCalloc  -- Allocate and clear elements of memory with "identifier".
    vlMemREALLOC -- Change size of memory block.
    vlMemRealloc -- Change size of memory block with "identifier".
    vlMemFree    -- Free a block of dynamic memory.

    These routines are layered on top of the popular C memory allocation
    routines malloc, realloc, calloc, and free.

The purpose of the vlMem*alloc routines is to handle out of memory
conditions.  When the lower level C allocation routine runs out of
memory, the procedure pointer vlMemOutV is called, and the *alloc is
tried again.  vlMemOutV is expected to eventually free up enough memory
for the allocation to succeed, or to die trying.  If the calling
program does not set vlMemOutV to some procedure, the default behavior
is to exit immediately, without attempting to free any memory.

In Workview, vlMemOutV is set to a routine that goes through 4 levels 
of memory "recovery", where various non-essential aspects of the
system are freed in an attempt to continue with the current 
operation.  After the fourth consecutive call to wl_mout, Workview 
exits, offering to save the contents of each window before it goes.

People who want their memory zeroed should call vlMemCalloc.

 Debugging --

Debug versions of the memory routines vlMemMalloc, vlMemCalloc, 
vlMemCalloc, and vlMemFree have been implemented.  The debugging 
versions will only be used if the the environment variable VL_MEMDBG
has been set before entering Workview.

The debugging routines accomplish the following:

1.  Attempts to free memory that was not allocated are caught.
2.  If you write past the beginning or end of your allocated area, 
    that is caught when you free or vlMemRealloc the object, or when 
    the routine vlMem_DbgTestMemory is called.
3.  If you attempt to use the contents of memory that you have freed, 
    you will find the contents have been destroyed.
4.  vlMemMalloc will put garbage in the memory it returns to you to 
    help eliminate dependencies on that routine returing zeroed 
    memory.
5.  Statistics are kept on the amount of memory allocated to 
    different kinds of objects.  A string parameter is 
    passed to vlMem*alloc to identify the kind of object being 
    allocated.  A histogram of memory usage is obtained by calling 
    vlMemPrintUsage.  vlMemPrintUsage takes a procedure 
    pointer for a print-string function.  The workview "version"
    command now prints this histogram.  The histogram can be very 
    useful for plugging "memory leaks" by helping to identifying
    all the memory that is currently allocated.
    If you don't wish to explicitly use the "string" parameter to
    vlMem*alloc then use the vlMem*ALLOC versions of the functions.
6.  The routine vlMem_DbgTestMemory() will loop through all allocated 
    blocks and verify that the memory boundaries have not been over-
    written.  It crashes if it detects this.  This is called in the 
    Workview "version" command.

Callers of the vlMem*alloc routines must supply a source id when using
the functions directly:

vlMemMalloc(size_t size, const char *source)
vlMemCalloc(size_t size1, size_t size2, const char *source)
vlMemRealloc(vlPointerT old, size_t newsize, const char *source)

Callers of the vlMem*alloc routines can avoid having to supply a source
id by using the macros:

vlMemMALLOC(size_t size)
vlMemCALLOC(size_t size1, size_t size2)
vlMemREALLOC(vlPointerT old, size_t newsize)

"source" is a string describing the data structure you are 
allocating.  The macros vlMemMALLOC, vlMemCALLOC, and vlMemREALLOC 
call the debugging functions with the name of the source file as
the source string, for upward compatibility.

If the memory debug routines detect an error, they terminate 
graphics (if necessary), print out the offending call, and dump 
core, access violate, or exit, depending on the OS.


Note that vlStrCpy calls vlMemMalloc (with the source id "String").  
Hence you must free strings created in this manner with vlMemFree.

You should follow these rules:

    1.  Do not call free() on anything created with vlMem*alloc or
        vlStrCpy.
    2.  Try to allocate and free objects from the same module.  
        This is the natural thing to do when using data abstractions.

ALLOCATING ZERO BYTES

     All the allocation routines will automatically turn a request for
     zero (0) bytes into a one (1) byte allocation with NO indication
     that they have done so!

*/

/*---------------------------------------------------------------------------*/
/*\Docpage vlMemMALLOC -- Allocate dynamic memory

DESCRIPTION
     Returns a pointer to a piece of newly allocated memory.
     If there is not enough memory the global routine (*vlMemOutV) () is called
     and the allocation is tried again.
     If the environment variable VL_MEMDBG exists in the environment a history
     of all dynamic memory usage is maintained and can be printed via a call
     to vlMemPrintUsage.
     Memory allocated by this function MUST be freed with vlMemFree.

RETURNS
     A pointer to the newly allocated memory space

SEE ALSO
     vlMemMalloc, vlMemCALLOC, vlMemCalloc, vlMemREALLOC, vlMemRealloc,
     vlMemFree

SYNOPSIS
     vlPointerT vlMemMALLOC(size)
         size_t size;   |* Number of BYTES to allocate *|
*/

#define vlMemMALLOC(size) vlMemMalloc(size, __FILE__)

/*---------------------------------------------------------------------------*/
/*\Docpage vlMemCALLOC -- Allocate and clear elements of memory

DESCRIPTION
     Returns a pointer to a piece of newly allocated memory. This memory is
     initialized (cleared) to all zeros (0).
     If there is not enough memory the global routine (*vlMemOutV) () is called
     and the allocation is tried again.
     If the environment variable VL_MEMDBG exists in the environment a history
     of all dynamic memory usage is maintained and can be printed via a call
     to vlMemPrintUsage.
     Memory allocated by this function MUST be freed with vlMemFree.

RETURNS
     A pointer to the newly allocated and cleared memory space

SEE ALSO
     vlMemMALLOC, vlMemMalloc, vlMemCalloc, vlMemREALLOC, vlMemRealloc,
     vlMemFree

SYNOPSIS
     vlPointerT vlMemMALLOC(nelems, elemsz)
         size_t nelems;  |* Number of ELEMENTS to allocate *|
         size_t elemsz;  |* Size of an element in BYTES *|
*/

#define vlMemCALLOC(nelem,elemsz) vlMemCalloc(nelem, elemsz, __FILE__)

/*---------------------------------------------------------------------------*/
/*\Docpage vlMemREALLOC -- Change size of memory block.

DESCRIPTION
     Returns a pointer to a piece of newly allocated memory. Any data contained
     within the old block is kept unchanged in the new block up to the smaller
     of the old and new sizes. If the original block is NULL then vlMemREALLOC
     acts just like vlMemMALLOC.
     If there is not enough memory the global routine (*vlMemOutV) () is called
     and the allocation is tried again.
     If the environment variable VL_MEMDBG exists in the environment a history
     of all dynamic memory usage is maintained and can be printed via a call
     to vlMemPrintUsage.
     Memory allocated by this function MUST be freed with vlMemFree.

RETURNS
     A pointer to the newly allocated memory space

SEE ALSO
     vlMemMALLOC, vlMemMalloc, vlMemCALLOC, vlMemCalloc, vlMemRealloc,
     vlMemFree

SYNOPSIS
     vlPointerT vlMemREALLOC(orig, size)
         vlPointerT orig; |* pointer to original block or NULL *|
         size_t size;     |* requested new size of block in BYTES *|
*/

#define vlMemREALLOC(orig,size) vlMemRealloc(orig, size, __FILE__)

/*---------------------------------------------------------------------------*/
/*\Docpage vlMemAlloca -- Conditionalized stack memory allocation.

DESCRIPTION
     Stack memory allocation -- use instead of alloca(), which only works
     on some platforms.  alloca(n) allocates n bytes off the stack.  When
     the current procedure returns, the n bytes are "freed" automatically.
     vlMemALLOCA() is macroed to alloca() on platforms that have it, and
     vlMemMALLOC() on platforms that do not.  vlMemFreea() must be called
     to release the storage obtained through vlMemALLOCA().  vlMemFreea()
     does nothing on platforms that support alloca() (since the storage is
     automatically freed on procedure return), and calls vlMemFree() on
     platforms that do not have alloca().  At present, all Unix systems are
     assumed to support alloca(), plus Microsoft C.

EXAMPLE
     char *s = (char *) vlMemAlloca (strlen (str) + 1, "temp string");
     mess_around_with_contents_of_string (s);
     vlMemFreea ((vlPointerT) s);

SYNOPSIS
     void *vlMemAlloca(size_t size, char *source); Annotates Memory histogram
     void *vlMemALLOCA(size_t size);
*/

/*\Docpage vlMemFreea -- Conditionalized stack memory allocation.

See vlMemAlloca
*/

/*\Docpage vlMemALLOCA -- Conditionalized stack memory allocation.

See vlMemAlloca
*/

#if (vlOS_UNIX || (vlCOMP_MC && !(vlOS_NT && vlHW_MIPS)) || vlCOMP_BC || vlCOMP_WC) && !(vlOS_AIX || vlOS_PCUNIX || vlOS_HPUX || (vlHW_INTEL386 && vlCOMP_GC)  || vlHW_ALPHA)

#define vlMemHAS_ALLOCA 1
#define vlMemAlloca(size, source) alloca (size)
#define vlMemALLOCA(size) alloca (size)
#define vlMemFreea(ptr)

#else

#define vlMemHAS_ALLOCA 0
#define vlMemAlloca(size, source) vlMemMalloc (size, source)
#define vlMemALLOCA(size) vlMemMALLOC (size)
#define vlMemFreea(ptr) vlMemFree (ptr)

#endif

#if vlCOMP_HC
/* extern void *memcpy(char *, char *, int); */
/* extern void *_rmemcpy(char *, char *, int); */
#define memmove(t,f,n) ((f) < (t) ? _rmemcpy((t),(f),(n)) : memcpy((t),(f),(n)))
#endif
#if vlCOMP_LC
#define memmove memcpy
#endif

/*---------------------------------------------------------------------------*/
/*\Docpage vlMemCpy -- copy a block of memory 

SYNOPSIS 

     s = vlMemCpy (destination, src, n); 

     char *s;               returns pointer to destination
     char *destination;     pointer to destination 
     char *src;             pointer to source 
     unsigned int n;        number of bytes to be copied 


DESCRIPTION 

    Copies n bytes of src to destination. If some regions of src 
and destination overlap, vlMemCpy ensures that the original src bytes 
in the overlapping region are copied before being overwritten. 

RETURNS 

     s = pointer to destination 

SEE ALSO
     vlMemCalloc, vlMemMalloc, vlMemRealloc, vlMemCALLOC, vlMemMALLOC,
     vlMemREALLOC, vlMemFree, vlMemMove
*/

/*---------------------------------------------------------------------------*/
/*\Docpage vlMemMove -- copy a block of memory 

SYNOPSIS 

     s = vlMemMove (destination, src, n); 

     char *s;               returns pointer to destination
     char *destination;     pointer to destination 
     char *src;             pointer to source 
     size_t n;              number of bytes to be copied 


DESCRIPTION 

    Copies n bytes of src to destination. If some regions of src 
and destination overlap, vlMemMove ensures that the original src bytes 
in the overlapping region are copied before being overwritten. 

RETURNS 

     s = pointer to destination 

SEE ALSO
     vlMemCalloc, vlMemMalloc, vlMemRealloc, vlMemCALLOC, vlMemMALLOC,
     vlMemREALLOC, vlMemFree, vlMemCpy
*/

#if (vlOS_UNIX && !(vlOS_ULTRIX || vlOS_HPUX || vlOS_OSF || (vlHW_MIPS && vlOS_SYSVR4)))
extern vlPointerT vlMemMove vlARG3(vlPointerT, vlPointerT, size_t);
#define vlMemCpy(t, f, n) vlMemMove(t, f, n)
#else
#define vlMemCpy(t, f, n)   memmove(t, f, n)
#define vlMemMove(t, f, n)  memmove(t, f, n)
#endif

extern vlPointerT   vlMemRchr               vlARG3(vlPointerT, int, int);

extern vlPointerT   vlMem_FastMalloc        vlARG1(size_t);
extern vlPointerT   vlMem_FastRealloc       vlARG2(vlPointerT, size_t);
extern vlPointerT   vlMem_FastCalloc        vlARG2(size_t, size_t);
extern int          vlMemExit               vlARG1(int);
extern void         vlMem_FastFree          vlARG1(vlPointerT);

extern vlPointerT   vlMem_DbgMalloc         vlARG2(size_t, const char *);
extern vlPointerT   vlMem_DbgCalloc         vlARG3(size_t, size_t,
                                                           const char *);
extern vlPointerT   vlMem_DbgRealloc        vlARG3(vlPointerT, size_t,
                                                           const char *);
extern void         vlMem_DbgFree           vlARG1(vlPointerT);
extern void         vlMem_DbgTestMemory     vlARG1(void);
extern void         vlMem_DbgCallFuncForStr vlARG3(const char *, vlVoidProcT, vlPointerT);
extern void         vlMem_DbgPrintStrings   vlARG1(void);
extern void         vlMem_CheckNoDbg        vlARG1(vlPointerT);
extern void         vlMemPrintUsage         vlARG1(vlVoidProcT);
extern void         vlMemPrintUsageStdout   vlARG1(void);

extern vlPointerT   vlMemMalloc             vlARG2(size_t, const char *);
extern vlPointerT   vlMemCalloc             vlARG3(size_t, size_t,
                                                   const char *);
extern vlPointerT   vlMemRealloc            vlARG3(vlPointerT, size_t,
                                                     const char *);
extern void         vlMemFree               vlARG1(vlPointerT);
extern void         vlMemPurge              vlARGS ((void));
extern void         vlAddPurgeRoutine       vlARGS ((vlVoidProcT));

#endif
