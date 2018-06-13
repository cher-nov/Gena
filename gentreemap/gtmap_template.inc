/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#define ZZ_GTMAP_DEFINE_TYPE( tpSurname ) \
  typedef gtmap_h gtmap_##tpSurname##_h

/* Static approach. */

#define ZZ_GTMAP_INSTANTIATE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
  tpKeyUseBy, tpValueUseBy, tpKeyCompareBy ) \
\
  ZGTMAP_DEFINITIONS( ZGENA_APPROACH_STATIC, tpKeyTypeInfo, tpValueTypeInfo, \
    tpSurname, tpKeyUseBy, tpKeyUseBy, tpValueUseBy, tpValueUseBy, \
    tpKeyCompareBy, GENA_ASSIGN_NAIVE, GENA_ASSIGN_NAIVE )

#define ZZ_GTMAP_INSTANTIATE_EX( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
  tpKeyPassBy, tpKeyReturnBy, tpValuePassBy, tpValueReturnBy, tpKeyCompareBy, \
  tpKeyAssignBy, tpValueAssignBy ) \
\
  ZGTMAP_DEFINITIONS( ZGENA_APPROACH_STATIC, tpKeyTypeInfo, tpValueTypeInfo, \
    tpSurname, tpKeyPassBy, tpKeyReturnBy, tpValuePassBy, tpValueReturnBy, \
    tpKeyCompareBy, tpKeyAssignBy, tpValueAssignBy )

/* Modular approach. */

#define ZZ_GTMAP_H_DECLARE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
  tpKeyUseBy, tpValueUseBy, tpKeyCompareBy ) \
\
  ZGTMAP_DECLARATIONS( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyUseBy, \
    tpKeyUseBy, tpValueUseBy, tpValueUseBy )

#define ZZ_GTMAP_C_DEFINE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
  tpKeyUseBy, tpValueUseBy, tpKeyCompareBy ) \
\
  ZGTMAP_DEFINITIONS( ZGENA_APPROACH_MODULAR, tpKeyTypeInfo, tpValueTypeInfo, \
    tpSurname, tpKeyUseBy, tpKeyUseBy, tpValueUseBy, tpValueUseBy, \
    tpKeyCompareBy, GENA_ASSIGN_NAIVE, GENA_ASSIGN_NAIVE )

#define ZZ_GTMAP_H_DECLARE_EX( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
  tpKeyPassBy, tpKeyReturnBy, tpValuePassBy, tpValueReturnBy, tpKeyCompareBy, \
  tpKeyAssignBy, tpValueAssignBy ) \
\
  ZGTMAP_DECLARATIONS( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyPassBy, \
    tpKeyReturnBy, tpValuePassBy, tpValueReturnBy )

#define ZZ_GTMAP_C_DEFINE_EX( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
  tpKeyPassBy, tpKeyReturnBy, tpValuePassBy, tpValueReturnBy, tpKeyCompareBy, \
  tpKeyAssignBy, tpValueAssignBy ) \
\
  ZGTMAP_DEFINITIONS( ZGENA_APPROACH_MODULAR, tpKeyTypeInfo, tpValueTypeInfo, \
    tpSurname, tpKeyPassBy, tpKeyReturnBy, tpValuePassBy, tpValueReturnBy, \
    tpKeyCompareBy, tpKeyAssignBy, tpValueAssignBy )

/******************************************************************************/

#define ZGTMAP_DECLARATIONS( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
  tpKeyPassBy, tpKeyReturnBy, tpValuePassBy, tpValueReturnBy ) \
\
  ZZ_GTMAP_DEFINE_TYPE( tpSurname ); \
  ZZ_GTMAP_DECLARATIONS_LIST( \
    tpSurname, \
    ZGENA_ENTRY_TYPE(tpKeyTypeInfo, tpKeyPassBy), \
    ZGENA_ENTRY_TYPE(tpValueTypeInfo, tpValuePassBy), \
    ZGENA_ENTRY_VALUE(tpKeyTypeInfo, tpKeyPassBy), \
    ZGENA_ENTRY_VALUE(tpKeyTypeInfo, tpKeyReturnBy), \
    ZGENA_ENTRY_VALUE(tpValueTypeInfo, tpValuePassBy), \
    ZGENA_ENTRY_VALUE(tpValueTypeInfo, tpValueReturnBy) \
  ); \
  ZGENA_REQUIRE_SEMICOLON_OUTDOOR

/******************************************************************************/

#define ZGTMAP_DEFINITIONS( tpApproach, tpKeyTypeInfo, tpValueTypeInfo, \
  tpSurname, tpKeyPassBy, tpKeyReturnBy, tpValuePassBy, tpValueReturnBy, \
  tpKeyCompareBy, tpKeyAssignBy, tpValueAssignBy ) \
\
  tpApproach ( ZZ_GTMAP_DEFINE_TYPE( tpSurname ); ) \
  tpApproach ( static ) const gena_tag_z \
    gtmap_##tpSurname##_tag = #tpSurname "_gtmap"; \
  IGENA_AVL_TREE_INSTANTIATE( gtmap, tpSurname, tpKeyTypeInfo, tpKeyPassBy, \
    tpKeyCompareBy, tpKeyAssignBy, \
    ZGENA_ENTRY_SIZE(tpValueTypeInfo, tpValuePassBy) ); \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  gtmap_##tpSurname##_h \
  gtmap_##tpSurname##_new( \
    void \
  ) { \
  { \
    return igtmap_new( \
      ZGENA_ENTRY_SIZE(tpKeyTypeInfo, tpKeyPassBy), \
      ZGENA_ENTRY_SIZE(tpValueTypeInfo, tpValuePassBy), \
      gtmap_##tpSurname##_tag \
    ); \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  ZGENA_ENTRY_TYPE(tpValueTypeInfo, tpValueReturnBy) * \
  gtmap_##tpSurname##_add( \
    gtmap_##tpSurname##_h handle, \
    const ZGENA_ENTRY_VALUE(tpKeyTypeInfo, tpKeyPassBy) key, \
    const ZGENA_ENTRY_VALUE(tpValueTypeInfo, tpValuePassBy) value \
  ) { \
    igena_avl_node_p new_node; \
    ZGENA_ENTRY_ENTITY( tpValueTypeInfo, tpValuePassBy, *node_value ); \
    gena_bool key_exists; \
  { \
    assert( handle != NULL ); \
\
    new_node = igtmap_avl_subtree_##tpSurname##_add( \
      &handle->tree_root, key, &key_exists, &handle->tree_leftmost, \
      &handle->tree_rightmost ); \
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
    return tpValueReturnBy##DATA node_value; \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  ZGENA_ENTRY_TYPE(tpValueTypeInfo, tpValueReturnBy) * \
  gtmap_##tpSurname##_put( \
    gtmap_##tpSurname##_h handle, \
    const ZGENA_ENTRY_VALUE(tpKeyTypeInfo, tpKeyPassBy) key, \
    const ZGENA_ENTRY_VALUE(tpValueTypeInfo, tpValuePassBy) value \
  ) { \
    igena_avl_node_p key_node; \
    ZGENA_ENTRY_ENTITY( tpValueTypeInfo, tpValuePassBy, *node_value ); \
    gena_bool key_exists; \
  { \
    assert( handle != NULL ); \
\
    key_node = igtmap_avl_subtree_##tpSurname##_add( \
      &handle->tree_root, key, &key_exists, &handle->tree_leftmost, \
      &handle->tree_rightmost ); \
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
    return tpValueReturnBy##DATA node_value; \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
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
      &handle->tree_root, key, &handle->tree_leftmost, \
      &handle->tree_rightmost ); \
    if (node_deleted) { --(handle->count); } \
    return node_deleted; \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  ZGENA_ENTRY_TYPE(tpValueTypeInfo, tpValueReturnBy) * \
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
    return tpValueReturnBy##DATA ZGENA_ENTRY_DATA( \
      tpValueTypeInfo, \
      tpValueReturnBy, \
      IGENA_AVL_NODE_VALUE( scan_node, \
        ZGENA_ENTRY_SIZE(tpKeyTypeInfo, tpKeyPassBy) ) \
    ); \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  ZGENA_ENTRY_VALUE(tpValueTypeInfo, tpValueReturnBy) \
  gtmap_##tpSurname##_first( \
    gtmap_##tpSurname##_h handle, \
    ZGENA_ENTRY_VALUE(tpKeyTypeInfo, tpKeyReturnBy) * OUT_key \
  ) { \
    ZGENA_ENTRY_ENTITY( tpValueTypeInfo, tpValuePassBy, *node_value ) = NULL; \
  { \
    assert( handle != NULL ); \
\
    if (handle->tree_leftmost != NULL) { \
      node_value = IGENA_AVL_NODE_VALUE( \
        handle->tree_leftmost, \
        ZGENA_ENTRY_SIZE(tpKeyTypeInfo, tpKeyPassBy) \
      ); \
    } \
\
    if ( (OUT_key != NULL) && (node_value != NULL) ) { \
      *OUT_key = tpKeyReturnBy##VALUE ZGENA_ENTRY_DATA( \
        tpKeyTypeInfo, \
        tpKeyReturnBy, \
        IGENA_AVL_NODE_KEY( handle->tree_leftmost ) \
      ); \
    } \
\
    return tpValueReturnBy##VALUE node_value; \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  ZGENA_ENTRY_VALUE(tpValueTypeInfo, tpValueReturnBy) \
  gtmap_##tpSurname##_last( \
    gtmap_##tpSurname##_h handle, \
    ZGENA_ENTRY_VALUE(tpKeyTypeInfo, tpKeyReturnBy) * OUT_key \
  ) { \
    ZGENA_ENTRY_ENTITY( tpValueTypeInfo, tpValuePassBy, *node_value ) = NULL; \
  { \
    assert( handle != NULL ); \
\
    if (handle->tree_rightmost != NULL) { \
      node_value = IGENA_AVL_NODE_VALUE( \
        handle->tree_rightmost, \
        ZGENA_ENTRY_SIZE(tpKeyTypeInfo, tpKeyPassBy) \
      ); \
    } \
\
    if ( (OUT_key != NULL) && (node_value != NULL) ) { \
      *OUT_key = tpKeyReturnBy##VALUE ZGENA_ENTRY_DATA( \
        tpKeyTypeInfo, \
        tpKeyReturnBy, \
        IGENA_AVL_NODE_KEY( handle->tree_rightmost ) \
      ); \
    } \
\
    return tpValueReturnBy##VALUE node_value; \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  ZGENA_ENTRY_VALUE(tpKeyTypeInfo, tpKeyReturnBy) \
  gtmap_##tpSurname##_key( \
    gena_iterator_p object, \
    ptrdiff_t offset \
  ) { \
    void* key = NULL; \
  { \
    assert( object != NULL ); \
    igena_iterator_entry( object, offset, &key ); \
    return tpKeyReturnBy##VALUE ZGENA_ENTRY_DATA( \
      tpKeyTypeInfo, \
      tpKeyReturnBy, \
      key \
    ); \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  ZGENA_ENTRY_VALUE(tpValueTypeInfo, tpValueReturnBy) \
  gtmap_##tpSurname##_value( \
    gena_iterator_p object, \
    ptrdiff_t offset \
  ) { \
  { \
    assert( object != NULL ); \
    return tpValueReturnBy##VALUE ZGENA_ENTRY_DATA( \
      tpValueTypeInfo, \
      tpValueReturnBy, \
      igena_iterator_entry( object, offset, NULL ) \
    ); \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  ZGENA_ENTRY_VALUE(tpValueTypeInfo, tpValueReturnBy) \
  gtmap_##tpSurname##_entry( \
    gena_iterator_p object, \
    ptrdiff_t offset, \
    ZGENA_ENTRY_VALUE(tpKeyTypeInfo, tpKeyReturnBy) * OUT_key \
  ) { \
    void *key = NULL, *value; \
  { \
    assert( object != NULL ); \
\
    value = igena_iterator_entry( object, offset, &key ); \
    if (OUT_key != NULL) { \
      *OUT_key = tpKeyReturnBy##VALUE ZGENA_ENTRY_DATA( \
        tpKeyTypeInfo, \
        tpKeyReturnBy, \
        key \
      ); \
    } \
\
    return tpValueReturnBy##VALUE ZGENA_ENTRY_DATA( \
      tpValueTypeInfo, \
      tpValueReturnBy, \
      value \
    ); \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  ZGENA_ENTRY_TYPE(tpValueTypeInfo, tpValueReturnBy) * \
  gtmap_##tpSurname##_emplace( \
    gena_iterator_p object, \
    ptrdiff_t offset, \
    const ZGENA_ENTRY_VALUE(tpValueTypeInfo, tpValuePassBy) value \
  ) { \
    ZGENA_ENTRY_ENTITY( tpValueTypeInfo, tpValuePassBy, *entry ); \
  { \
    assert( object != NULL ); \
\
    entry = igena_iterator_entry( object, offset, NULL ); \
    if (entry == NULL) { return NULL; } \
    tpValueAssignBy ( \
      tpValuePassBy##DATA entry, \
      tpValuePassBy##ADDRESS value, \
      ZGENA_ENTRY_SIZE(tpValueTypeInfo, tpValuePassBy) \
    ); \
\
    return tpValueReturnBy##DATA entry; \
  }} \
/********************************************************************/ \
  ZGENA_REQUIRE_SEMICOLON_OUTDOOR
