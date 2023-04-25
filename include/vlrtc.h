/*
 * $Id: vlrtc.h,v 1.17.3.1 1995/10/17 20:43:16 cway Stab $
 *
 * Run-time type checking!
 *
 * Copyright (c) 1991 by Viewlogic Systems, Inc.
 */


#ifndef vlRtc_H
#define vlRtc_H

#ifndef vlWLIB_H
#include "vllib.h"
#endif

/* Type checking macros */

/*\Docpage vlRtcDECLARE_TYPE -- Declare a static debugging type string

DESCRIPTION
     The run-time typechecking system requires a unique string to be
     shared by all code that operates on a given type.  This macro
     simply declares a static string, that could ultimately be
     compiled out by switching vlENV_DEBUG off.  At the moment, however,
     the strings are left in even if vlENV_DEBUG is off, because
     the type strings are also typically used in annotated calls
     to vlMemMalloc, which remain annotated for the moment regardless
     of whether debugging is on.

EXAMPLE
     vlRtcDECLARE_TYPE (MyStructType, "My Structure");
*/
#define vlRtcDECLARE_TYPE(tvar, tname) static const char *tvar = tname

/*\Docpage vlRtcDECLARE_TYPE_GLOBAL -- Declare a global debugging type string

DESCRIPTION
     Performs the same run-time type checking functions that are 
     used with vlRtcDECLARE_TYPE, but instead of a static string,
     vlRtcDECLARE_TYPE_GLOBAL allocates a global string and
     therefore is used only in implementations requiring global
     visibility for the type.  

NOTE
     There must be a corresponding extern declaration in a header file
     which must be included in all the modules requiring access
     to this global type.  Only the module that declares the
     type uses vlRtcDECLARE_TYPE_GLOBAL.

EXAMPLE
     (in header myshared.h)
     extern char * MyStructGlobalType;

     (in module mytype.c)
     #include "myshared.h"
     vlRtcDECLARE_TYPE_GLOBAL (MyStructGlobalType, "My Structure");
*/
#define vlRtcDECLARE_TYPE_GLOBAL(tvar, tname) const char *tvar = tname


#if vlENV_DEBUG

/*\Docpage vlRtcTYPE_DECLARATION -- Declare the type field of a structure

DESCRIPTION
     This macro is used as the beginning of a structure definition to
     optionally declare a character string debugging type field.  When
     vlENV_DEBUG is off, this macro has no effect.

EXAMPLE
     struct my_structure {
          vlRtcTYPE_DECLARATION
          int other_stuff;
          ...
     }

CAUTION
     Do not put a semi-colon after vlRtcTYPE_DECLARATION.  This is
     unfortunate, because it fools the Emacs c-mode indenter, but
     is unavoidable, since an extra ; in a structure definition
     violates C's grammar, and vlRtcTYPE_DECLARATION wants to compile
     to nothing when vlENV_DEBUG is off.
*/
#define vlRtcTYPE_DECLARATION const char *vlRtcDebugType;

/*\Docpage vlRtcSET_TYPE -- Set the type field of a typed structure

DESCRIPTION
     Used after allocating memory intended to be used as a specific
     kind of structure.  Typically, this macro is not called directly,
     because its called from inside vlRtcCREATE, which allocates
     a structure and sets its type.  This macro has no effect
     if vlENV_DEBUG is off.

EXAMPLE
     vlRtcDECLARE_TYPE (MyType, "My Type");

     {
         MyStruct *obj = (MyStruct *) vlMemMalloc (sizeof (MyStruct), MyType);
         vlRtcSET_TYPE (obj, MyType);
         obj -> foo = ...;
         ...
     }
*/
#define vlRtcSET_TYPE(p, type) (p) -> vlRtcDebugType = type

/*\Docpage vlRtcSET_FREE -- Set the type field to "Free"

DESCRIPTION
     Before freeing an object with vlMemFree, the type field should be
     cleared so that anyone who erroneously still has a pointer to it
     will trigger the type checking routines if he attempts to operate
     on it.  Normally, this routine is not called directly, because it
     is called from vlRtcDESTROY.  This macro has no effect if
     vlENV_DEBUG is off.

EXAMPLE
     vlRtcSET_FREE (obj);
     vlMemFree ((vlPointerT) obj);
*/
#define vlRtcSET_FREE(p) vlRtcSET_TYPE (p, "Free")

/*\Docpage vlRtcTYPE_CHECK -- check that a structure is of expected type

DESCRIPTION
     Verifies that the structure's first element is the same character
     string as the expected type (== is used, not strcmp).  If not, it
     prints as much useful information as it can and aborts, by calling
     vlRtcTypeFailure, which calls vlAbort.  This macro has no effect
     if vlENV_DEBUG is off.

SYNOPSIS
     vlRtcTYPE_CHECK (routine_name, expected_type, s)
         const char *routine_name, *expected_type;
         StructureWithTypeDeclaration *s;

CAUTIONS
     The structure type used should have vlRtcTYPE_DECLARATION as its
     first element.  If it doesn't have the declaration at all, the
     code will not compile.  If the vlRtcTYPE_DECLARATION is present
     but is not the first element of the structure, the type checking
     will work, but on failure, not as much useful information will
     be printed before core dumping, and unexpected beviour will occur
     with unsafe operating systems such as DOS.  This is because
     this macro calls vlRtcTypeFailure on error, passing in the structure
     pointer, and that routine assumes that the type field is the first
     element of the structure.  In general, it is not recommended practice,
     but if the first element of a structure is being used as a "next"
     pointer, it is better to have some typechecking than none at all.
*/

#define vlRtcTYPE_CHECK(routine, expected_type, s)\
    do {\
       if (((s) == NULL) || ((s) -> vlRtcDebugType != (expected_type)))\
       {\
          vlErrYell ("Error detected by RTC:\n");\
          vlASSERT (FALSE, vlRtcMsg (routine, expected_type, (vlPointerT)s));\
       }}\
    while (0)
     

/*#define vlRtcTYPE_CHECK(routine, expected_type, s) \
    vlASSERT (((s) != NULL) && ((s) -> vlRtcDebugType == expected_type), \
              vlRtcMsg (routine, expected_type, (vlPointerT) s))*/

#else

#define vlRtcTYPE_DECLARATION
#define vlRtcSET_TYPE(p, type)
#define vlRtcSET_FREE(p)
#define vlRtcTYPE_CHECK(routine, expected_type, structure)

#endif

/*\Docpage vlRtcCREATE -- Allocate a structure and set its type field

DESCRIPTION
     Declares a structure pointer variable "var", of type "vartype",
     assigns it to an allocated structure of size sizeof (*var),
     and sets its type field as specified.

EXAMPLE
     vlRtcDECLARE_TYPE (MyType, "My Type");

     {
         vlRtcCREATE (MyStruct *, obj, MyType);
         obj -> foo = ...;
         ...
     }

CAUTIONS
     This macro can only be called in the declarations section (i.e.
     the beginning) of a braced block, because it declares a variable.
*/
#define vlRtcCREATE(vartype, var, type) \
    vartype var = (vartype) vlMemFlAlloc (sizeof (*var), type); \
    vlRtcSET_TYPE(var, type)

/*
 * Note that vlRtcSET_TYPE here is not redundant even though vlMemFlAlloc
 * sets the field too.  This is because vlMemFlAlloc may have been compiled
 * with vlENV_DEBUG 0, even if this module is being compiled with
 * vlENV_DEBUG 1.
 *                                      -Josh, 12/31/92
 */

/*\Docpage vlRtcALLOC -- Allocate a type-checked structure
 *
 * DESCRIPTION
 *      Allocate a type-checked structure.
 *
 * NOTE
 *      You must set the type field using vlRtcSET_TYPE(man).
 *
 * EXAMPLE
 *      MyStruct *p;
 *
 *      vlRtcDECLARE_TYPE (MyType, "My Type");
 *      
 *      p = (MyStruct *) vlRtcALLOC (sizeof(*p));
 *      vlRtcSET_TYPE (p, MyType);
 *      ...
 *      vlRtcDESTROY (p);
 */
#define vlRtcALLOC(size) vlMemFlAlloc (size, NULL)
/*
 * Note that this macro serves to abstract the knowledge of
 * the vlMemFl implementation out of this call.  One can use this
 * without introducing a new scope; with vlRtcCREATE you have to
 * introduce a new scope, which is ofttimes inconvenient.
 */


/*\Docpage vlRtcDESTROY -- Clear a structures type field and free it

DESCRIPTION
     This macro sets the type field to "Free" before actually
     deallocating the memory.  Anyone who erroneously uses a pointer
     to this structure will be caught by the vlRtcTYPE_CHECK() macro.

EXAMPLE
     vlRtcDESTROY (obj);
*/
#define vlRtcDESTROY(obj) \
    do { \
        vlRtcSET_FREE (obj); \
        vlMemFlFree ((vlPointerT) obj, sizeof (*obj)); \
    } while (0)

/* Upward compatibility macros */
#define vlCREATE(objtype, obj, objstruct, type) \
    vlRtcCREATE (objtype, obj, type)

#define vlDESTROY(obj) vlRtcDESTROY (obj)

extern const char *vlRtcMsg vlARGS((const char *, const char *, vlPointerT));

#endif /* vlRtc_H */
