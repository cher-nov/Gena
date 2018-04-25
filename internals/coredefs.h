/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#ifndef ZZ_GENA_COREDEFS_H_IG
#define ZZ_GENA_COREDEFS_H_IG

/******************************************************************************/

/* Default includes, used throughout the whole library. */

#include <stddef.h>
#include <limits.h>
#include <assert.h>

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
  #define GENA_INLINE
#else
  #define GENA_INLINE inline
#endif

/******************************************************************************/

#define GENA_USE_VALUE ZZ_GENA_VAL__    /* simple type, by value */
#define GENA_USE_POINTER ZZ_GENA_PTR__  /* simple type, by pointer */
#define GENA_USE_BUFFER ZZ_GENA_BUF__   /* buffer type (array or string) */
#define GENA_USE_ARRAY ZZ_GENA_REF__    /* reference-access type (array) */

/* Operators. */

#define ZZ_GENA_VAL__VALUE *
#define ZZ_GENA_VAL__ADDRESS &
#define ZZ_GENA_VAL__DATA

#define ZZ_GENA_PTR__VALUE
#define ZZ_GENA_PTR__ADDRESS
#define ZZ_GENA_PTR__DATA

#define ZZ_GENA_BUF__VALUE *
#define ZZ_GENA_BUF__ADDRESS
#define ZZ_GENA_BUF__DATA *

#define ZZ_GENA_REF__VALUE *
#define ZZ_GENA_REF__ADDRESS
#define ZZ_GENA_REF__DATA *

/*
  Support for type info parameters in templates.
    simple type: typename
    buffer type: (typename, count)
*/

#define ZGENA_ENTRY_TYPE( tpTypeInfo, tpUseBy ) \
  tpUseBy ## ENTRY_TYPE( tpTypeInfo )

  #define ZZ_GENA_VAL__ENTRY_TYPE( tpTypeInfo ) \
    tpTypeInfo
  #define ZZ_GENA_PTR__ENTRY_TYPE( tpTypeInfo ) \
    tpTypeInfo
  #define ZZ_GENA_BUF__ENTRY_TYPE( tpTypeInfo ) \
    ZGENA_PAIR_1(tpTypeInfo)
  #define ZZ_GENA_REF__ENTRY_TYPE( tpTypeInfo ) \
    ZGENA_PAIR_2(tpTypeInfo)

#define ZGENA_ENTRY_SIZE( tpTypeInfo, tpUseBy ) \
  tpUseBy ## ENTRY_SIZE( tpTypeInfo )

  #define ZZ_GENA_VAL__ENTRY_SIZE( tpTypeInfo ) \
    ( sizeof(tpTypeInfo) )
  #define ZZ_GENA_PTR__ENTRY_SIZE( tpTypeInfo ) \
    ( sizeof(tpTypeInfo) )
  #define ZZ_GENA_BUF__ENTRY_SIZE( tpTypeInfo ) \
    ( sizeof(ZGENA_PAIR_1(tpTypeInfo)) * (ZGENA_PAIR_2(tpTypeInfo)) )
  #define ZZ_GENA_REF__ENTRY_SIZE( tpTypeInfo ) \
    ( sizeof(ZGENA_PAIR_1(tpTypeInfo)) )

#define ZGENA_ENTRY_VALUE( tpTypeInfo, tpUseBy ) \
  ZGENA_ENTRY_TYPE(tpTypeInfo, tpUseBy) tpUseBy##ENTRY_VALUE

  #define ZZ_GENA_VAL__ENTRY_VALUE
  #define ZZ_GENA_PTR__ENTRY_VALUE *
  #define ZZ_GENA_BUF__ENTRY_VALUE *
  #define ZZ_GENA_REF__ENTRY_VALUE *

#define ZGENA_ENTRY_DATA( tpTypeInfo, tpUseBy, tpPointer ) \
  ( ( tpUseBy ## ENTRY_DATA(tpTypeInfo) ) (tpPointer) )

  #define ZZ_GENA_VAL__ENTRY_DATA( tpTypeInfo ) \
    tpTypeInfo*
  #define ZZ_GENA_PTR__ENTRY_DATA( tpTypeInfo ) \
    tpTypeInfo*
  #define ZZ_GENA_BUF__ENTRY_DATA( tpTypeInfo ) \
    ZGENA_PAIR_1(tpTypeInfo) (*) [ ZGENA_PAIR_2(tpTypeInfo) ]
  #define ZZ_GENA_REF__ENTRY_DATA( tpTypeInfo ) \
    ZGENA_PAIR_1(tpTypeInfo) *

#define ZGENA_ENTRY_OBJECT( tpTypeInfo, tpUseBy, tpName ) \
  tpUseBy ## ENTRY_OBJECT( tpTypeInfo, tpName )

  #define ZZ_GENA_VAL__ENTRY_OBJECT( tpTypeInfo, tpName ) \
    tpTypeInfo tpName
  #define ZZ_GENA_PTR__ENTRY_OBJECT( tpTypeInfo, tpName ) \
    tpTypeInfo tpName
  #define ZZ_GENA_BUF__ENTRY_OBJECT( tpTypeInfo, tpName ) \
    ZGENA_PAIR_1(tpTypeInfo) (tpName) [ ZGENA_PAIR_2(tpTypeInfo) ]
  #define ZZ_GENA_REF__ENTRY_OBJECT( tpTypeInfo, tpName ) \
    ZGENA_PAIR_1(tpTypeInfo) tpName

/******************************************************************************/

#define GENA_ASSIGN_NAIVE ZZ_GENA_ASSIGN_NAIVE
#define GENA_ASSIGN_MEMCPY ZZ_GENA_ASSIGN_MEMCPY
#define GENA_ASSIGN_STRCPY ZZ_GENA_ASSIGN_STRCPY

#define ZZ_GENA_ASSIGN_NAIVE( ptr_destination, ptr_source, data_size ) \
  ( *(ptr_destination) = *(ptr_source) )

#define ZZ_GENA_ASSIGN_MEMCPY( ptr_destination, ptr_source, data_size ) \
  ( memcpy( ptr_destination, ptr_source, data_size ) )

#define ZZ_GENA_ASSIGN_STRCPY( ptr_destination, ptr_source, data_size ) \
  ( strncpy( (char*)ptr_destination, (const char*)ptr_source, data_size ) ); \
  ( ((char*)(ptr_destination)) [ (data_size)-1 ] = '\0' )

/******************************************************************************/

#define GENA_COMPARE_NAIVE ZZ_GENA_COMPARE_NAIVE
#define GENA_COMPARE_MEMCMP ZZ_GENA_COMPARE_MEMCMP
#define GENA_COMPARE_STRCMP ZZ_GENA_COMPARE_STRCMP

#define ZZ_GENA_COMPARE_NAIVE( ptr_entry_data, ptr_user_data, data_size ) \
  ( *(ptr_entry_data) - *(ptr_user_data) )

#define ZZ_GENA_COMPARE_MEMCMP( ptr_entry_data, ptr_user_data, data_size ) \
  ( memcmp( ptr_entry_data, ptr_user_data, data_size ) )

/* NOTE: strncmp() is not needed here over strcmp() because ptr_entry_data is
guaranteed to be a valid zero-terminated C string. */
#define ZZ_GENA_COMPARE_STRCMP( ptr_entry_data, ptr_user_data, data_size ) \
  ( strcmp( (const char*)ptr_entry_data, (const char*)ptr_user_data ) )

/******************************************************************************/

#define GENA_APPLY_TYPESET(macro, typeset) macro typeset

/******************************************************************************/

#define ZGENA_VOIDPTR_ADD(x, a) ( (void*)( (char*)(x) + (a) ) )
#define ZGENA_VOIDPTR_SUB(x, a) ( (void*)( (char*)(x) - (a) ) )

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
  ZGENA_MACRO_CONCAT( ZZ_GENA_THIS_REQUIRES_A_SEMICOLON_, __LINE__ ) \
  (void)

/******************************************************************************/

#define ZZ_GENA_FUNCTIONS_LIST_END ZGENA_REQUIRE_SEMICOLON_OUTDOOR

#endif /* ZZ_GENA_COREDEFS_H_IG */
