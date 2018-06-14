/*
  Copyright (c) 2018, Dmitry D. Chernov
*/

#include "../routines/internal/avl_tree/avl_tree.h"

typedef struct zz_gtset_s {
  size_t count;
  igena_avl_node_p tree_root;
  igena_avl_node_p tree_leftmost;
  igena_avl_node_p tree_rightmost;
  size_t entry_size;
  gena_tag_z tag;
} igtset_s;

/******************************************************************************/

extern gtset_h igtset_new( size_t entry_size, gena_tag_z tag );
