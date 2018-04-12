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

  #define ZZ_GTMAP_DEFINE_TYPE( tpSurname ) \
    typedef gtmap_h gtmap_##tpSurname##_h

  #define ZZ_GTMAP_INSTANTIATE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
    tpKeyCompareBy, tpKeyPassBy, tpValuePassBy ) \
\
    ZGTMAP_C_DEFINE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
      GENA_ASSIGN_NAIVE, GENA_ASSIGN_NAIVE, tpKeyCompareBy, tpKeyPassBy, \
      tpValuePassBy )

  #define ZZ_GTMAP_INSTANTIATE_EX( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
    tpKeyAssignBy, tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, \
    tpValuePassBy ) \
\
    ZGTMAP_C_DEFINE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyAssignBy, \
      tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy )

#else /* GTMAP_MODULAR_APPROACH */

  #define ZZ_GTMAP_FUNC_ONCE

  #define ZZ_GTMAP_DEFINE_TYPE( tpSurname ) \
    ZGENA_REQUIRE_SEMICOLON_OUTDOOR

  #define ZZ_GTMAP_C_DEFINE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
    tpKeyCompareBy, tpKeyPassBy, tpValuePassBy ) \
\
    ZGTMAP_C_DEFINE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
      GENA_ASSIGN_NAIVE, GENA_ASSIGN_NAIVE, tpKeyCompareBy, tpKeyPassBy, \
      tpValuePassBy )

  #define ZZ_GTMAP_C_DEFINE_EX( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
    tpKeyAssignBy, tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, \
    tpValuePassBy ) \
\
    ZGTMAP_C_DEFINE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyAssignBy, \
      tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy )

  #define ZZ_GTMAP_H_DECLARE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
    tpKeyCompareBy, tpKeyPassBy, tpValuePassBy ) \
\
    ZGTMAP_H_DECLARE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyPassBy, \
      tpValuePassBy )

  #define ZZ_GTMAP_H_DECLARE_EX( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
    tpKeyAssignBy, tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, \
    tpValuePassBy ) \
\
    ZGTMAP_H_DECLARE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, tpKeyPassBy, \
      tpValuePassBy )

#endif /* GTMAP_MODULAR_APPROACH */

/******************************************************************************/

#define ZGTMAP_H_DECLARE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
  tpKeyPassBy, tpValuePassBy ) \
\
  typedef gtmap_h gtmap_##tpSurname##_h; \
  ZZ_GTMAP_FUNCTIONS_LIST( \
    tpSurname, \
    ZGENA_TYPEINFO_NAME(tpValueTypeInfo, tpValuePassBy), \
    ZGENA_TYPEINFO_USERTYPE(tpKeyTypeInfo, tpKeyPassBy), \
    ZGENA_TYPEINFO_USERTYPE(tpValueTypeInfo, tpValuePassBy) \
  ); \
  ZGENA_REQUIRE_SEMICOLON_OUTDOOR

/******************************************************************************/

#define ZGTMAP_C_DEFINE( tpKeyTypeInfo, tpValueTypeInfo, tpSurname, \
  tpKeyAssignBy, tpValueAssignBy, tpKeyCompareBy, tpKeyPassBy, tpValuePassBy ) \
\
  ZZ_GTMAP_DEFINE_TYPE( tpSurname ); \
  IGENA_AVL_SUBTREE_INSTANTIATE( gtmap, tpSurname, tpKeyTypeInfo, \
    ZGENA_TYPEINFO_SIZE(tpValueTypeInfo, tpValuePassBy), tpKeyAssignBy, \
    tpKeyCompareBy, tpKeyPassBy ); \
/********************************************************************/ \
  ZZ_GTMAP_FUNC_ONCE \
  gtmap_##tpSurname##_h \
  gtmap_##tpSurname##_new( \
    void \
  ) { \
  { \
    return igtmap_new( \
      ZGENA_TYPEINFO_SIZE(tpKeyTypeInfo, tpKeyPassBy), \
      ZGENA_TYPEINFO_SIZE(tpValueTypeInfo, tpValuePassBy) \
    ); \
  }} \
/********************************************************************/ \
  ZZ_GTMAP_FUNC_ONCE \
  ZGENA_TYPEINFO_NAME(tpValueTypeInfo, tpValuePassBy) * \
  gtmap_##tpSurname##_add( \
    gtmap_##tpSurname##_h handle, \
    const ZGENA_TYPEINFO_USERTYPE(tpKeyTypeInfo, tpKeyPassBy) key, \
    const ZGENA_TYPEINFO_USERTYPE(tpValueTypeInfo, tpValuePassBy) value \
  ) { \
    igena_avl_retstate_e retstate; \
    igena_avl_node_head_p final_node; \
    ZGENA_TYPEINFO_NAME(tpValueTypeInfo, tpValuePassBy) * node_value; \
  { \
    assert( handle != NULL ); \
    retstate = igtmap_avl_subtree_##tpSurname##_add_key( \
      &handle->avltree_root, key, &final_node ); \
    if (final_node == NULL) { return NULL; } \
    node_value = IGENA_AVL_NODE_GET_VALUE( \
      final_node, \
      ZGENA_TYPEINFO_SIZE(tpKeyTypeInfo, tpKeyPassBy) \
    ); \
    if (retstate != IGENA_AVL_RETST_NOTHING) { \
      tpValueAssignBy ( \
        node_value, \
        tpValuePassBy##REFERENCE value, \
        ZGENA_TYPEINFO_SIZE(tpValueTypeInfo, tpValuePassBy) \
      ); \
      ++(handle->count); \
    } \
    return node_value; \
  }} \
/********************************************************************/ \
  ZZ_GTMAP_FUNC_ONCE \
  gena_bool \
  gtmap_##tpSurname##_delete( \
    gtmap_##tpSurname##_h handle, \
    const ZGENA_TYPEINFO_USERTYPE(tpKeyTypeInfo, tpKeyPassBy) key \
  ) { \
    igena_avl_retstate_e retstate; \
  { \
    assert( handle != NULL ); \
    retstate = igtmap_avl_subtree_##tpSurname##_delete_key( \
      &handle->avltree_root, key ); \
    if (retstate == IGENA_AVL_RETST_NOTHING) { return GENA_FALSE; } \
    --(handle->count); \
    return GENA_TRUE; \
  }} \
/********************************************************************/ \
  ZZ_GTMAP_FUNC_ONCE \
  ZGENA_TYPEINFO_NAME(tpValueTypeInfo, tpValuePassBy) * \
  gtmap_##tpSurname##_find( \
    gtmap_##tpSurname##_h handle, \
    const ZGENA_TYPEINFO_USERTYPE(tpKeyTypeInfo, tpKeyPassBy) key \
  ) { \
    igena_avl_node_head_p find_node; \
  { \
    assert( handle != NULL ); \
    find_node = igtmap_avl_subtree_##tpSurname##_find_node( \
      handle->avltree_root, key ); \
    return (find_node == NULL) ? NULL : IGENA_AVL_NODE_GET_VALUE( \
      find_node, \
      ZGENA_TYPEINFO_SIZE(tpKeyTypeInfo, tpKeyPassBy) \
    ); \
  }} \
/********************************************************************/ \
  ZGENA_REQUIRE_SEMICOLON_OUTDOOR
