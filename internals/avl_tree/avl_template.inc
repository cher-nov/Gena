/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#include <string.h>

#define IGENA_AVL_SUBTREE_INSTANTIATE( tpPrefix, tpTreeName, tpKeyType, \
  tpValueSize, tpKeyAssignBy, tpKeyCompareBy, tpKeyPassBy ) \
\
  ZZ_IGENA_AVL_SUBTREE_INSTANTIATE( tpPrefix, tpTreeName, tpKeyType, \
    tpValueSize, tpKeyAssignBy, tpKeyCompareBy, tpKeyPassBy )

/******************************************************************************/

/* NOTE: tpPrefix is needed to prevent name collisions because different data
structures that use AVL-tree can be instantiated with same names. */

#define ZZ_IGENA_AVL_SUBTREE_INSTANTIATE( tpPrefix, tpTreeName, tpKeyType, \
  tpValueSize, tpKeyAssignBy, tpKeyCompareBy, tpKeyPassBy ) \
\
/********************************************************************/ \
  static \
  igena_avl_retstate_e \
  i##tpPrefix##_avl_subtree_##tpTreeName##_add_key( \
    igena_avl_node_head_p* pnode, \
    const ZGENA_TYPEINFO_USERTYPE(tpKeyType, tpKeyPassBy) key, \
    igena_avl_node_head_p* OUT_final_node \
  ) { \
    igena_avl_retstate_e retstate; \
    igena_avl_node_head_p new_node; \
    int compare_result; \
  { \
    if (*pnode == NULL) { \
      new_node = igena_avl_node_create( \
        ZGENA_TYPEINFO_SIZE(tpKeyType, tpKeyPassBy), \
        tpValueSize \
      ); \
      if (new_node != NULL) { \
        tpKeyAssignBy ( \
          ( ZGENA_TYPEINFO_NAME(tpKeyType, tpKeyPassBy) * ) \
            IGENA_AVL_NODE_GET_KEY(new_node), \
          tpKeyPassBy##REFERENCE key, \
          ZGENA_TYPEINFO_SIZE(tpKeyType, tpKeyPassBy) \
        ); \
        *pnode = new_node; \
      } \
\
      if (OUT_final_node != NULL) { *OUT_final_node = new_node; } \
      return (new_node != NULL) \
             ? IGENA_AVL_RETST_BALANCE \
             : IGENA_AVL_RETST_NOTHING; \
    } \
\
    compare_result = tpKeyCompareBy ( \
      ( ZGENA_TYPEINFO_NAME(tpKeyType, tpKeyPassBy) * ) \
        IGENA_AVL_NODE_GET_KEY(*pnode), \
      tpKeyPassBy##REFERENCE key, \
      ZGENA_TYPEINFO_SIZE(tpKeyType, tpKeyPassBy) \
    ); \
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
  static \
  igena_avl_retstate_e \
  i##tpPrefix##_avl_subtree_##tpTreeName##_delete_key( \
    igena_avl_node_head_p* pnode, \
    const ZGENA_TYPEINFO_USERTYPE(tpKeyType, tpKeyPassBy) key \
  ) { \
    igena_avl_retstate_e retstate; \
    int compare_result; \
    gena_bool can_balance = GENA_TRUE; \
  { \
    if (*pnode == NULL) { return IGENA_AVL_RETST_NOTHING; } \
\
    compare_result = tpKeyCompareBy ( \
      ( ZGENA_TYPEINFO_NAME(tpKeyType, tpKeyPassBy) * ) \
        IGENA_AVL_NODE_GET_KEY(*pnode), \
      tpKeyPassBy##REFERENCE key, \
      ZGENA_TYPEINFO_SIZE(tpKeyType, tpKeyPassBy) \
    ); \
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
    const ZGENA_TYPEINFO_USERTYPE(tpKeyType, tpKeyPassBy) key \
  ) { \
    int compare_result; \
  { \
    while (node != NULL) { \
      compare_result = tpKeyCompareBy ( \
        ( ZGENA_TYPEINFO_NAME(tpKeyType, tpKeyPassBy) * ) \
          IGENA_AVL_NODE_GET_KEY(node), \
        tpKeyPassBy##REFERENCE key, \
        ZGENA_TYPEINFO_SIZE(tpKeyType, tpKeyPassBy) \
      ); \
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
  ZGENA_REQUIRE_SEMICOLON_OUTDOOR
