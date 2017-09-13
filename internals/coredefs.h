/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#ifndef ZZ_GENA_COREDEFS_H_IG
#define ZZ_GENA_COREDEFS_H_IG

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

#define GENA_USE_VAL ZZ_GENA_VAL__  /* simple type, by value */
#define GENA_USE_REF ZZ_GENA_REF__  /* simple type, by reference (pointer) */
#define GENA_USE_BUF ZZ_GENA_BUF__  /* buffer type (array) */

#define ZZ_GENA_VAL__RETURN *
#define ZZ_GENA_VAL__REFERENCE &
#define ZZ_GENA_VAL__ENTRY
#define ZZ_GENA_REF__RETURN
#define ZZ_GENA_REF__REFERENCE
#define ZZ_GENA_REF__ENTRY
#define ZZ_GENA_BUF__RETURN
#define ZZ_GENA_BUF__REFERENCE
#define ZZ_GENA_BUF__ENTRY *

/*
  Support for type info parameters in templates.
    simple type: typename
    buffer type: (typename, count)
*/

#define ZGENA_TYPEINFO_NAME( tpTypeInfo, tpUseBy ) \
  tpUseBy ## TYPEINFO_NAME( tpTypeInfo )

  #define ZZ_GENA_VAL__TYPEINFO_NAME( tpTypeInfo ) \
    tpTypeInfo
  #define ZZ_GENA_REF__TYPEINFO_NAME( tpTypeInfo ) \
    tpTypeInfo
  #define ZZ_GENA_BUF__TYPEINFO_NAME( tpTypeInfo ) \
    ZGENA_PAIR_1(tpTypeInfo)

#define ZGENA_TYPEINFO_SIZE( tpTypeInfo, tpUseBy ) \
  tpUseBy ## TYPEINFO_SIZE( tpTypeInfo )

  #define ZZ_GENA_VAL__TYPEINFO_SIZE( tpTypeInfo ) \
    ( sizeof(tpTypeInfo) )
  #define ZZ_GENA_REF__TYPEINFO_SIZE( tpTypeInfo ) \
    ( sizeof(tpTypeInfo) )
  #define ZZ_GENA_BUF__TYPEINFO_SIZE( tpTypeInfo ) \
    ( sizeof(ZGENA_PAIR_1(tpTypeInfo)) * (ZGENA_PAIR_2(tpTypeInfo)) )

#define ZGENA_TYPEINFO_USERTYPE( tpTypeInfo, tpUseBy ) \
  tpUseBy ## TYPEINFO_USERTYPE( tpTypeInfo, tpUseBy )

  #define ZZ_GENA_VAL__TYPEINFO_USERTYPE( tpTypeInfo, tpUseBy ) \
    ZGENA_TYPEINFO_NAME(tpTypeInfo, tpUseBy)
  #define ZZ_GENA_REF__TYPEINFO_USERTYPE( tpTypeInfo, tpUseBy ) \
    ZGENA_TYPEINFO_NAME(tpTypeInfo, tpUseBy) *
  #define ZZ_GENA_BUF__TYPEINFO_USERTYPE( tpTypeInfo, tpUseBy ) \
    ZGENA_TYPEINFO_NAME(tpTypeInfo, tpUseBy) *

#define ZGENA_TYPEINFO_BUFDEF( tpTypeInfo, tpUseBy, tpName ) \
  tpUseBy ## TYPEINFO_BUFDEF( tpTypeInfo, tpName )

  #define ZZ_GENA_VAL__TYPEINFO_BUFDEF( tpTypeInfo, tpName ) \
    typedef tpTypeInfo* tpName
  #define ZZ_GENA_REF__TYPEINFO_BUFDEF( tpTypeInfo, tpName ) \
    typedef tpTypeInfo* tpName
  #define ZZ_GENA_BUF__TYPEINFO_BUFDEF( tpTypeInfo, tpName ) \
    typedef ZGENA_PAIR_1(tpTypeInfo) (*tpName) [ ZGENA_PAIR_2(tpTypeInfo) ]

/******************************************************************************/

#define GENA_ASSIGN_NAIVE ZZ_GENA_ASSIGN_NAIVE
#define GENA_ASSIGN_MEMCPY ZZ_GENA_ASSIGN_MEMCPY
#define GENA_ASSIGN_STRCPY ZZ_GENA_ASSIGN_STRCPY

#define ZZ_GENA_ASSIGN_NAIVE( ptr_destination, ptr_source, data_size ) \
  ( *(ptr_destination) = *(ptr_source) )

#define ZZ_GENA_ASSIGN_MEMCPY( ptr_destination, ptr_source, data_size ) \
  ( memcpy( ptr_destination, ptr_source, data_size ) )

#define ZZ_GENA_ASSIGN_STRCPY( ptr_destination, ptr_source, data_size ) \
  ( strncpy( (char*)ptr_destination, (const char*)ptr_source, data_size ) )

/******************************************************************************/

#define GENA_COMPARE_NAIVE ZZ_GENA_COMPARE_NAIVE
#define GENA_COMPARE_MEMCMP ZZ_GENA_COMPARE_MEMCMP
#define GENA_COMPARE_STRCMP ZZ_GENA_COMPARE_STRCMP

#define ZZ_GENA_COMPARE_NAIVE( ptr_entry_data, ptr_user_data, data_size ) \
  ( (*(ptr_entry_data) < *(ptr_user_data)) ? (-1) \
  : (*(ptr_entry_data) > *(ptr_user_data)) ? (1) \
  : (0) )

#define ZZ_GENA_COMPARE_MEMCMP( ptr_entry_data, ptr_user_data, data_size ) \
  ( memcmp( ptr_entry_data, ptr_user_data, data_size ) )

/* NOTE: strncmp() is not needed here over strcmp() because ptr_entry_data is
guaranteed to be a valid zero-terminated C string. */
#define ZZ_GENA_COMPARE_STRCMP( ptr_entry_data, ptr_user_data, data_size ) \
  ( strcmp( (const char*)ptr_entry_data, (const char*)ptr_user_data ) )

/******************************************************************************/

#define GENA_APPLY_TYPESET(macro, typeset) macro typeset

/******************************************************************************/

#define ZGENA_VOIDP_ADD(x, a) ( (void*)( (char*)(x) + (a) ) )
#define ZGENA_VOIDP_SUB(x, a) ( (void*)( (char*)(x) - (a) ) )

/******************************************************************************/

#define ZZ_ZGENA_PAIR_1(item1, item2) item1
#define ZZ_ZGENA_PAIR_2(item1, item2) item2

#define ZGENA_PAIR_1(pair) ZZ_ZGENA_PAIR_1 pair
#define ZGENA_PAIR_2(pair) ZZ_ZGENA_PAIR_2 pair

/******************************************************************************/

#define ZZ_ZGENA_MACRO_CONCAT(x, y) x##y
#define ZGENA_MACRO_CONCAT(x, y) ZZ_ZGENA_MACRO_CONCAT(x, y)

/******************************************************************************/

#define ZGENA_BLOCK_REQUIRE_SEMICOLON(block) \
  do {block} while(0)

#define ZGENA_REQUIRE_SEMICOLON_OUTDOOR \
  extern void \
  ZGENA_MACRO_CONCAT(ZZ_GENA_THIS_REQUIRES_A_SEMICOLON, __LINE__) \
  (void)

#endif /* ZZ_GENA_COREDEFS_H_IG */
