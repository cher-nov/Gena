#include "genvector.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "gvmacro.h"

#ifndef GVEC_GROWTH_FACTOR
  #define GVEC_GROWTH_FACTOR 1.5
#endif

#if __STDC_VERSION__ < 199901L
  #define inline
#endif

#define VOIDP_ADD(x, a) ((void*)((char*)x + a))
#define VOIDP_SUB(x, a) ((void*)((char*)x - a))

#define ADDHDR_INT(x) (x + sizeof(gvhead_s))
#define ADDHDR_PTR(x) VOIDP_ADD(x, sizeof(gvhead_s))

#define ASSERT_PHANDLE(phandle) \
  assert( phandle != NULL ); \
  assert( *phandle != NULL )

#define RETVOID

/******************************************************************************/

static inline size_t calc_size( size_t current_size, size_t min_add ) {
  size_t size;
{
  size = (current_size > 0) ? current_size : 1;

  #ifdef GVEC_CALC_SIZE_MATH

  size = (size_t)pow(
      GVEC_GROWTH_FACTOR,
      ceil( log( size+min_add ) / log(GVEC_GROWTH_FACTOR) )
    );

  #else

  while (size < current_size+min_add) {
    /* GROWTH_FACTOR == 1.5: size = (size << 1) - (size >> 1);
       GROWTH_FACTOR == 2.0: size <<= 1; */
    size = (size_t)ceil( size * GVEC_GROWTH_FACTOR );
  }

  #endif

  return size;
}}

static gvhead_p set_storage( gvec_t* phandle, size_t size, size_t unitsz ) {
  void* buffer;
  gvhead_p header;
{
  assert( phandle != NULL );
  assert( size > 0 );
  assert( unitsz > 0 );

  buffer = (*phandle == NULL) ? NULL : GVEC_GET_BUFFER(*phandle);

  if (buffer != NULL) {
    header = (gvhead_p)buffer;
    if (size == header->size) { return header; }
  }

  buffer = realloc( buffer, ADDHDR_INT(size*unitsz) );
  if (buffer == NULL) { return NULL; }

  *phandle = ADDHDR_PTR(buffer);

  header = (gvhead_p)buffer;
  header->size = size;
  header->unitsz = unitsz;

  return header;
}}

/******************************************************************************/

gvec_t gvec_new( size_t min_count, size_t unitsz ) {
  gvec_t handle = NULL;
  gvhead_p header;
{
  header = set_storage( &handle, calc_size(0, min_count), unitsz );
  if (header == NULL) { return NULL; }

  header->count = 0;
  return handle;
}}

void __gvec_set( gvec_t* phandle, gvec_t source ) {
  gvhead_p dest_hdr, src_hdr;
{
  assert( phandle != NULL );

  if (source == NULL) {
    gvec_free( *phandle );
    return;
  }

  if (*phandle == NULL) {
    *phandle = gvec_copy(source);
    return;
  }

  dest_hdr = GVEC_GET_HEADER(*phandle);
  src_hdr = GVEC_GET_HEADER(source);

  if (
      (dest_hdr->size * dest_hdr->unitsz) >= (src_hdr->size * src_hdr->unitsz)
  ) {
    memcpy( *phandle, source, src_hdr->count * src_hdr->unitsz );
    dest_hdr->count = src_hdr->count;
    dest_hdr->unitsz = src_hdr->unitsz;
  } else {
    gvec_free( phandle );
    *phandle = gvec_copy(source);
  }
}}

gvec_t gvec_copy( gvec_t handle ) {
  gvec_t dest_handle = NULL;
  gvhead_p src_hdr, dest_hdr;
{
  assert( handle != NULL );
  src_hdr = GVEC_GET_HEADER(handle);

  dest_hdr = set_storage( &dest_handle, src_hdr->size, src_hdr->unitsz );
  if (dest_hdr == NULL) { return NULL; }

  dest_hdr->count = src_hdr->count;
  return memcpy( dest_handle, handle, src_hdr->count * src_hdr->unitsz );
}}

void gvec_free( gvec_t handle ) {
{
  if (handle != NULL) { free( GVEC_GET_BUFFER(handle) ); }
}}

/******************************************************************************/

gvec_error_e __gvec_resize( gvec_t* phandle, size_t new_count ) {
  gvhead_p header;
{
  ASSERT_PHANDLE(phandle);
  header = GVEC_GET_HEADER(*phandle);

  if (new_count <= header->size) {
    header->count = new_count;
    return GVEC_ERR_NO;
  }

  return gvec_insert( phandle, header->count, new_count - header->count );
}}

gvec_error_e __gvec_reserve( gvec_t* phandle, size_t count ) {
  gvhead_p header;
  size_t new_size;
{
  ASSERT_PHANDLE(phandle);
  header = GVEC_GET_HEADER(*phandle);

  new_size = calc_size( header->size, count );
  return (set_storage( phandle, new_size, header->unitsz ) != NULL)
         ? GVEC_ERR_NO
         : GVEC_ERR_MEMORY;
}}

gvec_error_e __gvec_shrink( gvec_t* phandle ) {
  gvhead_p header;
  size_t new_size;
{
  ASSERT_PHANDLE(phandle);
  header = GVEC_GET_HEADER(*phandle);

  new_size = calc_size( 0, header->count );
  return (set_storage( phandle, new_size, header->unitsz ) != NULL)
         ? GVEC_ERR_NO
         : GVEC_ERR_MEMORY;
}}

/******************************************************************************/

gvec_error_e __gvec_insert( gvec_t* phandle, size_t pos, size_t count ) {
  gvec_t dest_gvec;
  gvhead_p header;
  size_t unitsz, old_count, new_count;
{
  ASSERT_PHANDLE(phandle);
  header = GVEC_GET_HEADER(*phandle);
  assert( pos <= header->count );

  if (count == 0) { return GVEC_ERR_NO; }

  unitsz = header->unitsz;
  old_count = header->count;
  new_count = old_count + count;

  #ifndef GVEC_INSERT_NO_REALLOC

  if (new_count > header->size) {
    gvec_error_e errorcode = gvec_reserve( phandle, new_count - header->size );
    if (errorcode != GVEC_ERR_NO) { return errorcode; }
    header = GVEC_GET_HEADER(*phandle);
  }

  dest_gvec = *phandle;

  #else

  /* This one doesn't use memory relocation and better for many insertions at
  arbitrary positions, in theory. */
  if (new_count > header->size) {
    dest_gvec = gvec_new( new_count, unitsz );
    if (dest_gvec == NULL) { return GVEC_ERR_MEMORY; }
    header = GVEC_GET_HEADER(dest_gvec);
    memmove( dest_gvec, *phandle, pos*unitsz );
  } else {
    dest_gvec = *phandle;
  }

  #endif

  memmove( VOIDP_ADD( dest_gvec, (pos+count)*unitsz ),
           VOIDP_ADD( *phandle, pos*unitsz ), (old_count-pos)*unitsz );

  header->count = new_count;

  #ifdef GVEC_INSERT_NO_REALLOC
  if (*phandle != dest_gvec) {
    gvec_free(*phandle);
    *phandle = dest_gvec;
  }
  #endif

  return GVEC_ERR_NO;
}}

void gvec_erase( gvec_t handle, size_t pos, size_t count ) {
  gvhead_p header;
  size_t unitsz, tail_size;
{
  assert( handle != NULL );
  header = GVEC_GET_HEADER(handle);
  assert( pos+count <= header->count );

  if (count == 0) { return; }

  unitsz = header->unitsz;
  tail_size = (header->count-(pos+count)) * unitsz;

  memmove( VOIDP_ADD( handle, pos*unitsz ),
           VOIDP_ADD( handle, (pos+count)*unitsz ), tail_size );

  header->count -= count;
}}

gvec_error_e __gvec_push( gvec_t* phandle ) {
{
  ASSERT_PHANDLE(phandle);
  return gvec_resize( phandle, gvec_count(*phandle)+1 );
}}

void gvec_pop( gvec_t handle ) {
  assert( handle != NULL );
  gvec_erase( handle, gvec_count(handle)-1, 1 );
}

/******************************************************************************/

void* gvec_at( gvec_t handle, size_t pos ) {
  gvhead_p header;
{
  assert( handle != NULL );
  header = GVEC_GET_HEADER(handle);
  return (pos < header->count)
         ? VOIDP_ADD( handle, pos * header->unitsz )
         : NULL;
}}

void* gvec_front( gvec_t handle ) {
{
  assert( handle != NULL );
  /* actually equals to 'handle', but this is more clearly */
  return VOIDP_ADD( handle, 0 );
}}

void* gvec_back( gvec_t handle ) {
  gvhead_p header;
{
  assert( handle != NULL );
  header = GVEC_GET_HEADER(handle);
  return VOIDP_ADD( handle, (header->count-1)*header->unitsz );
}}

/******************************************************************************/

size_t gvec_count( gvec_t handle ) {
  assert( handle != NULL );
  return GVEC_GET_HEADER(handle)->count;
}

size_t gvec_size( gvec_t handle ) {
  assert( handle != NULL );
  return GVEC_GET_HEADER(handle)->size;
}
