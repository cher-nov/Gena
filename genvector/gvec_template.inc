/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#include <assert.h>

/*
  __IGVEC_FUNC_ONCE is necessary to prevent multiple declarations if
  genvector.h was included more than once.
  __IGVEC_DEFINE_TYPE needed to prevent typedef redefinition with modular
  approach.
*/

#ifndef GVEC_MODULAR_APPROACH

  #define __IGVEC_FUNC_ONCE static inline

  #define __IGVEC_DEFINE_TYPE( tpTypeInfo, tpUseBy, tpVecName ) \
    __IGENA_TYPEINFO_BUFDEF( tpTypeInfo, tpUseBy, tpVecName )

  #define GVEC_INSTANTIATE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy ) \
\
    _impl_GVEC_C_DEFINE( tpTypeInfo, tpVecName, GENA_ASSIGN_NAIVE, tpPassBy, \
      tpReturnBy )

  #define GVEC_INSTANTIATE_EX( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, \
    tpReturnBy ) \
\
    _impl_GVEC_C_DEFINE( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, \
      tpReturnBy )

#else /* GVEC_MODULAR_APPROACH */

  #define __IGVEC_FUNC_ONCE

  #define __IGVEC_DEFINE_TYPE( tpTypeInfo, tpUseBy, tpVecName ) \
    __IGENA_REQUIRE_SEMICOLON_OUTDOOR

  #define GVEC_C_DEFINE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy ) \
\
    _impl_GVEC_C_DEFINE( tpTypeInfo, tpVecName, GENA_ASSIGN_NAIVE, tpPassBy, \
      tpReturnBy )

  #define GVEC_C_DEFINE_EX( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, \
    tpReturnBy ) \
\
    _impl_GVEC_C_DEFINE( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, \
      tpReturnBy )

  #define GVEC_H_DECLARE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy ) \
    _impl_GVEC_H_DECLARE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy )

  #define GVEC_H_DECLARE_EX( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, \
    tpReturnBy ) \
\
    _impl_GVEC_H_DECLARE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy )

#endif /* GVEC_MODULAR_APPROACH */

/******************************************************************************/

#define _impl_GVEC_H_DECLARE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy ) \
\
  __IGENA_TYPEINFO_BUFDEF( tpTypeInfo, tpPassBy, gvec_##tpVecName##_t ); \
\
  extern \
  gvec_##tpVecName##_t \
  gvec_##tpVecName##_new( \
    size_t min_count \
  ); \
\
  extern \
  gena_error_e \
  gvec_##tpVecName##_assign( \
    gvec_##tpVecName##_t* phandle, \
    size_t count, \
    const __IGENA_TYPEINFO_TYPE(tpTypeInfo, tpPassBy, TYPE) value \
  ); \
\
  extern \
  gena_error_e \
  gvec_##tpVecName##_resize( \
    gvec_##tpVecName##_t* phandle, \
    size_t new_count, \
    const __IGENA_TYPEINFO_TYPE(tpTypeInfo, tpPassBy, TYPE) value \
  ); \
\
  extern \
  gena_error_e \
  gvec_##tpVecName##_insert( \
    gvec_##tpVecName##_t* phandle, \
    size_t pos, \
    size_t count, \
    const __IGENA_TYPEINFO_TYPE(tpTypeInfo, tpPassBy, TYPE) value \
  ); \
\
  extern \
  gena_error_e \
  gvec_##tpVecName##_push( \
    gvec_##tpVecName##_t* phandle, \
    const __IGENA_TYPEINFO_TYPE(tpTypeInfo, tpPassBy, TYPE) value \
  ); \
\
  extern \
  __IGENA_TYPEINFO_NAME(tpTypeInfo, tpReturnBy) * \
  gvec_##tpVecName##_at( \
    gvec_##tpVecName##_t handle, \
    size_t pos \
  ); \
\
  extern \
  __IGENA_TYPEINFO_TYPE(tpTypeInfo, tpReturnBy, TYPE) \
  gvec_##tpVecName##_front( \
    gvec_##tpVecName##_t handle \
  ); \
\
  extern \
  __IGENA_TYPEINFO_TYPE(tpTypeInfo, tpReturnBy, TYPE) \
  gvec_##tpVecName##_back( \
    gvec_##tpVecName##_t handle \
  ); \
\
  __IGENA_REQUIRE_SEMICOLON_OUTDOOR

/******************************************************************************/

#define _impl_GVEC_C_DEFINE( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, \
  tpReturnBy ) \
\
  __IGVEC_DEFINE_TYPE( tpTypeInfo, tpReturnBy, gvec_##tpVecName##_t ); \
/********************************************************************/ \
  __IGVEC_FUNC_ONCE \
  gvec_##tpVecName##_t \
  gvec_##tpVecName##_new( \
    size_t min_count \
  ) { \
  { \
    return igvec_new( \
      min_count, \
      __IGENA_TYPEINFO_SIZE(tpTypeInfo, tpPassBy) \
    ); \
  }} \
/********************************************************************/ \
  __IGVEC_FUNC_ONCE \
  gena_error_e \
  gvec_##tpVecName##_assign( \
    gvec_##tpVecName##_t* phandle, \
    size_t count, \
    const __IGENA_TYPEINFO_TYPE(tpTypeInfo, tpPassBy, TYPE) value \
  ) { \
    gena_error_e errorcode; \
    size_t i; \
  { \
    errorcode = gvec_resize( phandle, count ); \
    if (errorcode != GENA_ERR_NO) { return errorcode; } \
    for(i = 0; i < count; ++i) { \
      tpAssignBy ( \
        tpPassBy##LVREF (*phandle + i), \
        tpPassBy##BYREF value, \
        __IGENA_TYPEINFO_SIZE(tpTypeInfo, tpPassBy) \
      ); \
    } \
    return GENA_ERR_NO; \
  }} \
/********************************************************************/ \
  __IGVEC_FUNC_ONCE \
  gena_error_e \
  gvec_##tpVecName##_resize( \
    gvec_##tpVecName##_t* phandle, \
    size_t new_count, \
    const __IGENA_TYPEINFO_TYPE(tpTypeInfo, tpPassBy, TYPE) value \
  ) { \
    gena_error_e errorcode; \
    size_t i; \
  { \
    assert( phandle != NULL ); \
    i = gvec_count(*phandle); \
    errorcode = gvec_resize( phandle, new_count ); \
    if (errorcode != GENA_ERR_NO) { return errorcode; } \
    for(; i < new_count; ++i) { \
      tpAssignBy ( \
        tpPassBy##LVREF (*phandle + i), \
        tpPassBy##BYREF value, \
        __IGENA_TYPEINFO_SIZE(tpTypeInfo, tpPassBy) \
      ); \
    } \
    return GENA_ERR_NO; \
  }} \
/********************************************************************/ \
  __IGVEC_FUNC_ONCE \
  gena_error_e \
  gvec_##tpVecName##_insert( \
    gvec_##tpVecName##_t* phandle, \
    size_t pos, \
    size_t count, \
    const __IGENA_TYPEINFO_TYPE(tpTypeInfo, tpPassBy, TYPE) value \
  ) { \
    gena_error_e errorcode; \
    size_t i; \
  { \
    errorcode = igvec_insert( phandle, pos, count ); \
    if (errorcode != GENA_ERR_NO) { return errorcode; } \
    for(i = 0; i < count; ++i) { \
      tpAssignBy ( \
        tpPassBy##LVREF (*phandle + pos + i), \
        tpPassBy##BYREF value, \
        __IGENA_TYPEINFO_SIZE(tpTypeInfo, tpPassBy) \
      ); \
    } \
    return GENA_ERR_NO; \
  }} \
/********************************************************************/ \
  __IGVEC_FUNC_ONCE \
  gena_error_e \
  gvec_##tpVecName##_push( \
    gvec_##tpVecName##_t* phandle, \
    const __IGENA_TYPEINFO_TYPE(tpTypeInfo, tpPassBy, TYPE) value \
  ) { \
    gena_error_e errorcode; \
  { \
    errorcode = igvec_push(phandle); \
    if (errorcode != GENA_ERR_NO) { return errorcode; } \
    tpAssignBy ( \
      tpPassBy##LVREF (*phandle + gvec_count(*phandle)-1), \
      tpPassBy##BYREF value, \
      __IGENA_TYPEINFO_SIZE(tpTypeInfo, tpPassBy) \
    ); \
    return GENA_ERR_NO; \
  }} \
/********************************************************************/ \
  __IGVEC_FUNC_ONCE \
  __IGENA_TYPEINFO_NAME(tpTypeInfo, tpReturnBy) * \
  gvec_##tpVecName##_at( \
    gvec_##tpVecName##_t handle, \
    size_t pos \
  ) { \
  { \
    return gvec_at( handle, pos ); \
  }} \
/********************************************************************/ \
  __IGVEC_FUNC_ONCE \
  __IGENA_TYPEINFO_TYPE(tpTypeInfo, tpReturnBy, TYPE) \
  gvec_##tpVecName##_front( \
    gvec_##tpVecName##_t handle \
  ) { \
  { \
    return tpReturnBy##UNREF \
           ( __IGENA_TYPEINFO_NAME(tpTypeInfo, tpReturnBy) * ) \
           gvec_front(handle); \
  }} \
/********************************************************************/ \
  __IGVEC_FUNC_ONCE \
  __IGENA_TYPEINFO_TYPE(tpTypeInfo, tpReturnBy, TYPE) \
  gvec_##tpVecName##_back( \
    gvec_##tpVecName##_t handle \
  ) { \
  { \
    return tpReturnBy##UNREF \
           ( __IGENA_TYPEINFO_NAME(tpTypeInfo, tpReturnBy) * ) \
           gvec_back(handle); \
  }} \
/********************************************************************/ \
  __IGENA_REQUIRE_SEMICOLON_OUTDOOR
