#ifndef ZZ_GENA_AVL_TREE_H_IG
#define ZZ_GENA_AVL_TREE_H_IG

#include "../coredefs.h"

typedef enum {
  IGENA_AVL_RETST_NOTHING,  /* tree wasn't changed */
  IGENA_AVL_RETST_BALANCE,  /* balance node */
  IGENA_AVL_RETST_RETURN    /* no more balancing is needed */
} igena_avl_retstate_e;

typedef struct zz_igena_avl_node_head_s* igena_avl_node_head_p;
typedef struct zz_igena_avl_node_head_s {
  igena_avl_node_head_p left;
  igena_avl_node_head_p right;
  int factor;
} igena_avl_node_head_s;

#define IGENA_AVL_NODE_GET_KEY(node) \
  ZGENA_VOIDP_ADD( node, sizeof(igena_avl_node_head_s) )

#define IGENA_AVL_NODE_GET_VALUE(node, key_size) \
  ZGENA_VOIDP_ADD( node, sizeof(igena_avl_node_head_s) + key_size )

/******************************************************************************/

extern igena_avl_node_head_p igena_avl_node_create( size_t key_size,
  size_t value_size );
extern gena_bool igena_avl_node_discard( igena_avl_node_head_p* pnode );
extern void igena_avl_node_balance( igena_avl_node_head_p* pnode );

extern void igena_avl_subtree_free( igena_avl_node_head_p node );

/******************************************************************************/

#include "avl_template.inc"

#endif /* ZZ_GENA_AVL_TREE_H_IG */
