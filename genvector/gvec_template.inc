/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#include <assert.h>

/*
  ZZ_GVEC_FUNC_ONCE is necessary to prevent multiple declarations if
  genvector.h was included more than once.
  ZZ_GVEC_DEFINE_TYPE needed to prevent typedef redefinition with modular
  approach.
*/

#ifndef GVEC_MODULAR_APPROACH

  #define ZZ_GVEC_FUNC_ONCE static inline

  #define ZZ_GVEC_DEFINE_TYPE( tpTypeInfo, tpUseBy, tpVecName ) \
    ZGENA_TYPEINFO_BUFDEF( tpTypeInfo, tpUseBy, tpVecName )

  #define GVEC_INSTANTIATE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy ) \
\
    ZZ_GVEC_C_DEFINE( tpTypeInfo, tpVecName, GENA_ASSIGN_NAIVE, tpPassBy, \
      tpReturnBy )

  #define GVEC_INSTANTIATE_EX( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, \
    tpReturnBy ) \
\
    ZZ_GVEC_C_DEFINE( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, tpReturnBy )

#else /* GVEC_MODULAR_APPROACH */

  #define ZZ_GVEC_FUNC_ONCE

  #define ZZ_GVEC_DEFINE_TYPE( tpTypeInfo, tpUseBy, tpVecName ) \
    ZGENA_REQUIRE_SEMICOLON_OUTDOOR

  #define GVEC_C_DEFINE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy ) \
\
    ZZ_GVEC_C_DEFINE( tpTypeInfo, tpVecName, GENA_ASSIGN_NAIVE, tpPassBy, \
      tpReturnBy )

  #define GVEC_C_DEFINE_EX( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, \
    tpReturnBy ) \
\
    ZZ_GVEC_C_DEFINE( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, tpReturnBy )

  #define GVEC_H_DECLARE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy ) \
    ZZ_GVEC_H_DECLARE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy )

  #define GVEC_H_DECLARE_EX( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, \
    tpReturnBy ) \
\
    ZZ_GVEC_H_DECLARE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy )

#endif /* GVEC_MODULAR_APPROACH */

/******************************************************************************/

#define ZZ_GVEC_H_DECLARE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy ) \
\
  ZGENA_TYPEINFO_BUFDEF( tpTypeInfo, tpPassBy, gvec_##tpVecName##_t ); \
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
    const ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy) value \
  ); \
\
  extern \
  gena_error_e \
  gvec_##tpVecName##_resize( \
    gvec_##tpVecName##_t* phandle, \
    size_t new_count, \
    const ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy) value \
  ); \
\
  extern \
  gena_error_e \
  gvec_##tpVecName##_insert( \
    gvec_##tpVecName##_t* phandle, \
    size_t pos, \
    size_t count, \
    const ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy) value \
  ); \
\
  extern \
  gena_error_e \
  gvec_##tpVecName##_push( \
    gvec_##tpVecName##_t* phandle, \
    const ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy) value \
  ); \
\
  extern \
  ZGENA_TYPEINFO_NAME(tpTypeInfo, tpReturnBy) * \
  gvec_##tpVecName##_at( \
    gvec_##tpVecName##_t handle, \
    size_t pos \
  ); \
\
  extern \
  ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpReturnBy) \
  gvec_##tpVecName##_front( \
    gvec_##tpVecName##_t handle \
  ); \
\
  extern \
  ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpReturnBy) \
  gvec_##tpVecName##_back( \
    gvec_##tpVecName##_t handle \
  ); \
\
  ZGENA_REQUIRE_SEMICOLON_OUTDOOR

/******************************************************************************/

#define ZZ_GVEC_C_DEFINE( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, \
  tpReturnBy ) \
\
  ZZ_GVEC_DEFINE_TYPE( tpTypeInfo, tpReturnBy, gvec_##tpVecName##_t ); \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  gvec_##tpVecName##_t \
  gvec_##tpVecName##_new( \
    size_t min_count \
  ) { \
  { \
    return igvec_new( \
      min_count, \
      ZGENA_TYPEINFO_SIZE(tpTypeInfo, tpPassBy) \
    ); \
  }} \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  gena_error_e \
  gvec_##tpVecName##_assign( \
    gvec_##tpVecName##_t* phandle, \
    size_t count, \
    const ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy) value \
  ) { \
    gena_error_e errorcode; \
    size_t i; \
  { \
    errorcode = gvec_resize( phandle, count ); \
    if (errorcode != GENA_ERR_NO) { return errorcode; } \
    for(i = 0; i < count; ++i) { \
      tpAssignBy ( \
        tpPassBy##ENTRY (*phandle + i), \
        tpPassBy##REFERENCE value, \
        ZGENA_TYPEINFO_SIZE(tpTypeInfo, tpPassBy) \
      ); \
    } \
    return GENA_ERR_NO; \
  }} \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  gena_error_e \
  gvec_##tpVecName##_resize( \
    gvec_##tpVecName##_t* phandle, \
    size_t new_count, \
    const ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy) value \
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
        tpPassBy##ENTRY (*phandle + i), \
        tpPassBy##REFERENCE value, \
        ZGENA_TYPEINFO_SIZE(tpTypeInfo, tpPassBy) \
      ); \
    } \
    return GENA_ERR_NO; \
  }} \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  gena_error_e \
  gvec_##tpVecName##_insert( \
    gvec_##tpVecName##_t* phandle, \
    size_t pos, \
    size_t count, \
    const ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy) value \
  ) { \
    gena_error_e errorcode; \
    size_t i; \
  { \
    errorcode = igvec_insert( phandle, pos, count ); \
    if (errorcode != GENA_ERR_NO) { return errorcode; } \
    for(i = 0; i < count; ++i) { \
      tpAssignBy ( \
        tpPassBy##ENTRY (*phandle + pos + i), \
        tpPassBy##REFERENCE value, \
        ZGENA_TYPEINFO_SIZE(tpTypeInfo, tpPassBy) \
      ); \
    } \
    return GENA_ERR_NO; \
  }} \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  gena_error_e \
  gvec_##tpVecName##_push( \
    gvec_##tpVecName##_t* phandle, \
    const ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy) value \
  ) { \
    gena_error_e errorcode; \
  { \
    errorcode = igvec_push(phandle); \
    if (errorcode != GENA_ERR_NO) { return errorcode; } \
    tpAssignBy ( \
      tpPassBy##ENTRY (*phandle + gvec_count(*phandle)-1), \
      tpPassBy##REFERENCE value, \
      ZGENA_TYPEINFO_SIZE(tpTypeInfo, tpPassBy) \
    ); \
    return GENA_ERR_NO; \
  }} \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  ZGENA_TYPEINFO_NAME(tpTypeInfo, tpReturnBy) * \
  gvec_##tpVecName##_at( \
    gvec_##tpVecName##_t handle, \
    size_t pos \
  ) { \
  { \
    return gvec_at( handle, pos ); \
  }} \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpReturnBy) \
  gvec_##tpVecName##_front( \
    gvec_##tpVecName##_t handle \
  ) { \
  { \
    return tpReturnBy##RETURN \
           ( ZGENA_TYPEINFO_NAME(tpTypeInfo, tpReturnBy) * ) \
           gvec_front(handle); \
  }} \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpReturnBy) \
  gvec_##tpVecName##_back( \
    gvec_##tpVecName##_t handle \
  ) { \
  { \
    return tpReturnBy##RETURN \
           ( ZGENA_TYPEINFO_NAME(tpTypeInfo, tpReturnBy) * ) \
           gvec_back(handle); \
  }} \
/********************************************************************/ \
  ZGENA_REQUIRE_SEMICOLON_OUTDOOR
