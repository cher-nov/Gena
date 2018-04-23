/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

/* NOTE: tpPrefix is needed to prevent name collisions because different data
structures that use AVL-tree can be instantiated with the same name. */

#define ZZ_IGENA_AVL_TREE_INSTANTIATE( tpPrefix, tpSurname, tpKeyTypeInfo, \
  tpValueSize, tpKeyPassBy, tpKeyCompareBy, tpKeyAssignBy ) \
\
/********************************************************************/ \
  static \
  igena_avl_bias \
  i##tpPrefix##_avl_subtree_##tpSurname##_scan( \
    igena_avl_node_p root, \
    const ZGENA_ENTRY_VALUE(tpKeyTypeInfo, tpKeyPassBy) key, \
    igena_avl_node_p* OUT_final_node \
  ) { \
    igena_avl_node_p final_node = NULL; \
    igena_avl_bias link = IGENA_AVL_BIAS_SELF; \
    int compare; \
  { \
    while (root != NULL) { \
      compare = tpKeyCompareBy ( \
        tpKeyPassBy##ADDRESS key, \
        tpKeyPassBy##DATA ZGENA_ENTRY_DATA( tpKeyTypeInfo, tpKeyPassBy, \
          IGENA_AVL_NODE_KEY(root) ), \
        ZGENA_ENTRY_SIZE(tpKeyTypeInfo, tpKeyPassBy) \
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
  static \
  igena_avl_node_p \
  i##tpPrefix##_avl_subtree_##tpSurname##_add( \
    igena_avl_node_p* proot, \
    const ZGENA_ENTRY_VALUE(tpKeyTypeInfo, tpKeyPassBy) key, \
    gena_bool* OUT_key_exists \
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
      ZGENA_ENTRY_SIZE(tpKeyTypeInfo, tpKeyPassBy), \
      tpValueSize \
    ); \
\
    if (new_leaf == NULL) { return NULL; } \
\
    tpKeyAssignBy ( \
      tpKeyPassBy##DATA ZGENA_ENTRY_DATA( tpKeyTypeInfo, tpKeyPassBy, \
        IGENA_AVL_NODE_KEY(new_leaf) ), \
      tpKeyPassBy##ADDRESS key, \
      ZGENA_ENTRY_SIZE(tpKeyTypeInfo, tpKeyPassBy) \
    ); \
\
    new_root = igena_avl_node_attach( new_leaf, scan_node, scan_link ); \
    if (new_root != NULL) { *proot = new_root; } \
\
    return new_leaf; \
  }} \
/********************************************************************/ \
  static \
  gena_bool \
  i##tpPrefix##_avl_subtree_##tpSurname##_delete( \
    igena_avl_node_p* proot, \
    const ZGENA_ENTRY_VALUE(tpKeyTypeInfo, tpKeyPassBy) key \
  ) { \
    igena_avl_node_p scan_node, new_root; \
    igena_avl_bias scan_link; \
  { \
    scan_link = i##tpPrefix##_avl_subtree_##tpSurname##_scan( \
      *proot, key, &scan_node ); \
    if (scan_link != IGENA_AVL_BIAS_PARENT) { return GENA_FALSE; } \
\
    new_root = igena_avl_node_detach( scan_node ); \
    if (new_root != scan_node) { *proot = new_root; } \
    igena_avl_subtree_free( scan_node ); \
    return GENA_TRUE; \
  }} \
/********************************************************************/ \
  ZGENA_REQUIRE_SEMICOLON_OUTDOOR
