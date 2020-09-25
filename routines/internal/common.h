/*
  Copyright (c) 2018, Dmitry D. Chernov
*/

#ifndef ZZ_ZGENA_COMMON_H_IG
#define ZZ_ZGENA_COMMON_H_IG

#include "../shared.h"

/******************************************************************************/

/* Operators. */

#define ZZ_GENA_VAL__OBTAIN *
#define ZZ_GENA_VAL__REFER &
#define ZZ_GENA_VAL__ACCESS

#define ZZ_GENA_REF__OBTAIN
#define ZZ_GENA_REF__REFER
#define ZZ_GENA_REF__ACCESS

#define ZZ_GENA_PTR__OBTAIN *
#define ZZ_GENA_PTR__REFER
#define ZZ_GENA_PTR__ACCESS *

#define ZZ_GENA_ARR__OBTAIN *
#define ZZ_GENA_ARR__REFER
#define ZZ_GENA_ARR__ACCESS *

/*
  Support for type info parameters in templates.
    plain type: entity_type
    buffer type: (entity_type, entity_count)
    array type: (array_type, entity_type)
*/

#define ZGENA_DATA_TYPE( tpTypeInfo, tpUseBy ) \
  tpUseBy ## DATA_TYPE( tpTypeInfo )

  #define ZZ_GENA_VAL__DATA_TYPE( tpTypeInfo ) \
    tpTypeInfo
  #define ZZ_GENA_REF__DATA_TYPE( tpTypeInfo ) \
    tpTypeInfo
  #define ZZ_GENA_PTR__DATA_TYPE( tpTypeInfo ) \
    ZGENA_PAIR_1(tpTypeInfo)
  #define ZZ_GENA_ARR__DATA_TYPE( tpTypeInfo ) \
    ZGENA_PAIR_2(tpTypeInfo)

#define ZGENA_DATA_SIZE( tpTypeInfo, tpUseBy ) \
  tpUseBy ## DATA_SIZE( tpTypeInfo )

  #define ZZ_GENA_VAL__DATA_SIZE( tpTypeInfo ) \
    ( sizeof(tpTypeInfo) )
  #define ZZ_GENA_REF__DATA_SIZE( tpTypeInfo ) \
    ( sizeof(tpTypeInfo) )
  #define ZZ_GENA_PTR__DATA_SIZE( tpTypeInfo ) \
    ( sizeof(ZGENA_PAIR_1(tpTypeInfo)) * (ZGENA_PAIR_2(tpTypeInfo)) )
  #define ZZ_GENA_ARR__DATA_SIZE( tpTypeInfo ) \
    ( sizeof(ZGENA_PAIR_1(tpTypeInfo)) )

#define ZGENA_DATA_NAKED( tpTypeInfo, tpUseBy ) \
  ZGENA_DATA_TYPE(tpTypeInfo, tpUseBy) tpUseBy ## DATA_NAKED

  #define ZZ_GENA_VAL__DATA_NAKED
  #define ZZ_GENA_REF__DATA_NAKED *
  #define ZZ_GENA_PTR__DATA_NAKED *
  #define ZZ_GENA_ARR__DATA_NAKED *

#define ZGENA_DATA_CAST( tpTypeInfo, tpUseBy, tpAddress ) \
  ( ( tpUseBy ## DATA_CAST(tpTypeInfo) ) (tpAddress) )

  #define ZZ_GENA_VAL__DATA_CAST( tpTypeInfo ) \
    tpTypeInfo*
  #define ZZ_GENA_REF__DATA_CAST( tpTypeInfo ) \
    tpTypeInfo*
  #define ZZ_GENA_PTR__DATA_CAST( tpTypeInfo ) \
    ZGENA_PAIR_1(tpTypeInfo) (*) [ ZGENA_PAIR_2(tpTypeInfo) ]
  #define ZZ_GENA_ARR__DATA_CAST( tpTypeInfo ) \
    ZGENA_PAIR_1(tpTypeInfo) *

#define ZGENA_DATA_BIND( tpTypeInfo, tpUseBy, tpName ) \
  tpUseBy ## DATA_BIND( tpTypeInfo, tpName )

  #define ZZ_GENA_VAL__DATA_BIND( tpTypeInfo, tpName ) \
    tpTypeInfo tpName
  #define ZZ_GENA_REF__DATA_BIND( tpTypeInfo, tpName ) \
    tpTypeInfo tpName
  #define ZZ_GENA_PTR__DATA_BIND( tpTypeInfo, tpName ) \
    ZGENA_PAIR_1(tpTypeInfo) (tpName) [ ZGENA_PAIR_2(tpTypeInfo) ]
  #define ZZ_GENA_ARR__DATA_BIND( tpTypeInfo, tpName ) \
    ZGENA_PAIR_1(tpTypeInfo) tpName

#define ZGENA_DATA_VERIFY( tpUseBy, tpAddress ) \
  tpUseBy ## DATA_VERIFY( tpUseBy, tpAddress )

  #define ZZ_GENA_VAL__DATA_VERIFY( tpTypeInfo, tpAddress ) \
    assert( tpAddress != NULL )
  #define ZZ_GENA_REF__DATA_VERIFY( tpTypeInfo, tpAddress ) \
    ZGENA_STATEMENT_REQUIRE_SEMICOLON
  #define ZZ_GENA_PTR__DATA_VERIFY( tpTypeInfo, tpAddress ) \
    ZGENA_STATEMENT_REQUIRE_SEMICOLON
  #define ZZ_GENA_ARR__DATA_VERIFY( tpTypeInfo, tpAddress ) \
    ZGENA_STATEMENT_REQUIRE_SEMICOLON

/******************************************************************************/

#define ZZ_GENA_ASSIGN_NAIVE( ptr_destination, ptr_source, data_size ) \
  ( *(ptr_destination) = *(ptr_source) )

#define ZZ_GENA_ASSIGN_MEMORY( ptr_destination, ptr_source, data_size ) \
  ( memcpy( ptr_destination, ptr_source, data_size ) )

#define ZZ_GENA_ASSIGN_STRING( ptr_destination, ptr_source, data_size ) ( \
  ((char*)(ptr_destination)) [ (data_size)-1 ] = '\0', \
  strncpy( (char*)(ptr_destination), (const char*)(ptr_source), \
    (data_size)-1 ) \
)

/******************************************************************************/

/* NOTE: We can't simply subtract ptr_user_data from ptr_entry_data here
because values may be unsigned. */
#define ZZ_GENA_COMPARE_NAIVE( ptr_entry_data, ptr_user_data, data_size ) \
  ( (*(ptr_entry_data) < *(ptr_user_data)) ? (-1) \
  : (*(ptr_entry_data) > *(ptr_user_data)) ? (1) \
  : (0) )

#define ZZ_GENA_COMPARE_MEMORY( ptr_entry_data, ptr_user_data, data_size ) \
  ( memcmp( ptr_entry_data, ptr_user_data, data_size ) )

/* NOTE: strncmp() is not needed here over strcmp() because ptr_entry_data is
guaranteed to be a valid zero-terminated C string. */
#define ZZ_GENA_COMPARE_STRING( ptr_entry_data, ptr_user_data, data_size ) \
  ( strcmp( (const char*)(ptr_entry_data), (const char*)(ptr_user_data) ) )

/******************************************************************************/

#define ZGENA_APPROACH_STATIC ZZ_ZGENA_APPROACH_STATIC
#define ZGENA_APPROACH_MODULAR ZZ_ZGENA_APPROACH_MODULAR

#define ZZ_ZGENA_APPROACH_STATIC(once_code) once_code
#define ZZ_ZGENA_APPROACH_MODULAR(once_code)

#define ZGENA_STATIC_APPROACH_FUNCTION static GENA_INLINE

/******************************************************************************/

#define ZZ_ZGENA_PAIR_1(item1, item2) item1
#define ZZ_ZGENA_PAIR_2(item1, item2) item2

#define ZGENA_PAIR_1(pair) ZZ_ZGENA_PAIR_1 pair
#define ZGENA_PAIR_2(pair) ZZ_ZGENA_PAIR_2 pair

/******************************************************************************/

#define ZZ_ZGENA_MACRO_JOIN(x, y) x##y
#define ZGENA_MACRO_JOIN(x, y) ZZ_ZGENA_MACRO_JOIN(x, y)

/******************************************************************************/

#define ZGENA_VOID_POINTER(x, a) ( (void*)( (char*)(x) + (a) ) )

/******************************************************************************/

#define ZGENA_STATEMENT_REQUIRE_SEMICOLON \
  ((void)0)

#define ZGENA_SCOPE_REQUIRE_SEMICOLON(scope) \
  do {scope} while(0)

#define ZGENA_REQUIRE_SEMICOLON_OUTSIDE \
  extern void \
  ZGENA_MACRO_JOIN( ZZ_GENA_THIS_REQUIRES_A_SEMICOLON_, __LINE__ ) \
  (void)

/******************************************************************************/

#define ZZ_GENA_DECLARATIONS_LIST_END ZGENA_REQUIRE_SEMICOLON_OUTSIDE

/******************************************************************************/

#endif /* ZZ_ZGENA_COMMON_H_IG */
