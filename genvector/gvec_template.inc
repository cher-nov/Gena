/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#include <assert.h>

/*
  ZZ_GVEC_FUNC_ONCE is necessary to prevent multiple declarations if the main
  header was included more than once.
  ZZ_GVEC_DEFINE_TYPE needed to prevent typedef redefinition with modular
  approach.
*/

#ifndef GVEC_MODULAR_APPROACH

  #define ZZ_GVEC_FUNC_ONCE static GENA_INLINE

  #define ZZ_GVEC_DEFINE_TYPE( tpTypeInfo, tpUseBy, tpVecName ) \
    ZGENA_TYPEINFO_BUFDEF( tpTypeInfo, tpUseBy, tpVecName )

  #define ZZ_GVEC_INSTANTIATE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy ) \
\
    ZGVEC_C_DEFINE( tpTypeInfo, tpVecName, GENA_ASSIGN_NAIVE, tpPassBy, \
      tpReturnBy )

  #define ZZ_GVEC_INSTANTIATE_EX( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, \
    tpReturnBy ) \
\
    ZGVEC_C_DEFINE( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, tpReturnBy )

#else /* GVEC_MODULAR_APPROACH */

  #define ZZ_GVEC_FUNC_ONCE

  #define ZZ_GVEC_DEFINE_TYPE( tpTypeInfo, tpUseBy, tpVecName ) \
    ZGENA_REQUIRE_SEMICOLON_OUTDOOR

  #define ZZ_GVEC_C_DEFINE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy ) \
\
    ZGVEC_C_DEFINE( tpTypeInfo, tpVecName, GENA_ASSIGN_NAIVE, tpPassBy, \
      tpReturnBy )

  #define ZZ_GVEC_C_DEFINE_EX( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, \
    tpReturnBy ) \
\
    ZGVEC_C_DEFINE( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, tpReturnBy )

  #define ZZ_GVEC_H_DECLARE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy ) \
    ZGVEC_H_DECLARE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy )

  #define ZZ_GVEC_H_DECLARE_EX( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, \
    tpReturnBy ) \
\
    ZGVEC_H_DECLARE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy )

#endif /* GVEC_MODULAR_APPROACH */

/******************************************************************************/

#define ZGVEC_H_DECLARE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy ) \
\
  ZGENA_TYPEINFO_BUFDEF( tpTypeInfo, tpPassBy, gvec_##tpVecName##_h ); \
\
  extern \
  gvec_##tpVecName##_h \
  gvec_##tpVecName##_new( \
    size_t min_count \
  ); \
\
  extern \
  gena_bool \
  gvec_##tpVecName##_assign( \
    gvec_##tpVecName##_h* phandle, \
    size_t count, \
    const ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy) value \
  ); \
\
  extern \
  gena_bool \
  gvec_##tpVecName##_resize( \
    gvec_##tpVecName##_h* phandle, \
    size_t new_count, \
    const ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy) value \
  ); \
\
  extern \
  gena_bool \
  gvec_##tpVecName##_reserve( \
    gvec_##tpVecName##_h* phandle, \
    size_t min_count \
  ); \
\
  extern \
  gena_bool \
  gvec_##tpVecName##_shrink( \
    gvec_##tpVecName##_h* phandle \
  ); \
\
  extern \
  gena_bool \
  gvec_##tpVecName##_insert( \
    gvec_##tpVecName##_h* phandle, \
    size_t pos, \
    size_t count, \
    const ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy) value \
  ); \
\
  extern \
  gena_bool \
  gvec_##tpVecName##_push( \
    gvec_##tpVecName##_h* phandle, \
    const ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy) value \
  ); \
\
  extern \
  ZGENA_TYPEINFO_NAME(tpTypeInfo, tpReturnBy) * \
  gvec_##tpVecName##_at( \
    gvec_##tpVecName##_h handle, \
    size_t pos \
  ); \
\
  extern \
  ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpReturnBy) \
  gvec_##tpVecName##_front( \
    gvec_##tpVecName##_h handle \
  ); \
\
  extern \
  ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpReturnBy) \
  gvec_##tpVecName##_back( \
    gvec_##tpVecName##_h handle \
  ); \
\
  ZGENA_REQUIRE_SEMICOLON_OUTDOOR

/******************************************************************************/

#define ZGVEC_C_DEFINE( tpTypeInfo, tpVecName, tpAssignBy, tpPassBy, \
  tpReturnBy ) \
\
  ZZ_GVEC_DEFINE_TYPE( tpTypeInfo, tpReturnBy, gvec_##tpVecName##_h ); \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  gvec_##tpVecName##_h \
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
  gena_bool \
  gvec_##tpVecName##_assign( \
    gvec_##tpVecName##_h* phandle, \
    size_t count, \
    const ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy) value \
  ) { \
    gvec_##tpVecName##_h new_handle; \
    size_t i; \
  { \
    assert( phandle != NULL ); \
    new_handle = igvec_resize( *phandle, count ); \
    if (new_handle == NULL) { return GENA_FALSE; } \
    for(i = 0; i < count; ++i) { \
      tpAssignBy ( \
        tpPassBy##ENTRY (new_handle + i), \
        tpPassBy##REFERENCE value, \
        ZGENA_TYPEINFO_SIZE(tpTypeInfo, tpPassBy) \
      ); \
    } \
    *phandle = new_handle; \
    return GENA_TRUE; \
  }} \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  gena_bool \
  gvec_##tpVecName##_resize( \
    gvec_##tpVecName##_h* phandle, \
    size_t new_count, \
    const ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy) value \
  ) { \
    gvec_##tpVecName##_h new_handle; \
    size_t i; \
  { \
    assert( phandle != NULL ); \
    i = gvec_count(*phandle); \
    new_handle = igvec_resize( *phandle, new_count ); \
    if (new_handle == NULL) { return GENA_FALSE; } \
    for(; i < new_count; ++i) { \
      tpAssignBy ( \
        tpPassBy##ENTRY (new_handle + i), \
        tpPassBy##REFERENCE value, \
        ZGENA_TYPEINFO_SIZE(tpTypeInfo, tpPassBy) \
      ); \
    } \
    *phandle = new_handle; \
    return GENA_TRUE; \
  }} \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  gena_bool \
  gvec_##tpVecName##_reserve( \
    gvec_##tpVecName##_h* phandle, \
    size_t min_count \
  ) { \
    gvec_##tpVecName##_h new_handle; \
  { \
    new_handle = igvec_reserve( *phandle, min_count ); \
    if (new_handle == NULL) { return GENA_FALSE; } \
    *phandle = new_handle; \
    return GENA_TRUE; \
  }} \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  gena_bool \
  gvec_##tpVecName##_shrink( \
    gvec_##tpVecName##_h* phandle \
  ) { \
    gvec_##tpVecName##_h new_handle; \
  { \
    new_handle = igvec_shrink( *phandle ); \
    if (new_handle == NULL) { return GENA_FALSE; } \
    *phandle = new_handle; \
    return GENA_TRUE; \
  }} \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  gena_bool \
  gvec_##tpVecName##_insert( \
    gvec_##tpVecName##_h* phandle, \
    size_t pos, \
    size_t count, \
    const ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy) value \
  ) { \
    gvec_##tpVecName##_h new_handle; \
    size_t i; \
  { \
    new_handle = igvec_insert( *phandle, pos, count ); \
    if (new_handle == NULL) { return GENA_FALSE; } \
    for(i = 0; i < count; ++i) { \
      tpAssignBy ( \
        tpPassBy##ENTRY (new_handle + pos + i), \
        tpPassBy##REFERENCE value, \
        ZGENA_TYPEINFO_SIZE(tpTypeInfo, tpPassBy) \
      ); \
    } \
    *phandle = new_handle; \
    return GENA_TRUE; \
  }} \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  gena_bool \
  gvec_##tpVecName##_push( \
    gvec_##tpVecName##_h* phandle, \
    const ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy) value \
  ) { \
    gvec_##tpVecName##_h new_handle; \
  { \
    new_handle = igvec_push(*phandle); \
    if (new_handle == NULL) { return GENA_FALSE; } \
    tpAssignBy ( \
      tpPassBy##ENTRY (new_handle + gvec_count(new_handle)-1), \
      tpPassBy##REFERENCE value, \
      ZGENA_TYPEINFO_SIZE(tpTypeInfo, tpPassBy) \
    ); \
    *phandle = new_handle; \
    return GENA_TRUE; \
  }} \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  ZGENA_TYPEINFO_NAME(tpTypeInfo, tpReturnBy) * \
  gvec_##tpVecName##_at( \
    gvec_##tpVecName##_h handle, \
    size_t pos \
  ) { \
  { \
    return gvec_at( handle, pos ); \
  }} \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpReturnBy) \
  gvec_##tpVecName##_front( \
    gvec_##tpVecName##_h handle \
  ) { \
  { \
    return tpReturnBy##RETURN \
      ( ZGENA_TYPEINFO_NAME(tpTypeInfo, tpReturnBy) * ) gvec_front(handle); \
  }} \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpReturnBy) \
  gvec_##tpVecName##_back( \
    gvec_##tpVecName##_h handle \
  ) { \
  { \
    return tpReturnBy##RETURN \
      ( ZGENA_TYPEINFO_NAME(tpTypeInfo, tpReturnBy) * ) gvec_back(handle); \
  }} \
/********************************************************************/ \
  ZGENA_REQUIRE_SEMICOLON_OUTDOOR
