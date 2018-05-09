/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#include "../routines/internal/avl_tree/avl_tree.h"

typedef struct zz_gtmap_s {
  size_t count;
  igena_avl_node_p tree_root;
  size_t key_size;
  size_t value_size;
  gena_tag_z tag;
} igtmap_s;

/******************************************************************************/

extern gtmap_h igtmap_new( size_t key_size, size_t value_size, gena_tag_z tag );
