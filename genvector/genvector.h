/*
  genvector - Generalized Vector
  Pseudo-templated, Cpp-like dynamic linear array for custom data types.
  Copyright (c) 2017, Dmitry D. Chernov
*/

#ifndef __GENA_GENVECTOR_H__
#define __GENA_GENVECTOR_H__

#include "../internals/coredefs.h"

typedef void* gvec_t;
typedef void* gvec_ptr; /* because void** is not a generic pointer */

typedef struct {
  size_t count;
  size_t size;
  size_t entry_size;
} igvec_head_s, *igvec_head_p;

#define IGVEC_GET_BUFFER(handle) \
  __IGENA_VOIDP_SUB(handle, sizeof(igvec_head_s))

#define IGVEC_GET_HEADER(handle) \
  ((igvec_head_p)IGVEC_GET_BUFFER(handle))

/******************************************************************************/

extern gvec_t igvec_new( size_t min_count, size_t entry_size );
extern gvec_t gvec_set( gvec_ptr phandle, gvec_t source );
extern gvec_t gvec_copy( gvec_t handle );
extern void gvec_clear( gvec_t handle );
extern void gvec_free( gvec_t handle );

extern gena_error_e gvec_resize( gvec_ptr phandle, size_t new_count );
extern gena_error_e gvec_reserve( gvec_ptr phandle, size_t count );
extern gena_error_e gvec_shrink( gvec_ptr phandle );

extern gena_error_e igvec_insert( gvec_ptr phandle, size_t pos, size_t count );
extern void gvec_erase( gvec_t handle, size_t pos, size_t count );
extern gena_error_e igvec_push( gvec_ptr phandle );
extern void gvec_pop( gvec_t handle );

extern void* gvec_at( gvec_t handle, size_t pos );
extern void* gvec_front( gvec_t handle );
extern void* gvec_back( gvec_t handle );

extern size_t gvec_count( gvec_t handle );
extern size_t gvec_size( gvec_t handle );
extern gena_bool gvec_empty( gvec_t handle );

/******************************************************************************/

#include "gvec_template.inc"

#endif /*__GENA_GENVECTOR_H__*/
