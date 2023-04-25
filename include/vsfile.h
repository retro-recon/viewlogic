/*
 * $Id: vsfile.h,v 2.12.9.1 1995/10/17 20:40:53 cway Stab $
 *
 * Rick Lucier, November, 1987
 *
 */


/* IMPORTANT NOTE
 * Most of the functions in this file are simply macros of vr functions,
 * that ought to be phased out but are being kept aruond for backward
 * compatability.
 * Any maintenance to be done to them (e.g. #if'ing) should be done
 * in vrlib.h rather than here, so that both vs and vr functions reflect
 * the change made.
 */

#ifndef vsWSFILE_H
#define vsWSFILE_H

#ifndef vlLIB_H
#include "vllib.h"
#endif

/* "level 1" file functions (POSIX) */

/*\Docpage vsClose -- close a file opened for level 1 I/O

DESCRIPTION
    This function is equivalent to the POSIX/UNIX function close.
    vrClose is identical and should be preferred.

RETURNS
    0 - for success
    -1 for failure

SYNOPSIS

    int vsClose(fd)
         int fd;
*/
#define vsClose(fh)                vrClose(fh)

/*\Docpage vsCreat -- create a file for level 1 I/O

DESCRIPTION
     Same as vsOpen with flags O_WRONLY | O_TRUNC | O_CREAT.
     vrCreat is identical and should be preferred.

SYNOPSIS
     int vsCreat(name,prot)
          char *name;
          int prot;
*/
#if (vlCOMP_HC || vlCOMP_BC || vlCOMP_MC)
#define vsCreat(name, prot)                                 \
    vrOpen (name,                                           \
          O_WRONLY | O_TRUNC | O_CREAT | (prot & O_RAW),    \
          (prot & ~O_RAW))
#else
#define vsCreat(name, prot)        vrCreat(name, prot)
#endif

/*\Docpage vsLseek -- seek to specified position in file

DESCRIPTION
     This function changes the file pointer to a new position
     in the file.  The offset is specified as a long int and
     is added to the current position or to the logical end
     of file for offset modes 1 and 2, respectively.

     vrLseek is identical and should be preferred.

RETURNS
     -1 if error occurred, else new file position

SYNOPSIS
    long vsLseek(f, pos, mode)
        int f;                  |* File Handle *|
        long pos;               |* file position (relative byte number) *|
        int mode;               |* Offset Mode
                                   0 = relative to beginning of file
                                   1 = relative to current position
                                   2 = relative to logical end of file *|
*/
#define vsLseek(fh, pos, mode)     vrLseek(fh, pos, mode)

/*\Docpage vsOpen -- open a file for level 1 I/O

DESCRIPTION
    This function is equivalent to the POSIX/UNIX function open.
    For the PC O_RAW can be ORd into the mode and all file permissions
    (prot) except S_IREAD/S_IRUSR and S_IWRITE/S_IWUSR are ignored.

    vrOpen is identical and should be preferred.

RETURNS
    A file descriptor to reference the open file

SYNOPSIS

    int vsOpen(pathname, mode, prot)
         char *pathname;
         int mode;
         int prot;
*/
#define vsOpen(name, mode, prot)   vrOpen(name, mode, prot)

/*\Docpage vsRead -- read a file

DESCRIPTION
     This function reads the next set of bytes from a file
     that has been activated via a previous open call.

     vrRead is identical and should be preferred.

RETURNS
     0 if end of file
     -1 if error occurred
     number of bytes actually read if successful

SYNOPSIS
    int vsRead(f, b, n)
        int f;                      |* File Handle *|
        unsigned n;                 |* Buffer length in bytes *|
        char *b;                    |* Input Buffer *|
*/
#define vsRead(fh, buf, len)       vrRead(fh, buf, len)

/*\Docpage vsWrite -- write a file

DESCRIPTION
     This function writes a set of bytes to the current file position.

     vrWrite is identical and should be preferred.

RETURNS
     -1 if error, or number of bytes actually written

SYNOPSIS
    int vsWrite(f,b,n)
        int f;                      |* File handle *|
        unsigned n;                 |* Buffer Length *|
        char *b;                    |* Output Buffer *|
*/
#define vsWrite(fh, buf, len)      vrWrite(fh, buf, len)

/* "level 2" file functions (ANSI-C stdio) */

/*\Docpage vsFopen -- open a level 2 file

WARNING
     If using portable binary files use vlDufsBFopen instead of this
     function. See the manpages for the vlDufsB package for further
     information.

DESCRIPTION

     Opens the file "name" for level 2 file operations.  
     The "mode" specifies whether the file is opened 
          "r"  open existing file for read.
          "w"  create file for write, truncate if exists
          "a"  open or create file for appending to end
     Mode may contain one of the preceding and any 
     combination of "+" and "b".  If the "mode" contains 
     "+", the file is opened for update; if "b" is 
     contained within "mode", the stream is considered 
     binary and no translation occurs (on applicable 
     systems). 

     vrFopen is identical and should be preferred.

RETURNS

     file_ptr = pointer to the newly opened file.

CAUTIONS

     If "name" is opened for writing, if the file 
     exists, the file will be destroyed (truncated to 
     zero before writing occurs).

SYNOPSIS

     file_ptr = vsFopen ( name, mode );

     FILE *file_ptr;     pointer to opened level 2 file stream
     char *name;         file name to be opened
     char *mode;         mode which file is to be opened
*/

#if vlOS_VMS   /*  || vlOS_ULTRIX */
#define vsFopen(f,m)	       vlVFopen(f,m)
extern FILE *vlVFopen();
#else
#define vsFopen(f,m)	       vrFopen(f,m)
#endif

/*\Docpage vsFprintf -- converts, formats and writes arguments to a file

DESCRIPTION

     The vsFprintf function formats and prints a series of 
     characters and values to the output stream.  Each 
     argument (if any) is converted and the output according 
     to the corresponding format specification in format.

     vsFprintf was created because fprintf does not work the 
     same on all the platforms we support.  For example, fprintf
     on the Pmax returns 0 if it worked correctly and -1 otherwise
     where Lattice returns the number of bytes it expected to write
     regardless of whether or not the routine was successful.

     vsFprintf is guarenteed to return a negative status code when 
     it fails on any platform.  See the example below.

     vrFprintf is identical and should be preferred.

RETURNS

     Negative status on failure.  Can return anything but negative
     on success. 

CAUTIONS

     vsFprintf can format no more than 500 bytes (including the 
     NULL byte).  There is also a 52 byte limit for the number of
     formatting arguments it can be passed.  Developers who need to 
     exceed these limits must use fprintf with caution.  vsFprintf 
     does a sprintf into a 500 byte buffer, followed by a fwrite 
     which returns useful status (for HighC, VMS, and Lattice).  
     For the Unix platforms fprintf already returns a negative 
     status on failure and vsfprintf is just macroed. 

EXAMPLE

     if (vsFprintf (f, ...) < 0) { failure (); }

SYNOPSIS

     int vsFprintf ( stream, format[[, argument]]...);

     FILE *stream;       Pointer to opened level 2 file stream
     const char *format; Format-control string
*/

#if !(vlCOMP_LC || vlCOMP_VC)
#define vsFprintf vrFprintf
#endif

/*\Docpage vsFbuffer -- set level 2 file buffer mode

WARNING
     Use vrSetbuf instead of this function.

DESCRIPTION

     Causes the BUFSIZ byte segment of memory beginning 
     with the location referenced by "buffer" to be used 
     by the file stream instead of an automatically 
     allocated buffer.  If "buffer" is NULL I/O on the 
     file stream is unbuffered.  

     If buffered I/O has been done on the stream at the 
     time wl_fbuffer is called, the contents of the 
     buffer in use are copied into "buffer" and the 
     buffer in use is deallocated if it was 
     automatically allocated.

     vrSetbuf is identical and should be preferred.

CAUTIONS

     Library functions that perform I/O assume that the 
     buffer associated with a file stream is BUFSIZ 
     bytes in length.  If wl_fbuffer is called with a 
     smaller "buffer", the behavior is undefined.

SYNOPSIS

     vsFbuffer ( file_ptr, buffer );

     FILE *file_ptr;          level 2 file pointer
     char *buffer;            buffer for level 2 file stream
*/

#define vsFbuffer(f,b)	    vrSetbuf(f,b)

/*\Docpage vsFclose -- close a level 2 file

WARNING
     Use vrFclose instead of this function.

     If using portable binary files use vlDufsBFclose (see the manpages for
     the vlDufsB portable binary file package)

DESCRIPTION

     Closes the file stream associated with "file_ptr" 
     and if file was open for writes, the buffer is 
     written before closing occurs.  If the buffer for 
     the file stream was automatically allocated 
     (wl_fbuffer was not used), the buffer is freed.

RETURNS

     status = zero if successful, non-zero if an error 
     occured.

CAUTIONS

     file_ptr must be a valid file pointer upon entry
     to this routine.  A NULL pointer will cause problems. 

SYNOPSIS

     status = vsFclose ( file_ptr );

     FILE *file_ptr;          level 2 file pointer
     int status;              returned error status
*/

#define vsFclose(f)	       vrFclose(f)

/*\Docpage vsFread -- read blocks from a level 2 file

WARNING
     Use vrFread instead of this function.

     If using portable binary files there are a number of different
     read functions that should be used in place of vrFread. Consult
     the manpages for the vlDufsB package for further information.

DESCRIPTION

     Reads block count elements of block size bytes each 
     from the file stream into the memory buffer 
     block_ptr.  The file pointer location marker is 
     advanced by the number of bytes read.

RETURNS

     read_cnt = the number of block_siz blocks actually 
     read.  This will be the same as block_cnt unless an 
     error occurs or eof is encountered.

SYNOPSIS

     read_cnt = vsFread ( block_ptr, block_siz, 
                           block_cnt, file_ptr );

     int read_cnt;       the number of whole blocks read
     char *block_ptr;    the buffer of blocks
     int block_siz;      the size of each block
     int block_cnt;      the number of blocks being read
     FILE *file_ptr;     pointer the the file stream
*/

#define vsFread(b,s,c,f)     vrFread(b,s,c,f)

/*\Docpage vsFtell -- get position in a level 2 file

WARNING
     Use vrFtell instead of this function.

     If using portable binary files use vlDufsBFtell. For further information
     see the manpages for the vlDufsB portable binary file package.

DESCRIPTION

     Returns the value of the file marker for the 
     specified file stream.  The value is an offset from 
     the beginning of hte file.

RETURNS

     position = the offset from beginning of file 
     stream.

SYNOPSIS

     position = vsftell ( file_ptr );

     long position;      the current file marker position
     FILE *file_ptr;     the pointer to the file stream
*/

#define vsFtell(f)	          vrFtell(f)

/*\Docpage vsFseek -- set position in a level 2 file

WARNING
     Use vrFseek instead of this function.

     If using portable binary files use vlDufsBFseek instead. For further
     information see the manpages on the vlDufsB portable binary file package.

DESCRIPTION

     Moves the file marker associated with file_ptr, 
     "offset" bytes from the position specified by mode.  
     The possible modes for vsFseek are:
          0  offset from the beginning of file
             (value must be positive)
          1  offset from the current file mark position
             (value may be positive or negative)
          2  offset from the end of the file
             (value must be negative)

RETURNS

     status = 0 unless the request is invalid.  

SYNOPSIS

     status = vsFseek ( file_ptr, offset, mode );

     int status;         returned error status
     FILE *file_ptr;     pointer to file stream
     long offset;        offset in file
     int mode;           seek mode
*/
#define vsFseek(f,p,m)	    vrFseek(f,p,m)

/*\Docpage vsFwrite -- write blocks to a level 2 file

WARNING
     Use vrFwrite instead of this function.

     If using portable binary files there are a number of different
     write functions that should be used in place of vrFwrite. Consult
     the manpages for the vlDufsB package for further information.

DESCRIPTION

     Writes block count elements of block size bytes to
     the file stream from the memory buffer block_ptr.  
     The file pointer location marker is advanced by 
     the number of bytes written.

RETURNS

     write_cnt = the number of block_siz blocks actually 
     written.  This will be the same as block_cnt unless an 
     error.

SYNOPSIS

     write_cnt = vsFwrite (block_ptr, block_siz,
                            block_cnt, file_ptr );

     int write_cnt;      the number of whole blocks written
     char *block_ptr;    the buffer of blocks
     int block_siz;      the size of each block
     int block_cnt;      the number of blocks being written
     FILE *file_ptr;     pointer the the file stream
*/

#define vsFwrite(b,s,c,f)    vrFwrite(b,s,c,f)

   /* FILE NAME CASE CONVERSION DEFINE */

/*\Docpage vsCvtFname -- convert file name to platform case

DESCRIPTION

     Converts the string s to lower case under UNIX and upper
     case otherwise. 

RETURNS

     p = pointer to the modified string s 

CAUTIONS

    Modifies the input string. 

SYNOPSIS

     p = vsCvtFname (s); 

     char *p;               pointer to modified string 
     char *s;               string to modify 
*/

#if vlOS_UNIX
#define vsCvtFname       vlStrLoc
#else
#define vsCvtFname       vlStrUpc
#endif

#endif /* vsWSFILE_H */
