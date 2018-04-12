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

  #define ZZ_GVEC_DEFINE_TYPE( tpTypeInfo, tpUseBy, tpSurname ) \
    ZGENA_TYPEINFO_BUFDEF( tpTypeInfo, tpUseBy, tpSurname )

  #define ZZ_GVEC_INSTANTIATE( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy ) \
\
    ZGVEC_C_DEFINE( tpTypeInfo, tpSurname, GENA_ASSIGN_NAIVE, tpPassBy, \
      tpReturnBy )

  #define ZZ_GVEC_INSTANTIATE_EX( tpTypeInfo, tpSurname, tpAssignBy, tpPassBy, \
    tpReturnBy ) \
\
    ZGVEC_C_DEFINE( tpTypeInfo, tpSurname, tpAssignBy, tpPassBy, tpReturnBy )

#else /* GVEC_MODULAR_APPROACH */

  #define ZZ_GVEC_FUNC_ONCE

  #define ZZ_GVEC_DEFINE_TYPE( tpTypeInfo, tpUseBy, tpSurname ) \
    ZGENA_REQUIRE_SEMICOLON_OUTDOOR

  #define ZZ_GVEC_C_DEFINE( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy ) \
\
    ZGVEC_C_DEFINE( tpTypeInfo, tpSurname, GENA_ASSIGN_NAIVE, tpPassBy, \
      tpReturnBy )

  #define ZZ_GVEC_C_DEFINE_EX( tpTypeInfo, tpSurname, tpAssignBy, tpPassBy, \
    tpReturnBy ) \
\
    ZGVEC_C_DEFINE( tpTypeInfo, tpSurname, tpAssignBy, tpPassBy, tpReturnBy )

  #define ZZ_GVEC_H_DECLARE( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy ) \
    ZGVEC_H_DECLARE( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy )

  #define ZZ_GVEC_H_DECLARE_EX( tpTypeInfo, tpSurname, tpAssignBy, tpPassBy, \
    tpReturnBy ) \
\
    ZGVEC_H_DECLARE( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy )

#endif /* GVEC_MODULAR_APPROACH */

/******************************************************************************/

#define ZGVEC_H_DECLARE( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy ) \
\
  ZGENA_TYPEINFO_BUFDEF( tpTypeInfo, tpPassBy, gvec_##tpSurname##_h ); \
  ZZ_GVEC_FUNCTIONS_LIST( \
    tpSurname, \
    ZGENA_TYPEINFO_NAME(tpTypeInfo, tpReturnBy), \
    ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy), \
    ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpReturnBy) \
  ); \
  ZGENA_REQUIRE_SEMICOLON_OUTDOOR

/******************************************************************************/

#define ZGVEC_C_DEFINE( tpTypeInfo, tpSurname, tpAssignBy, tpPassBy, \
  tpReturnBy ) \
\
  ZZ_GVEC_DEFINE_TYPE( tpTypeInfo, tpReturnBy, gvec_##tpSurname##_h ); \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  gvec_##tpSurname##_h \
  gvec_##tpSurname##_new( \
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
  gvec_##tpSurname##_assign( \
    gvec_##tpSurname##_h* phandle, \
    size_t count, \
    const ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy) value \
  ) { \
    gvec_##tpSurname##_h new_handle; \
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
  gvec_##tpSurname##_resize( \
    gvec_##tpSurname##_h* phandle, \
    size_t new_count, \
    const ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy) value \
  ) { \
    gvec_##tpSurname##_h new_handle; \
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
  gvec_##tpSurname##_reserve( \
    gvec_##tpSurname##_h* phandle, \
    size_t min_count \
  ) { \
    gvec_##tpSurname##_h new_handle; \
  { \
    new_handle = igvec_reserve( *phandle, min_count ); \
    if (new_handle == NULL) { return GENA_FALSE; } \
    *phandle = new_handle; \
    return GENA_TRUE; \
  }} \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  gena_bool \
  gvec_##tpSurname##_shrink( \
    gvec_##tpSurname##_h* phandle \
  ) { \
    gvec_##tpSurname##_h new_handle; \
  { \
    new_handle = igvec_shrink( *phandle ); \
    if (new_handle == NULL) { return GENA_FALSE; } \
    *phandle = new_handle; \
    return GENA_TRUE; \
  }} \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  gena_bool \
  gvec_##tpSurname##_insert( \
    gvec_##tpSurname##_h* phandle, \
    size_t position, \
    size_t count, \
    const ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy) value \
  ) { \
    gvec_##tpSurname##_h new_handle; \
    size_t i; \
  { \
    new_handle = igvec_insert( *phandle, position, count ); \
    if (new_handle == NULL) { return GENA_FALSE; } \
    for(i = 0; i < count; ++i) { \
      tpAssignBy ( \
        tpPassBy##ENTRY (new_handle + position + i), \
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
  gvec_##tpSurname##_push( \
    gvec_##tpSurname##_h* phandle, \
    const ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpPassBy) value \
  ) { \
    gvec_##tpSurname##_h new_handle; \
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
  gvec_##tpSurname##_at( \
    gvec_##tpSurname##_h handle, \
    size_t position \
  ) { \
  { \
    return gvec_at( handle, position ); \
  }} \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpReturnBy) \
  gvec_##tpSurname##_front( \
    gvec_##tpSurname##_h handle \
  ) { \
  { \
    return tpReturnBy##RETURN \
      ( ZGENA_TYPEINFO_NAME(tpTypeInfo, tpReturnBy) * ) gvec_front(handle); \
  }} \
/********************************************************************/ \
  ZZ_GVEC_FUNC_ONCE \
  ZGENA_TYPEINFO_USERTYPE(tpTypeInfo, tpReturnBy) \
  gvec_##tpSurname##_back( \
    gvec_##tpSurname##_h handle \
  ) { \
  { \
    return tpReturnBy##RETURN \
      ( ZGENA_TYPEINFO_NAME(tpTypeInfo, tpReturnBy) * ) gvec_back(handle); \
  }} \
/********************************************************************/ \
  ZGENA_REQUIRE_SEMICOLON_OUTDOOR
