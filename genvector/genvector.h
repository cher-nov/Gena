/*
  genvector - Generalized Vector
  Pseudo-templated, Cpp-like dynamic linear array for custom data types.
  Copyright (c) 2017, Dmitry D. Chernov
*/

#ifndef ZZ_GENA_GENVECTOR_H_IG
#define ZZ_GENA_GENVECTOR_H_IG

#include "../routines/global.h"
#include "../routines/iterator/iterator.h"

typedef void* gvec_h;

#include "gvec_internal.inc"

/******************************************************************************/

/* Instantiation macros, static approach. */

#define \
GVEC_INSTANTIATE( tpTypeInfo, tpSurname, tpUseBy ) \
  ZZ_GVEC_INSTANTIATE(tpTypeInfo,tpSurname,tpUseBy)

#define \
GVEC_INSTANTIATE_EX( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy, tpAssignBy ) \
  ZZ_GVEC_INSTANTIATE_EX(tpTypeInfo,tpSurname,tpPassBy,tpReturnBy,tpAssignBy)

/* Instantiation macros, modular approach. */

#define \
GVEC_H_DECLARE( tpTypeInfo, tpSurname, tpUseBy ) \
  ZZ_GVEC_H_DECLARE(tpTypeInfo,tpSurname,tpUseBy)

#define \
GVEC_C_DEFINE( tpTypeInfo, tpSurname, tpUseBy ) \
  ZZ_GVEC_C_DEFINE(tpTypeInfo,tpSurname,tpUseBy)

#define \
GVEC_H_DECLARE_EX( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy, tpAssignBy ) \
  ZZ_GVEC_H_DECLARE_EX(tpTypeInfo,tpSurname,tpPassBy,tpReturnBy,tpAssignBy)

#define \
GVEC_C_DEFINE_EX( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy, tpAssignBy ) \
  ZZ_GVEC_C_DEFINE_EX(tpTypeInfo,tpSurname,tpPassBy,tpReturnBy,tpAssignBy)

/******************************************************************************/

/* General-purpose functions. */

extern gvec_h gvec_assign( gvec_h handle, gvec_h source );
extern gvec_h gvec_copy( gvec_h handle );
extern void gvec_free( gvec_h handle );

extern void gvec_clear( gvec_h handle );
extern void gvec_reduce( gvec_h handle, size_t new_count );
extern gena_bool gvec_remove( gvec_h handle, size_t position, size_t count );
extern gena_bool gvec_drop( gvec_h handle );

extern size_t gvec_count( gvec_h handle );
extern size_t gvec_size( gvec_h handle );
extern gena_bool gvec_empty( gvec_h handle );

/******************************************************************************/

/* Iterator-related functions. */

extern gena_bool gvec_begin( gvec_h handle, gena_bool reversed,
  gena_iterator_p OUT_object );
extern gena_bool gvec_end( gvec_h handle, gena_bool reversed,
  gena_iterator_p OUT_object );
extern gena_bool gvec_at( gvec_h handle, size_t position, gena_bool reversed,
  gena_iterator_p OUT_object );

/******************************************************************************/

/* Pseudo-templated functions to be specialized at type instantiation. */
/* NOTE: Do not invoke this directly. Instead, use the instantiation macros. */

#define ZZ_GVEC_DECLARATIONS_LIST( Surname, TypeName, PassType, ReturnType ) \
\
extern const gena_tag_z gvec_##tpSurname##_tag; \
\
extern gvec_##Surname##_h gvec_##Surname##_new( size_t min_count ); \
\
extern gena_bool gvec_##Surname##_reset( gvec_##Surname##_h* phandle, \
  size_t count, const PassType value ); \
\
extern gena_bool gvec_##Surname##_resize( gvec_##Surname##_h* phandle, \
  size_t new_count, const PassType value ); \
\
extern gena_bool gvec_##Surname##_reserve( gvec_##Surname##_h* phandle, \
  size_t min_count ); \
\
extern gena_bool gvec_##Surname##_shrink( gvec_##Surname##_h* phandle ); \
\
extern gena_bool gvec_##Surname##_insert( gvec_##Surname##_h* phandle, \
  size_t position, size_t count, const PassType value ); \
\
extern gena_bool gvec_##Surname##_push( gvec_##Surname##_h* phandle, \
  const PassType value ); \
\
extern ReturnType gvec_##Surname##_pop( gvec_##Surname##_h handle ); \
\
extern ReturnType gvec_##Surname##_value( gena_iterator_p object, \
  ptrdiff_t offset ); \
\
extern TypeName* gvec_##Surname##_emplace( gena_iterator_p object, \
  ptrdiff_t offset, const PassType value ); \
\
ZZ_GENA_DECLARATIONS_LIST_END

/******************************************************************************/

/* Pseudo-templates. User-type management functions are defined there. */
#include "gvec_template.inc"

#endif /* ZZ_GENA_GENVECTOR_H_IG */
