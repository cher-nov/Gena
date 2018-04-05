/*
  genmap - Generalized Map
  Pseudo-templated, Cpp-like dynamic associative array for custom data types.
  Copyright (c) 2017, Dmitry D. Chernov
*/

#ifndef ZZ_GENA_GENMAP_H_IG
#define ZZ_GENA_GENMAP_H_IG

typedef struct zz_gmap_s* gmap_h;

#include "gmap_internal.inc"

/******************************************************************************/

/* Instantiation macros. */

#ifndef GMAP_MODULAR_APPROACH

#define \
GMAP_INSTANTIATE( tpKeyType, tpValueType, tpMapName, tpKeyCompareBy, \
  tpKeyPassBy, tpValuePassBy ) \
\
  ZZ_GMAP_INSTANTIATE(tpKeyType,tpValueType,tpMapName,tpKeyCompareBy,\
  tpKeyPassBy,tpValuePassBy)

#define \
GMAP_INSTANTIATE_EX( tpKeyType, tpValueType, tpMapName, tpKeyAssignBy, \
  tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy ) \
\
  ZZ_GMAP_INSTANTIATE_EX(tpKeyType,tpValueType,tpMapName,tpKeyAssignBy,\
  tpValueAssignBy,tpKeyCompareBy,tpKeyPassBy,tpValuePassBy)

#else /* GMAP_MODULAR_APPROACH */

#define \
GMAP_C_DEFINE( tpKeyType, tpValueType, tpMapName, tpKeyCompareBy, \
  tpKeyPassBy, tpValuePassBy ) \
\
  ZZ_GMAP_C_DEFINE(tpKeyType,tpValueType,tpMapName,tpKeyCompareBy,\
  tpKeyPassBy,tpValuePassBy)

#define \
GMAP_C_DEFINE_EX( tpKeyType, tpValueType, tpMapName, tpKeyAssignBy, \
  tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy ) \
\
  ZZ_GMAP_C_DEFINE_EX(tpKeyType,tpValueType,tpMapName,tpKeyAssignBy,\
  tpValueAssignBy,tpKeyCompareBy,tpKeyPassBy,tpValuePassBy)

#define \
GMAP_H_DECLARE( tpKeyType, tpValueType, tpMapName, tpKeyCompareBy, \
  tpKeyPassBy, tpValuePassBy ) \
\
  ZZ_GMAP_H_DECLARE(tpKeyType,tpValueType,tpMapName,tpKeyCompareBy,\
  tpKeyPassBy,tpValuePassBy)

#define \
GMAP_H_DECLARE_EX( tpKeyType, tpValueType, tpMapName, tpKeyAssignBy, \
  tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy ) \
\
  ZZ_GMAP_H_DECLARE_EX(tpKeyType,tpValueType,tpMapName,tpKeyAssignBy,\
  tpValueAssignBy,tpKeyCompareBy,tpKeyPassBy,tpValuePassBy)

#endif /* GMAP_MODULAR_APPROACH */

/******************************************************************************/

/* General-purpose functions. */

extern void gmap_clear( gmap_h handle );
extern void gmap_free( gmap_h handle );

extern size_t gmap_count( gmap_h handle );
extern gena_bool gmap_empty( gmap_h handle );

/******************************************************************************/

/* Pseudo-templates. User-type management functions are defined there. */
#include "gmap_template.inc"

#endif /* ZZ_GENA_GENMAP_H_IG */
