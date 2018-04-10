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

/* Instantiation macros. */

#ifndef GTMAP_MODULAR_APPROACH

#define \
GTMAP_INSTANTIATE( tpKeyType, tpValueType, tpMapName, tpKeyCompareBy, \
  tpKeyPassBy, tpValuePassBy ) \
\
  ZZ_GTMAP_INSTANTIATE(tpKeyType,tpValueType,tpMapName,tpKeyCompareBy,\
  tpKeyPassBy,tpValuePassBy)

#define \
GTMAP_INSTANTIATE_EX( tpKeyType, tpValueType, tpMapName, tpKeyAssignBy, \
  tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy ) \
\
  ZZ_GTMAP_INSTANTIATE_EX(tpKeyType,tpValueType,tpMapName,tpKeyAssignBy,\
  tpValueAssignBy,tpKeyCompareBy,tpKeyPassBy,tpValuePassBy)

#else /* GTMAP_MODULAR_APPROACH */

#define \
GTMAP_C_DEFINE( tpKeyType, tpValueType, tpMapName, tpKeyCompareBy, \
  tpKeyPassBy, tpValuePassBy ) \
\
  ZZ_GTMAP_C_DEFINE(tpKeyType,tpValueType,tpMapName,tpKeyCompareBy,\
  tpKeyPassBy,tpValuePassBy)

#define \
GTMAP_C_DEFINE_EX( tpKeyType, tpValueType, tpMapName, tpKeyAssignBy, \
  tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy ) \
\
  ZZ_GTMAP_C_DEFINE_EX(tpKeyType,tpValueType,tpMapName,tpKeyAssignBy,\
  tpValueAssignBy,tpKeyCompareBy,tpKeyPassBy,tpValuePassBy)

#define \
GTMAP_H_DECLARE( tpKeyType, tpValueType, tpMapName, tpKeyCompareBy, \
  tpKeyPassBy, tpValuePassBy ) \
\
  ZZ_GTMAP_H_DECLARE(tpKeyType,tpValueType,tpMapName,tpKeyCompareBy,\
  tpKeyPassBy,tpValuePassBy)

#define \
GTMAP_H_DECLARE_EX( tpKeyType, tpValueType, tpMapName, tpKeyAssignBy, \
  tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy ) \
\
  ZZ_GTMAP_H_DECLARE_EX(tpKeyType,tpValueType,tpMapName,tpKeyAssignBy,\
  tpValueAssignBy,tpKeyCompareBy,tpKeyPassBy,tpValuePassBy)

#endif /* GTMAP_MODULAR_APPROACH */

/******************************************************************************/

/* General-purpose functions. */

extern void gtmap_clear( gtmap_h handle );
extern void gtmap_free( gtmap_h handle );

extern size_t gtmap_count( gtmap_h handle );
extern gena_bool gtmap_empty( gtmap_h handle );

/******************************************************************************/

/* Pseudo-templates. User-type management functions are defined there. */
#include "gtmap_template.inc"

#endif /* ZZ_GENA_GENTREEMAP_H_IG */