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

  #define __IGVEC_DEFINE_TYPE( tpTypename, tpVecName ) \
    typedef tpTypename* gvec_##tpVecName##_t

  #define GVEC_INSTANTIATE( tpTypename, tpVecName, tpPassBy, tpReturnBy ) \
\
    _impl_GVEC_C_DEFINE( tpTypename, tpVecName, GENA_ASSIGN_NAIVE, tpPassBy, \
      tpReturnBy )

  #define GVEC_INSTANTIATE_EX( tpTypename, tpVecName, tpAssignBy, tpPassBy, \
    tpReturnBy ) \
\
    _impl_GVEC_C_DEFINE( tpTypename, tpVecName, tpAssignBy, tpPassBy, \
      tpReturnBy )

#else /* GVEC_MODULAR_APPROACH */

  #define __IGVEC_FUNC_ONCE

  #define __IGVEC_DEFINE_TYPE( tpTypename, tpVecName ) \
    __IGENA_REQUIRE_SEMICOLON_OUTDOOR

  #define GVEC_C_DEFINE( tpTypename, tpVecName, tpPassBy, tpReturnBy ) \
\
    _impl_GVEC_C_DEFINE( tpTypename, tpVecName, GENA_ASSIGN_NAIVE, tpPassBy, \
      tpReturnBy )

  #define GVEC_C_DEFINE_EX( tpTypename, tpVecName, tpAssignBy, tpPassBy, \
    tpReturnBy ) \
\
    _impl_GVEC_C_DEFINE( tpTypename, tpVecName, tpAssignBy, tpPassBy, \
      tpReturnBy )

  #define GVEC_H_DECLARE( tpTypename, tpVecName, tpPassBy, tpReturnBy ) \
    _impl_GVEC_H_DECLARE( tpTypename, tpVecName, tpPassBy, tpReturnBy )

  #define GVEC_H_DECLARE_EX( tpTypename, tpVecName, tpAssignBy, tpPassBy, \
    tpReturnBy ) \
\
    _impl_GVEC_H_DECLARE( tpTypename, tpVecName, tpPassBy, tpReturnBy )

#endif /* GVEC_MODULAR_APPROACH */

/******************************************************************************/

#define _impl_GVEC_H_DECLARE( tpTypename, tpVecName, tpPassBy, tpReturnBy ) \
\
  typedef tpTypename* gvec_##tpVecName##_t; \
\
  extern gvec_##tpVecName##_t gvec_##tpVecName##_new( \
    size_t min_count ); \
  extern gena_error_e gvec_##tpVecName##_assign( \
    gvec_##tpVecName##_t* phandle, \
    size_t count, \
    const tpTypename tpPassBy##TYPE value ); \
  extern gena_error_e gvec_##tpVecName##_resize( \
    gvec_##tpVecName##_t* phandle, \
    size_t new_count, \
    const tpTypename tpPassBy##TYPE value ); \
  extern gena_error_e gvec_##tpVecName##_insert( \
    gvec_##tpVecName##_t* phandle, \
    size_t pos, \
    size_t count, \
    const tpTypename tpPassBy##TYPE value ); \
  extern gena_error_e gvec_##tpVecName##_push( \
    gvec_##tpVecName##_t* phandle, \
    const tpTypename tpPassBy##TYPE value ); \
  extern tpTypename tpReturnBy##TYPE gvec_##tpVecName##_front( \
    gvec_##tpVecName##_t handle ); \
  extern tpTypename tpReturnBy##TYPE gvec_##tpVecName##_back( \
    gvec_##tpVecName##_t handle ); \
\
  __IGENA_REQUIRE_SEMICOLON_OUTDOOR

/******************************************************************************/

#define _impl_GVEC_C_DEFINE( tpTypename, tpVecName, tpAssignBy, tpPassBy, \
  tpReturnBy ) \
\
  __IGVEC_DEFINE_TYPE( tpTypename, tpVecName ); \
/********************************************************************/ \
  __IGVEC_FUNC_ONCE gvec_##tpVecName##_t \
  gvec_##tpVecName##_new( \
    size_t min_count \
  ) { \
  { \
    return igvec_new( min_count, sizeof(tpTypename) ); \
  }} \
/********************************************************************/ \
  __IGVEC_FUNC_ONCE gena_error_e \
  gvec_##tpVecName##_assign( \
    gvec_##tpVecName##_t* phandle, \
    size_t count, \
    const tpTypename tpPassBy##TYPE value \
  ) { \
    gena_error_e errorcode; \
    size_t i; \
  { \
    errorcode = igvec_resize( phandle, count ); \
    if (errorcode == GENA_ERR_NO) { \
      tpTypename* ptr_entry = *phandle; \
      for(i = 0; i < count; ++i) { \
        tpAssignBy ( \
          tpPassBy##LVREF (ptr_entry + i), \
          tpPassBy##BYREF value, \
          sizeof(tpTypename) \
        ); \
      } \
    } \
    return errorcode; \
  }} \
/********************************************************************/ \
  __IGVEC_FUNC_ONCE gena_error_e \
  gvec_##tpVecName##_resize( \
    gvec_##tpVecName##_t* phandle, \
    size_t new_count, \
    const tpTypename tpPassBy##TYPE value \
  ) { \
    gena_error_e errorcode; \
    size_t i; \
  { \
    assert( phandle != NULL ); \
    i = gvec_count(*phandle); \
    errorcode = igvec_resize( phandle, new_count ); \
    if (errorcode == GENA_ERR_NO) { \
      tpTypename* ptr_entry = *phandle; \
      for(; i < new_count; ++i) { \
        tpAssignBy ( \
          tpPassBy##LVREF (ptr_entry + i), \
          tpPassBy##BYREF value, \
          sizeof(tpTypename) \
        ); \
      } \
    } \
    return errorcode; \
  }} \
/********************************************************************/ \
  __IGVEC_FUNC_ONCE gena_error_e \
  gvec_##tpVecName##_insert( \
    gvec_##tpVecName##_t* phandle, \
    size_t pos, \
    size_t count, \
    const tpTypename tpPassBy##TYPE value \
  ) { \
    gena_error_e errorcode; \
    size_t i; \
  { \
    errorcode = igvec_insert( phandle, pos, count ); \
    if (errorcode == GENA_ERR_NO) { \
      tpTypename* ptr_entry = *phandle; \
      for(i = 0; i < count; ++i) { \
        tpAssignBy ( \
          tpPassBy##LVREF (ptr_entry + i), \
          tpPassBy##BYREF value, \
          sizeof(tpTypename) \
        ); \
      } \
    } \
    return errorcode; \
  }} \
/********************************************************************/ \
  __IGVEC_FUNC_ONCE gena_error_e \
  gvec_##tpVecName##_push( \
    gvec_##tpVecName##_t* phandle, \
    const tpTypename tpPassBy##TYPE value \
  ) { \
    gena_error_e errorcode; \
  { \
    errorcode = igvec_push(phandle); \
    if (errorcode == GENA_ERR_NO) { \
      tpAssignBy ( \
        tpPassBy##LVREF (*phandle + gvec_count(*phandle)-1), \
        tpPassBy##BYREF value, \
        sizeof(tpTypename) \
      ); \
    } \
    return errorcode; \
  }} \
/********************************************************************/ \
  __IGVEC_FUNC_ONCE tpTypename tpReturnBy##TYPE \
  gvec_##tpVecName##_front( \
    gvec_##tpVecName##_t handle \
  ) { \
  { \
    return tpReturnBy##UNREF (tpTypename*) gvec_front(handle); \
  }} \
/********************************************************************/ \
  __IGVEC_FUNC_ONCE tpTypename tpReturnBy##TYPE \
  gvec_##tpVecName##_back( \
    gvec_##tpVecName##_t handle \
  ) { \
  { \
    return tpReturnBy##UNREF (tpTypename*) gvec_back(handle); \
  }} \
/********************************************************************/ \
  __IGENA_REQUIRE_SEMICOLON_OUTDOOR
