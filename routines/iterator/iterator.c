/*
  Copyright (c) 2018, Dmitry D. Chernov
*/

#include "iterator.h"

/******************************************************************************/

static GENA_INLINE void* access_data( gena_iterator_p object,
  ptrdiff_t offset ) {
{
  assert( object != NULL );
  assert( object->internal.func_data != NULL );

  if (offset == 0) { return object->internal.data; }
  if (object->reversed) { offset = -offset; }

  return object->internal.func_data( object->handle, object->internal.data,
    offset );
}}

/******************************************************************************/

void* igena_iterator_entry( gena_iterator_p object, ptrdiff_t offset,
  void** OUT_key )
{
  void* data;
{
  assert( object->internal.func_value != NULL );

  data = access_data( object, offset );
  if (data == NULL) { return NULL; }

  if (OUT_key != NULL) {
    *OUT_key = (object->internal.func_key != NULL)
      ? object->internal.func_key( object->handle, data )
      : NULL;
  }

  return object->internal.func_value( object->handle, data );
}}

/******************************************************************************/

gena_bool gena_iterator_next( gena_iterator_p object ) {
  void* new_data;
{
  new_data = access_data( object, 1 );
  if (new_data == NULL) { return GENA_FALSE; }
  object->internal.data = new_data;
  return GENA_TRUE;
}}

gena_bool gena_iterator_prior( gena_iterator_p object ) {
  void* new_data;
{
  new_data = access_data( object, -1 );
  if (new_data == NULL) { return GENA_FALSE; }
  object->internal.data = new_data;
  return GENA_TRUE;
}}

gena_bool gena_iterator_move( gena_iterator_p object, ptrdiff_t offset ) {
  void* new_data;
{
  new_data = access_data( object, offset );
  if (new_data == NULL) { return GENA_FALSE; }
  object->internal.data = new_data;
  return GENA_TRUE;
}}

/******************************************************************************/

gena_bool gena_iterator_front( gena_iterator_p object, ptrdiff_t offset ) {
{
  return ( access_data( object, offset-1 ) == NULL );
}}

gena_bool gena_iterator_back( gena_iterator_p object, ptrdiff_t offset ) {
{
  return ( access_data( object, offset+1 ) == NULL );
}}

/******************************************************************************/

gena_bool gena_iterator_equal( gena_iterator_p object, ptrdiff_t offset1,
  gena_iterator_p iterator, ptrdiff_t offset2 )
{
  void *data1, *data2;
{
  data1 = access_data( object, offset1 );
  data2 = access_data( iterator, offset2 );

  return (data1 == data2);
}}

int gena_iterator_compare( gena_iterator_p object, ptrdiff_t offset1,
  gena_iterator_p iterator, ptrdiff_t offset2 )
{
  void *data1, *data2;
{
  data1 = access_data( object, offset1 );
  data2 = access_data( iterator, offset2 );

  assert( object->handle == iterator->handle );
  assert( object->internal.func_compare != NULL );

  return object->internal.func_compare( data1, data2 );
}}
