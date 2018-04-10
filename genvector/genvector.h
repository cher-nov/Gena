/*
  genvector - Generalized Vector
  Pseudo-templated, Cpp-like dynamic linear array for custom data types.
  Copyright (c) 2017, Dmitry D. Chernov
*/

#ifndef ZZ_GENA_GENVECTOR_H_IG
#define ZZ_GENA_GENVECTOR_H_IG

typedef void* gvec_h;

#include "gvec_internal.inc"

/******************************************************************************/

/* Instantiation macros. */

#ifndef GVEC_MODULAR_APPROACH

#define \
GVEC_INSTANTIATE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy ) \
  ZZ_GVEC_INSTANTIATE(tpTypeInfo,tpVecName,tpPassBy,tpReturnBy)

#define \
GVEC_INSTANTIATE_EX( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, tpReturnBy ) \
  ZZ_GVEC_INSTANTIATE_EX(tpTypeInfo,tpVecName,tpAssignBy,tpPassBy,tpReturnBy)

#else /* GVEC_MODULAR_APPROACH */

#define \
GVEC_C_DEFINE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy ) \
  ZZ_GVEC_C_DEFINE(tpTypeInfo,tpVecName,tpPassBy,tpReturnBy)

#define \
GVEC_C_DEFINE_EX( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, tpReturnBy ) \
  ZZ_GVEC_C_DEFINE_EX(tpTypeInfo,tpVecName,tpAssignBy,tpPassBy,tpReturnBy)

#define \
GVEC_H_DECLARE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy ) \
  ZZ_GVEC_H_DECLARE(tpTypeInfo,tpVecName,tpPassBy,tpReturnBy)

#define \
GVEC_H_DECLARE_EX( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, tpReturnBy ) \
  ZZ_GVEC_H_DECLARE_EX(tpTypeInfo,tpVecName,tpAssignBy,tpPassBy,tpReturnBy)

#endif /* GVEC_MODULAR_APPROACH */

/******************************************************************************/

/* General-purpose functions. */

extern gvec_h gvec_set( gvec_h handle, gvec_h source );
extern gvec_h gvec_copy( gvec_h handle );
extern void gvec_free( gvec_h handle );

extern void gvec_clear( gvec_h handle );
extern void gvec_reduce( gvec_h handle, size_t new_count );
extern void gvec_erase( gvec_h handle, size_t pos, size_t count );
extern void gvec_pop( gvec_h handle );

extern void* gvec_at( gvec_h handle, size_t pos );
extern void* gvec_front( gvec_h handle );
extern void* gvec_back( gvec_h handle );

extern size_t gvec_count( gvec_h handle );
extern size_t gvec_size( gvec_h handle );
extern gena_bool gvec_empty( gvec_h handle );

/******************************************************************************/

/* Pseudo-templates. User-type management functions are defined there. */
#include "gvec_template.inc"

#endif /* ZZ_GENA_GENVECTOR_H_IG */
