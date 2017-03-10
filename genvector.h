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

/*
  TODO:
  1. 'type' field in header
  2. custom memory management
  3. callbacks on-create, on-copy, on-free etc. (not sure)
  4. iterators
*/

typedef void* gvec_t;

typedef enum {
  GVEC_ERR_NO,
  GVEC_ERR_IDLE,
  GVEC_ERR_MEMORY
} gvec_error_e;

typedef struct __gvhead_s {
  size_t count;
  size_t size;
  size_t unitsz;
  gvec_error_e error;
} gvhead_s, *gvhead_p;

#define GVEC_HDR(hgvec) \
  ((gvhead_p)((char*)hgvec - sizeof(gvhead_s)))

/******************************************************************************/

#define gvec_count(hgvec) (GVEC_HDR(hgvec)->count)
#define gvec_size(hgvec) (GVEC_HDR(hgvec)->size)
#define gvec_error(hgvec) (GVEC_HDR(hgvec)->error)

#define gvec_empty(hgvec) (gvec_count(hgvec) == 0)
#define gvec_clear(hgvec) (gvec_resize(hgvec, 0))

/******************************************************************************/

extern gvec_t gvec_new( size_t min_count, size_t unitsz );
extern gvec_t gvec_set( gvec_t hgvec_dest, gvec_t hgvec_src );
extern gvec_t gvec_copy( gvec_t hgvec );
extern void gvec_free( gvec_t hgvec );

extern gvec_t gvec_resize( gvec_t hgvec, size_t new_count );
extern gvec_t gvec_reserve( gvec_t hgvec, size_t count );
extern gvec_t gvec_shrink( gvec_t hgvec );

extern gvec_t gvec_insert( gvec_t hgvec, size_t pos, size_t count );
extern void gvec_erase( gvec_t hgvec, size_t pos, size_t count );
extern gvec_t gvec_push( gvec_t hgvec );
extern void gvec_pop( gvec_t hgvec );

extern void* gvec_at( gvec_t hgvec, size_t pos );
extern void* gvec_front( gvec_t hgvec );
extern void* gvec_back( gvec_t hgvec );

/******************************************************************************/

#define GVEC_ERROR_SAFE(error) \
  ((error == GVEC_ERR_NO) || (error == GVEC_ERR_IDLE))

#define GVEC_NO_ERROR(hgvec) GVEC_ERROR_SAFE(gvec_error(hgvec))

#define GVEC_USE_VAL
#define GVEC_USE_REF *

#include "gvec_template.inc"

#endif /*__GENVECTOR_H__*/
