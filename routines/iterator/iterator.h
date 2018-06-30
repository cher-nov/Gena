/*
  Copyright (c) 2018, Dmitry D. Chernov
*/

#ifndef ZZ_GENA_ITERATOR_H_IG
#define ZZ_GENA_ITERATOR_H_IG

typedef struct zz_gena_iterator_o* gena_iterator_p;

#include "iter_internal.inc"

typedef struct zz_gena_iterator_o {
  igena_iterator_object_s internal;
  void* handle;
  gena_tag_z tag;
  size_t key_size;
  size_t value_size;
  gena_bool reversed;
} gena_iterator_o;

/******************************************************************************/

extern gena_bool gena_iterator_next( gena_iterator_p object );
extern gena_bool gena_iterator_prior( gena_iterator_p object );
extern gena_bool gena_iterator_move( gena_iterator_p object, ptrdiff_t offset );

extern gena_bool gena_iterator_front( gena_iterator_p object,
  ptrdiff_t offset );
extern gena_bool gena_iterator_back( gena_iterator_p object, ptrdiff_t offset );

extern gena_bool gena_iterator_equal( gena_iterator_p object,
  ptrdiff_t offset1, gena_iterator_p iterator, ptrdiff_t offset2 );
extern int gena_iterator_compare( gena_iterator_p object, ptrdiff_t offset1,
  gena_iterator_p iterator, ptrdiff_t offset2 );

/******************************************************************************/

#endif /* ZZ_GENA_ITERATOR_H_IG */
