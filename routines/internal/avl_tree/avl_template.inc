/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

/* NOTE: tpPrefix is needed to prevent name collisions because different data
structures that use AVL-tree can be instantiated with the same name. */

#define ZZ_IGENA_AVL_TREE_INSTANTIATE( tpPrefix, tpSurname, tpKeyTypeInfo, \
  tpKeyPassBy, tpKeyCompareBy, tpKeyAssignBy, tpValueSize ) \
\
/********************************************************************/ \
  ZGENA_STATIC_APPROACH_FUNCTION \
  igena_avl_bias \
  i##tpPrefix##_avl_subtree_##tpSurname##_scan( \
    igena_avl_node_p root, \
    const ZGENA_DATA_NAKED(tpKeyTypeInfo, tpKeyPassBy) key, \
    igena_avl_node_p* OUT_final_node \
  ) { \
    igena_avl_node_p final_node = NULL; \
    igena_avl_bias link = IGENA_AVL_BIAS_SELF; \
    int compare; \
  { \
    while (root != NULL) { \
      compare = tpKeyCompareBy ( \
        tpKeyPassBy##REFER key, \
        tpKeyPassBy##ACCESS ZGENA_DATA_CAST( tpKeyTypeInfo, tpKeyPassBy, \
          IGENA_AVL_NODE_KEY(root) ), \
        ZGENA_DATA_SIZE(tpKeyTypeInfo, tpKeyPassBy) \
      ); \
      final_node = root; \
      if (compare == 0) { \
        link = IGENA_AVL_BIAS_PARENT; \
        root = NULL; \
      } else { \
        link = (compare < 0) ? IGENA_AVL_BIAS_LEFT : IGENA_AVL_BIAS_RIGHT; \
        root = IGENA_AVL_NODE_LINK( root, link ); \
      } \
    } \
    if (OUT_final_node != NULL) { *OUT_final_node = final_node; } \
    return link; \
  }} \
/********************************************************************/ \
  ZGENA_STATIC_APPROACH_FUNCTION \
  igena_avl_node_p \
  i##tpPrefix##_avl_subtree_##tpSurname##_add( \
    igena_avl_node_p* proot, \
    const ZGENA_DATA_NAKED(tpKeyTypeInfo, tpKeyPassBy) key, \
    gena_bool* OUT_key_exists, \
    igena_avl_node_p* OUT_leftmost, \
    igena_avl_node_p* OUT_rightmost \
  ) { \
    igena_avl_node_p scan_node, new_root, new_leaf; \
    igena_avl_bias scan_link; \
    gena_bool key_exists; \
  { \
    scan_link = i##tpPrefix##_avl_subtree_##tpSurname##_scan( \
      *proot, key, &scan_node ); \
    key_exists = (scan_link == IGENA_AVL_BIAS_PARENT); \
    if (OUT_key_exists != NULL) { *OUT_key_exists = key_exists; } \
    if (key_exists) { return scan_node; } \
\
    new_leaf = igena_avl_node_create( \
      ZGENA_DATA_SIZE(tpKeyTypeInfo, tpKeyPassBy) + tpValueSize \
    ); \
\
    if (new_leaf == NULL) { return NULL; } \
\
    tpKeyAssignBy ( \
      tpKeyPassBy##ACCESS ZGENA_DATA_CAST( tpKeyTypeInfo, tpKeyPassBy, \
        IGENA_AVL_NODE_KEY(new_leaf) ), \
      tpKeyPassBy##REFER key, \
      ZGENA_DATA_SIZE(tpKeyTypeInfo, tpKeyPassBy) \
    ); \
\
    new_root = igena_avl_node_attach( new_leaf, scan_node, scan_link ); \
    if (new_root != NULL) { *proot = new_root; } \
\
    if ( (OUT_leftmost != NULL) && (scan_link != IGENA_AVL_BIAS_RIGHT) ) { \
      if (scan_node == *OUT_leftmost) { *OUT_leftmost = new_leaf; } \
    } \
\
    if ( (OUT_rightmost != NULL) && (scan_link != IGENA_AVL_BIAS_LEFT) ) { \
      if (scan_node == *OUT_rightmost) { *OUT_rightmost = new_leaf; } \
    } \
\
    return new_leaf; \
  }} \
/********************************************************************/ \
  ZGENA_STATIC_APPROACH_FUNCTION \
  gena_bool \
  i##tpPrefix##_avl_subtree_##tpSurname##_delete( \
    igena_avl_node_p* proot, \
    const ZGENA_DATA_NAKED(tpKeyTypeInfo, tpKeyPassBy) key, \
    igena_avl_node_p* OUT_leftmost, \
    igena_avl_node_p* OUT_rightmost \
  ) { \
    igena_avl_node_p scan_node, ancestor, new_root; \
    igena_avl_bias scan_link; \
  { \
    scan_link = i##tpPrefix##_avl_subtree_##tpSurname##_scan( \
      *proot, key, &scan_node ); \
    if (scan_link != IGENA_AVL_BIAS_PARENT) { return GENA_FALSE; } \
\
    ancestor = scan_node->parent; \
    new_root = igena_avl_node_detach( scan_node ); \
    if (new_root != scan_node) { *proot = new_root; } \
\
    if (OUT_leftmost != NULL) { \
      if (scan_node == *OUT_leftmost) { \
        *OUT_leftmost = (ancestor == NULL) \
          ? new_root \
          : ( (ancestor->left == NULL) ? ancestor : ancestor->left ); \
      } \
    } \
\
    if (OUT_rightmost != NULL) { \
      if (scan_node == *OUT_rightmost) { \
        *OUT_rightmost = (ancestor == NULL) \
          ? new_root \
          : ( (ancestor->right == NULL) ? ancestor : ancestor->right ); \
      } \
    } \
\
    igena_avl_subtree_free( scan_node ); \
    return GENA_TRUE; \
  }} \
/********************************************************************/ \
  ZGENA_REQUIRE_SEMICOLON_OUTSIDE
