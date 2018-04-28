/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

/*
  ZZ_GTMAP_FUNC_ONCE is necessary to prevent multiple declarations if the
  main header was included more than once.
  ZZ_GTMAP_STATIC_TYPEDEF is needed to prevent typedef redefinition with
  modular approach.
*/

#define ZZ_GTMAP_DEFINE_TYPE( tpSurname ) \
  typedef gtmap_h gtmap_##tpSurname##_h

#ifndef GTMAP_MODULAR_APPROACH

  #define ZZ_GTMAP_FUNC_ONCE static GENA_INLINE

  #define ZZ_GTMAP_STATIC_TYPEDEF( tpSurname ) \
    ZZ_GTMAP_DEFINE_TYPE( tpSurname )

  #define ZZ_GTMAP_INSTANTIATE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
    tpKeyPassBy, tpValuePassBy, tpKeyCompareBy ) \
\
    ZGTMAP_C_DEFINE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
      tpKeyPassBy, tpValuePassBy, tpKeyCompareBy, GENA_ASSIGN_NAIVE, \
      GENA_ASSIGN_NAIVE )

  #define ZZ_GTMAP_INSTANTIATE_EX( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
    tpKeyPassBy, tpValuePassBy, tpKeyCompareBy, tpKeyAssignBy, \
    tpValueAssignBy ) \
\
    ZGTMAP_C_DEFINE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyPassBy, \
      tpValuePassBy, tpKeyCompareBy, tpKeyAssignBy, tpValueAssignBy )

#else /* GTMAP_MODULAR_APPROACH */

  #define ZZ_GTMAP_FUNC_ONCE

  #define ZZ_GTMAP_STATIC_TYPEDEF( tpSurname ) \
    ZGENA_REQUIRE_SEMICOLON_OUTDOOR

  #define ZZ_GTMAP_C_DEFINE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
    tpKeyPassBy, tpValuePassBy, tpKeyCompareBy ) \
\
    ZGTMAP_C_DEFINE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
      tpKeyPassBy, tpValuePassBy, tpKeyCompareBy, GENA_ASSIGN_NAIVE, \
      GENA_ASSIGN_NAIVE )

  #define ZZ_GTMAP_C_DEFINE_EX( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
    tpKeyPassBy, tpValuePassBy, tpKeyCompareBy, tpKeyAssignBy, \
    tpValueAssignBy ) \
\
    ZGTMAP_C_DEFINE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyPassBy, \
      tpValuePassBy, tpKeyCompareBy, tpKeyAssignBy, tpValueAssignBy )

  #define ZZ_GTMAP_H_DECLARE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
    tpKeyPassBy, tpValuePassBy, tpKeyCompareBy ) \
\
    ZGTMAP_H_DECLARE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyPassBy, \
      tpValuePassBy )

  #define ZZ_GTMAP_H_DECLARE_EX( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
    tpKeyPassBy, tpValuePassBy, tpKeyCompareBy, tpKeyAssignBy, \
    tpValueAssignBy ) \
\
    ZGTMAP_H_DECLARE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyPassBy, \
      tpValuePassBy )

#endif /* GTMAP_MODULAR_APPROACH */

/******************************************************************************/

#define ZGTMAP_H_DECLARE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
  tpKeyPassBy, tpValuePassBy ) \
\
  ZZ_GTMAP_DEFINE_TYPE( tpSurname ); \
  ZZ_GTMAP_FUNCTIONS_LIST( \
    tpSurname, \
    ZGENA_ENTRY_TYPE(tpValueTypeInfo, tpValuePassBy), \
    ZGENA_ENTRY_VALUE(tpKeyTypeInfo, tpKeyPassBy), \
    ZGENA_ENTRY_VALUE(tpValueTypeInfo, tpValuePassBy) \
  ); \
  ZGENA_REQUIRE_SEMICOLON_OUTDOOR

/******************************************************************************/

#define ZGTMAP_C_DEFINE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
  tpKeyPassBy, tpValuePassBy, tpKeyCompareBy, tpKeyAssignBy, tpValueAssignBy ) \
\
  ZZ_GTMAP_STATIC_TYPEDEF( tpSurname ); \
  IGENA_AVL_TREE_INSTANTIATE( gtmap, tpSurname, tpKeyTypeInfo, \
    ZGENA_ENTRY_SIZE(tpValueTypeInfo, tpValuePassBy), tpKeyPassBy, \
    tpKeyCompareBy, tpKeyAssignBy ); \
/********************************************************************/ \
  ZZ_GTMAP_FUNC_ONCE \
  gtmap_##tpSurname##_h \
  gtmap_##tpSurname##_new( \
    void \
  ) { \
  { \
    return igtmap_new( \
      ZGENA_ENTRY_SIZE(tpKeyTypeInfo, tpKeyPassBy), \
      ZGENA_ENTRY_SIZE(tpValueTypeInfo, tpValuePassBy) \
    ); \
  }} \
/********************************************************************/ \
  ZZ_GTMAP_FUNC_ONCE \
  ZGENA_ENTRY_TYPE(tpValueTypeInfo, tpValuePassBy) * \
  gtmap_##tpSurname##_add( \
    gtmap_##tpSurname##_h handle, \
    const ZGENA_ENTRY_VALUE(tpKeyTypeInfo, tpKeyPassBy) key, \
    const ZGENA_ENTRY_VALUE(tpValueTypeInfo, tpValuePassBy) value \
  ) { \
    igena_avl_node_p new_node; \
    ZGENA_ENTRY_OBJECT( tpValueTypeInfo, tpValuePassBy, *node_value ); \
    gena_bool key_exists; \
  { \
    assert( handle != NULL ); \
\
    new_node = igtmap_avl_subtree_##tpSurname##_add( \
      &handle->tree_root, key, &key_exists ); \
    if (new_node == NULL) { return NULL; } \
\
    node_value = IGENA_AVL_NODE_VALUE( \
      new_node, \
      ZGENA_ENTRY_SIZE(tpKeyTypeInfo, tpKeyPassBy) \
    ); \
\
    if (!key_exists) { \
      tpValueAssignBy ( \
        tpValuePassBy##DATA node_value, \
        tpValuePassBy##ADDRESS value, \
        ZGENA_ENTRY_SIZE(tpValueTypeInfo, tpValuePassBy) \
      ); \
      ++(handle->count); \
    } \
\
    return tpValuePassBy##DATA node_value; \
  }} \
/********************************************************************/ \
  ZZ_GTMAP_FUNC_ONCE \
  ZGENA_ENTRY_TYPE(tpValueTypeInfo, tpValuePassBy) * \
  gtmap_##tpSurname##_put( \
    gtmap_##tpSurname##_h handle, \
    const ZGENA_ENTRY_VALUE(tpKeyTypeInfo, tpKeyPassBy) key, \
    const ZGENA_ENTRY_VALUE(tpValueTypeInfo, tpValuePassBy) value \
  ) { \
    igena_avl_node_p key_node; \
    ZGENA_ENTRY_OBJECT( tpValueTypeInfo, tpValuePassBy, *node_value ); \
    gena_bool key_exists; \
  { \
    assert( handle != NULL ); \
\
    key_node = igtmap_avl_subtree_##tpSurname##_add( \
      &handle->tree_root, key, &key_exists ); \
    if (key_node == NULL) { return NULL; } \
\
    node_value = IGENA_AVL_NODE_VALUE( \
      key_node, \
      ZGENA_ENTRY_SIZE(tpKeyTypeInfo, tpKeyPassBy) \
    ); \
\
    tpValueAssignBy ( \
      tpValuePassBy##DATA node_value, \
      tpValuePassBy##ADDRESS value, \
      ZGENA_ENTRY_SIZE(tpValueTypeInfo, tpValuePassBy) \
    ); \
\
    if (!key_exists) { ++(handle->count); } \
    return tpValuePassBy##DATA node_value; \
  }} \
/********************************************************************/ \
  ZZ_GTMAP_FUNC_ONCE \
  gena_bool \
  gtmap_##tpSurname##_delete( \
    gtmap_##tpSurname##_h handle, \
    const ZGENA_ENTRY_VALUE(tpKeyTypeInfo, tpKeyPassBy) key \
  ) { \
    gena_bool node_deleted; \
  { \
    assert( handle != NULL ); \
\
    node_deleted = igtmap_avl_subtree_##tpSurname##_delete( \
      &handle->tree_root, key ); \
    if (node_deleted) { --(handle->count); } \
    return node_deleted; \
  }} \
/********************************************************************/ \
  ZZ_GTMAP_FUNC_ONCE \
  ZGENA_ENTRY_TYPE(tpValueTypeInfo, tpValuePassBy) * \
  gtmap_##tpSurname##_find( \
    gtmap_##tpSurname##_h handle, \
    const ZGENA_ENTRY_VALUE(tpKeyTypeInfo, tpKeyPassBy) key \
  ) { \
    igena_avl_node_p scan_node; \
    igena_avl_bias scan_bias; \
  { \
    assert( handle != NULL ); \
\
    scan_bias = igtmap_avl_subtree_##tpSurname##_scan( \
      handle->tree_root, key, &scan_node ); \
    if (scan_bias != IGENA_AVL_BIAS_PARENT) { return NULL; } \
\
    return tpValuePassBy##DATA ZGENA_ENTRY_DATA( \
      tpValueTypeInfo, \
      tpValuePassBy, \
      IGENA_AVL_NODE_VALUE( scan_node, \
        ZGENA_ENTRY_SIZE(tpKeyTypeInfo, tpKeyPassBy) ) \
    ); \
  }} \
/********************************************************************/ \
  ZGENA_REQUIRE_SEMICOLON_OUTDOOR
