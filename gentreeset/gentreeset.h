/*
  gentreeset - Generalized TreeSet
  Pseudo-templated, Cpp-like set container for custom data types,
  implemented using a self-balancing binary search tree.
  Copyright (c) 2018, Dmitry D. Chernov
*/

#ifndef ZZ_GENA_GENTREESET_H_IG
#define ZZ_GENA_GENTREESET_H_IG

#include "../routines/global.h"
#include "../routines/iterator/iterator.h"

typedef struct zz_gtset_s* gtset_h;

#include "gtset_internal.inc"

/******************************************************************************/

/* Instantiation macros, static approach. */

#define \
GTSET_INSTANTIATE( tpTypeInfo, tpSurname, tpUseBy, tpCompareBy ) \
\
  ZZ_GTSET_INSTANTIATE(tpTypeInfo,tpSurname,tpUseBy,tpCompareBy)

#define \
GTSET_INSTANTIATE_EX( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy, \
  tpCompareBy, tpAssignBy ) \
\
  ZZ_GTSET_INSTANTIATE_EX(tpTypeInfo,tpSurname,tpPassBy,tpReturnBy,\
  tpCompareBy,tpAssignBy)

/* Instantiation macros, modular approach. */

#define \
GTSET_H_DECLARE( tpTypeInfo, tpSurname, tpUseBy, tpCompareBy ) \
\
  ZZ_GTSET_H_DECLARE(tpTypeInfo,tpSurname,tpUseBy,tpCompareBy)

#define \
GTSET_C_DEFINE( tpTypeInfo, tpSurname, tpUseBy, tpCompareBy ) \
\
  ZZ_GTSET_C_DEFINE(tpTypeInfo,tpSurname,tpUseBy,tpCompareBy)

#define \
GTSET_H_DECLARE_EX( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy, tpCompareBy, \
  tpAssignBy ) \
\
  ZZ_GTSET_H_DECLARE_EX(tpTypeInfo,tpSurname,tpPassBy,tpReturnBy,tpCompareBy,\
  tpAssignBy)

#define \
GTSET_C_DEFINE_EX( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy, tpCompareBy, \
  tpAssignBy ) \
\
  ZZ_GTSET_C_DEFINE_EX(tpTypeInfo,tpSurname,tpPassBy,tpReturnBy,tpCompareBy,\
  tpAssignBy)

/******************************************************************************/

/* General-purpose functions. */

extern void gtset_clear( gtset_h handle );
extern void gtset_free( gtset_h handle );

extern size_t gtset_count( gtset_h handle );
extern gena_bool gtset_empty( gtset_h handle );

/******************************************************************************/

/* Iterator-related functions. */

extern gena_bool gtset_begin( gtset_h handle, gena_bool reversed,
  gena_iterator_p OUT_object );
extern gena_bool gtset_end( gtset_h handle, gena_bool reversed,
  gena_iterator_p OUT_object );
extern gena_bool gtset_at( gtset_h handle, size_t position, gena_bool reversed,
  gena_iterator_p OUT_object );

/******************************************************************************/

/* Pseudo-templated functions to be specialized at type instantiation. */
/* NOTE: Do not invoke this directly. Instead, use the instantiation macros. */

#define ZZ_GTSET_DECLARATIONS_LIST( Surname, TypeName, PassType, ReturnType ) \
\
extern const gena_tag_z gtset_##tpSurname##_tag; \
\
extern gtset_##Surname##_h gtset_##Surname##_new(void); \
\
extern gena_bool gtset_##Surname##_add( gtset_##Surname##_h handle, \
  const PassType value, gena_bool* OUT_key_exists ); \
\
extern gena_bool gtset_##Surname##_delete( gtset_##Surname##_h handle, \
  const PassType value ); \
\
extern gena_bool gtset_##Surname##_check( gtset_##Surname##_h handle, \
  const PassType value ); \
\
extern ReturnType gtset_##Surname##_first( gtset_##Surname##_h handle ); \
\
extern ReturnType gtset_##Surname##_last( gtset_##Surname##_h handle ); \
\
extern ReturnType gtset_##Surname##_value( gena_iterator_p object, \
  ptrdiff_t offset ); \
\
ZZ_GENA_DECLARATIONS_LIST_END

/******************************************************************************/

/* Pseudo-templates. User-type management functions are defined there. */
#include "gtset_template.inc"

#endif /* ZZ_GENA_GENTREESET_H_IG */
