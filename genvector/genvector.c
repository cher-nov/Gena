/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#include "genvector.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#ifndef GVEC_GROWTH_FACTOR
  #define GVEC_GROWTH_FACTOR 1.5
#endif

/******************************************************************************/

static GENA_INLINE size_t calc_size( size_t current_size, size_t min_add ) {
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

static igvec_head_p set_storage( gvec_h* phandle, size_t size,
  size_t entry_size )
{
  void* buffer;
  igvec_head_p header;
{
  assert( phandle != NULL );
  assert( size > 0 );
  assert( entry_size > 0 );

  buffer = (*phandle == NULL) ? NULL : IGVEC_GET_BUFFER(*phandle);

  if (buffer != NULL) {
    header = (igvec_head_p)buffer;
    if (size == header->size) { return header; }
  }

  buffer = realloc( buffer, sizeof(igvec_head_s) + size * entry_size );
  if (buffer == NULL) { return NULL; }

  *phandle = ZGENA_VOIDP_ADD( buffer, sizeof(igvec_head_s) );

  header = (igvec_head_p)buffer;
  header->size = size;
  header->entry_size = entry_size;

  return header;
}}

/******************************************************************************/

gvec_h igvec_new( size_t min_count, size_t entry_size ) {
  gvec_h handle = NULL;
  igvec_head_p header;
{
  header = set_storage( &handle, calc_size(0, min_count), entry_size );
  if (header == NULL) { return NULL; }

  header->count = 0;
  return handle;
}}

gvec_h igvec_resize( gvec_h handle, size_t new_count ) {
{
  assert( handle != NULL );

  handle = igvec_reserve( handle, new_count );
  if (handle == NULL) { return NULL; }

  IGVEC_GET_HEADER(handle)->count = new_count;
  return handle;
}}

gvec_h igvec_reserve( gvec_h handle, size_t min_count ) {
  igvec_head_p header;
  size_t new_size;
{
  assert( handle != NULL );
  header = IGVEC_GET_HEADER(handle);

  if (min_count <= header->size) { return handle; }

  new_size = calc_size( header->size, min_count - header->count );
  header = set_storage( &handle, new_size, header->entry_size );
  if (header == NULL) { return NULL; }

  return handle;
}}

gvec_h igvec_shrink( gvec_h handle ) {
  igvec_head_p header;
  size_t new_size;
{
  assert( handle != NULL );
  header = IGVEC_GET_HEADER(handle);

  new_size = calc_size( 0, header->count );
  header = set_storage( &handle, new_size, header->entry_size );
  if (header == NULL) { return NULL; }

  return handle;
}}

gvec_h igvec_insert( gvec_h handle, size_t pos, size_t count ) {
  gvec_h dest_gvec;
  igvec_head_p header;
  size_t entry_size, old_count, new_count;
{
  assert( handle != NULL );
  header = IGVEC_GET_HEADER(handle);
  assert( pos <= header->count );

  if (count == 0) { return handle; }

  entry_size = header->entry_size;
  old_count = header->count;
  new_count = old_count + count;

  #ifndef GVEC_INSERT_NO_REALLOC

  handle = igvec_reserve( handle, new_count );
  if (handle == NULL) { return NULL; }
  header = IGVEC_GET_HEADER(handle);
  dest_gvec = handle;

  #else

  /* This one doesn't use memory relocation and better for many insertions at
  arbitrary positions, in theory. */
  if (new_count > header->size) {
    dest_gvec = igvec_new( new_count, entry_size );
    if (dest_gvec == NULL) { return NULL; }
    header = IGVEC_GET_HEADER(dest_gvec);
    memmove( dest_gvec, handle, pos*entry_size );
  } else {
    dest_gvec = handle;
  }

  #endif

  memmove(
    ZGENA_VOIDP_ADD( dest_gvec, (pos+count) * entry_size ),
    ZGENA_VOIDP_ADD( handle, pos * entry_size ),
    (old_count-pos) * entry_size
  );

  header->count = new_count;

  #ifdef GVEC_INSERT_NO_REALLOC
  if (handle != dest_gvec) { gvec_free(handle); }
  #endif

  return dest_gvec;
}}

gvec_h igvec_push( gvec_h handle ) {
{
  assert( handle != NULL );
  return igvec_resize( handle, gvec_count(handle)+1 );
}}

/******************************************************************************/

gvec_h gvec_set( gvec_h handle, gvec_h source ) {
  igvec_head_p dest_hdr, src_hdr;
{
  assert( handle != NULL );
  assert( source != NULL );

  dest_hdr = IGVEC_GET_HEADER(handle);
  src_hdr = IGVEC_GET_HEADER(source);

  assert( dest_hdr->entry_size == src_hdr->entry_size );

  handle = igvec_resize( handle, src_hdr->count );
  if (handle == NULL) { return NULL; }

  return memcpy( handle, source, src_hdr->count * src_hdr->entry_size );
}}

gvec_h gvec_copy( gvec_h handle ) {
  gvec_h dest_handle = NULL;
  igvec_head_p src_hdr, dest_hdr;
{
  assert( handle != NULL );
  src_hdr = IGVEC_GET_HEADER(handle);

  dest_hdr = set_storage( &dest_handle, src_hdr->size, src_hdr->entry_size );
  if (dest_hdr == NULL) { return NULL; }

  dest_hdr->count = src_hdr->count;
  return memcpy( dest_handle, handle, src_hdr->count * src_hdr->entry_size );
}}

void gvec_free( gvec_h handle ) {
{
  if (handle == NULL) { return; }
  free( IGVEC_GET_BUFFER(handle) );
}}

/******************************************************************************/

void gvec_clear( gvec_h handle ) {
{
  gvec_reduce( handle, 0 );
}}

void gvec_reduce( gvec_h handle, size_t new_count ) {
  igvec_head_p header;
{
  assert( handle != NULL );
  header = IGVEC_GET_HEADER(handle);
  assert( new_count <= header->count );

  header->count = new_count;
}}

void gvec_erase( gvec_h handle, size_t pos, size_t count ) {
  igvec_head_p header;
  size_t entry_size, tail_size;
{
  assert( handle != NULL );
  header = IGVEC_GET_HEADER(handle);
  assert( pos+count <= header->count );

  if (count == 0) { return; }

  entry_size = header->entry_size;
  tail_size = (header->count-(pos+count)) * entry_size;

  memmove(
    ZGENA_VOIDP_ADD( handle, pos * entry_size ),
    ZGENA_VOIDP_ADD( handle, (pos+count) * entry_size ),
    tail_size
  );

  header->count -= count;
}}

void gvec_pop( gvec_h handle ) {
{
  assert( handle != NULL ); /* not really necessary here */
  gvec_reduce( handle, gvec_count(handle)-1 );
}}

/******************************************************************************/

void* gvec_at( gvec_h handle, size_t pos ) {
  igvec_head_p header;
{
  assert( handle != NULL );
  header = IGVEC_GET_HEADER(handle);
  return (pos < header->count)
    ? ZGENA_VOIDP_ADD( handle, pos * header->entry_size )
    : NULL;
}}

void* gvec_front( gvec_h handle ) {
{
  assert( handle != NULL );
  /* actually equals to 'handle', but this is more clearly */
  return ZGENA_VOIDP_ADD( handle, 0 );
}}

void* gvec_back( gvec_h handle ) {
  igvec_head_p header;
{
  assert( handle != NULL );
  header = IGVEC_GET_HEADER(handle);
  return ZGENA_VOIDP_ADD( handle, (header->count-1) * header->entry_size );
}}

/******************************************************************************/

size_t gvec_count( gvec_h handle ) {
{
  assert( handle != NULL );
  return IGVEC_GET_HEADER(handle)->count;
}}

size_t gvec_size( gvec_h handle ) {
{
  assert( handle != NULL );
  return IGVEC_GET_HEADER(handle)->size;
}}

gena_bool gvec_empty( gvec_h handle ) {
{
  return (gvec_count(handle) == 0);
}}
