/*
  Copyright (c) 2018, Dmitry D. Chernov
*/

#define ZZ_GTSET_DEFINE_TYPE( tpSurname ) \
  typedef gtset_h gtset_##tpSurname##_h

/* Static approach. */

#define ZZ_GTSET_INSTANTIATE( tpTypeInfo, tpSurname, tpUseBy, tpCompareBy ) \
\
  ZGTSET_DEFINITIONS( ZGENA_APPROACH_STATIC, tpTypeInfo, tpSurname, tpUseBy, \
    tpUseBy, tpCompareBy, GENA_ASSIGN_NAIVE )

#define ZZ_GTSET_INSTANTIATE_EX( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy, \
  tpCompareBy, tpAssignBy ) \
\
  ZGTSET_DEFINITIONS( ZGENA_APPROACH_STATIC, tpTypeInfo, tpSurname, tpPassBy, \
    tpReturnBy, tpCompareBy, tpAssignBy )

/* Modular approach. */

#define ZZ_GTSET_H_DECLARE( tpTypeInfo, tpSurname, tpUseBy, tpCompareBy ) \
\
  ZGTSET_DECLARATIONS( tpTypeInfo, tpSurname, tpUseBy, tpUseBy )

#define ZZ_GTSET_C_DEFINE( tpTypeInfo, tpSurname, tpUseBy, tpCompareBy ) \
\
  ZGTSET_DEFINITIONS( ZGENA_APPROACH_MODULAR, tpTypeInfo, tpSurname, tpUseBy, \
    tpUseBy, tpCompareBy, GENA_ASSIGN_NAIVE )

#define ZZ_GTSET_H_DECLARE_EX( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy, \
  tpCompareBy, tpAssignBy ) \
\
  ZGTSET_DECLARATIONS( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy )

#define ZZ_GTSET_C_DEFINE_EX( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy, \
  tpCompareBy, tpAssignBy ) \
\
  ZGTSET_DEFINITIONS( ZGENA_APPROACH_MODULAR, tpTypeInfo, tpSurname, tpPassBy, \
    tpReturnBy, tpCompareBy, tpAssignBy )

/******************************************************************************/

#define ZGTSET_DECLARATIONS( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy ) \
\
  ZZ_GTSET_DEFINE_TYPE( tpSurname ); \
  ZZ_GTSET_DECLARATIONS_LIST( \
    tpSurname, \
    ZGENA_DATA_TYPE(tpTypeInfo, tpPassBy), \
    ZGENA_DATA_NAKED(tpTypeInfo, tpPassBy), \
    ZGENA_DATA_NAKED(tpTypeInfo, tpReturnBy) \
  ); \
  ZGENA_REQUIRE_SEMICOLON_OUTSIDE

/******************************************************************************/

#define ZGTSET_DEFINITIONS( tpApproach, tpTypeInfo, tpSurname, tpPassBy, \
  tpReturnBy, tpCompareBy, tpAssignBy ) \
\
  tpApproach ( ZZ_GTSET_DEFINE_TYPE( tpSurname ); ) \
  tpApproach ( static ) const gena_tag_z \
    gtset_##tpSurname##_tag = #tpSurname "_gtset"; \
  IGENA_AVL_TREE_INSTANTIATE( gtset, tpSurname, tpTypeInfo, tpPassBy, \
    tpCompareBy, tpAssignBy, 0 ); \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  gtset_##tpSurname##_h \
  gtset_##tpSurname##_new( \
    void \
  ) { \
  { \
    return igtset_new( \
      ZGENA_DATA_SIZE(tpTypeInfo, tpPassBy), \
      gtset_##tpSurname##_tag \
    ); \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  gena_bool \
  gtset_##tpSurname##_add( \
    gtset_##tpSurname##_h handle, \
    const ZGENA_DATA_NAKED(tpTypeInfo, tpPassBy) value, \
    gena_bool* OUT_key_exists \
  ) { \
    igena_avl_node_p new_node; \
    gena_bool key_exists; \
  { \
    assert( handle != NULL ); \
    new_node = igtset_avl_subtree_##tpSurname##_add( \
      &handle->tree_root, value, &key_exists, &handle->tree_leftmost, \
      &handle->tree_rightmost ); \
    if (!key_exists) { ++(handle->count); } \
    if (OUT_key_exists != NULL) { *OUT_key_exists = key_exists; } \
    return (new_node != NULL); \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  gena_bool \
  gtset_##tpSurname##_delete( \
    gtset_##tpSurname##_h handle, \
    const ZGENA_DATA_NAKED(tpTypeInfo, tpPassBy) value \
  ) { \
    gena_bool node_deleted; \
  { \
    assert( handle != NULL ); \
    node_deleted = igtset_avl_subtree_##tpSurname##_delete( \
      &handle->tree_root, value, &handle->tree_leftmost, \
      &handle->tree_rightmost ); \
    if (node_deleted) { --(handle->count); } \
    return node_deleted; \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  gena_bool \
  gtset_##tpSurname##_check( \
    gtset_##tpSurname##_h handle, \
    const ZGENA_DATA_NAKED(tpTypeInfo, tpPassBy) value \
  ) { \
    igena_avl_bias scan_bias; \
  { \
    assert( handle != NULL ); \
    scan_bias = igtset_avl_subtree_##tpSurname##_scan( \
      handle->tree_root, value, NULL ); \
    return (scan_bias == IGENA_AVL_BIAS_PARENT); \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  ZGENA_DATA_NAKED(tpTypeInfo, tpReturnBy) \
  gtset_##tpSurname##_first( \
    gtset_##tpSurname##_h handle \
  ) { \
    ZGENA_DATA_BIND( tpTypeInfo, tpPassBy, *entry ) = NULL; \
  { \
    assert( handle != NULL ); \
\
    if (handle->tree_leftmost != NULL) { \
      entry = IGENA_AVL_NODE_KEY( handle->tree_leftmost ); \
    } \
\
    ZGENA_DATA_VERIFY( tpReturnBy, entry ); \
    return tpReturnBy##OBTAIN entry; \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  ZGENA_DATA_NAKED(tpTypeInfo, tpReturnBy) \
  gtset_##tpSurname##_last( \
    gtset_##tpSurname##_h handle \
  ) { \
    ZGENA_DATA_BIND( tpTypeInfo, tpPassBy, *entry ) = NULL; \
  { \
    assert( handle != NULL ); \
\
    if (handle->tree_rightmost != NULL) { \
      entry = IGENA_AVL_NODE_KEY( handle->tree_rightmost ); \
    } \
\
    ZGENA_DATA_VERIFY( tpReturnBy, entry ); \
    return tpReturnBy##OBTAIN entry; \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  ZGENA_DATA_NAKED(tpTypeInfo, tpReturnBy) \
  gtset_##tpSurname##_value( \
    gena_iterator_p object, \
    ptrdiff_t offset \
  ) { \
    ZGENA_DATA_BIND( tpTypeInfo, tpPassBy, *value ); \
  { \
    assert( object != NULL ); \
    value = igena_iterator_entry( object, offset, NULL ); \
    ZGENA_DATA_VERIFY( tpReturnBy, value ); \
    return tpReturnBy##OBTAIN value; \
  }} \
/********************************************************************/ \
  ZGENA_REQUIRE_SEMICOLON_OUTSIDE
