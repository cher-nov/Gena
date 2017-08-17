/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#include <assert.h>

/*
  __IGMAP_FUNC_ONCE is necessary to prevent multiple declarations if
  genmap.h was included more than once.
  __IGMAP_DEFINE_TYPE needed to prevent typedef redefinition with modular
  approach.
*/

#ifndef GMAP_MODULAR_APPROACH

  #define __IGMAP_FUNC_ONCE static inline

  #define __IGMAP_DEFINE_TYPE( tpMapName ) \
    typedef gmap_t gmap_##tpMapName##_t

  #define GMAP_INSTANTIATE( tpKeyType, tpValueType, tpMapName, tpKeyCompareBy, \
    tpKeyPassBy, tpValuePassBy ) \
\
    _impl_GMAP_C_DEFINE( tpKeyType, tpValueType, tpMapName, GENA_ASSIGN_NAIVE, \
      GENA_ASSIGN_NAIVE, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy )

  #define GMAP_INSTANTIATE_EX( tpKeyType, tpValueType, tpMapName, \
    tpKeyAssignBy, tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, \
    tpValuePassBy ) \
\
    _impl_GMAP_C_DEFINE( tpKeyType, tpValueType, tpMapName, tpKeyAssignBy, \
      tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy )

#else /* GMAP_MODULAR_APPROACH */

  #define __IGMAP_FUNC_ONCE

  #define __IGMAP_DEFINE_TYPE( tpMapName ) \
    __IGENA_REQUIRE_SEMICOLON_OUTDOOR

  #define GMAP_C_DEFINE( tpKeyType, tpValueType, tpMapName, tpKeyCompareBy, \
    tpKeyPassBy, tpValuePassBy ) \
\
    _impl_GMAP_C_DEFINE( tpKeyType, tpValueType, tpMapName, GENA_ASSIGN_NAIVE, \
      GENA_ASSIGN_NAIVE, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy )

  #define GMAP_C_DEFINE_EX( tpKeyType, tpValueType, tpMapName, tpKeyAssignBy, \
    tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy ) \
\
    _impl_GMAP_C_DEFINE( tpKeyType, tpValueType, tpMapName, tpKeyAssignBy, \
      tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy )

  #define GMAP_H_DECLARE( tpKeyType, tpValueType, tpMapName, tpKeyCompareBy, \
    tpKeyPassBy, tpValuePassBy ) \
\
    _impl_GMAP_H_DECLARE( tpKeyType, tpValueType, tpMapName, tpKeyPassBy, \
      tpValuePassBy )

  #define GMAP_H_DECLARE_EX( tpKeyType, tpValueType, tpMapName, tpKeyAssignBy, \
    tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy ) \
\
    _impl_GMAP_H_DECLARE( tpKeyType, tpValueType, tpMapName, tpKeyPassBy, \
      tpValuePassBy )

#endif /* GMAP_MODULAR_APPROACH */

/******************************************************************************/

#define _impl_GMAP_H_DECLARE( tpKeyType, tpValueType, tpMapName, tpKeyPassBy, \
  tpValuePassBy ) \
\
  typedef gmap_t gmap_##tpMapName##_t; \
\
  extern tpValueType* gmap_##tpMapName##_add( \
    gmap_##tpMapName##_t handle, \
    const tpKeyType tpKeyPassBy##TYPE key, \
    const tpValueType tpValuePassBy##TYPE value ); \
  extern gena_bool gmap_##tpMapName##_delete( \
    gmap_##tpMapName##_t handle, \
    const tpKeyType tpKeyPassBy##TYPE key ); \
  extern tpValueType* gmap_##tpMapName##_find( \
    gmap_##tpMapName##_t handle, \
    const tpKeyType tpKeyPassBy##TYPE key ); \
\
  __IGENA_REQUIRE_SEMICOLON_OUTDOOR

/******************************************************************************/

#define _impl_GMAP_C_DEFINE( tpKeyType, tpValueType, tpMapName, tpKeyAssignBy, \
  tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy ) \
\
  __IGMAP_DEFINE_TYPE( tpMapName ); \
  IGENA_AVL_SUBTREE_INSTANTIATE( gmap, tpMapName, tpKeyType, \
    sizeof(tpValueType), tpKeyAssignBy, tpKeyCompareBy, tpKeyPassBy ); \
/********************************************************************/ \
  __IGMAP_FUNC_ONCE tpValueType* \
  gmap_##tpMapName##_add( \
    gmap_##tpMapName##_t handle, \
    const tpKeyType tpKeyPassBy##TYPE key, \
    const tpValueType tpValuePassBy##TYPE value \
  ) { \
    igena_avl_retstate_e retstate; \
    igena_avl_node_head_p final_node; \
    tpValueType* node_value; \
  { \
    assert( handle != NULL ); \
    retstate = igmap_avl_subtree_##tpMapName##_add_key( &handle->avltree_root, \
      key, &final_node ); \
    if (final_node == NULL) { return NULL; } \
    node_value = IGENA_AVL_NODE_GET_VALUE( final_node, tpKeyType, \
      tpValueType ); \
    if (retstate != IGENA_AVL_RETST_NOTHING) { \
      tpValueAssignBy ( \
        tpValuePassBy##LVREF node_value, \
        tpValuePassBy##BYREF value, \
        sizeof(tpValueType) \
      ); \
      ++(handle->count); \
    } \
    return node_value; \
  }} \
/********************************************************************/ \
  __IGMAP_FUNC_ONCE gena_bool \
  gmap_##tpMapName##_delete( \
    gmap_##tpMapName##_t handle, \
    const tpKeyType tpKeyPassBy##TYPE key \
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
  __IGMAP_FUNC_ONCE tpValueType* \
  gmap_##tpMapName##_find( \
    gmap_##tpMapName##_t handle, \
    const tpKeyType tpKeyPassBy##TYPE key \
  ) { \
    igena_avl_node_head_p find_node; \
  { \
    assert( handle != NULL ); \
    find_node = igmap_avl_subtree_##tpMapName##_find_node( \
      handle->avltree_root, key ); \
    return (find_node != NULL) \
           ? IGENA_AVL_NODE_GET_VALUE( find_node, tpKeyType, tpValueType ) \
           : NULL; \
  }} \
/********************************************************************/ \
  __IGENA_REQUIRE_SEMICOLON_OUTDOOR
