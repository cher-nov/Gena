#include <assert.h>

#include "gvmacro.h"

#define __GVVAL_OP
#define __GVREF_OP *
#define __GVVAL_IOP *
#define __GVREF_IOP

/*
  __GVONCEFUNC is necessary to prevent multiple declarations if
  genvector.h was included more than once.
  __GVVECTYPE needed to prevent typedef redefinition with modular approach.
*/

#ifndef GVEC_MODULAR_APPROACH

  #if __STDC_VERSION__ < 199901L
    #define __GVONCEFUNC static
  #else
    #define __GVONCEFUNC static inline
  #endif

  #define __GVVECTYPE( gvTypename, gvVecName ) \
    typedef gvTypename* gvec_##gvVecName##_t

  #define GVEC_INSTANTIATE( gvTypename, gvVecName, gvPassBy, gvRetBy ) \
    __GVINSTANTIATE( gvTypename, gvVecName, gvPassBy, gvRetBy )

#else /* GVEC_MODULAR_APPROACH */

  #define __GVONCEFUNC

  #define __GVVECTYPE( gvTypename, gvVecName ) __GV_REQUIRE_SEMICOLON_OUTDOOR

  #define GVEC_C_DEFINE( gvTypename, gvVecName, gvPassBy, gvRetBy ) \
    __GVINSTANTIATE( gvTypename, gvVecName, gvPassBy, gvRetBy )

  #define GVEC_H_DECLARE( gvTypename, gvVecName, gvPassBy, gvRetBy ) \
    __GVDECLAREFUNC( gvTypename, gvVecName, gvPassBy, gvRetBy )

  #define __GVDECLAREFUNC( gvTypename, gvVecName, gvPassBy, gvRetBy ) \
  \
    typedef gvTypename* gvec_##gvVecName##_t; \
  \
    extern gvec_##gvVecName##_t gvec_##gvVecName##_new( \
      size_t min_count ); \
    extern gvec_error_e gvec_##gvVecName##_assign( \
      gvec_##gvVecName##_t* phandle, size_t count, \
      const gvTypename gvPassBy##OP value ); \
    extern gvec_error_e gvec_##gvVecName##_resize( \
      gvec_##gvVecName##_t* phandle, size_t new_count, \
      const gvTypename gvPassBy##OP value ); \
    extern gvec_error_e gvec_##gvVecName##_insert( \
      gvec_##gvVecName##_t* phandle, size_t pos, size_t count, \
      const gvTypename gvPassBy##OP value ); \
    extern gvec_error_e gvec_##gvVecName##_push( \
      gvec_##gvVecName##_t* phandle, const gvTypename gvPassBy##OP value ); \
    extern gvTypename gvRetBy##OP gvec_##gvVecName##_front( \
      gvec_##gvVecName##_t handle ); \
    extern gvTypename gvRetBy##OP gvec_##gvVecName##_back( \
      gvec_##gvVecName##_t handle ); \
  \
  __GV_REQUIRE_SEMICOLON_OUTDOOR

#endif /* GVEC_MODULAR_APPROACH */

#define GVEC_APPLY_TYPESET(macro, typeset) macro typeset

/******************************************************************************/

#define __GVINSTANTIATE( gvTypename, gvVecName, gvPassBy, gvRetBy ) \
\
  __GVVECTYPE( gvTypename, gvVecName ); \
/********************************************************************/ \
  __GVONCEFUNC gvec_##gvVecName##_t \
  gvec_##gvVecName##_new( \
    size_t min_count \
  ) { \
  { \
    return gvec_new( min_count, sizeof(gvTypename) ); \
  }} \
/********************************************************************/ \
  __GVONCEFUNC gvec_error_e \
  gvec_##gvVecName##_assign( \
    gvec_##gvVecName##_t* phandle, \
    size_t count, \
    const gvTypename gvPassBy##OP value \
  ) { \
    gvec_error_e errorcode; \
    size_t i; \
  { \
    errorcode = gvec_resize( phandle, count ); \
    if (errorcode == GVEC_ERR_NO) { \
      for(i = 0; i < count; ++i) { \
        (*phandle)[i] = gvPassBy##OP value; \
      } \
    } \
    return errorcode; \
  }} \
/********************************************************************/ \
  __GVONCEFUNC gvec_error_e \
  gvec_##gvVecName##_resize( \
    gvec_##gvVecName##_t* phandle, \
    size_t new_count, \
    const gvTypename gvPassBy##OP value \
  ) { \
    gvec_error_e errorcode; \
    size_t i; \
  { \
    assert( phandle != NULL ); \
    i = gvec_count(*phandle); \
    errorcode = gvec_resize( phandle, new_count ); \
    if (errorcode == GVEC_ERR_NO) { \
      for(; i < new_count; ++i) { \
        (*phandle)[i] = gvPassBy##OP value; \
      } \
    } \
    return errorcode; \
  }} \
/********************************************************************/ \
  __GVONCEFUNC gvec_error_e \
  gvec_##gvVecName##_insert( \
    gvec_##gvVecName##_t* phandle, \
    size_t pos, \
    size_t count, \
    const gvTypename gvPassBy##OP value \
  ) { \
    gvec_error_e errorcode; \
    size_t i; \
  { \
    errorcode = gvec_insert( phandle, pos, count ); \
    if (errorcode == GVEC_ERR_NO) { \
      for(i = 0; i < count; ++i) { \
        (*phandle)[i] = gvPassBy##OP value; \
      } \
    } \
    return errorcode; \
  }} \
/********************************************************************/ \
  __GVONCEFUNC gvec_error_e \
  gvec_##gvVecName##_push( \
    gvec_##gvVecName##_t* phandle, \
    const gvTypename gvPassBy##OP value \
  ) { \
    gvec_error_e errorcode; \
  { \
    errorcode = gvec_push(phandle); \
    if (errorcode == GVEC_ERR_NO) { \
      (*phandle)[gvec_count(*phandle)-1] = gvPassBy##OP value; \
    } \
    return errorcode; \
  }} \
/********************************************************************/ \
  __GVONCEFUNC gvTypename gvRetBy##OP \
  gvec_##gvVecName##_front( \
    gvec_##gvVecName##_t handle \
  ) { \
  { \
    return gvRetBy##IOP (gvTypename*) gvec_front(handle); \
  }} \
/********************************************************************/ \
  __GVONCEFUNC gvTypename gvRetBy##OP \
  gvec_##gvVecName##_back( \
    gvec_##gvVecName##_t handle \
  ) { \
  { \
    return gvRetBy##IOP (gvTypename*) gvec_back(handle); \
  }} \
/********************************************************************/ \
  __GV_REQUIRE_SEMICOLON_OUTDOOR
