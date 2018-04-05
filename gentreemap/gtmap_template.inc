/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#include <assert.h>

/*
  ZZ_GTMAP_FUNC_ONCE is necessary to prevent multiple declarations if the main
  header was included more than once.
  ZZ_GTMAP_DEFINE_TYPE needed to prevent typedef redefinition with modular
  approach.
*/

#ifndef GTMAP_MODULAR_APPROACH

  #define ZZ_GTMAP_FUNC_ONCE static GENA_INLINE

  #define ZZ_GTMAP_DEFINE_TYPE( tpMapName ) \
    typedef gtmap_h gtmap_##tpMapName##_h

  #define ZZ_GTMAP_INSTANTIATE( tpKeyType, tpValueType, tpMapName, \
    tpKeyCompareBy, tpKeyPassBy, tpValuePassBy ) \
\
    ZGTMAP_C_DEFINE( tpKeyType, tpValueType, tpMapName, GENA_ASSIGN_NAIVE, \
      GENA_ASSIGN_NAIVE, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy )

  #define ZZ_GTMAP_INSTANTIATE_EX( tpKeyType, tpValueType, tpMapName, \
    tpKeyAssignBy, tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, \
    tpValuePassBy ) \
\
    ZGTMAP_C_DEFINE( tpKeyType, tpValueType, tpMapName, tpKeyAssignBy, \
      tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy )

#else /* GTMAP_MODULAR_APPROACH */

  #define ZZ_GTMAP_FUNC_ONCE

  #define ZZ_GTMAP_DEFINE_TYPE( tpMapName ) \
    ZGENA_REQUIRE_SEMICOLON_OUTDOOR

  #define ZZ_GTMAP_C_DEFINE( tpKeyType, tpValueType, tpMapName, \
    tpKeyCompareBy, tpKeyPassBy, tpValuePassBy ) \
\
    ZGTMAP_C_DEFINE( tpKeyType, tpValueType, tpMapName, GENA_ASSIGN_NAIVE, \
      GENA_ASSIGN_NAIVE, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy )

  #define ZZ_GTMAP_C_DEFINE_EX( tpKeyType, tpValueType, tpMapName, \
    tpKeyAssignBy, tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, \
    tpValuePassBy ) \
\
    ZGTMAP_C_DEFINE( tpKeyType, tpValueType, tpMapName, tpKeyAssignBy, \
      tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy )

  #define ZZ_GTMAP_H_DECLARE( tpKeyType, tpValueType, tpMapName, \
    tpKeyCompareBy, tpKeyPassBy, tpValuePassBy ) \
\
    ZGTMAP_H_DECLARE( tpKeyType, tpValueType, tpMapName, tpKeyPassBy, \
      tpValuePassBy )

  #define ZZ_GTMAP_H_DECLARE_EX( tpKeyType, tpValueType, tpMapName, \
    tpKeyAssignBy, tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, \
    tpValuePassBy ) \
\
    ZGTMAP_H_DECLARE( tpKeyType, tpValueType, tpMapName, tpKeyPassBy, \
      tpValuePassBy )

#endif /* GTMAP_MODULAR_APPROACH */

/******************************************************************************/

#define ZGTMAP_H_DECLARE( tpKeyType, tpValueType, tpMapName, tpKeyPassBy, \
  tpValuePassBy ) \
\
  typedef gtmap_h gtmap_##tpMapName##_h; \
\
  extern \
  gtmap_##tpMapName##_h \
  gtmap_##tpMapName##_new( \
    void \
  ); \
\
  extern \
  ZGENA_TYPEINFO_NAME(tpValueType, tpValuePassBy) * \
  gtmap_##tpMapName##_add( \
    gtmap_##tpMapName##_h handle, \
    const ZGENA_TYPEINFO_USERTYPE(tpKeyType, tpKeyPassBy) key, \
    const ZGENA_TYPEINFO_USERTYPE(tpValueType, tpValuePassBy) value \
  ); \
\
  extern \
  gena_bool \
  gtmap_##tpMapName##_delete( \
    gtmap_##tpMapName##_h handle, \
    const ZGENA_TYPEINFO_USERTYPE(tpKeyType, tpKeyPassBy) key \
  ); \
\
  extern \
  ZGENA_TYPEINFO_NAME(tpValueType, tpValuePassBy) * \
  gtmap_##tpMapName##_find( \
    gtmap_##tpMapName##_h handle, \
    const ZGENA_TYPEINFO_USERTYPE(tpKeyType, tpKeyPassBy) key \
  ); \
\
  ZGENA_REQUIRE_SEMICOLON_OUTDOOR

/******************************************************************************/

#define ZGTMAP_C_DEFINE( tpKeyType, tpValueType, tpMapName, tpKeyAssignBy, \
  tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy ) \
\
  ZZ_GTMAP_DEFINE_TYPE( tpMapName ); \
  IGENA_AVL_SUBTREE_INSTANTIATE( gtmap, tpMapName, tpKeyType, \
    ZGENA_TYPEINFO_SIZE(tpValueType, tpValuePassBy), tpKeyAssignBy, \
    tpKeyCompareBy, tpKeyPassBy ); \
/********************************************************************/ \
  ZZ_GTMAP_FUNC_ONCE \
  gtmap_##tpMapName##_h \
  gtmap_##tpMapName##_new( \
    void \
  ) { \
  { \
    return igtmap_new( \
      ZGENA_TYPEINFO_SIZE(tpKeyType, tpKeyPassBy), \
      ZGENA_TYPEINFO_SIZE(tpValueType, tpValuePassBy) \
    ); \
  }} \
/********************************************************************/ \
  ZZ_GTMAP_FUNC_ONCE \
  ZGENA_TYPEINFO_NAME(tpValueType, tpValuePassBy) * \
  gtmap_##tpMapName##_add( \
    gtmap_##tpMapName##_h handle, \
    const ZGENA_TYPEINFO_USERTYPE(tpKeyType, tpKeyPassBy) key, \
    const ZGENA_TYPEINFO_USERTYPE(tpValueType, tpValuePassBy) value \
  ) { \
    igena_avl_retstate_e retstate; \
    igena_avl_node_head_p final_node; \
    ZGENA_TYPEINFO_NAME(tpValueType, tpValuePassBy) * node_value; \
  { \
    assert( handle != NULL ); \
    retstate = igtmap_avl_subtree_##tpMapName##_add_key( \
      &handle->avltree_root, key, &final_node ); \
    if (final_node == NULL) { return NULL; } \
    node_value = IGENA_AVL_NODE_GET_VALUE( \
      final_node, \
      ZGENA_TYPEINFO_SIZE(tpKeyType, tpKeyPassBy) \
    ); \
    if (retstate != IGENA_AVL_RETST_NOTHING) { \
      tpValueAssignBy ( \
        node_value, \
        tpValuePassBy##REFERENCE value, \
        ZGENA_TYPEINFO_SIZE(tpValueType, tpValuePassBy) \
      ); \
      ++(handle->count); \
    } \
    return node_value; \
  }} \
/********************************************************************/ \
  ZZ_GTMAP_FUNC_ONCE \
  gena_bool \
  gtmap_##tpMapName##_delete( \
    gtmap_##tpMapName##_h handle, \
    const ZGENA_TYPEINFO_USERTYPE(tpKeyType, tpKeyPassBy) key \
  ) { \
    igena_avl_retstate_e retstate; \
  { \
    assert( handle != NULL ); \
    retstate = igtmap_avl_subtree_##tpMapName##_delete_key( \
      &handle->avltree_root, key ); \
    if (retstate == IGENA_AVL_RETST_NOTHING) { return GENA_FALSE; } \
    --(handle->count); \
    return GENA_TRUE; \
  }} \
/********************************************************************/ \
  ZZ_GTMAP_FUNC_ONCE \
  ZGENA_TYPEINFO_NAME(tpValueType, tpValuePassBy) * \
  gtmap_##tpMapName##_find( \
    gtmap_##tpMapName##_h handle, \
    const ZGENA_TYPEINFO_USERTYPE(tpKeyType, tpKeyPassBy) key \
  ) { \
    igena_avl_node_head_p find_node; \
  { \
    assert( handle != NULL ); \
    find_node = igtmap_avl_subtree_##tpMapName##_find_node( \
      handle->avltree_root, key ); \
    return (find_node == NULL) ? NULL : IGENA_AVL_NODE_GET_VALUE( \
      find_node, \
      ZGENA_TYPEINFO_SIZE(tpKeyType, tpKeyPassBy) \
    ); \
  }} \
/********************************************************************/ \
  ZGENA_REQUIRE_SEMICOLON_OUTDOOR
