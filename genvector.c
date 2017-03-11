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

#define INIT_GVHEAD_PTR(var, hgvec) \
  var = GVEC_HDR(hgvec); \
  var->error = GVEC_ERR_NO

#define RETURN_GVEC_ERROR(cond, header, errcode, retval) \
  if (cond) { \
    header->error = errcode; \
    return retval; \
  } __GV_REQUIRE_SEMICOLON_INDOOR

#define RETVOID

/******************************************************************************/

static inline size_t calc_size( size_t count ) {
#ifdef GVEC_CALC_SIZE_MATH
  return (size_t)pow(
      GVEC_GROWTH_FACTOR,
      ceil( log( (count>0) ?count :1 ) / log(GVEC_GROWTH_FACTOR) )
    );
}
#else
  size_t size = 1;
{
  while (size < count) {
    /* GROWTH_FACTOR == 1.5: size = (size << 1) - (size >> 1);
       GROWTH_FACTOR == 2.0: size <<= 1; */
    size = (size_t)ceil( size * GVEC_GROWTH_FACTOR );
  }
  return size;
}}
#endif

static void* set_storage( size_t size, size_t unitsz, gvec_t origin ) {
  void* buffer;
  gvhead_p header;
  size_t buf_sz;
{
  buffer = (origin == NULL) ? NULL : GVEC_HDR(origin);
  buf_sz = (size == 0) ? 0 : ADDHDR_INT(size*unitsz);
  buffer = realloc( buffer, buf_sz );
  if (buffer == NULL) { return NULL; }

  header = (gvhead_p)buffer;
  /* if (header->count > size) { header->count = size; } */
  header->size = size;
  header->unitsz = unitsz;

  return buffer;
}}

/******************************************************************************/

gvec_t gvec_new( size_t min_count, size_t unitsz ) {
  void* buffer;
  gvhead_p header;
{
  assert( unitsz > 0 );

  buffer = set_storage( calc_size(min_count), unitsz, NULL );
  if (buffer == NULL) { return NULL; }

  header = (gvhead_p)buffer;
  header->count = 0;
  header->error = GVEC_ERR_NO;

  return ADDHDR_PTR(buffer);
}}

gvec_t gvec_set( gvec_t hgvec_dest, gvec_t hgvec_src ) {
  gvhead_p dest_hdr, src_hdr;
{
  assert( hgvec_dest != NULL );

  if (hgvec_src == NULL) {
    gvec_free( hgvec_dest );
    return NULL;
  }

  INIT_GVHEAD_PTR(dest_hdr, hgvec_dest);
  src_hdr = GVEC_HDR(hgvec_src);

  if (
      (dest_hdr->unitsz == src_hdr->unitsz) &&
      (dest_hdr->count >= src_hdr->count)
  ) {
    memcpy( hgvec_dest, hgvec_src, src_hdr->count * src_hdr->unitsz );
    dest_hdr->count = src_hdr->count;
  } else {
    gvec_free( hgvec_dest );
    hgvec_dest = gvec_copy( hgvec_src );
  }

  return hgvec_dest;
}}

gvec_t gvec_copy( gvec_t hgvec ) {
  void* buffer;
  gvhead_p src_hdr, dest_hdr;
{
  assert( hgvec != NULL );

  src_hdr = GVEC_HDR(hgvec);
  buffer = set_storage( src_hdr->size, src_hdr->unitsz, NULL );
  if (buffer == NULL) { return NULL; }

  dest_hdr = (gvhead_p)buffer;
  dest_hdr->count = src_hdr->count;
  dest_hdr->error = src_hdr->error;

  return memcpy( ADDHDR_PTR(buffer), hgvec,
      dest_hdr->count * dest_hdr->unitsz );
}}

void gvec_free( gvec_t hgvec ) {
{
  /* it should accept NULL as well as free() does */
  set_storage( 0, 0, hgvec );
}}

/******************************************************************************/

gvec_t gvec_resize( gvec_t hgvec, size_t new_count ) {
  gvhead_p header;
{
  assert( hgvec != NULL );
  INIT_GVHEAD_PTR(header, hgvec);

  RETURN_GVEC_ERROR( (header->count == new_count),
                     header, GVEC_ERR_IDLE, hgvec );

  if (new_count > header->size) {
    hgvec = gvec_insert( hgvec, header->count, new_count - header->count );
  } else {
    header->count = new_count;
  }

  return hgvec;
}}

gvec_t gvec_reserve( gvec_t hgvec, size_t count ) {
  void* new_buffer;
  gvhead_p header;
  size_t new_size;
{
  assert( hgvec != NULL );
  INIT_GVHEAD_PTR(header, hgvec);

  RETURN_GVEC_ERROR( (count == 0), header, GVEC_ERR_IDLE, hgvec );

  new_size = calc_size( header->size + count );
  new_buffer = set_storage( new_size, header->unitsz, hgvec );
  RETURN_GVEC_ERROR( (new_buffer == NULL), header, GVEC_ERR_MEMORY, hgvec );

  return ADDHDR_PTR(new_buffer);
}}

gvec_t gvec_shrink( gvec_t hgvec ) {
  void* new_buffer;
  gvhead_p header;
  size_t new_size;
{
  assert( hgvec != NULL );
  INIT_GVHEAD_PTR(header, hgvec);

  new_size = calc_size(header->count);
  RETURN_GVEC_ERROR( (header->size <= new_size), header, GVEC_ERR_IDLE, hgvec );

  new_buffer = set_storage( new_size, header->unitsz, hgvec );
  RETURN_GVEC_ERROR( (new_buffer == NULL), header, GVEC_ERR_MEMORY, hgvec );

  return ADDHDR_PTR(new_buffer);
}}

/******************************************************************************/

gvec_t gvec_insert( gvec_t hgvec, size_t pos, size_t count ) {
  gvec_t dest_gvec;
  gvhead_p header;
  size_t unitsz, old_count, new_count;
{
  assert( hgvec != NULL );
  INIT_GVHEAD_PTR(header, hgvec);
  assert( pos <= header->count );

  RETURN_GVEC_ERROR( (count == 0), header, GVEC_ERR_IDLE, hgvec );

  unitsz = header->unitsz;
  old_count = header->count;
  new_count = old_count + count;

  #ifndef GVEC_INSERT_NO_REALLOC

  if (new_count > header->size) {
    hgvec = gvec_reserve( hgvec, new_count - header->size );
    header = GVEC_HDR(hgvec);
    if (header->error != GVEC_ERR_NO) { return hgvec; }
  }

  dest_gvec = hgvec;

  #else

  /* This one doesn't use memory relocation and better for many insertions at
  arbitrary positions, in theory. */
  if (new_count > header->size) {
    dest_gvec = gvec_new( new_count, unitsz );
    RETURN_GVEC_ERROR( (dest_gvec == NULL), header, GVEC_ERR_MEMORY, hgvec );
    header = GVEC_HDR(dest_gvec);
    memmove( dest_gvec, hgvec, pos*unitsz );
  } else {
    dest_gvec = hgvec;
  }

  #endif

  memmove( VOIDP_ADD( dest_gvec, (pos+count)*unitsz ),
           VOIDP_ADD( hgvec, pos*unitsz ), (old_count-pos)*unitsz );

  header->count = new_count;

  #ifdef GVEC_INSERT_NO_REALLOC
  if (dest_gvec != hgvec) { gvec_free(hgvec); }
  #endif

  return dest_gvec;
}}

void gvec_erase( gvec_t hgvec, size_t pos, size_t count ) {
  gvhead_p header;
  size_t unitsz, tail_size;
{
  assert( hgvec != NULL );
  INIT_GVHEAD_PTR(header, hgvec);
  assert( pos+count <= header->count );

  RETURN_GVEC_ERROR( (count == 0), header, GVEC_ERR_IDLE, RETVOID );

  unitsz = header->unitsz;
  tail_size = (header->count-(pos+count)) * unitsz;

  memmove( VOIDP_ADD( hgvec, pos*unitsz ),
           VOIDP_ADD( hgvec, (pos+count)*unitsz ), tail_size );

  header->count -= count;
}}

gvec_t gvec_push( gvec_t hgvec ) {
{
  assert( hgvec != NULL );
  return gvec_resize( hgvec, gvec_count(hgvec)+1 );
}}

void gvec_pop( gvec_t hgvec ) {
  assert( hgvec != NULL );
  gvec_resize( hgvec, gvec_count(hgvec)-1 );
}

/******************************************************************************/

void* gvec_at( gvec_t hgvec, size_t pos ) {
  gvhead_p header;
{
  assert( hgvec != NULL );
  INIT_GVHEAD_PTR(header, hgvec);

  RETURN_GVEC_ERROR( (pos >= header->count), header, GVEC_ERR_IDLE, NULL );
  return VOIDP_ADD( hgvec, pos * header->unitsz );
}}

void* gvec_front( gvec_t hgvec ) {
{
  assert( hgvec != NULL );
  /* actually equals to 'hgvec', but this is more clearly */
  return VOIDP_ADD( hgvec, 0 );
}}

void* gvec_back( gvec_t hgvec ) {
  gvhead_p header;
{
  assert( hgvec != NULL );
  INIT_GVHEAD_PTR(header, hgvec);

  return VOIDP_ADD( hgvec, (header->count-1)*header->unitsz );
}}
