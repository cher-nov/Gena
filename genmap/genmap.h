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

typedef gmap_s* gmap_t;

/******************************************************************************/

extern gmap_t igmap_new( size_t key_size, size_t value_size );
extern void gmap_clear( gmap_t handle );
extern void gmap_free( gmap_t handle );

extern size_t gmap_count( gmap_t handle );
extern gena_bool gmap_empty( gmap_t handle );

/******************************************************************************/

#include "gmap_template.inc"

#endif /* ZZ_GENA_GENMAP_H_IG */
