/*
 *  $Revision: 2.94.4.1 $
 *
 *  Typespecs and Typedata macros and definitions.
 *  Preferences typedefs, macros and prototypes.
 *
 *  Copyright (c) 1991,1993 by Viewlogic Systems, Inc.
 */


#ifndef vlTypeTYPES_H
#define vlTypeTYPES_H

#ifndef vlSymTAB_H
#include "vlsymtab.h"
#endif

#ifndef vlINT64_H
#include "vlint64.h"
#endif

#include "vlstr.h"
/* this is idempotent */

/*
 * Type specifications for input data.
 */
#define vlTypeLONG               0
#define vlTypeMOUSE_XY           1
#define vlTypePOINTER            2


/*\Section vlType -- Type specification system.

vllib provides a type specification system called "typespecs".  Typespecs
are a run-time data structure describing a data type.  They are used by
the vllib preference system (see the man page for vlPref) ViewScript, and
Powerview Core.

A typespec is a C structure that indicates the name of the type, a flag
indicating whether its instance representation is a C long or a pointer,
and a set of procedures for printing, parsing, freeing, and copying the
data.

Typespecs are typically created using one of several macros, described
in this section.  Some special applications may wish to define typespecs
directly using the public structure definitions in this file.

The following table describes various pointer-based data structures and
which macros to use to create typespecs for those data structures:

Example Structure            Mem. Mgmt?  Parseable? Has name?  Macro

char *name; FILE *f;         No          No         Yes        vlTypeMAKE_PTR
int x, FILE *f;              No          No         No         vlTypeMAKE_PTR1
char *name, FILE *f, int rc; Yes         No         Yes        vlTypeMAKE_PTR2
int x, rc, FILE *f;          Yes         No         No         vlTypeMAKE_PTR3
int x, y, rc;                Yes         Yes        No         vlTypeMAKE_PTR4

Note: In these examples, the structure element "int rc" is used for
reference counts, which indicates that there is memory management for
the data structure.  However, it is not necessary to use reference
counts for memory management.  Some data structures (such as strings)
use real copies instead of incremented reference counts.

The presence of "FILE *f" in the structure indicates that you can't
create one of these objects by parsing it from a string.  Structures
which contain IPC channels, windows, viewport, or other data
structures that require handle into the operating system, often cannot
be automatically created by parsing a string, hence they are not
"Parseable".

The "name" field indicates that a string representation of the object
is easily accessible from the data structure.  The simplest way to
print such an object is to print its name, and all that's required is
to supply a routine that returns the name field of the data structure.
If such a string does not exist, then it is cumbersome to have to
create such a string and return it to the caller, which will not know
whether to free it.  Instead, such routines use an "output" procedure, which
calls a procedure pointer with a string, and then discards the string.
This is easy to do using a temporary buffer on the stack.  See the
examples in the documentation of vlTypeMAKE_PTR1 for more details.
*/


/*\Docpage vlTypeDataT -- Union for specifying typespec data.

DESCRIPTION
     This is a generic data representation for objects of a any typespec
     class.  These generally fall into two representations: "long" and
     "pointer".  The fields of type vlTypeDataT can be directly accessed as
     .long_data and .ptr_data, or via vlTypeVALUE.

SEE ALSO
     vlTypeOBJECT, vlTypeINT and vlTypePTR macros used 
     to create and initialize a vlTypeDataT object.
*/
typedef union typedata {
    long        long_data;
    vlPointerT  ptr_data;
    struct {short x, y;} mouse_data;
} vlTypeDataT;


/*\Docpage vlTypeDataProcT -- Typedef for a procedure that returns vlTypeDataT
*/
typedef vlTypeDataT (*vlTypeDataProcT) ();

/*\Docpage vlTypeBaseT -- Structure for specifying common typespecs info.

DESCRIPTION
     In this structure there is stored information about the typespec's type
     (long or pointer) and how the typespec should be handled by the automatic
     memory management system (GC).  The four procedure pointers specify
     routines for: converting a string into the typespec, printing
     representation of the typespec, freeing and copying of the typespec.

     For more information check vlType and vlTypeMAKE_PTR macro man pages.
*/
typedef struct vlTypeBase {
    int             primitive_type;
    vlVoidProcT     convert;
    vlVoidProcT     output;
    vlVoidProcT     free;
    vlPointerProcT  copy;
    vlVoidProcT     free_specifics;
} *vlTypeBasePtrT, vlTypeBaseT;


/*\Docpage vlTypeSpecT -- Structure for describing data types.

DESCRIPTION
     A typedef for the C structure implementing typespecs.  vlTypeSpecPtrT is
     a typedef'ed pointer to this structure.
*/
typedef struct vlTypeSpec {
    const char     *name;
    vlTypeBasePtrT  base;
    vlPointerT      specifics;
    int             referent_count;
} *vlTypeSpecPtrT, vlTypeSpecT;


extern vlTypeDataT vlTypeLongToTypedata    vlARG1 (long);
extern vlTypeDataT vlTypePtrToTypedata     vlARG1 (vlPointerT);


/*\Docpage vlTypeBASE -- Get the typebase from a typespec.

DESCRIPTION
     This is an access macro: given a typespec, it will return its typebase.

SYNOPSIS
     vlTypeBasePtrT vlTypeBASE(ts)
         vlTypeSpecPtrT ts;
*/
#define vlTypeBASE(ts) (ts -> base)


/*\Docpage vlTypeOBJECT -- Convert a value into a vlTypeDataT

DESCRIPTION
     This creates an object of type vlTypeDataT. The typespec is used
     to determine if we are dealing with a long or pointer representation.

SEE ALSO
     vlTypeIS_POINTER, vlTypeINT, vlTypePTR

SYNOPSIS
     vlTypeDataT vlTypeOBJECT(ts, data)
        vlTypeSpecPtrT ts;
        long/vlPointerT data;
*/

#define vlTypeOBJECT(ts, data)\
   (vlTypeIS_POINTER (ts) ? vlTypePTR (data) : vlTypeINT (data))
    
/*\Docpage vlTypeINT -- Convert a long object into a vlTypeDataT union.

DESCRIPTION
     All of the API's that accept typespec data force the user to pass the
     data wrapped in the vlTypeDataT union.  This macro facilitates the
     conversion of a long-based data.  Its twin is the vlTypePTR macro for
     the pointer-based data.

SEE ALSO
     vlTypeOBJECT, vlTypePTR

SYNOPSIS
     vlTypeDataT vlTypeINT(data)
         long   data;
*/
#define vlTypeINT(i) (vlTypeLongToTypedata ((long) (i)))


/*\Docpage vlTypePTR -- Convert a pointer object into a vlTypeDataT union.

DESCRIPTION
     All of the API's that accept typespec data force the user to pass the
     data wrapped in the vlTypeDataT union.  This macro facilitates the
     conversion of a pointer-based data.  Its twin is the vlTypeINT macro for
     the long-based data.

SEE ALSO
     vlTypeOBJECT, vlTypeINT

SYNOPSIS
     vlTypeDataT vlTypePTR(data)
         vlPointerT data;
*/
#define vlTypePTR(p) (vlTypePtrToTypedata ((vlPointerT) (p)))


/*
 * This macro is undocumented because we are phasing it out.
 */
#define vlTypeMAKE_PTR_TS(c_type, tsname, ts, spec_name, getname) \
  static struct {vlStringProcT name;} spec_name = {(vlStringProcT) getname};\
  vlTypeSpecT ts = {tsname, &vlPointerNoAllocTB, (vlPointerT) &spec_name, 1}

typedef struct {
    vlStringProcT name;
    vlPointerProcT copy;
    vlVoidProcT free;
} vlTypeNameCopyFreeT;

typedef struct {
    vlVoidProcT name;
    vlPointerProcT copy;
    vlVoidProcT free;
    vlVoidProcT convert;
} vlTypeNameCopyFreeCvtT;


/*\Docpage vlTypeMAKE_PTR -- Make a typespec for a simple pointer type.

DESCRIPTION
     If a pointer-based data type is very static in nature, i.e. it has no
     real memory management associated with it, then a simple way to make a
     typespec out of it is to use this macro.  It only requires that one
     routine be written to return a character string representation for the
     instance.

     By convention, use the TS suffix for the typespec name and the VT suffix
     for the typespec name as it will be known in ViewScript.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

EXAMPLE
     typedef struct {
         char *name;
         ...
     } *my_typeID;

     static const char *getname(data)
         my_typeID  data;
     {
         return (data -> name);
     }

     vlTypeMAKE_PTR (my_typeTS, "my_typeVT", getname);

CAUTIONS
     If you use this typespec to share dynamic data with ViewScript, you must
     call vscmTypespecDestroy when you free the data in order to insure that
     ViewScript doesn't hang on to an invalid pointer.

     This macro is implemented using token concatenation, which works with
     UNIX and ANSII compilers.  For preprocessors that do not support token
     concatenation, you must use a different version of this macro,
     vlTypeMAKE_PTR_TS, which is not currently documented.

SEE ALSO
     vlTypeMAKE_PTR1, vscmTypespecDestroy, vscmRegisterType

SYNOPSIS
     vlTypeMAKE_PTR(ts, ts_name, name_proc)
         vlTypeSpecT    ts;
         char          *ts_name;
         vlStringProcT  name_proc;
*/
#define vlTypeMAKE_PTR(ts, tsname, getname) \
  static struct {vlStringProcT name;} vlCONCAT_TOKEN(ts,_spec) = \
      {(vlStringProcT) getname}; \
  vlTypeSpecT ts = {tsname, &vlPointerNoAllocTB, \
                            (vlPointerT) &vlCONCAT_TOKEN(ts,_spec), 1}


/*\Docpage vlTypeMAKE_PTR1 -- Make a typespec for a pointer type.

DESCRIPTION
     If a pointer-based data type is very static in nature, i.e. it has no
     real memory management associated with it, then a simple way to make a
     typespec out of it is to use this macro.  It differs from vlTypeMAKE_PTR
     in its usage of an output routine.  vlTypeMAKE_PTR requires a routine
     that returns a character string representation of the object, which may
     be inconvenient to do without keeping a wasteful static buffer around.
     This macro requires a routine that is called with the object, a procedure
     pointer, and data to be passed to the procedure pointer.  The routine
     must call the procedure pointer with a char * buffer that displays the
     object, but the char * doesn't have to outlive the life of the routine.

     By convention, use the TS suffix for the typespec name and the VT suffix
     for the typespec name as it will be known in ViewScript.

CAUTIONS
     You must call vscmTypespecDestroy when you free the data in order to
     insure that ViewScript doesn't hang on to an invalid pointer.  This macro
     is implemented using token concatenation, which works with UNIX and ANSII
     compilers.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

EXAMPLE
     typedef struct {
         int    member1;
         char  *member2;
         ...
     } *my_typeID;

     static void output(data, outproc, outproc_data)
         my_typeID      data;
         vlVoidProcT    outproc;
         vlPointerT     outproc_data;
     {
         (*outproc) (outproc_data,
                     vlSprintfStatic ("member1=%d, ", data -> member1);
         (*outproc) (outproc_data,
                     vlSprintfStatic ("member2=%s, ", data -> member2);
     }

     vlTypeMAKE_PTR1 (my_typeTS, "my_typeVT", output);

SEE ALSO
     vlTypeMAKE_PTR, vscmRegisterType

SYNOPSIS
     vlTypeMAKE_PTR1(ts, ts_name, output_proc)
         vlTypeSpecT    ts;
         char          *ts_name;
         vlVoidProcT    output_proc;
*/
#define vlTypeMAKE_PTR1(ts, tsname, getname) \
  static struct {vlVoidProcT name;} vlCONCAT_TOKEN(ts,_spec) = \
      {getname}; \
  vlTypeSpecT ts = {tsname, &vlPointerNoAlloc1TB, \
                            (vlPointerT) &vlCONCAT_TOKEN(ts,_spec), 1}


/*\Docpage vlTypeMAKE_PTR2 -- Make a typespec for a complex pointer type.

DESCRIPTION
     If a pointer-based data type is very dynamic in nature, i.e. it is
     frequently allocated, freed, or copied, then a simple way to make a
     typespec out of it is to use this macro.  It requires that three routines
     be written:  print(), copy(), and free().

     vlTypeMAKE_PTR2 is used when the memory management is complex, but the
     printing of the data type is simple -- it is easy to write a routine that
     returns a "const char *" that contains a printable representation of the
     object.  This would be the case for objects that are identified by their
     name, which is stored as a member of the structure, and can be returned
     by the routine.

     This routine is used when there is no way to parse a string into an
     instance of the object.  If there is a way, a new macro will have to be
     written to deal with it easier.  Until then, write a new typebase.

     By convention, use the TS suffix for the typespec name and the VT suffix
     for the typespec name as it will be known in ViewScript.

NOTE
     Note that the copy routine need not actually allocate new data--it
     might prefer to increment a reference count inside the structure and
     return the same object.  The free routine would then decrement and check
     the reference count, and avoid destroying it until the count went to 0.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

EXAMPLE
     typedef struct {
         char  *name;
         int    reference_count;
         ...
     } *my_typeID;

     static const char *getname(data)
         my_typeID  data;
     {
         return (data -> name);
     }

     static my_typeID copy(data)
         my_typeID  data;
     {
         data -> reference_count++;
         return (data);
     }

     static void free(my_data)
         my_typeID  data;
     {
         data -> reference_count--;
         if (data -> reference_count == 0)
             vlMemFree ((vlPointerT) data);
     }

     vlTypeMAKE_PTR2 (my_typeTS, "my_typeVT", getname, copy, free);

SEE ALSO
     vlTypeMAKE_PTR3, vscmRegisterType

SYNOPSIS
     vlTypeMAKE_PTR2(ts, ts_name, name_proc, copy_proc, free_proc)
         vlTypeSpecT    ts;
         char          *ts_name;
         vlStringProcT  name_proc;
         vlPointerProcT copy_proc;
         vlVoidProcT    free_proc;
*/
#define vlTypeMAKE_PTR2(ts, tsname, name_proc, copy_proc, free_proc)    \
    static vlTypeNameCopyFreeT vlCONCAT_TOKEN(ts,_spec) = {             \
        (vlStringProcT) name_proc, (vlPointerProcT) copy_proc,          \
        (vlVoidProcT) free_proc};                                       \
    vlTypeSpecT ts = {                                              \
        tsname, &vlPointerTB, (vlPointerT) &vlCONCAT_TOKEN(ts,_spec), 1}


/*\Docpage vlTypeMAKE_PTR3 -- Make a typespec for a way-complex pointer type.

DESCRIPTION
     If a pointer-based data type is very dynamic in nature, i.e. it is
     frequently allocated, freed, or copied, then a simple way to make a
     typespec out of it is to use this macro.  It requires that three routines
     be written:  output(), copy(), and free().

     vlTypeMAKE_PTR3 is used when the memory management is complex and the
     printing of the data type is also complex -- it is *not* easy to write a
     routine that returns a "const char *" that contains a printable
     representation of the object.  This would be the case for objects that
     have externally relevant scalar members, such as rectangles or graphical
     transformations.

     This routine is used when there is no way to parse a string into an
     instance of the object.  If there is a way, use vlTypeMAKE_PTR4.

     By convention, use the TS suffix for the typespec name and the VT suffix
     for the typespec name as it will be known in ViewScript.

NOTE
     Note that the copy routine need not actually allocate new data -- it
     might prefer to increment a reference count inside the structure and
     return the same object.  The free routine would then decrement and check
     the reference count, and avoid destroying it until the count went to 0.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

EXAMPLE
     typedef struct {
         int    member1;
         char  *member2;
         int    reference_count;
         ...
     } *my_typeID;

     static void output(data, outproc, outproc_data)
         my_typeID      data;
         vlVoidProcT    outproc;
         vlPointerT     outproc_data;
     {
         (*outproc) (outproc_data,
                     vlSprintfStatic ("member1=%d, ", data -> member1);
         (*outproc) (outproc_data,
                     vlSprintfStatic ("member2=%s, ", data -> member2);
     }

     static my_typeID copy(data)
         my_typeID  data;
     {
         data -> reference_count++;
         return (data);
     }

     static void free(my_data)
         my_typeID  data;
     {
         data -> reference_count--;
         if (data -> reference_count == 0)
             vlMemFree ((vlPointerT) data);
     }

     vlTypeMAKE_PTR3 (my_typeTS, "my_typeVT", output, copy, free);

SEE ALSO
     vlTypeMAKE_PTR2, vscmRegisterType

SYNOPSIS
     vlTypeMAKE_PTR3(ts, ts_name, output_proc, copy_proc, free_proc)
         vlTypeSpecT    ts;
         char          *ts_name;
         vlVoidProcT    output_proc;
         vlPointerProcT copy_proc;
         vlVoidProcT    free_proc;
*/
#define vlTypeMAKE_PTR3(ts, tsname, output_proc, copy_proc, free_proc)  \
    static vlTypeNameCopyFreeT vlCONCAT_TOKEN(ts,_spec) = {             \
        (vlStringProcT) output_proc, (vlPointerProcT) copy_proc,        \
        (vlVoidProcT) free_proc};                                       \
    vlTypeSpecT ts = {                                                  \
        tsname, &vlPointer3TB, (vlPointerT) &vlCONCAT_TOKEN(ts,_spec), 1}


/*\Docpage vlTypeMAKE_PTR4 -- Make a typespec for a parsable pointer type.

DESCRIPTION
     If a pointer-based data type is very dynamic in nature, i.e. it is
     frequently allocated, freed, or copied, then a simple way to make a
     typespec out of it is to use this macro.  It requires that three routines
     be written:  output(), copy(), and free().  In addition, if the data type
     can be parsed and created from a string, then provide a fourth procedure:
     convert(), using this macro.

     vlTypeMAKE_PTR4 is used when the memory management is complex and the
     printing of the data type is also complex -- it is *not* easy to write a
     routine that returns a "const char *" that contains a printable
     representation of the object.  This would be the case for objects that
     have externally relevant scalar members, such as rectangles or graphical
     transformations.

     Use vlTypeMAKE_PTR3 if there is no way to parse a string into an instance
     of the object.

     By convention, use the TS suffix for the typespec name and the VT suffix
     for the typespec name as it will be known in ViewScript.

NOTE
     Note that the copy routine need not actually allocate new data--it might
     prefer to increment a reference count inside the structure and return 
     the same object.  The free routine would then decrement and check the
     reference count, and avoid destroying it until the count went to 0.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

CAUTION
     You *must* use the vlCbRETURN_PTR or vlCbRETURN_LONG macros to pass the
     newly created object in the convert() procedure.  Which one to use
     depends whether the object is pointer based or fits in the long word.

EXAMPLE
     typedef struct my_type {
         int    member1;
         double member2;
         int    reference_count;
     } *my_typeID;

     #define MY_FORMAT "member1=%d, member2=%lf"

     static void output(my_data, outproc, outproc_data)
         my_typeID      data;
         vlVoidProcT    outproc;
         vlPointerT     outproc_data;
     {
         (*outproc) (outproc_data,
                     vlSprintfStatic (MY_FORMAT,
                                      data -> member1, data -> member2));
     }

     static my_typeID copy(data)
         my_typeID  data;
     {
         data -> reference_count++;
         return (data);
     }

     static void free(my_data)
         my_typeID  data;
     {
         data -> reference_count--;
         if (data -> reference_count == 0)
             vlMemFree ((vlPointerT) data);
     }

     static void convert(str)
         const char *str;
     {
         int        member1;
         double     member2;
         my_typeID  data;

         if (sscanf (str, MY_FORMAT, &member1, &member2) != 2)
             vlCbERROR (vlSprintfStatic ("Cannot parse `%s' into my_typeID",
                                         str));
         data = (my_data_type *) vlMemMalloc (sizeof (my_type), "my_type");
         data -> member1 = member1;
         data -> member2 = member2;
         data -> reference_count = 1;
         vlCbRETURN_PTR (data);
     }

     vlTypeMAKE_PTR4 (my_typeTS, "my_typeVT", output, copy, free, convert);

SEE ALSO
     vscmRegisterType

SYNOPSIS
     vlTypeMAKE_PTR4(ts, ts_name, out_proc, copy_proc, free_proc, convert_proc)
         vlTypeSpecT    ts;
         char          *ts_name;
         vlVoidProcT    out_proc;
         vlPointerProcT copy_proc;
         vlVoidProcT    free_proc;
         vlVoidProcT    convert_proc;
*/
#define vlTypeMAKE_PTR4(ts, tsname, output_proc, copy_proc,free_proc,cvt_proc)\
    static vlTypeNameCopyFreeCvtT vlCONCAT_TOKEN(ts,_spec) = {          \
        (vlVoidProcT) output_proc, (vlPointerProcT) copy_proc,          \
        (vlVoidProcT) free_proc, (vlVoidProcT) cvt_proc};               \
    vlTypeSpecT ts = {                                                  \
        tsname, &vlPointer4TB, (vlPointerT) &vlCONCAT_TOKEN(ts,_spec), 1}


/*******************Macros to help make Enum typespecs*********************/

#define vlTypeMAKE_ENUM_TS(ts, tsname, str_var, len) \
    static vlTypeEnuminfoT vlCONCAT_TOKEN(ts,_einfo) = {len, str_var}; \
    vlTypeSpecT ts = {tsname, &vlEnumTB, \
        (vlPointerT) &(vlCONCAT_TOKEN(ts,_einfo)), 1}

/*\Docpage vlTypeMAKE_ENUM -- Make an enum typespec from a string array.

DESCRIPTION
     This macro provides a convenient way to make a typespec for an enumerated
     type with any number choices, from a string array.  It should be called
     outside any procedures, in a module's static data initialization section.

     The other macros, such as vlTypeMAKE_ENUM2, are easier to call, since
     they combine the steps of creating the string array and making the
     typespec.

     By convention, use the TS suffix for the typespec name and the VT suffix
     for the typespec name as it will be known in ViewScript.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

EXAMPLE
     static const char *choices = {"choice1", "choice2", "choice3", ...};
     vlTypeMAKE_ENUM (my_enumTS, "my_enumVT", choices);

CAUTIONS
     Do not permit any whitespace to surround the first argument "typespec".
     For example, vlTypeMAKE_ENUM2 ( typespec, ...) and
     vlTypeMAKE_ENUM2 (typespec , ...) will not work.

     This macro is implemented using token concatenation, which works with
     UNIX and ANSII compilers.

     You should follow the example very closely, because the macro uses the
     sizeof operator on the string array to get the number of strings.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

SEE ALSO
     vlTypeMAKE_ENUM2..10, vscmRegisterType

SYNOPSIS
     vlTypeMAKE_ENUM(ts, ts_name, str_array)
         vlTypeSpecT    ts;
         char          *ts_name;
         char          *str_array;
*/
#define vlTypeMAKE_ENUM(ts, tsname, str_var) \
    vlTypeMAKE_ENUM_TS (ts, tsname, str_var, \
                        (sizeof (str_var) / sizeof (char *)))


/*\Docpage vlTypeMAKE_ENUM2 -- Make an enum typespec with two choices.

DESCRIPTION
     This macro provides a convenient way to make a typespec for an enumerated
     type with two choices.  It should be called outside any procedures, in a
     module's static data initialization section.

     By convention, use the TS suffix for the typespec name and the VT suffix
     for the typespec name as it will be known in ViewScript.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

EXAMPLE
     vlTypeMAKE_ENUM2 (vlYesNoTS, "vlYesNoVT", "No", "Yes");

CAUTIONS
     Do not permit any whitespace to surround the first argument "typespec".
     For example, vlTypeMAKE_ENUM2 ( typespec, ...) and
     vlTypeMAKE_ENUM2 (typespec , ...) will not work.

     This macro is implemented using token concatenation, which works with
     UNIX and ANSII compilers.

SEE ALSO
     vlTypeMAKE_ENUM2..10

SYNOPSIS
     vlTypeMAKE_ENUM2(ts, ts_name, choice0, choice1)
         vlTypeSpecT    ts;
         char          *ts_name;
         char          *choice0, *choice1;
*/
#define vlTypeMAKE_ENUM2(ts, tsname, str1, str2) \
    static const char *vlCONCAT_TOKEN(ts,_strings)[2] = {str1, str2}; \
    vlTypeMAKE_ENUM_TS (ts, tsname, vlCONCAT_TOKEN(ts,_strings), 2)


/*\Docpage vlTypeMAKE_ENUM3 -- Make an enum typespec with three choices.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

SEE ALSO
     vlTypeMAKE_ENUM2

SYNOPSIS
     vlTypeMAKE_ENUM3(ts, ts_name, choice0, choice1, choice2)
         vlTypeSpecT    ts;
         char          *ts_name;
         char          *choice0, *choice1, *choice2;
*/
#define vlTypeMAKE_ENUM3(ts, tsname, str1, str2, str3)                  \
    static const char *vlCONCAT_TOKEN(ts,_strings)[3] = {str1, str2, str3};   \
    vlTypeMAKE_ENUM_TS (ts, tsname, vlCONCAT_TOKEN(ts,_strings), 3)
                        

/*\Docpage vlTypeMAKE_ENUM4 -- Make an enum typespec with four choices.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

SEE ALSO
    vlTypeMAKE_ENUM2.

SYNOPSIS
     vlTypeMAKE_ENUM4(ts, ts_name, choice0, choice1, choice2, choice3)
         vlTypeSpecT    ts;
         char          *ts_name;
         char          *choice0, *choice1, *choice2, *choice3;
*/
#define vlTypeMAKE_ENUM4(ts, tsname, str1, str2, str3, str4) \
    static const char *vlCONCAT_TOKEN(ts,_strings)[4] = {str1, str2, str3, str4}; \
    vlTypeMAKE_ENUM_TS (ts, tsname, vlCONCAT_TOKEN(ts,_strings), 4)
                        

/*\Docpage vlTypeMAKE_ENUM5 -- Make an enum typespec with five choices.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

SEE ALSO
    vlTypeMAKE_ENUM2

SYNOPSIS
     vlTypeMAKE_ENUM5(ts, ts_name, choice0, choice1, choice2, choice3, choice4)
         vlTypeSpecT    ts;
         char          *ts_name;
         char          *choice0, *choice1, *choice2, *choice3, *choice4;
*/
#define vlTypeMAKE_ENUM5(ts, tsname, str1, str2, str3, str4, str5) \
    static const char *vlCONCAT_TOKEN(ts,_strings)[5] = {str1, str2, str3, str4, \
                                                   str5}; \
    vlTypeMAKE_ENUM_TS (ts, tsname, vlCONCAT_TOKEN(ts,_strings), 5)
                        

/*\Docpage vlTypeMAKE_ENUM6 -- Make an enum typespec with six choices.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

SEE ALSO
    vlTypeMAKE_ENUM2

SYNOPSIS
     vlTypeMAKE_ENUM6(ts, ts_name, choice0, choice1, choice2, choice3,
                      choice4, choice5)
         vlTypeSpecT    ts;
         char          *ts_name;
         char          *choice0, *choice1, *choice2, *choice3, *choice4;
         char          *choice5;
*/
#define vlTypeMAKE_ENUM6(ts, tsname, str1, str2, str3, str4, str5, str6) \
    static const char *vlCONCAT_TOKEN(ts,_strings)[6] = {str1, str2, str3, str4, \
                                                   str5, str6}; \
    vlTypeMAKE_ENUM_TS (ts, tsname, vlCONCAT_TOKEN(ts,_strings), 6)
                        

/*\Docpage vlTypeMAKE_ENUM7 -- Make an enum typespec with seven choices.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

SEE ALSO
    vlTypeMAKE_ENUM2

SYNOPSIS
     vlTypeMAKE_ENUM7(ts, ts_name, choice0, choice1, choice2, choice3,
                      choice4, choice5, choice6)
         vlTypeSpecT    ts;
         char          *ts_name;
         char          *choice0, *choice1, *choice2, *choice3, *choice4;
         char          *choice5, *choice6
*/
#define vlTypeMAKE_ENUM7(ts, tsname, str1, str2, str3, str4, str5, str6, str7)\
    static const char *vlCONCAT_TOKEN(ts,_strings)[7] = {str1, str2, str3, str4, \
                                                   str5, str6, str7}; \
    vlTypeMAKE_ENUM_TS (ts, tsname, vlCONCAT_TOKEN(ts,_strings), 7)
                        

/*\Docpage vlTypeMAKE_ENUM8 -- Make an enum typespec with eight choices.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

SEE ALSO
    vlTypeMAKE_ENUM2

SYNOPSIS
     vlTypeMAKE_ENUM8(ts, ts_name, choice0, choice1, choice2, choice3,
                      choice4, choice5, choice6, choice7)
         vlTypeSpecT    ts;
         char          *ts_name;
         char          *choice0, *choice1, *choice2, *choice3, *choice4;
         char          *choice5, *choice6, *choice7;
*/
#define vlTypeMAKE_ENUM8(ts, tsname, str1, str2, str3, str4, str5, str6, str7, str8) \
    static const char *vlCONCAT_TOKEN(ts,_strings)[8] = {str1, str2, str3, str4, \
                                                   str5, str6, str7, str8}; \
    vlTypeMAKE_ENUM_TS (ts, tsname, vlCONCAT_TOKEN(ts,_strings), 8)


/*\Docpage vlTypeMAKE_ENUM9 -- Make an enum typespec with nine choices.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

SEE ALSO
    vlTypeMAKE_ENUM2

SYNOPSIS
     vlTypeMAKE_ENUM9(ts, ts_name, choice0, choice1, choice2, choice3,
                      choice4, choice5, choice6, choice7, choice8)
         vlTypeSpecT    ts;
         char          *ts_name;
         char          *choice0, *choice1, *choice2, *choice3, *choice4;
         char          *choice5, *choice6, *choice7, *choice8;
*/
#define vlTypeMAKE_ENUM9(ts, tsname, str1, str2, str3, str4, str5, str6, str7, str8, str9) \
    static const char *vlCONCAT_TOKEN(ts,_strings)[9] = {str1, str2, str3, str4, \
                                                   str5, str6, str7, str8, \
                                                   str9}; \
    vlTypeMAKE_ENUM_TS (ts, tsname, vlCONCAT_TOKEN(ts,_strings), 9)

/*\Docpage vlTypeMAKE_ENUM10 -- Make an enum typespec with nine choices.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

SEE ALSO
    vlTypeMAKE_ENUM2.

SYNOPSIS
     vlTypeMAKE_ENUM10(ts, ts_name, choice0, choice1, choice2, choice3,
                       choice4, choice5, choice6, choice7, choice8, choice9)
         vlTypeSpecT    ts;
         char          *ts_name;
         char          *choice0, *choice1, *choice2, *choice3, *choice4;
         char          *choice5, *choice6, *choice7, *choice8, *choice9;
*/
#define vlTypeMAKE_ENUM10(ts, tsname, str1, str2, str3, str4, str5, str6, str7, str8, str9, str10) \
    static const char *vlCONCAT_TOKEN(ts,_strings)[10] = {str1, str2, str3, str4, \
                                                    str5, str6, str7, str8, \
                                                    str9, str10}; \
    vlTypeMAKE_ENUM_TS (ts, tsname, vlCONCAT_TOKEN(ts,_strings), 10)


/*******************Macros to help make Mask typespecs*********************/

#define vlTypeMAKE_MASK_TS(ts, tsname, str_var, len) \
    static vlTypeMaskinfoT vlCONCAT_TOKEN(ts,_einfo) = {len, str_var}; \
    vlTypeSpecT ts = {tsname, &vlMaskTB, \
        (vlPointerT) &(vlCONCAT_TOKEN(ts,_einfo)), 1}


/*\Docpage vlTypeMAKE_MASK -- Make a mask typespec from a string array.

DESCRIPTION
     This macro provides a convenient way to make a typespec for a masked
     type with any number choices, from a string array.  It should be called
     outside any procedures, in a module's static data initialization section.

     The other macros, such as vlTypeMAKE_MASK2, are easier to call, since
     they combine the steps of creating the string array and making the
     typespec.

     By convention, use the TS suffix for the typespec name and the VT suffix
     for the typespec name as it will be known in ViewScript.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

EXAMPLE
     static char *choices = {"choice1", "choice2", "choice3", ...};
     vlTypeMAKE_MASK (my_typeTS, "my_typeVT", choices);

CAUTIONS
     Do not permit any whitespace to surround the first argument "typespec".
     For example, vlTypeMAKE_MASK2 ( typespec, ...) and
     vlTypeMAKE_MASK2 (typespec , ...) will not work.

     This macro is implemented using token concatenation, which works with
     UNIX and ANSII compilers.

     You should follow the example very closely, because the macros uses the
     sizeof operator on the string array to get the number of strings.

SEE ALSO
     vlTypeMAKE_MASK2..10, vscmRegisterType

SYNOPSIS
     vlTypeMAKE_MASK(ts, ts_name, str_array)
         vlTypeSpecT    ts;
         char          *ts_name;
         char          *str_array;
*/
#define vlTypeMAKE_MASK(ts, tsname, str_var) \
    vlTypeMAKE_MASK_TS (ts, tsname, str_var, \
                        (sizeof (str_var) / sizeof (char *)))


/*\Docpage vlTypeMAKE_MASK2 -- Make an mask typespec with two choices.

DESCRIPTION
     This macro provides a convenient way to make a typespec for a masked
     type with two choices.  It should be called outside any procedures, in a
     module's static data initialization section.

     By convention, use the TS suffix for the typespec name and the VT suffix
     for the typespec name as it will be known in ViewScript.

EXAMPLE
     vlTypeMAKE_MASK2 (vlYesNoTS, "vlYesNoVT", "No", "Yes");

CAUTIONS
     Do not permit any whitespace to surround the first argument "typespec".
     For example, vlTypeMAKE_MASK2 ( typespec, ...) and
     vlTypeMAKE_MASK2 (typespec , ...) will not work.

     This macro is implemented using token concatenation, which works with
     UNIX and ANSII compilers.

SEE ALSO
     vlTypeMAKE_MASK2..10

SYNOPSIS
     vlTypeMAKE_MASK2(ts, ts_name, choice0, choice1)
         vlTypeSpecT    ts;
         char          *ts_name;
         char          *choice0, *choice1;
*/
#define vlTypeMAKE_MASK2(ts, tsname, str1, str2) \
    static const char *vlCONCAT_TOKEN(ts,_strings)[2] = {str1, str2}; \
    vlTypeMAKE_MASK_TS (ts, tsname, vlCONCAT_TOKEN(ts,_strings), 2)


/*\Docpage vlTypeMAKE_MASK3 -- Make an mask typespec with three choices.

SEE ALSO
    vlTypeMAKE_MASK2

SYNOPSIS
     vlTypeMAKE_MASK3(ts, ts_name, choice0, choice1, choice2)
         vlTypeSpecT    ts;
         char          *ts_name;
         char          *choice0, *choice1, *choice2;
*/
#define vlTypeMAKE_MASK3(ts, tsname, str1, str2, str3) \
    static const char *vlCONCAT_TOKEN(ts,_strings)[3] = {str1, str2, str3}; \
    vlTypeMAKE_MASK_TS (ts, tsname, vlCONCAT_TOKEN(ts,_strings), 3)
                        

/*\Docpage vlTypeMAKE_MASK4 -- Make an mask typespec with four choices.

SEE ALSO
    vlTypeMAKE_MASK2

SYNOPSIS
     vlTypeMAKE_MASK4(ts, ts_name, choice0, choice1, choice2, choice3)
         vlTypeSpecT    ts;
         char          *ts_name;
         char          *choice0, *choice1, *choice2, *choice3;
*/
#define vlTypeMAKE_MASK4(ts, tsname, str1, str2, str3, str4) \
    static const char *vlCONCAT_TOKEN(ts,_strings)[4] = {str1, str2, str3, str4}; \
    vlTypeMAKE_MASK_TS (ts, tsname, vlCONCAT_TOKEN(ts,_strings), 4)
                        

/*\Docpage vlTypeMAKE_MASK5 -- Make an mask typespec with five choices.

SEE ALSO
    vlTypeMAKE_MASK2.

SYNOPSIS
     vlTypeMAKE_MASK5(ts, ts_name, choice0, choice1, choice2, choice3, choice4)
         vlTypeSpecT    ts;
         char          *ts_name;
         char          *choice0, *choice1, *choice2, *choice3, *choice4;
*/
#define vlTypeMAKE_MASK5(ts, tsname, str1, str2, str3, str4, str5) \
    static const char *vlCONCAT_TOKEN(ts,_strings)[5] = {str1, str2, str3, str4, \
                                                   str5}; \
    vlTypeMAKE_MASK_TS (ts, tsname, vlCONCAT_TOKEN(ts,_strings), 5)
                        

/*\Docpage vlTypeMAKE_MASK6 -- Make an mask typespec with six choices.

SEE ALSO
    vlTypeMAKE_MASK2

SYNOPSIS
     vlTypeMAKE_MASK6(ts, ts_name, choice0, choice1, choice2, choice3,
                      choice4, choice5)
         vlTypeSpecT    ts;
         char          *ts_name;
         char          *choice0, *choice1, *choice2, *choice3, *choice4;
         char          *choice5;
*/
#define vlTypeMAKE_MASK6(ts, tsname, str1, str2, str3, str4, str5, str6) \
    static const char *vlCONCAT_TOKEN(ts,_strings)[6] = {str1, str2, str3, str4, \
                                                   str5, str6}; \
    vlTypeMAKE_MASK_TS (ts, tsname, vlCONCAT_TOKEN(ts,_strings), 6)
                        

/*\Docpage vlTypeMAKE_MASK7 -- Make an mask typespec with seven choices.

SEE ALSO
    vlTypeMAKE_MASK2

SYNOPSIS
     vlTypeMAKE_MASK7(ts, ts_name, choice0, choice1, choice2, choice3,
                      choice4, choice5, choice6)
         vlTypeSpecT    ts;
         char          *ts_name;
         char          *choice0, *choice1, *choice2, *choice3, *choice4;
         char          *choice5, *choice6;
*/
#define vlTypeMAKE_MASK7(ts, tsname, str1, str2, str3, str4, str5, str6, str7)\
    static const char *vlCONCAT_TOKEN(ts,_strings)[7] = {str1, str2, str3, str4, \
                                                   str5, str6, str7}; \
    vlTypeMAKE_MASK_TS (ts, tsname, vlCONCAT_TOKEN(ts,_strings), 7)
                        

/*\Docpage vlTypeMAKE_MASK8 -- Make an mask typespec with eight choices.

SEE ALSO
    vlTypeMAKE_MASK2

SYNOPSIS
     vlTypeMAKE_MASK8(ts, ts_name, choice0, choice1, choice2, choice3,
                      choice4, choice5, choice6, choice7)
         vlTypeSpecT    ts;
         char          *ts_name;
         char          *choice0, *choice1, *choice2, *choice3, *choice4;
         char          *choice5, *choice6, *choice7;
*/
#define vlTypeMAKE_MASK8(ts, tsname, str1, str2, str3, str4, str5, str6, str7, str8) \
    static const char *vlCONCAT_TOKEN(ts,_strings)[8] = {str1, str2, str3, str4, \
                                                   str5, str6, str7, str8}; \
    vlTypeMAKE_MASK_TS (ts, tsname, vlCONCAT_TOKEN(ts,_strings), 8)


/*\Docpage vlTypeMAKE_MASK9 -- Make an mask typespec with nine choices.

SEE ALSO
    vlTypeMAKE_MASK2.

SYNOPSIS
     vlTypeMAKE_MASK9(ts, ts_name, choice0, choice1, choice2, choice3,
                      choice4, choice5, choice6, choice7, choice8)
         vlTypeSpecT    ts;
         char          *ts_name;
         char          *choice0, *choice1, *choice2, *choice3, *choice4;
         char          *choice5, *choice6, *choice7, *choice8;
*/
#define vlTypeMAKE_MASK9(ts, tsname, str1, str2, str3, str4, str5, str6, str7, str8, str9) \
    static const char *vlCONCAT_TOKEN(ts,_strings)[9] = {str1, str2, str3, str4, \
                                                   str5, str6, str7, str8, \
                                                   str9}; \
    vlTypeMAKE_MASK_TS (ts, tsname, vlCONCAT_TOKEN(ts,_strings), 9)


/*\Docpage vlTypeMAKE_MASK10 -- Make an mask typespec with nine choices.

SEE ALSO
    vlTypeMAKE_MASK2.

SYNOPSIS
     vlTypeMAKE_MASK10(ts, ts_name, choice0, choice1, choice2, choice3,
                       choice4, choice5, choice6, choice7, choice8, choice9)
         vlTypeSpecT    ts;
         char          *ts_name;
         char          *choice0, *choice1, *choice2, *choice3, *choice4;
         char          *choice5, *choice6, *choice7, *choice8, *choice9;
*/
#define vlTypeMAKE_MASK10(ts, tsname, str1, str2, str3, str4, str5, str6, str7, str8, str9, str10) \
    static const char *vlCONCAT_TOKEN(ts,_strings)[10] = {str1, str2, str3, str4, \
                                                    str5, str6, str7, str8, \
                                                    str9, str10}; \
    vlTypeMAKE_MASK_TS (ts, tsname, vlCONCAT_TOKEN(ts,_strings), 10)


/*\Docpage vlTypeMAKE_INT -- Create an integer typespec.

CAUTIONS
     This macro is provided to make it easier to create typespecs that are
     variations on the basic integer typespec.  The "variations" are
     distinquished from each other by the lower and upper bounds for the
     values accepted by those typespecs.

     Do not permit any whitespace to surround the first argument
     "typespec_variable".  For example, vlTypeMAKE_INT ( typespec, ...)
     and vlTypeMAKE_INT (typespec , ...) will not work.

     This macro is implemented using token concatenation, which works with
     UNIX and ANSII compilers.

     By convention, use the TS suffix for the typespec name and the VT suffix
     for the typespec name as it will be known in ViewScript.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

EXAMPLE
     vlTypeMAKE_INT (vlPositiveIntTS, "vcPositiveIntVT", 1, vlLINFINITY);

SEE ALSO
     vscmRegisterType

SYNOPSIS
     vlTypeMAKE_INT(ts, ts_name, lower_bound, upper_bound)
         vlTypeSpecT    ts;
         char          *ts_name;
         long           lower_bound, upper_bound;
*/
#define vlTypeMAKE_INT(ts, tsname, low, high) \
    static vlTypeRangeIntT vlCONCAT_TOKEN(ts,_intinfo) = {low, high}; \
    vlTypeSpecT ts = {tsname, &vlIntTB, \
                              (vlPointerT) &(vlCONCAT_TOKEN(ts,_intinfo)), 1}
    

/*\Docpage vlTypeMAKE_INT64 -- Create a 64-bit integer typespec.

CAUTIONS
     This macro is provided to make it easier to create typespecs that are
     variations on the 64-bit integer typespec.  The "variations" are
     distinquished from each other by the lower and upper bounds for the
     values accepted by those typespecs.

     Do not permit any whitespace to surround the first argument
     "typespec_variable".  For example, vlTypeMAKE_INT ( typespec, ...)
     and vlTypeMAKE_INT (typespec , ...) will not work.

     This macro is implemented using token concatenation, which works with
     UNIX and ANSII compilers.

     By convention, use the TS suffix for the typespec name and the VT suffix
     for the typespec name as it will be known in ViewScript.

NOTE
     The lower and upper bound must be specified as a range of the type 
     vlTypeRangeInt64T. This is different than with the vlTypeMAKE_INT macro.

     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

EXAMPLE
     vlTypeRangeInt64T range;
     ...
     range.imin = vlInt64One;
     range.imin = vlInt64MAX;
     ...
     vlTypeMAKE_INT64 (vlPositiveInt64TS, "vlPositiveInt64VT", range);

SEE ALSO
     vscmRegisterType

SYNOPSIS
     vlTypeMAKE_INT(ts, ts_name, lower_bound, upper_bound)
         vlTypeSpecT    ts;
         char          *ts_name;
         long           lower_bound, upper_bound;
*/
#define vlTypeMAKE_INT64(ts, tsname, range) \
    vlTypeSpecT ts = {tsname, &vlInt64TB, (vlPointerT) &range, 1}
    

/*\Docpage vlTypeMAKE_FLOAT -- Create a floating point typespec.

CAUTIONS
     This macro is provided to make it easier to create typespecs that are
     variations on the basic floting point number typespec.  The "variations"
     are distinquished from each other by the lower and upper bounds for the
     values accepted by those typespecs.

     Do not permit any whitespace to surround the first argument
     "typespec_variable".  For example, vlTypeMAKE_FLOAT ( typespec, ...)
     and vlTypeMAKE_FLOAT (typespec , ...) will not work.

     This macro is implemented using token concatenation, which works
     with Unix and Ansi compilers.

     By convention, use the TS suffix for the typespec name and the VT suffix
     for the typespec name as it will be known in ViewScript.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

EXAMPLE
     vlTypeMAKE_FLOAT (vlPositiveFloatTS, "vcPositiveFloatVT", 0, vlDINFINITY);

SEE ALSO
     vscmRegisterType

SYNOPSIS
     vlTypeMAKE_FLOAT(ts, ts_name, lower_bound, upper_bound)
         vlTypeSpecT    ts;
         char          *ts_name;
         double         lower_bound, upper_bound;
*/
#define vlTypeMAKE_FLOAT(ts, tsname, low, high) \
    static vlTypeRangeFloatT vlCONCAT_TOKEN(ts,_floatinfo) = {low, high}; \
    vlTypeSpecT ts = {tsname, &vlFloatTB, \
                              (vlPointerT) &(vlCONCAT_TOKEN(ts,_floatinfo)), 1}


typedef struct {
    vlBoolProcT check;
    const char *type_name;
} vlTypeStringSpecificsT;

/*
 * vlTypeFilenameSpecificsT is like StringSpecifics, above, except that
 * it contains an optional msg_number field which is used to improve the
 * appearance of error messages for invalid filenames.  This is done in
 * a not-so-general way, and will have to be improved sometime, but it
 * solves an immediate problem -- when the user types a non-existent filename,
 * the error message should be "file not found", not "Invalid vlFileReadVT".
 *
 * The msg_number field is used in an alternate version of vlTypeMAKE_FILENAME,
 * called vlTypeMAKE_FILENAME2.  This is not documented, and should not be,
 * for it will change when we solve this problem in a more general way, for
 * all typespecs.
 */
typedef struct {
    vlBoolProcT check;
    const char *type_name;
    int msg_number;             /* vllib.vmt # for errors, or -1 if none */
} vlTypeFilenameSpecificsT;

/*\Docpage vlTypeMAKE_STRING -- Make a string datatype with a check routine.

DESCRIPTION
     The standard string typespec, vlStringTS, accepts any null-terminated
     string.  More specialized string types can be generated using this
     macro.  The programmer supplies a routine that takes a candidate char *
     and returns TRUE if it is acceptable for that type.  If it is
     unacceptable, it can return FALSE, or it can raise an exception that
     might contain more detailed information as to why the string was not
     acceptable.  Such information might typically be included in an error
     window that pops up when the user enters invalid data in a dialog box.

     By convention, use the TS suffix for the typespec name and the VT suffix
     for the typespec name as it will be known in ViewScript.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

EXAMPLE
     (vsValidFile returns TRUE if the filename is valid on the current
     platform)

     vlTypeMAKE_STRING (vsFileNameTS, "vsFileNameT", vsValidFile);

SEE ALSO
     vscmRegisterType

SYNOPSIS
     vlTypeMAKE_STRING(ts, ts_name, check_proc)
         vlTypeSpecT    ts;
         char          *ts_name;
         vlBoolT        (check_proc) ();
*/
#define vlTypeMAKE_STRING(ts, name, check) \
    static vlTypeStringSpecificsT vlCONCAT_TOKEN(ts,_strinfo) = {check, name};\
    vlTypeSpecT ts = {name, &vlStringTB,                                   \
                          (vlPointerT) &(vlCONCAT_TOKEN(ts,_strinfo)), 1}


/*\Docpage vlTypeMAKE_FILENAME -- Make filename datatype with a check routine.

DESCRIPTION
     The standard filename typespec, vlFilenameTS, accepts any valid
     filename.  More specialized filename types can be generated using this
     macro.  The programmer supplies a routine that takes a candidate char *
     and returns TRUE if it is acceptable for that type.  If it is
     unacceptable, it can return FALSE, or it can raise an exception that
     might contain more detailed information as to why the string was not
     acceptable.  Such information might typically be included in an error
     window that pops up when the user enters invalid data in a dialog box.

     By convention, use the TS suffix for the typespec name and the VT suffix
     for the typespec name as it will be known in ViewScript.

NOTE
     You must call the vscmRegisterType function if you want the new typespec
     to be visible to ViewScript users.

EXAMPLES
     // Note 1: vsFexists returns TRUE if the filename is readable

     // Note 2: vlFileRead is an already implemented filename type

     vlTypeMAKE_FILENAME (vlFileReadTS, "vlFileReadVT", vsFexists);

SEE ALSO
     vscmRegisterType, vlFileNameVT

SYNOPSIS
     vlTypeMAKE_FILENAME(ts, ts_name, check_proc)
         vlTypeSpecT    ts;
         char          *ts_name;
         vlBoolT        (check_proc) ();
*/
#define vlTypeMAKE_FILENAME(ts, name, check) \
    static vlTypeFilenameSpecificsT vlCONCAT_TOKEN(ts,_filinfo) = \
        {check, name, -1};\
    vlTypeSpecT ts = {name, &vlFileTB,                                    \
                          (vlPointerT) &(vlCONCAT_TOKEN(ts,_filinfo)), 1}

/*
 * Undocumented version of vlTypeMAKE_FILENAME that takes an alternate
 * message number, from vllib.vmt.
 */
#define vlTypeMAKE_FILENAME2(ts, name, check, msg) \
    static vlTypeFilenameSpecificsT vlCONCAT_TOKEN(ts,_filinfo) = \
        {check, name, msg};\
    vlTypeSpecT ts = {name, &vlFileTB,                                    \
                          (vlPointerT) &(vlCONCAT_TOKEN(ts,_filinfo)), 1}



/*\Docpage vlTypeOUTPUT -- Call a routine with printed rep. of typespec data.

DESCRIPTION
     Calls an action routine with a character string representation of a
     typespec, passing through an arbitrary object (such as a file pointer or
     a window Id).

EXAMPLE
     static void print_to_file(f, str)
         FILE       *fp;
         const char *str;
     {
         vrFprintf (fp, "%s\n", str);
     }

     vlTypeOUTPUT (&vlStringTS, vlTypePTR ("abc"), print_to_file, stdout);

SYNOPSIS
     void vlTypeOUTPUT(ts, data, outproc, ptr)
         vlTypeSpecPtrT  ts;
         vlTypeDataT     data;
         void (*outproc) (vlPointerT, const char *);
         vlPointerT      ptr;
*/
#define vlTypeOUTPUT(ts, data, outproc, ptr) \
    if (((ts) -> base) == NULL) ; else \
        ((*((ts) -> base -> output)) (data, (ts) -> specifics, outproc, ptr))

/*\Docpage vlTypeCONVERT -- Convert a string into data for a typespec.

DESCRIPTION
     Calls the typespec's typebase conversion routine with the supplied
     string.  If the conversion is successful, the result will be left in
     the global variable

           vlTypeDataT vlTypeReturnDataV;

     If unsuccessful, the type converter raises an exception, and control is
     transferred to the innermost handler.

CAUTIONS
     You must PROTECT your call to vlTypeCONVERT if your routine needs to
     clean up when an error is encountered.

     Not all typespecs have conversion routines.  For example, any typespec
     created using the macro vlTypeMAKE_PTR or vlTypeMAKE_PTR_TS cannot be
     created from a string.  In that case, this macro will have no effect,
     and the value left in vlTypeReturnDataV is unspecified.  It is the
     caller's responsibility to call vlTypeIS_CONVERTIBLE to ensure that a
     conversion will actually take place.

SEE ALSO
     vlTypeIS_CONVERTIBLE

SYNOPSIS
     void vlTypeCONVERT(ts, str)
         vlTypeSpecPtrT ts;
         const char    *str;
*/
#define vlTypeCONVERT(ts, str) \
    if ((ts) == &vlVoidTS) \
        vlTypeReturnDataV.long_data = 0; \
    else \
        (*((ts) -> base -> convert)) (str, (ts) -> specifics)


/*\Docpage vlTypeIS_CONVERTIBLE -- Determine if a typespec is convertible.

DESCRIPTION
     Not all typespecs have conversion routines.  For example, any typespec
     created using the macro vlTypeMAKE_PTR or vlTypeMAKE_PTR_TS cannot be
     created from a string.  In that case, the vlTypeCONVERT will have no
     effect, and the value left in vlTypeReturnDataV is unspecified.  It is
     the caller's responsibility to call vlTypeIS_CONVERTIBLE to ensure that a
     conversion will actually take place.
    
SEE ALSO
     vlTypeCONVERT

SYNOPSIS
     vlBoolT vlTypeIS_CONVERTIBLE(ts)
         vlTypeSpecPtrT ts;
*/
#define vlTypeIS_CONVERTIBLE(ts) \
    (((ts) == &vlVoidTS) || \
     (((ts) -> base != NULL) && \
      ((ts) -> base -> convert != vlNullTypedataProc)))
    

/*\Docpage vlTypeIS_POINTER -- Determine if a typespec's rep. is a pointer.

SYNOPSIS
     vlBoolT vlTypeIS_POINTER(ts)
         vlTypeSpecPtrT ts;
*/
#define vlTypeIS_POINTER(ts) \
    (((ts) -> base != NULL) && \
     ((ts) -> base -> primitive_type == vlTypePOINTER))


/*\Docpage vlTypeNAME -- Get the name of a typespec.

SYNOPSIS
     const char *vlTypeNAME(ts)
         vlTypeSpecPtrT ts;
*/
#define vlTypeNAME(ts) ((ts) -> name)


/*\Docpage vlTypeEQUAL -- Determine if two typedata objects are equal.

DESCRIPTION
    This macro makes it easier to compare two typedata objects, which are
    represented as unions, and are therefore difficult to compare.

SYNOPSIS
     vlBoolT vlTypeEQUAL(ts, d1, d2)
         vlTypeSpecPtrT ts;
         vlTypeDataT   *d1;
         vlTypeDataT   *d2;
*/
#define vlTypeEQUAL(ts, d1, d2)                                 \
    (((ts) -> base -> primitive_type == vlTypePOINTER) ?        \
     ((d1) -> ptr_data == (d2) -> ptr_data) :                   \
     ((d1) -> long_data == (d2) -> long_data))


/*\Docpage vlTypeVALUE -- Get the value from typespec data

DESCRIPTION
     Gets the value, in long or pointer form, from the typespec. It
     expects the typespec of the object (to determine whether it is in
     long or pointer form), the object itself, and the type to which
     it should be cast.

EXAMPLE 
     float f, g;
     vlTypeDataT obj;
     ...
     obj = vlTypeOBJECT (&vlFloatTS, &f);
     ...
     g = *vlTypeVALUE (&vlFloatTS, obj, float *);

     (Remember that floats have pointer representation!)

SYNOPSIS
     (type) vlTypeVALUE (ts, obj, type)
        vlTypeSpecPtrT ts;
        vlTypeDataT obj;
*/

#define vlTypeVALUE(ts, obj, type) \
   (vlTypeIS_POINTER(ts) ? ((type)((obj).ptr_data)) : \
                                  ((type)((obj).long_data)))

/*\Docpage vlTypeCOPY -- Copy typespec data.

DESCRIPTION
     Copies the data for a typespec, using whatever mechanism is appropriate
     for that typespec.  Leaves the new copy in "target".  Note that "copying"
     can take on different meanings for different typespecs.  All typespecs
     whose representation is "long" simply copy the old value to the target.
     Some pointer-based typespecs may allocate a new copy of the existing
     data, and some may simply copy the pointer.

SEE ALSO
     vlTypeFREE

SYNOPSIS
     void vlTypeCOPY(ts, target, source)
         vlTypeSpecPtrT     ts;
         vlTypeDataT        target;
         const vlTypeDataT  source;
*/
#define vlTypeCOPY(ts, target, source)  \
    if (vlTypeIS_POINTER (ts))          \
        target.ptr_data = ((*((ts) -> base -> copy)) (source.ptr_data,      \
                                                      (ts) -> specifics));  \
    else \
        target.long_data = source.long_data


/*\Docpage vlTypeFREE -- Free typespec data.

DESCRIPTION
     Frees the data for a typespec, using whatever mechanism is appropriate
     for that typespec.  Note that "freeing" can take on different meanings
     for different typespecs.  For all typespecs whose representation is
     "long", vlTypeFREE does nothing.  Some pointer-based typespecs may also
     do nothing, such as those made with vlTypeMAKE_PTR.

SEE ALSO
     vlTypeCOPY

SYNOPSIS
     void vlTypeFree(ts, data)
         vlTypeSpecPtrT ts;
         vlTypeDataT    data;
*/
/*
 * Note the else keyword at the end of this definition.  It's on purpose.
 */
#define vlTypeFREE(ts, data) \
    if (!vlTypeIS_POINTER (ts) || ((data).ptr_data == NULL)) ; else \
        ((*((ts) -> base -> free)) ((vlPointerT) (data).ptr_data, \
                                    (vlPointerT) (ts) -> specifics))

extern vlStrBufID vlTypeErrBuf;
extern vlBoolT vlTypeCheckVal vlARG2(vlTypeSpecPtrT, vlTypeDataT *);

/*\Docpage vlTypeCHECK_VAL -- Check the legality of a type value
 * 
 *
 * DESCRIPTION
 *    This macro checks the value of an object against a type and
 * aborts if the value is not legal for that type. It works with 
 * types whose base types are the vl-defined integer, float, enum, 
 * string, and filename base types. For all other types, the macro
 * will allow any value to pass. 
 *
 * NOTE
 *    If vlENV_DEBUG is turned off, this macro vanishes.
 *
 * SYNOPSIS
 *    vlTypeCHECK_VAL (description, t, o);
 *        char           *description;
 *        vlTypeSpecPtrT  t;
 *        vlTypeDataT     o;
 *
 * For maximum cogency, the descrption string should begin with a 
 * present participle, i.e., "evaluating the size"
 */

#define vlTypeCHECK_VAL(descr, t, o) \
    vlASSERT (vlTypeCheckVal ((t), &(o)), \
     vlSprintfStatic ("While %s, found %s, not a legal value of %s.", \
           (descr), vlStrBufString (vlTypeErrBuf), (t) -> name))

typedef struct {
    int     x, y;
} vlTypeMouseXyT;


typedef struct {
    long    imin, imax;
} vlTypeRangeIntT;


typedef struct {
    double  fmin, fmax;
} vlTypeRangeFloatT;


typedef struct {
    int     nchoices;
    const char    **choices;
} vlTypeEnuminfoT, vlTypeMaskinfoT;

#define vlTypeEnumNCHOICES(ts) \
    (((vlTypeEnuminfoT *) ((ts) -> specifics)) -> nchoices)
#define vlTypeEnumCHOICES(ts) \
    (((vlTypeEnuminfoT *) ((ts) -> specifics)) -> choices)

#define vlTypeMaskNCHOICES(ts) \
    (((vlTypeMaskinfoT *) ((ts) -> specifics)) -> nchoices)
#define vlTypeMaskCHOICES(ts) \
    (((vlTypeMaskinfoT *) ((ts) -> specifics)) -> choices)

typedef void   (*vlTypeConverterT) vlARGS ((vlTypeSpecPtrT, vlTypeSpecPtrT,
                                            vlTypeDataT));

#if 0
extern vlTypeBaseT vlRefptrTB;
typedef struct {
    char            *typename;
    vlSymTableID    names_to_ptrs;
    vlVoidProcT     free;
} vlTypeRefptrinfoT;
typedef struct refptr *vlTypeRefptrID;
#endif

extern union typedata vlTypeReturnDataV;
extern vlTypeSpecPtrT return_typespec;

extern vlTypeBaseT vlIntTB;
extern vlTypeBaseT vlInt64TB;
extern vlTypeBaseT vlStringTB;
extern vlTypeBaseT vlFileTB;
extern vlTypeBaseT vlEnumTB;
extern vlTypeBaseT vlMaskTB;
extern vlTypeBaseT vlFloatTB;
extern vlTypeBaseT vlPointerTB;
extern vlTypeBaseT vlPointer3TB;
extern vlTypeBaseT vlPointer4TB;
extern vlTypeBaseT vlPointerNoAllocTB;
extern vlTypeBaseT vlPointerNoAlloc1TB;

extern vlTypeSpecT vlPositiveIntTS;
extern vlTypeSpecT vlUnsignedIntTS;
extern vlTypeSpecT vlIntTS;
extern vlTypeSpecT vlInt64TS;
extern vlTypeSpecT vlCharTS;
extern vlTypeSpecT vlPositiveFloatTS;
extern vlTypeSpecT vlFloatTS;
extern vlTypeSpecT vlStringTS;
extern vlTypeSpecT vlStringConstTS;
extern vlTypeSpecT vlStringUpperTS;
extern vlTypeSpecT vlStringLowerTS;
extern vlTypeSpecT vlStringNotEmptyTS;
extern vlTypeSpecT vlFileNameTS;
extern vlTypeSpecT vlFileReadTS;
extern vlTypeSpecT vlFileWriteTS;
extern vlTypeSpecT vlFileReadWriteTS;
extern vlTypeSpecT vlDirTS;
extern vlTypeSpecT vlDirWriteTS;
/* extern vlTypeSpecT vsFileTS; */
extern vlTypeSpecT vlYesNoTS;
extern vlTypeSpecT vlTrueFalseTS;
extern vlTypeSpecT vlOnOffTS;
extern vlTypeSpecT vlVoidTS;
extern vlTypeSpecT vscmTS;
extern vlTypeSpecT vgRectTS;
extern vlTypeSpecT vlTypespecTS;
extern vlTypeSpecT vlRestTS;
extern vlTypeSpecT vlRest1TS;
extern vlTypeSpecT vlAnyTS;
extern vlTypeSpecT vlCallbackTS;
extern vlTypeSpecT vlPrefTS;
extern vlTypeSpecT vcCommandTS;
extern vlTypeSpecT vlStrArrayTS;
extern vlTypeSpecT vlErrActionTS;
extern vlTypeSpecT vlErrTS;
extern vlTypeSpecT vlErrCntxTS;
extern vlTypeSpecT vlErrSevTS;
extern vlTypeSpecT vlErrStreamTS;
extern vlTypeSpecT vsAttrTS;
extern vlTypeSpecT vlByteBlockTS;

extern void vlNullTypedataProc vlARGS((void));
extern vlPointerT vlTypeReturnArg vlARGS((vlPointerT, vlPointerT));
extern void vlTypeFreeDouble vlARGS((double *));
extern double *vlTypeAllocDouble vlARGS((double));
extern void vlTypeFreeInt64 vlARGS((vlInt64T *));
extern vlInt64T *vlTypeAllocInt64 vlARGS((vlInt64T));
extern char **vlTypeStrArrayCopy vlARGS((const vlStringPtrT *));
extern void vlTypeStrArrayFree vlARGS((char **));
extern vlTypeDataT vlTypePtrToTypedata vlARGS((vlPointerT));
extern vlTypeDataT vlTypeLongToTypedata vlARGS((long));
extern void vlTypeConvert vlARGS((vlTypeSpecPtrT, vlTypeSpecPtrT, vlTypeDataT));
extern void vlTypeAddConverter vlARGS((vlTypeConverterT, vlTypeSpecPtrT, vlTypeSpecPtrT));
extern vlTypeSpecPtrT vlTypeCreateEnum vlARGS((const char *,
                                             const char **, int));
extern vlTypeSpecPtrT vlTypeTSCopy vlARGS((vlTypeSpecPtrT));
extern void vlTypeTSFree vlARGS((vlTypeSpecPtrT));

#define vlTypeFreeStrArray vlTypeStrArrayFree

/*===========================================================================*/
/* Preferences */

typedef struct vlPrefDBStruct *vlPreferencesID;
#define vlPrefNAMESIZE 80
#define vlPrefPACKAGESIZE 80
#define vlPrefINIEXT "ini"

extern vlPreferencesID  vlPrefCreate vlARGS((const char *));
extern void             vlPrefDestroy vlARGS((vlPreferencesID));
extern void             vlPrefDestroyAll vlARGS((void));
extern void             vlPrefAdd vlARGS((vlPreferencesID, const char *, vlTypeSpecPtrT, const char *, vlTypeDataT));
extern vlBoolT             vlPrefReplace
             vlARGS((vlPreferencesID, const char *, vlTypeSpecPtrT, const char *, vlTypeDataT));
extern void             vlPrefAdd2 vlARGS((vlPreferencesID, const char *, vlTypeSpecPtrT, vlMsgFileID, int, vlTypeDataT));
extern vlBoolT             vlPrefReplace2 vlARGS((vlPreferencesID, const char *, vlTypeSpecPtrT, vlMsgFileID, int, vlTypeDataT));
extern vlTypeSpecPtrT   vlPrefTypespec vlARGS((vlPreferencesID, const char *));
extern vlTypeSpecPtrT   vlPrefTypespec vlARGS((vlPreferencesID, const char *));
extern vlTypeDataT      vlPrefVal vlARGS((vlPreferencesID, const char *));
extern vlTypeDataT      vlPrefDefault vlARGS((vlPreferencesID, const char *));
extern vlBoolT          vlPrefChanged vlARGS((vlPreferencesID, const char *));
extern void             vlPrefSetval vlARGS((vlPreferencesID, const char *, vlTypeDataT));
extern void             vlPrefRevert vlARGS((vlPreferencesID, const char *));
extern vlBoolT          vlPrefParse vlARGS((const char *, int *, char **));
extern vlBoolT          vlPrefUsage vlARGS((int *, char **));
extern void             vlPrefForEachOption vlARGS((vlPreferencesID, vlLoopProcT, vlPointerT));
extern void             vlPrefForEachUserOption vlARGS((vlPreferencesID, vlLoopProcT, vlPointerT));
extern vlBoolT          vlPrefWriteIniFile vlARGS((vlPreferencesID, const char *, vlBoolT));
extern vlBoolT          vlPrefReadIniFile vlARGS((vlPreferencesID, const char *, vlLoopProcT, vlPointerT));
extern void vlPrefCompatible vlARGS((vlPreferencesID, const char *, vlBoolT));
extern void vlPrefSetShorthand vlARG1(char *);
extern void vlPrefAlphabetize vlARG1 (vlPreferencesID);
extern void vlPrefRegisterSpecialTs vlARG3(vlTypeSpecPtrT, 
                                           vlVoidProcT, vlVoidProcT);

#endif
