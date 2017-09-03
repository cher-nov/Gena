/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#ifndef __GENA_COREDEFS_H__
#define __GENA_COREDEFS_H__

/******************************************************************************/

#include <stddef.h>

#if __STDC_VERSION__ < 199901L
  typedef int gena_bool;
  #define GENA_TRUE (1)
  #define GENA_FALSE (0)
#else
  #include <stdbool.h>
  typedef bool gena_bool;
  #define GENA_TRUE (true)
  #define GENA_FALSE (false)
#endif

#if __STDC_VERSION__ < 199901L
  #define inline
#endif

/******************************************************************************/

typedef enum {
  GENA_ERR_NO,
  GENA_ERR_MEMORY
} gena_error_e;

/******************************************************************************/

#define GENA_USE_VAL __IGENA_VAL__    /* simple type, by value */
#define GENA_USE_REF __IGENA_REF__    /* simple type, by reference (pointer) */
#define GENA_USE_BUF __IGENA_BUF__    /* buffer type (array) */

#define __IGENA_VAL__RETURN *
#define __IGENA_VAL__REFERENCE &
#define __IGENA_VAL__ENTRY
#define __IGENA_REF__RETURN
#define __IGENA_REF__REFERENCE
#define __IGENA_REF__ENTRY
#define __IGENA_BUF__RETURN
#define __IGENA_BUF__REFERENCE
#define __IGENA_BUF__ENTRY *

/*
  Support for type info parameters in templates.
    simple type: typename
    buffer type: (typename, count)
*/

#define __IGENA_TYPEINFO_NAME( tpTypeInfo, tpUseBy ) \
  tpUseBy ## TYPEINFO_NAME( tpTypeInfo )

  #define __IGENA_VAL__TYPEINFO_NAME( tpTypeInfo ) \
    tpTypeInfo
  #define __IGENA_REF__TYPEINFO_NAME( tpTypeInfo ) \
    tpTypeInfo
  #define __IGENA_BUF__TYPEINFO_NAME( tpTypeInfo ) \
    __IGENA_PAIR_1(tpTypeInfo)

#define __IGENA_TYPEINFO_SIZE( tpTypeInfo, tpUseBy ) \
  tpUseBy ## TYPEINFO_SIZE( tpTypeInfo )

  #define __IGENA_VAL__TYPEINFO_SIZE( tpTypeInfo ) \
    ( sizeof(tpTypeInfo) )
  #define __IGENA_REF__TYPEINFO_SIZE( tpTypeInfo ) \
    ( sizeof(tpTypeInfo) )
  #define __IGENA_BUF__TYPEINFO_SIZE( tpTypeInfo ) \
    ( sizeof(__IGENA_PAIR_1(tpTypeInfo)) * (__IGENA_PAIR_2(tpTypeInfo)) )

#define __IGENA_TYPEINFO_USERTYPE( tpTypeInfo, tpUseBy ) \
  tpUseBy ## TYPEINFO_USERTYPE( tpTypeInfo, tpUseBy )

  #define __IGENA_VAL__TYPEINFO_USERTYPE( tpTypeInfo, tpUseBy ) \
    __IGENA_TYPEINFO_NAME(tpTypeInfo, tpUseBy)
  #define __IGENA_REF__TYPEINFO_USERTYPE( tpTypeInfo, tpUseBy ) \
    __IGENA_TYPEINFO_NAME(tpTypeInfo, tpUseBy) *
  #define __IGENA_BUF__TYPEINFO_USERTYPE( tpTypeInfo, tpUseBy ) \
    __IGENA_TYPEINFO_NAME(tpTypeInfo, tpUseBy) *

#define __IGENA_TYPEINFO_BUFDEF( tpTypeInfo, tpUseBy, tpName ) \
  tpUseBy ## TYPEINFO_BUFDEF( tpTypeInfo, tpName )

  #define __IGENA_VAL__TYPEINFO_BUFDEF( tpTypeInfo, tpName ) \
    typedef tpTypeInfo* tpName
  #define __IGENA_REF__TYPEINFO_BUFDEF( tpTypeInfo, tpName ) \
    typedef tpTypeInfo* tpName
  #define __IGENA_BUF__TYPEINFO_BUFDEF( tpTypeInfo, tpName ) \
    typedef __IGENA_PAIR_1(tpTypeInfo) (*tpName) [ __IGENA_PAIR_2(tpTypeInfo) ]

/******************************************************************************/

#define GENA_ASSIGN_NAIVE __IGENA_ASSIGN_NAIVE
#define GENA_ASSIGN_MEMCPY __IGENA_ASSIGN_MEMCPY
#define GENA_ASSIGN_STRCPY __IGENA_ASSIGN_STRCPY

#define __IGENA_ASSIGN_NAIVE( ptr_destination, ptr_source, data_size ) \
  ( *(ptr_destination) = *(ptr_source) )

#define __IGENA_ASSIGN_MEMCPY( ptr_destination, ptr_source, data_size ) \
  ( memcpy( ptr_destination, ptr_source, data_size ) )

#define __IGENA_ASSIGN_STRCPY( ptr_destination, ptr_source, data_size ) \
  ( strncpy( (char*)ptr_destination, (const char*)ptr_source, data_size ) )

/******************************************************************************/

#define GENA_COMPARE_NAIVE __IGENA_COMPARE_NAIVE
#define GENA_COMPARE_MEMCMP __IGENA_COMPARE_MEMCMP
#define GENA_COMPARE_STRCMP __IGENA_COMPARE_STRCMP

#define __IGENA_COMPARE_NAIVE( ptr_entry_data, ptr_user_data, data_size ) \
  ( (*(ptr_entry_data) < *(ptr_user_data)) ? (-1) \
  : (*(ptr_entry_data) > *(ptr_user_data)) ? (1) \
  : (0) )

#define __IGENA_COMPARE_MEMCMP( ptr_entry_data, ptr_user_data, data_size ) \
  ( memcmp( ptr_entry_data, ptr_user_data, data_size ) )

/* NOTE: strncmp() is not needed here over strcmp() because ptr_entry_data is
guaranteed to be a valid zero-terminated C string. */
#define __IGENA_COMPARE_STRCMP( ptr_entry_data, ptr_user_data, data_size ) \
  ( strcmp( (const char*)ptr_entry_data, (const char*)ptr_user_data ) )

/******************************************************************************/

#define GENA_APPLY_TYPESET(macro, typeset) macro typeset

/******************************************************************************/

#define __IGENA_VOIDP_ADD(x, a) ( (void*)( (char*)(x) + (a) ) )
#define __IGENA_VOIDP_SUB(x, a) ( (void*)( (char*)(x) - (a) ) )

/******************************************************************************/

#define _impl_IGENA_PAIR_1(pair1, pair2) pair1
#define _impl_IGENA_PAIR_2(pair1, pair2) pair2

#define __IGENA_PAIR_1(pair) _impl_IGENA_PAIR_1 pair
#define __IGENA_PAIR_2(pair) _impl_IGENA_PAIR_2 pair

/******************************************************************************/

#define _impl_IGENA_MACRO_CONCAT(x, y) x##y
#define __IGENA_MACRO_CONCAT(x, y) _impl_IGENA_MACRO_CONCAT(x, y)

/******************************************************************************/

#define __IGENA_BLOCK_REQUIRE_SEMICOLON(block) \
  do {block} while(0)

#define __IGENA_REQUIRE_SEMICOLON_OUTDOOR \
  extern void \
  __IGENA_MACRO_CONCAT(__THIS_REQUIRES_A_SEMICOLON_, __LINE__) \
  (void)

#endif /*__GENA_COREDEFS_H__*/
