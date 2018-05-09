/*
  gentreemap - Generalized TreeMap
  Pseudo-templated, Cpp-like dynamic associative array for custom data types,
  implemented using a self-balancing binary search tree.
  Copyright (c) 2017, Dmitry D. Chernov
*/

#ifndef ZZ_GENA_GENTREEMAP_H_IG
#define ZZ_GENA_GENTREEMAP_H_IG

typedef struct zz_gtmap_s* gtmap_h;

#include "gtmap_internal.inc"

/******************************************************************************/

/* Instantiation macros, static approach. */

#define \
GTMAP_INSTANTIATE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyPassBy, \
  tpValuePassBy, tpKeyCompareBy ) \
\
  ZZ_GTMAP_INSTANTIATE(tpKeyTypeInfo,tpValueTypeInfo,tpSurname,tpKeyPassBy,\
  tpValuePassBy,tpKeyCompareBy)

#define \
GTMAP_INSTANTIATE_EX( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyPassBy, \
  tpValuePassBy, tpKeyCompareBy, tpKeyAssignBy, tpValueAssignBy ) \
\
  ZZ_GTMAP_INSTANTIATE_EX(tpKeyTypeInfo,tpValueTypeInfo,tpSurname,tpKeyPassBy,\
  tpValuePassBy,tpKeyCompareBy,tpKeyAssignBy,tpValueAssignBy)

/* Instantiation macros, modular approach. */

#define \
GTMAP_H_DECLARE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyPassBy, \
  tpValuePassBy, tpKeyCompareBy ) \
\
  ZZ_GTMAP_H_DECLARE(tpKeyTypeInfo,tpValueTypeInfo,tpSurname,tpKeyPassBy,\
  tpValuePassBy,tpKeyCompareBy)

#define \
GTMAP_C_DEFINE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyPassBy, \
  tpValuePassBy, tpKeyCompareBy ) \
\
  ZZ_GTMAP_C_DEFINE(tpKeyTypeInfo,tpValueTypeInfo,tpSurname,tpKeyPassBy,\
  tpValuePassBy,tpKeyCompareBy)

#define \
GTMAP_H_DECLARE_EX( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyPassBy, \
  tpValuePassBy, tpKeyCompareBy, tpKeyAssignBy, tpValueAssignBy ) \
\
  ZZ_GTMAP_H_DECLARE_EX(tpKeyTypeInfo,tpValueTypeInfo,tpSurname,tpKeyPassBy,\
  tpValuePassBy,tpKeyCompareBy,tpKeyAssignBy,tpValueAssignBy)

#define \
GTMAP_C_DEFINE_EX( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyPassBy, \
  tpValuePassBy, tpKeyCompareBy, tpKeyAssignBy, tpValueAssignBy ) \
\
  ZZ_GTMAP_C_DEFINE_EX(tpKeyTypeInfo,tpValueTypeInfo,tpSurname,tpKeyPassBy,\
  tpValuePassBy,tpKeyCompareBy,tpKeyAssignBy,tpValueAssignBy)

/******************************************************************************/

/* General-purpose functions. */

extern void gtmap_clear( gtmap_h handle );
extern void gtmap_free( gtmap_h handle );

extern size_t gtmap_count( gtmap_h handle );
extern gena_bool gtmap_empty( gtmap_h handle );

/******************************************************************************/

/* Pseudo-templated functions to be specialized at type instantiation. */
/* NOTE: Do not call this directly. Instead, use the instantiation macros. */

#define ZZ_GTMAP_DECLARATIONS_LIST( Surname, ValueTypeName, KeyPassType, \
  ValuePassType ) \
\
extern const gena_tag_z gvec_##tpSurname##_tag; \
\
extern gtmap_##Surname##_h gtmap_##Surname##_new(void); \
\
extern ValueTypeName* gtmap_##Surname##_add( gtmap_##Surname##_h handle, \
  const KeyPassType key, const ValuePassType value ); \
\
extern ValueTypeName* gtmap_##Surname##_put( gtmap_##Surname##_h handle, \
  const KeyPassType key, const ValuePassType value ); \
\
extern gena_bool gtmap_##Surname##_delete( gtmap_##Surname##_h handle, \
  const KeyPassType key ); \
\
extern ValueTypeName* gtmap_##Surname##_find( gtmap_##Surname##_h handle, \
  const KeyPassType key ); \
\
ZZ_GENA_DECLARATIONS_LIST_END

/******************************************************************************/

/* Pseudo-templates. User-type management functions are defined there. */
#include "gtmap_template.inc"

#endif /* ZZ_GENA_GENTREEMAP_H_IG */
