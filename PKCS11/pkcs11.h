/*******************************************************************************
*                       Copyright (c) 1994-1997 RSA Laboratories
*                       Copyright (c) 1997 Gemplus Development
*
* Name        : PKCS11.H
*
* Description : Gemplus Public Key Cryptography Standards (Cryptoki) v2.01
*
* Author      : Choukri LAHMAR, Laurent CASSIER
*
* Compiler    : Microsoft Visual C 1.5x/2.0/4.0
*                ANSI C UNIX.
*
*  Host        : IBM PC and compatible machines under Windows 3.x.
*                UNIX machine.
*
* Release     : 1.00.002
*
* Last Modif  : 29/03/99: V1.00.002 - Modification of registry emplacement
*				20/12/99: V1.00.001 - Adaption of PKCS#11 v2.01 PKCS11.H file
*                                     Based on header files provides by RSA.
*
********************************************************************************
*
* Warning       :
*
* Remarks       :
*
*******************************************************************************/

#ifndef _PKCS11_H_
#define _PKCS11_H_ 1

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------
                         GEMPLUS Specific definitions
------------------------------------------------------------------------------*/
#define GEMPLUS_REGISTER_PATH  "SOFTWARE\\Gemplus\\Cryptography\\PKCS11\\4.0"
#define GEMPLUS_TOKEN_REGISTER_PATH  "SOFTWARE\\Gemplus\\Cryptography\\PKCS11\\Token"



/* these data types are platform/implementation-dependent.                    */

#if defined(_WINDOWS) 

#if defined(WIN32) /* win32                                                  */



/* New for version 2.01														  */
#define CK_DEFINE_FUNCTION(returnType, name)  returnType __declspec(dllexport) name

/* New for version 2.01														  */
#define CK_DECLARE_FUNCTION(returnType, name)  returnType __declspec(dllexport) name

/* New for version 2.01														  */
#define CK_DECLARE_FUNCTION_POINTER(returnType, name) returnType __declspec(dllimport) (* name)

/* New for version 2.01														  */
#define CK_CALLBACK_FUNCTION(returnType, name)  returnType (* name)



/* Modification to be compatible with PKCS version 2.01 */

//#define CK_ENTRY          __declspec( dllexport )
#define CK_ENTRY      





#define CK_PTR            *

#ifndef NULL_PTR
#define NULL_PTR          0

#endif





#pragma pack(push, cryptoki, 1)



#else /* win16                                                                */



/* New for version 2.01														  */
#define CK_DEFINE_FUNCTION(returnType, name)  returnType __export _far _pascal name

/* New for version 2.01														  */

#define CK_DECLARE_FUNCTION(returnType, name)   returnType __export _far _pascal name

/* New for version 2.01														  */

#define CK_DECLARE_FUNCTION_POINTER(returnType, name)  returnType __export _far _pascal (* name)

/* New for version 2.01														  */

#define CK_CALLBACK_FUNCTION(returnType, name)  returnType _far _pascal (* name)



/* Modification to be compatible with PKCS version 2.01 */

//#define CK_ENTRY          _export _far _pascal

#define CK_ENTRY      





#define CK_PTR            far *

#ifndef NULL_PTR

#define NULL_PTR          0

#endif



#pragma pack(push, cryptoki, 1)

#endif



#else /* not windows                                                          */

/* New for version 2.01														  */

#define CK_DEFINE_FUNCTION(returnType, name)   returnType name

/* New for version 2.01														  */

#define CK_DECLARE_FUNCTION(returnType, name)   returnType name

/* New for version 2.01														  */

#define CK_DECLARE_FUNCTION_POINTER(returnType, name) returnType (* name)

/* New for version 2.01														  */

#define CK_CALLBACK_FUNCTION(returnType, name) returnType (* name)

#define CK_PTR *
#define CK_ENTRY
#ifndef NULL_PTR
#define NULL_PTR          0
#endif

typedef unsigned long int CK_ULONG;
typedef unsigned char     CK_BYTE;

typedef CK_BYTE     CK_PTR   CK_BYTE_PTR;

#endif

/*------------------ GEMPLUS Specific definitions : END ----------------------

  ----------------------------------------------------------------------------*/



/* All the various Cryptoki types and #define'd values are in the
 * file pkcs11t.h. */
#include "pkcs11t.h"

#define __PASTE(x,y)      x##y


/* ==============================================================
 * Define the "extern" form of all the entry points.
 * ==============================================================
 */

#define CK_NEED_ARG_LIST  1
#define CK_PKCS11_FUNCTION_INFO(name) \
  extern CK_DECLARE_FUNCTION(CK_RV, name)	

/* pkcs11f.h has all the information about the Cryptoki
 * function prototypes. */
#include "pkcs11f.h"

#undef CK_NEED_ARG_LIST
#undef CK_PKCS11_FUNCTION_INFO


/* ==============================================================
 * Define the typedef form of all the entry points.  That is, for
 * each Cryptoki function C_XXX, define a type CK_C_XXX which is
 * a pointer to that kind of function.
 * ==============================================================
 */

#define CK_NEED_ARG_LIST  1
#define CK_PKCS11_FUNCTION_INFO(name) \
  typedef CK_DECLARE_FUNCTION_POINTER(CK_RV, __PASTE(CK_,name))

/* pkcs11f.h has all the information about the Cryptoki
 * function prototypes. */
#include "pkcs11f.h"

#undef CK_NEED_ARG_LIST
#undef CK_PKCS11_FUNCTION_INFO


/* ==============================================================
 * Define structed vector of entry points.  A CK_FUNCTION_LIST
 * contains a CK_VERSION indicating a library's Cryptoki version
 * and then a whole slew of function pointers to the routines in
 * the library.  This type was declared, but not defined, in
 * pkcs11t.h.
 * ==============================================================
 */

#define CK_PKCS11_FUNCTION_INFO(name) \
  __PASTE(CK_,name) name;
  
struct CK_FUNCTION_LIST {

  CK_VERSION    version;  /* Cryptoki version */

/* Pile all the function pointers into the CK_FUNCTION_LIST. */
/* pkcs11f.h has all the information about the Cryptoki
 * function prototypes. */
#include "pkcs11f.h"

};

#undef CK_PKCS11_FUNCTION_INFO


#undef __PASTE

#ifdef __cplusplus
}
#endif

#endif
