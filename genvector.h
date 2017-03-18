/*
  genvector - Generalized Vector
  Pseudo-templated, Cpp-like dynamic linear array for custom data types.
  Copyright (c) 2017, Dmitry D. Chernov.
  This library is free software; you can redistribute it and/or modify it
  under the terms of the MIT license. See LICENSE for details.

  NAMING CONVENTION:
  GVEC* - auxiliary macros
  gvec_* - user types and functions
  gv* - internal types and functions

  *_e - enum
  *_s - struct
  *_p - struct pointer
  *_t - plain typedef
*/

#ifndef __GENVECTOR_H__
#define __GENVECTOR_H__

#include <stddef.h>

#if __STDC_VERSION__ < 199901L
  typedef int gvbool;
#else
  #include <stdbool.h>
  typedef bool gvbool;
#endif

/*
  TODO:
  1. 'type' field in header
  2. custom memory management
  3. callbacks on-create, on-copy, on-free etc. (not sure)
  4. iterators
*/

typedef void* gvec_t;
typedef void* gvec_ptr; /* because void** is not a generic pointer */

typedef enum {
  GVEC_ERR_NO,
  GVEC_ERR_MEMORY
} gvec_error_e;

typedef struct __gvhead_s {
  size_t count;
  size_t size;
  size_t unitsz;
} gvhead_s, *gvhead_p;

#define GVEC_GET_BUFFER(handle) \
  ((void*)((char*)handle - sizeof(gvhead_s)))

#define GVEC_GET_HEADER(handle) \
  ((gvhead_p)GVEC_GET_BUFFER(handle))

/******************************************************************************/

extern gvec_t gvec_new( size_t min_count, size_t unitsz );
extern void gvec_set( gvec_ptr phandle, gvec_t source );
extern gvec_t gvec_copy( gvec_t handle );
extern void gvec_free( gvec_t handle );

extern gvec_error_e gvec_resize( gvec_ptr phandle, size_t new_count );
extern gvec_error_e gvec_reserve( gvec_ptr phandle, size_t count );
extern gvec_error_e gvec_shrink( gvec_ptr phandle );

extern gvec_error_e gvec_insert( gvec_ptr phandle, size_t pos, size_t count );
extern void gvec_erase( gvec_t handle, size_t pos, size_t count );
extern gvec_error_e gvec_push( gvec_ptr phandle );
extern void gvec_pop( gvec_t handle );

extern void* gvec_at( gvec_t handle, size_t pos );
extern void* gvec_front( gvec_t handle );
extern void* gvec_back( gvec_t handle );

extern size_t gvec_count( gvec_t handle );
extern size_t gvec_size( gvec_t handle );
extern gvbool gvec_empty( gvec_t handle );
extern void gvec_clear( gvec_t handle );

/******************************************************************************/

#define GVEC_USE_VAL __GVVAL_
#define GVEC_USE_REF __GVREF_

#include "gvec_template.inc"

#endif /*__GENVECTOR_H__*/
