/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#include <string.h>

#define IGENA_AVL_SUBTREE_INSTANTIATE( tpPrefix, tpTreeName, tpKeyType, \
  tpValueSize, tpKeyCompareBy, tpKeyPassBy ) \
\
  _impl_IGENA_AVL_SUBTREE_INSTANTIATE( tpPrefix, tpTreeName, tpKeyType, \
    tpValueSize, tpKeyCompareBy, tpKeyPassBy )

/******************************************************************************/

/* NOTE: tpPrefix is needed to prevent name collisions because different data
structures that use AVL-tree can be instantiated with same names. */

#define _impl_IGENA_AVL_SUBTREE_INSTANTIATE( tpPrefix, tpTreeName, tpKeyType, \
  tpValueSize, tpKeyCompareBy, tpKeyPassBy ) \
\
/********************************************************************/ \
  static igena_avl_retstate_e \
  i##tpPrefix##_avl_subtree_##tpTreeName##_add_key( \
    igena_avl_node_head_p* pnode, \
    const tpKeyType tpKeyPassBy##OP key, \
    igena_avl_node_head_p* OUT_final_node \
  ) { \
    igena_avl_retstate_e retstate; \
    igena_avl_node_head_p new_node; \
    int compare_result; \
  { \
    if (*pnode == NULL) { \
      new_node = igena_avl_node_create( sizeof(tpKeyType), tpValueSize ); \
      if (new_node != NULL) { \
        *IGENA_AVL_NODE_GET_KEY(new_node, tpKeyType) = tpKeyPassBy##OP key; \
        *pnode = new_node; \
      } \
\
      if (OUT_final_node != NULL) { *OUT_final_node = new_node; } \
      return (new_node != NULL) \
             ? IGENA_AVL_RETST_BALANCE \
             : IGENA_AVL_RETST_NOTHING; \
    } \
\
    compare_result = tpKeyCompareBy ( tpKeyPassBy##AOF key, \
      IGENA_AVL_NODE_GET_KEY(*pnode, tpKeyType) ); \
\
    if (compare_result < 0) { \
      retstate = i##tpPrefix##_avl_subtree_##tpTreeName##_add_key( \
        &(*pnode)->left, key, OUT_final_node ); \
      if (retstate == IGENA_AVL_RETST_BALANCE) { --((*pnode)->factor); } \
    } else if (compare_result > 0) { \
      retstate = i##tpPrefix##_avl_subtree_##tpTreeName##_add_key( \
        &(*pnode)->right, key, OUT_final_node ); \
      if (retstate == IGENA_AVL_RETST_BALANCE) { ++((*pnode)->factor); } \
    } else { \
      if (OUT_final_node != NULL) { *OUT_final_node = *pnode; } \
      return IGENA_AVL_RETST_NOTHING; \
    } \
\
    if (retstate == IGENA_AVL_RETST_BALANCE) { \
      igena_avl_node_balance( pnode ); \
      if ( (*pnode)->factor == 0 ) { return IGENA_AVL_RETST_RETURN; } \
    } \
\
    return retstate; \
  }} \
/********************************************************************/ \
  static igena_avl_retstate_e \
  i##tpPrefix##_avl_subtree_##tpTreeName##_delete_key( \
    igena_avl_node_head_p* pnode, \
    const tpKeyType tpKeyPassBy##OP key \
  ) { \
    igena_avl_retstate_e retstate; \
    int compare_result; \
    gena_bool can_balance = GENA_TRUE; \
  { \
    if (*pnode == NULL) { return IGENA_AVL_RETST_NOTHING; } \
\
    compare_result = tpKeyCompareBy ( tpKeyPassBy##AOF key, \
      IGENA_AVL_NODE_GET_KEY(*pnode, tpKeyType) ); \
\
    if (compare_result < 0) { \
      retstate = i##tpPrefix##_avl_subtree_##tpTreeName##_delete_key( \
        &(*pnode)->left, key ); \
      if (retstate == IGENA_AVL_RETST_BALANCE) { ++((*pnode)->factor); } \
    } else if (compare_result > 0) { \
      retstate = i##tpPrefix##_avl_subtree_##tpTreeName##_delete_key( \
        &(*pnode)->right, key ); \
      if (retstate == IGENA_AVL_RETST_BALANCE) { --((*pnode)->factor); } \
    } else { \
      can_balance = !igena_avl_node_discard( pnode ); \
      retstate = IGENA_AVL_RETST_BALANCE; \
    } \
\
    if ( (can_balance) && (retstate == IGENA_AVL_RETST_BALANCE) ) { \
      igena_avl_node_balance( pnode ); \
      if ( (*pnode)->factor != 0 ) { return IGENA_AVL_RETST_RETURN; } \
    } \
\
    return retstate; \
  }} \
/********************************************************************/ \
  static igena_avl_node_head_p \
  i##tpPrefix##_avl_subtree_##tpTreeName##_find_node( \
    igena_avl_node_head_p node, \
    const tpKeyType tpKeyPassBy##OP key \
  ) { \
    int compare_result; \
  { \
    while (node != NULL) { \
      compare_result = tpKeyCompareBy ( tpKeyPassBy##AOF key, \
        IGENA_AVL_NODE_GET_KEY(node, tpKeyType) ); \
      if (compare_result < 0) { \
        node = node->left; \
      } else if (compare_result > 0) { \
        node = node->right; \
      } else { \
        return node; \
      } \
    } \
    return NULL; \
  }} \
/********************************************************************/ \
  __IGENA_REQUIRE_SEMICOLON_OUTDOOR
