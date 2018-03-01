/*
  genmap - Generalized Map
  Pseudo-templated, Cpp-like dynamic associative array for custom data types.
  Copyright (c) 2017, Dmitry D. Chernov
*/

#ifndef ZZ_GENA_GENMAP_H_IG
#define ZZ_GENA_GENMAP_H_IG

#include "../internals/avl_tree/avl_tree.h"

typedef struct {
  size_t count;
  igena_avl_node_head_p avltree_root;
  size_t key_size;
  size_t value_size;
} gmap_s;

typedef gmap_s* gmap_h;

/******************************************************************************/

extern gmap_h igmap_new( size_t key_size, size_t value_size );
extern void gmap_clear( gmap_h handle );
extern void gmap_free( gmap_h handle );

extern size_t gmap_count( gmap_h handle );
extern gena_bool gmap_empty( gmap_h handle );

/******************************************************************************/

#include "gmap_template.inc"

#endif /* ZZ_GENA_GENMAP_H_IG */
