/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#include "../internals/coredefs.h"

#define IGVEC_GET_BUFFER(handle) \
  ZGENA_VOIDP_SUB(handle, sizeof(igvec_head_s))

#define IGVEC_GET_HEADER(handle) \
  ((igvec_head_p)IGVEC_GET_BUFFER(handle))

typedef struct {
  size_t count;
  size_t size;
  size_t entry_size;
} igvec_head_s, *igvec_head_p;

extern gvec_h igvec_new( size_t min_count, size_t entry_size );
extern gena_bool igvec_insert( gvec_ptr phandle, size_t pos, size_t count );
extern gena_bool igvec_push( gvec_ptr phandle );
