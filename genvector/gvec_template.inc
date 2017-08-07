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

  #define GVEC_INSTANTIATE( tpTypename, tpVecName, tpPassBy, tpRetBy ) \
    _impl_GVEC_C_DEFINE( tpTypename, tpVecName, tpPassBy, tpRetBy )

#else /* GVEC_MODULAR_APPROACH */

  #define __IGVEC_FUNC_ONCE

  #define __IGVEC_DEFINE_TYPE( tpTypename, tpVecName ) \
    __IGENA_REQUIRE_SEMICOLON_OUTDOOR

  #define GVEC_C_DEFINE( tpTypename, tpVecName, tpPassBy, tpRetBy ) \
    _impl_GVEC_C_DEFINE( tpTypename, tpVecName, tpPassBy, tpRetBy )

  #define GVEC_H_DECLARE( tpTypename, tpVecName, tpPassBy, tpRetBy ) \
    _impl_GVEC_H_DECLARE( tpTypename, tpVecName, tpPassBy, tpRetBy )

#endif /* GVEC_MODULAR_APPROACH */

/******************************************************************************/

#define _impl_GVEC_H_DECLARE( tpTypename, tpVecName, tpPassBy, tpRetBy ) \
\
  typedef tpTypename* gvec_##tpVecName##_t; \
\
  extern gvec_##tpVecName##_t gvec_##tpVecName##_new( \
    size_t min_count ); \
  extern gena_error_e gvec_##tpVecName##_assign( \
    gvec_##tpVecName##_t* phandle, size_t count, \
    const tpTypename tpPassBy##OP value ); \
  extern gena_error_e gvec_##tpVecName##_resize( \
    gvec_##tpVecName##_t* phandle, size_t new_count, \
    const tpTypename tpPassBy##OP value ); \
  extern gena_error_e gvec_##tpVecName##_insert( \
    gvec_##tpVecName##_t* phandle, size_t pos, size_t count, \
    const tpTypename tpPassBy##OP value ); \
  extern gena_error_e gvec_##tpVecName##_push( \
    gvec_##tpVecName##_t* phandle, const tpTypename tpPassBy##OP value ); \
  extern tpTypename tpRetBy##OP gvec_##tpVecName##_front( \
    gvec_##tpVecName##_t handle ); \
  extern tpTypename tpRetBy##OP gvec_##tpVecName##_back( \
    gvec_##tpVecName##_t handle ); \
\
  __IGENA_REQUIRE_SEMICOLON_OUTDOOR

/******************************************************************************/

#define _impl_GVEC_C_DEFINE( tpTypename, tpVecName, tpPassBy, tpRetBy ) \
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
    const tpTypename tpPassBy##OP value \
  ) { \
    gena_error_e errorcode; \
    size_t i; \
  { \
    errorcode = igvec_resize( phandle, count ); \
    if (errorcode == GENA_ERR_NO) { \
      for(i = 0; i < count; ++i) { \
        (*phandle)[i] = tpPassBy##OP value; \
      } \
    } \
    return errorcode; \
  }} \
/********************************************************************/ \
  __IGVEC_FUNC_ONCE gena_error_e \
  gvec_##tpVecName##_resize( \
    gvec_##tpVecName##_t* phandle, \
    size_t new_count, \
    const tpTypename tpPassBy##OP value \
  ) { \
    gena_error_e errorcode; \
    size_t i; \
  { \
    assert( phandle != NULL ); \
    i = gvec_count(*phandle); \
    errorcode = igvec_resize( phandle, new_count ); \
    if (errorcode == GENA_ERR_NO) { \
      for(; i < new_count; ++i) { \
        (*phandle)[i] = tpPassBy##OP value; \
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
    const tpTypename tpPassBy##OP value \
  ) { \
    gena_error_e errorcode; \
    size_t i; \
  { \
    errorcode = igvec_insert( phandle, pos, count ); \
    if (errorcode == GENA_ERR_NO) { \
      for(i = 0; i < count; ++i) { \
        (*phandle)[i] = tpPassBy##OP value; \
      } \
    } \
    return errorcode; \
  }} \
/********************************************************************/ \
  __IGVEC_FUNC_ONCE gena_error_e \
  gvec_##tpVecName##_push( \
    gvec_##tpVecName##_t* phandle, \
    const tpTypename tpPassBy##OP value \
  ) { \
    gena_error_e errorcode; \
  { \
    errorcode = igvec_push(phandle); \
    if (errorcode == GENA_ERR_NO) { \
      (*phandle)[gvec_count(*phandle)-1] = tpPassBy##OP value; \
    } \
    return errorcode; \
  }} \
/********************************************************************/ \
  __IGVEC_FUNC_ONCE tpTypename tpRetBy##OP \
  gvec_##tpVecName##_front( \
    gvec_##tpVecName##_t handle \
  ) { \
  { \
    return tpRetBy##IOP (tpTypename*) gvec_front(handle); \
  }} \
/********************************************************************/ \
  __IGVEC_FUNC_ONCE tpTypename tpRetBy##OP \
  gvec_##tpVecName##_back( \
    gvec_##tpVecName##_t handle \
  ) { \
  { \
    return tpRetBy##IOP (tpTypename*) gvec_back(handle); \
  }} \
/********************************************************************/ \
  __IGENA_REQUIRE_SEMICOLON_OUTDOOR
