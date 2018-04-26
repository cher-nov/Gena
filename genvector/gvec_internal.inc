/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#include "../internals/coredefs.h"

#define IGVEC_BUFFER(handle) \
  ZGENA_VOIDPTR_SUB( handle, sizeof(igvec_head_s) )

#define IGVEC_HEADER(handle) \
  ( (igvec_head_p) IGVEC_BUFFER(handle) )

typedef struct {
  size_t count;
  size_t size;
  size_t entry_size;
} igvec_head_s, *igvec_head_p;

extern gvec_h igvec_new( size_t min_count, size_t entry_size );

extern gvec_h igvec_resize( gvec_h handle, size_t new_count );
extern gvec_h igvec_reserve( gvec_h handle, size_t min_count );
extern gvec_h igvec_shrink( gvec_h handle );

extern gvec_h igvec_insert( gvec_h handle, size_t pos, size_t count );
extern gvec_h igvec_push( gvec_h handle );

extern void* igvec_pop( gvec_h handle );
extern void* igvec_at( gvec_h handle, size_t position );
