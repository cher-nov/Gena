#ifndef ZZ_GENA_AVL_TREE_H_IG
#define ZZ_GENA_AVL_TREE_H_IG

#include "../coredefs.h"

#define IGENA_AVL_BIAS_LEFT (-1)
#define IGENA_AVL_BIAS_PARENT (0)
#define IGENA_AVL_BIAS_RIGHT (1)
#define IGENA_AVL_BIAS_SELF INT_MIN  /* special 'null-like' value */

typedef signed int igena_avl_bias;

typedef struct zz_igena_avl_node_s* igena_avl_node_p;
typedef struct zz_igena_avl_node_s {
  /* order of links must be that, to provide link access by bias value */
  igena_avl_node_p left;
  igena_avl_node_p parent;
  igena_avl_node_p right;
  igena_avl_bias weight;  /* aka 'balance factor' */
} igena_avl_node_s;

#define IGENA_AVL_NODE_LINK(node, link_bias) \
  ( *(&(node)->parent + (link_bias)) )

#define IGENA_AVL_NODE_KEY(node) \
  ZGENA_VOIDPTR_ADD( node, sizeof(igena_avl_node_s) )

#define IGENA_AVL_NODE_VALUE(node, key_size) \
  ZGENA_VOIDPTR_ADD( node, sizeof(igena_avl_node_s) + (key_size) )

/******************************************************************************/

#define \
IGENA_AVL_TREE_INSTANTIATE( tpPrefix, tpSurname, tpKeyTypeInfo, tpValueSize, \
  tpKeyAssignBy, tpKeyCompareBy, tpKeyPassBy ) \
\
  ZZ_IGENA_AVL_TREE_INSTANTIATE(tpPrefix,tpSurname,tpKeyTypeInfo,tpValueSize,\
  tpKeyAssignBy,tpKeyCompareBy,tpKeyPassBy)

/******************************************************************************/

extern igena_avl_node_p igena_avl_node_create( size_t key_size,
  size_t value_size );
extern igena_avl_node_p igena_avl_node_attach( igena_avl_node_p node,
  igena_avl_node_p parent, igena_avl_bias link );
extern igena_avl_node_p igena_avl_node_detach( igena_avl_node_p node );
extern void igena_avl_subtree_free( igena_avl_node_p root );

/******************************************************************************/

#include "avl_template.inc"

#endif /* ZZ_GENA_AVL_TREE_H_IG */
