/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#define ZZ_GVEC_DEFINE_TYPE( tpTypeInfo, tpUseBy, tpSurname ) \
  typedef ZGENA_DATA_BIND( tpTypeInfo, tpUseBy, *gvec_##tpSurname##_h )

/* Static approach. */

#define ZZ_GVEC_INSTANTIATE( tpTypeInfo, tpSurname, tpUseBy ) \
\
  ZGVEC_DEFINITIONS( ZGENA_APPROACH_STATIC, tpTypeInfo, tpSurname, tpUseBy, \
    tpUseBy, GENA_ASSIGN_NAIVE )

#define ZZ_GVEC_INSTANTIATE_EX( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy, \
  tpAssignBy ) \
\
  ZGVEC_DEFINITIONS( ZGENA_APPROACH_STATIC, tpTypeInfo, tpSurname, tpPassBy, \
    tpReturnBy, tpAssignBy )

/* Modular approach. */

#define ZZ_GVEC_H_DECLARE( tpTypeInfo, tpSurname, tpUseBy ) \
  ZGVEC_DECLARATIONS( tpTypeInfo, tpSurname, tpUseBy, tpUseBy )

#define ZZ_GVEC_C_DEFINE( tpTypeInfo, tpSurname, tpUseBy ) \
\
  ZGVEC_DEFINITIONS( ZGENA_APPROACH_MODULAR, tpTypeInfo, tpSurname, tpUseBy, \
    tpUseBy, GENA_ASSIGN_NAIVE )

#define ZZ_GVEC_H_DECLARE_EX( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy, \
  tpAssignBy ) \
\
  ZGVEC_DECLARATIONS( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy )

#define ZZ_GVEC_C_DEFINE_EX( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy, \
  tpAssignBy ) \
\
  ZGVEC_DEFINITIONS( ZGENA_APPROACH_MODULAR, tpTypeInfo, tpSurname, tpPassBy, \
    tpReturnBy, tpAssignBy )

/******************************************************************************/

#define ZGVEC_DECLARATIONS( tpTypeInfo, tpSurname, tpPassBy, tpReturnBy ) \
\
  ZZ_GVEC_DEFINE_TYPE( tpTypeInfo, tpPassBy, tpSurname ); \
  ZZ_GVEC_DECLARATIONS_LIST( \
    tpSurname, \
    ZGENA_DATA_TYPE(tpTypeInfo, tpReturnBy), \
    ZGENA_DATA_NAKED(tpTypeInfo, tpPassBy), \
    ZGENA_DATA_NAKED(tpTypeInfo, tpReturnBy) \
  ); \
  ZGENA_REQUIRE_SEMICOLON_OUTSIDE

/******************************************************************************/

#define ZGVEC_DEFINITIONS( tpApproach, tpTypeInfo, tpSurname, tpPassBy, \
  tpReturnBy, tpAssignBy ) \
\
  tpApproach ( ZZ_GVEC_DEFINE_TYPE( tpTypeInfo, tpReturnBy, tpSurname ); ) \
  tpApproach ( static ) const gena_tag_z \
    gvec_##tpSurname##_tag = #tpSurname "_gvec"; \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  gvec_##tpSurname##_h \
  gvec_##tpSurname##_new( \
    size_t min_count \
  ) { \
  { \
    return igvec_new( \
      min_count, \
      ZGENA_DATA_SIZE(tpTypeInfo, tpPassBy), \
      gvec_##tpSurname##_tag \
    ); \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  gena_bool \
  gvec_##tpSurname##_reset( \
    gvec_##tpSurname##_h* phandle, \
    size_t count, \
    const ZGENA_DATA_NAKED(tpTypeInfo, tpPassBy) value \
  ) { \
    gvec_##tpSurname##_h new_handle; \
    size_t i; \
  { \
    assert( phandle != NULL ); \
    new_handle = igvec_resize( *phandle, count ); \
    if (new_handle == NULL) { return GENA_FALSE; } \
    for (i = 0; i < count; ++i) { \
      tpAssignBy ( \
        tpPassBy##ACCESS (new_handle + i), \
        tpPassBy##REFER value, \
        ZGENA_DATA_SIZE(tpTypeInfo, tpPassBy) \
      ); \
    } \
    *phandle = new_handle; \
    return GENA_TRUE; \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  gena_bool \
  gvec_##tpSurname##_resize( \
    gvec_##tpSurname##_h* phandle, \
    size_t new_count, \
    const ZGENA_DATA_NAKED(tpTypeInfo, tpPassBy) value \
  ) { \
    gvec_##tpSurname##_h new_handle; \
    size_t i; \
  { \
    assert( phandle != NULL ); \
    i = gvec_count(*phandle); \
    new_handle = igvec_resize( *phandle, new_count ); \
    if (new_handle == NULL) { return GENA_FALSE; } \
    for (; i < new_count; ++i) { \
      tpAssignBy ( \
        tpPassBy##ACCESS (new_handle + i), \
        tpPassBy##REFER value, \
        ZGENA_DATA_SIZE(tpTypeInfo, tpPassBy) \
      ); \
    } \
    *phandle = new_handle; \
    return GENA_TRUE; \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  gena_bool \
  gvec_##tpSurname##_reserve( \
    gvec_##tpSurname##_h* phandle, \
    size_t min_count \
  ) { \
    gvec_##tpSurname##_h new_handle; \
  { \
    assert( phandle != NULL ); \
    new_handle = igvec_reserve( *phandle, min_count ); \
    if (new_handle == NULL) { return GENA_FALSE; } \
    *phandle = new_handle; \
    return GENA_TRUE; \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  gena_bool \
  gvec_##tpSurname##_shrink( \
    gvec_##tpSurname##_h* phandle \
  ) { \
    gvec_##tpSurname##_h new_handle; \
  { \
    assert( phandle != NULL ); \
    new_handle = igvec_shrink( *phandle ); \
    if (new_handle == NULL) { return GENA_FALSE; } \
    *phandle = new_handle; \
    return GENA_TRUE; \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  gena_bool \
  gvec_##tpSurname##_insert( \
    gvec_##tpSurname##_h* phandle, \
    size_t position, \
    size_t count, \
    const ZGENA_DATA_NAKED(tpTypeInfo, tpPassBy) value \
  ) { \
    gvec_##tpSurname##_h new_handle; \
    size_t i; \
  { \
    assert( phandle != NULL ); \
    new_handle = igvec_insert( *phandle, position, count ); \
    if (new_handle == NULL) { return GENA_FALSE; } \
    for (i = 0; i < count; ++i) { \
      tpAssignBy ( \
        tpPassBy##ACCESS (new_handle + position + i), \
        tpPassBy##REFER value, \
        ZGENA_DATA_SIZE(tpTypeInfo, tpPassBy) \
      ); \
    } \
    *phandle = new_handle; \
    return GENA_TRUE; \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  gena_bool \
  gvec_##tpSurname##_push( \
    gvec_##tpSurname##_h* phandle, \
    const ZGENA_DATA_NAKED(tpTypeInfo, tpPassBy) value \
  ) { \
    gvec_##tpSurname##_h new_handle; \
    size_t count; \
  { \
    assert( phandle != NULL ); \
    count = gvec_count(*phandle); \
    new_handle = igvec_resize( *phandle, count+1 ); \
    if (new_handle == NULL) { return GENA_FALSE; } \
    tpAssignBy ( \
      tpPassBy##ACCESS (new_handle + count), \
      tpPassBy##REFER value, \
      ZGENA_DATA_SIZE(tpTypeInfo, tpPassBy) \
    ); \
    *phandle = new_handle; \
    return GENA_TRUE; \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  ZGENA_DATA_NAKED(tpTypeInfo, tpReturnBy) \
  gvec_##tpSurname##_pop( \
    gvec_##tpSurname##_h handle \
  ) { \
    igvec_header_p header; \
    ZGENA_DATA_BIND( tpTypeInfo, tpPassBy, *entry ) = NULL; \
  { \
    assert( handle != NULL ); \
    header = IGVEC_HEADER(handle); \
    if (header->count > 0) { entry = &handle[ --(header->count) ]; } \
    ZGENA_DATA_VERIFY( tpReturnBy, entry ); \
    return tpReturnBy##OBTAIN entry; \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  ZGENA_DATA_NAKED(tpTypeInfo, tpReturnBy) \
  gvec_##tpSurname##_value( \
    gena_iterator_p object, \
    ptrdiff_t offset \
  ) { \
    ZGENA_DATA_BIND( tpTypeInfo, tpPassBy, *entry ); \
  { \
    assert( object != NULL ); \
    entry = igena_iterator_entry( object, offset, NULL ); \
    ZGENA_DATA_VERIFY( tpReturnBy, entry ); \
    return tpReturnBy##OBTAIN entry; \
  }} \
/********************************************************************/ \
  tpApproach ( ZGENA_STATIC_APPROACH_FUNCTION ) \
  ZGENA_DATA_TYPE(tpTypeInfo, tpReturnBy) * \
  gvec_##tpSurname##_emplace( \
    gena_iterator_p object, \
    ptrdiff_t offset, \
    const ZGENA_DATA_NAKED(tpTypeInfo, tpPassBy) value \
  ) { \
    ZGENA_DATA_BIND( tpTypeInfo, tpPassBy, *entry ); \
  { \
    assert( object != NULL ); \
    entry = igena_iterator_entry( object, offset, NULL ); \
    if (entry == NULL) { return NULL; } \
    tpAssignBy ( \
      tpPassBy##ACCESS entry, \
      tpPassBy##REFER value, \
      ZGENA_DATA_SIZE(tpTypeInfo, tpPassBy) \
    ); \
    return tpReturnBy##ACCESS entry; \
  }} \
/********************************************************************/ \
  ZGENA_REQUIRE_SEMICOLON_OUTSIDE
