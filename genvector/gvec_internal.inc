/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

typedef struct {
  size_t count;
  size_t size;
  size_t entry_size;
  gena_tag_z tag;
} igvec_header_s, *igvec_header_p;

/******************************************************************************/

#define IGVEC_BLOCK(handle) \
  ZGENA_VOID_POINTER( handle, -sizeof(igvec_header_s) )

#define IGVEC_HEADER(handle) \
  ( (igvec_header_p) IGVEC_BLOCK(handle) )

/******************************************************************************/

extern gvec_h igvec_new( size_t min_count, size_t entry_size, gena_tag_z tag );
extern gvec_h igvec_resize( gvec_h handle, size_t new_count );
extern gvec_h igvec_reserve( gvec_h handle, size_t min_count );
extern gvec_h igvec_shrink( gvec_h handle );
extern gvec_h igvec_insert( gvec_h handle, size_t pos, size_t count );
