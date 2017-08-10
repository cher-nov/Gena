/*
  genmap - Generalized Map
  Pseudo-templated, Cpp-like dynamic associative array for custom data types.
  Copyright (c) 2017, Dmitry D. Chernov
*/

#ifndef __GENA_GENMAP_H__
#define __GENA_GENMAP_H__

#include "../internals/avl_tree/avl_tree.h"

typedef struct {
  size_t count;
  igena_avl_node_head_p avltree_root;
} gmap_s;

typedef gmap_s* gmap_t;

/******************************************************************************/

extern gmap_t gmap_new();
extern void gmap_clear( gmap_t handle );
extern void gmap_free( gmap_t handle );

extern size_t gmap_count( gmap_t handle );
extern gena_bool gmap_empty( gmap_t handle );

/******************************************************************************/

#include "gmap_template.inc"

#endif /*__GENA_GENMAP_H__*/
