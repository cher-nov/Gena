#ifndef __GENA_AVL_TREE_H__
#define __GENA_AVL_TREE_H__

#include "../coredefs.h"

typedef enum {
  IGENA_AVL_RETST_NOTHING,  /* tree wasn't changed */
  IGENA_AVL_RETST_BALANCE,  /* balance node */
  IGENA_AVL_RETST_RETURN    /* no more balancing is needed */
} igena_avl_retstate_e;

typedef struct __igena_avl_node_head_s_typedef* igena_avl_node_head_p;
typedef struct __igena_avl_node_head_s_typedef {
  igena_avl_node_head_p left;
  igena_avl_node_head_p right;
  int factor;
} igena_avl_node_head_s;

#define IGENA_AVL_NODE_GET_KEY(node, key_type) ( \
  (key_type*) \
  __IGENA_VOIDP_ADD( node, sizeof(igena_avl_node_head_s) ) \
)

#define IGENA_AVL_NODE_GET_VALUE(node, key_type, value_type) ( \
  (value_type*) \
  __IGENA_VOIDP_ADD( node, sizeof(igena_avl_node_head_s) + sizeof(key_type) ) \
)

/******************************************************************************/

extern igena_avl_node_head_p igena_avl_node_create( size_t key_size,
  size_t value_size );
extern gena_bool igena_avl_node_discard( igena_avl_node_head_p* pnode );
extern void igena_avl_node_balance( igena_avl_node_head_p* pnode );

extern void igena_avl_subtree_free( igena_avl_node_head_p node );

/******************************************************************************/

#include "avl_template.inc"

#endif /*__GENA_AVL_TREE_H__*/
