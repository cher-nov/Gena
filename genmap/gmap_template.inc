/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#include <assert.h>

/*
  ZZ_GMAP_FUNC_ONCE is necessary to prevent multiple declarations if the main
  header was included more than once.
  ZZ_GMAP_DEFINE_TYPE needed to prevent typedef redefinition with modular
  approach.
*/

#ifndef GMAP_MODULAR_APPROACH

  #define ZZ_GMAP_FUNC_ONCE static GENA_INLINE

  #define ZZ_GMAP_DEFINE_TYPE( tpMapName ) \
    typedef gmap_h gmap_##tpMapName##_h

  #define ZZ_GMAP_INSTANTIATE( tpKeyType, tpValueType, tpMapName, \
    tpKeyCompareBy, tpKeyPassBy, tpValuePassBy ) \
\
    ZGMAP_C_DEFINE( tpKeyType, tpValueType, tpMapName, GENA_ASSIGN_NAIVE, \
      GENA_ASSIGN_NAIVE, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy )

  #define ZZ_GMAP_INSTANTIATE_EX( tpKeyType, tpValueType, tpMapName, \
    tpKeyAssignBy, tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, \
    tpValuePassBy ) \
\
    ZGMAP_C_DEFINE( tpKeyType, tpValueType, tpMapName, tpKeyAssignBy, \
      tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy )

#else /* GMAP_MODULAR_APPROACH */

  #define ZZ_GMAP_FUNC_ONCE

  #define ZZ_GMAP_DEFINE_TYPE( tpMapName ) \
    ZGENA_REQUIRE_SEMICOLON_OUTDOOR

  #define ZZ_GMAP_C_DEFINE( tpKeyType, tpValueType, tpMapName, tpKeyCompareBy, \
    tpKeyPassBy, tpValuePassBy ) \
\
    ZGMAP_C_DEFINE( tpKeyType, tpValueType, tpMapName, GENA_ASSIGN_NAIVE, \
      GENA_ASSIGN_NAIVE, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy )

  #define ZZ_GMAP_C_DEFINE_EX( tpKeyType, tpValueType, tpMapName, \
    tpKeyAssignBy, tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, \
    tpValuePassBy ) \
\
    ZGMAP_C_DEFINE( tpKeyType, tpValueType, tpMapName, tpKeyAssignBy, \
      tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy )

  #define ZZ_GMAP_H_DECLARE( tpKeyType, tpValueType, tpMapName, \
    tpKeyCompareBy, tpKeyPassBy, tpValuePassBy ) \
\
    ZGMAP_H_DECLARE( tpKeyType, tpValueType, tpMapName, tpKeyPassBy, \
      tpValuePassBy )

  #define ZZ_GMAP_H_DECLARE_EX( tpKeyType, tpValueType, tpMapName, \
    tpKeyAssignBy, tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, \
    tpValuePassBy ) \
\
    ZGMAP_H_DECLARE( tpKeyType, tpValueType, tpMapName, tpKeyPassBy, \
      tpValuePassBy )

#endif /* GMAP_MODULAR_APPROACH */

/******************************************************************************/

#define ZGMAP_H_DECLARE( tpKeyType, tpValueType, tpMapName, tpKeyPassBy, \
  tpValuePassBy ) \
\
  typedef gmap_h gmap_##tpMapName##_h; \
\
  extern \
  gmap_##tpMapName##_h \
  gmap_##tpMapName##_new( \
    void \
  ); \
\
  extern \
  ZGENA_TYPEINFO_NAME(tpValueType, tpValuePassBy) * \
  gmap_##tpMapName##_add( \
    gmap_##tpMapName##_h handle, \
    const ZGENA_TYPEINFO_USERTYPE(tpKeyType, tpKeyPassBy) key, \
    const ZGENA_TYPEINFO_USERTYPE(tpValueType, tpValuePassBy) value \
  ); \
\
  extern \
  gena_bool \
  gmap_##tpMapName##_delete( \
    gmap_##tpMapName##_h handle, \
    const ZGENA_TYPEINFO_USERTYPE(tpKeyType, tpKeyPassBy) key \
  ); \
\
  extern \
  ZGENA_TYPEINFO_NAME(tpValueType, tpValuePassBy) * \
  gmap_##tpMapName##_find( \
    gmap_##tpMapName##_h handle, \
    const ZGENA_TYPEINFO_USERTYPE(tpKeyType, tpKeyPassBy) key \
  ); \
\
  ZGENA_REQUIRE_SEMICOLON_OUTDOOR

/******************************************************************************/

#define ZGMAP_C_DEFINE( tpKeyType, tpValueType, tpMapName, tpKeyAssignBy, \
  tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy ) \
\
  ZZ_GMAP_DEFINE_TYPE( tpMapName ); \
  IGENA_AVL_SUBTREE_INSTANTIATE( gmap, tpMapName, tpKeyType, \
    ZGENA_TYPEINFO_SIZE(tpValueType, tpValuePassBy), tpKeyAssignBy, \
    tpKeyCompareBy, tpKeyPassBy ); \
/********************************************************************/ \
  ZZ_GMAP_FUNC_ONCE \
  gmap_##tpMapName##_h \
  gmap_##tpMapName##_new( \
    void \
  ) { \
  { \
    return igmap_new( \
      ZGENA_TYPEINFO_SIZE(tpKeyType, tpKeyPassBy), \
      ZGENA_TYPEINFO_SIZE(tpValueType, tpValuePassBy) \
    ); \
  }} \
/********************************************************************/ \
  ZZ_GMAP_FUNC_ONCE \
  ZGENA_TYPEINFO_NAME(tpValueType, tpValuePassBy) * \
  gmap_##tpMapName##_add( \
    gmap_##tpMapName##_h handle, \
    const ZGENA_TYPEINFO_USERTYPE(tpKeyType, tpKeyPassBy) key, \
    const ZGENA_TYPEINFO_USERTYPE(tpValueType, tpValuePassBy) value \
  ) { \
    igena_avl_retstate_e retstate; \
    igena_avl_node_head_p final_node; \
    ZGENA_TYPEINFO_NAME(tpValueType, tpValuePassBy) * node_value; \
  { \
    assert( handle != NULL ); \
    retstate = igmap_avl_subtree_##tpMapName##_add_key( &handle->avltree_root, \
      key, &final_node ); \
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
  ZZ_GMAP_FUNC_ONCE \
  gena_bool \
  gmap_##tpMapName##_delete( \
    gmap_##tpMapName##_h handle, \
    const ZGENA_TYPEINFO_USERTYPE(tpKeyType, tpKeyPassBy) key \
  ) { \
    igena_avl_retstate_e retstate; \
  { \
    assert( handle != NULL ); \
    retstate = igmap_avl_subtree_##tpMapName##_delete_key( \
      &handle->avltree_root, key ); \
    if (retstate == IGENA_AVL_RETST_NOTHING) { return GENA_FALSE; } \
    --(handle->count); \
    return GENA_TRUE; \
  }} \
/********************************************************************/ \
  ZZ_GMAP_FUNC_ONCE \
  ZGENA_TYPEINFO_NAME(tpValueType, tpValuePassBy) * \
  gmap_##tpMapName##_find( \
    gmap_##tpMapName##_h handle, \
    const ZGENA_TYPEINFO_USERTYPE(tpKeyType, tpKeyPassBy) key \
  ) { \
    igena_avl_node_head_p find_node; \
  { \
    assert( handle != NULL ); \
    find_node = igmap_avl_subtree_##tpMapName##_find_node( \
      handle->avltree_root, key ); \
    return (find_node == NULL) ? NULL : IGENA_AVL_NODE_GET_VALUE( \
      find_node, \
      ZGENA_TYPEINFO_SIZE(tpKeyType, tpKeyPassBy) \
    ); \
  }} \
/********************************************************************/ \
  ZGENA_REQUIRE_SEMICOLON_OUTDOOR
