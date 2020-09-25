/*
  gentreemap - Generalized TreeMap
  Pseudo-templated, Cpp-like dynamic associative array for custom data types,
  implemented using a self-balancing binary search tree.
  Copyright (c) 2017, Dmitry D. Chernov
*/

#ifndef ZZ_GENA_GENTREEMAP_H_IG
#define ZZ_GENA_GENTREEMAP_H_IG

#include "../routines/global.h"
#include "../routines/iterator/iterator.h"

typedef struct zz_gtmap_s* gtmap_h;

#include "gtmap_internal.inc"

/******************************************************************************/

/* Instantiation macros, static approach. */

#define \
GTMAP_INSTANTIATE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyUseBy, \
  tpValueUseBy, tpKeyCompareBy ) \
\
  ZZ_GTMAP_INSTANTIATE(tpKeyTypeInfo,tpValueTypeInfo,tpSurname,tpKeyUseBy,\
  tpValueUseBy,tpKeyCompareBy)

#define \
GTMAP_INSTANTIATE_EX( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyPassBy, \
  tpKeyReturnBy, tpValuePassBy, tpValueReturnBy, tpKeyCompareBy, \
  tpKeyAssignBy, tpValueAssignBy ) \
\
  ZZ_GTMAP_INSTANTIATE_EX(tpKeyTypeInfo,tpValueTypeInfo,tpSurname,tpKeyPassBy,\
  tpKeyReturnBy,tpValuePassBy,tpValueReturnBy,tpKeyCompareBy,tpKeyAssignBy,\
  tpValueAssignBy)

/* Instantiation macros, modular approach. */

#define \
GTMAP_H_DECLARE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyUseBy, \
  tpValueUseBy, tpKeyCompareBy ) \
\
  ZZ_GTMAP_H_DECLARE(tpKeyTypeInfo,tpValueTypeInfo,tpSurname,tpKeyUseBy,\
  tpValueUseBy,tpKeyCompareBy)

#define \
GTMAP_C_DEFINE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyUseBy, \
  tpValueUseBy, tpKeyCompareBy ) \
\
  ZZ_GTMAP_C_DEFINE(tpKeyTypeInfo,tpValueTypeInfo,tpSurname,tpKeyUseBy,\
  tpValueUseBy,tpKeyCompareBy)

#define \
GTMAP_H_DECLARE_EX( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyPassBy, \
  tpKeyReturnBy, tpValuePassBy, tpValueReturnBy, tpKeyCompareBy, \
  tpKeyAssignBy, tpValueAssignBy ) \
\
  ZZ_GTMAP_H_DECLARE_EX(tpKeyTypeInfo,tpValueTypeInfo,tpSurname,tpKeyPassBy,\
  tpKeyReturnBy,tpValuePassBy,tpValueReturnBy,tpKeyCompareBy,tpKeyAssignBy,\
  tpValueAssignBy)

#define \
GTMAP_C_DEFINE_EX( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyPassBy, \
  tpKeyReturnBy, tpValuePassBy, tpValueReturnBy, tpKeyCompareBy, \
  tpKeyAssignBy, tpValueAssignBy ) \
\
  ZZ_GTMAP_C_DEFINE_EX(tpKeyTypeInfo,tpValueTypeInfo,tpSurname,tpKeyPassBy,\
  tpKeyReturnBy,tpValuePassBy,tpValueReturnBy,tpKeyCompareBy,tpKeyAssignBy,\
  tpValueAssignBy)

/******************************************************************************/

/* General-purpose functions. */

extern void gtmap_clear( gtmap_h handle );
extern void gtmap_free( gtmap_h handle );

extern size_t gtmap_count( gtmap_h handle );
extern gena_bool gtmap_empty( gtmap_h handle );

/******************************************************************************/

/* Iterator-related functions. */

extern gena_bool gtmap_begin( gtmap_h handle, gena_bool reversed,
  gena_iterator_p OUT_object );
extern gena_bool gtmap_end( gtmap_h handle, gena_bool reversed,
  gena_iterator_p OUT_object );
extern gena_bool gtmap_at( gtmap_h handle, size_t position, gena_bool reversed,
  gena_iterator_p OUT_object );

/******************************************************************************/

/* Pseudo-templated functions to be specialized at type instantiation. */
/* NOTE: Do not invoke this directly. Instead, use the instantiation macros. */

#define ZZ_GTMAP_DECLARATIONS_LIST( Surname, KeyTypeName, ValueTypeName, \
  KeyPassType, KeyReturnType, ValuePassType, ValueReturnType ) \
\
extern const gena_tag_z gtmap_##tpSurname##_tag; \
\
extern gtmap_##Surname##_h gtmap_##Surname##_new(void); \
\
extern ValueTypeName* gtmap_##Surname##_add( gtmap_##Surname##_h handle, \
  KeyPassType const key, ValuePassType const value ); \
\
extern ValueTypeName* gtmap_##Surname##_put( gtmap_##Surname##_h handle, \
  KeyPassType const key, ValuePassType const value ); \
\
extern gena_bool gtmap_##Surname##_delete( gtmap_##Surname##_h handle, \
  KeyPassType const key ); \
\
extern ValueTypeName* gtmap_##Surname##_find( gtmap_##Surname##_h handle, \
  KeyPassType const key ); \
\
extern ValueReturnType gtmap_##Surname##_first( gtmap_##Surname##_h handle, \
  KeyReturnType* OUT_key ); \
\
extern ValueReturnType gtmap_##Surname##_last( gtmap_##Surname##_h handle, \
  KeyReturnType* OUT_key ); \
\
extern KeyReturnType gtmap_##Surname##_key( gena_iterator_p object, \
  ptrdiff_t offset ); \
\
extern ValueReturnType gtmap_##Surname##_value( gena_iterator_p object, \
  ptrdiff_t offset ); \
\
extern ValueReturnType gtmap_##Surname##_entry( gena_iterator_p object, \
  ptrdiff_t offset, KeyReturnType* OUT_key ); \
\
extern ValueTypeName* gtmap_##Surname##_emplace( gena_iterator_p object, \
  ptrdiff_t offset, ValuePassType const value ); \
\
ZZ_GENA_DECLARATIONS_LIST_END

/******************************************************************************/

/* Pseudo-templates. User-type management functions are defined there. */
#include "gtmap_template.inc"

#endif /* ZZ_GENA_GENTREEMAP_H_IG */
