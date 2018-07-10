/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#include "gentreemap.h"

#include <stdlib.h>

/******************************************************************************/

static void* iterator_data( void* handle, void* data, ptrdiff_t offset ) {
  const gtmap_h info = handle;
{
  return igena_avl_node_step( data, offset,
    (offset < 0) ? info->tree_leftmost : info->tree_rightmost );
}}

static void* iterator_key( void* handle, void* data ) {
{
  return IGENA_AVL_NODE_KEY(data);
  GENA_VARIABLE_UNUSED(handle);
}}

static void* iterator_value( void* handle, void* data ) {
{
  return IGENA_AVL_NODE_VALUE( data, ((gtmap_h)handle)->key_size );
}}

static GENA_INLINE gena_bool init_iterator( gtmap_h handle, gena_bool reversed,
  igena_avl_node_p node, gena_iterator_p OUT_object ) {
{
  assert( OUT_object != NULL );

  if (handle->count == 0) { return GENA_FALSE; }

  OUT_object->internal.func_data = &iterator_data;
  OUT_object->internal.func_key = &iterator_key;
  OUT_object->internal.func_value = &iterator_value;
  OUT_object->internal.func_compare = NULL;

  OUT_object->internal.data = node;

  OUT_object->handle = handle;
  OUT_object->tag = handle->tag;
  OUT_object->key_size = handle->key_size;
  OUT_object->value_size = handle->value_size;
  OUT_object->reversed = reversed;

  return GENA_TRUE;
}}

/******************************************************************************/

gtmap_h igtmap_new( size_t key_size, size_t value_size, gena_tag_z tag ) {
  gtmap_h handle;
{
  handle = malloc( sizeof(igtmap_s) );
  if (handle == NULL) { return NULL; }

  handle->count = 0;
  handle->tree_root = NULL;
  handle->tree_leftmost = NULL;
  handle->tree_rightmost = NULL;

  handle->key_size = key_size;
  handle->value_size = value_size;
  handle->tag = tag;

  return handle;
}}

void gtmap_clear( gtmap_h handle ) {
{
  assert( handle != NULL );
  igena_avl_subtree_free( handle->tree_root );
  handle->count = 0;
  handle->tree_root = NULL;
  handle->tree_leftmost = NULL;
  handle->tree_rightmost = NULL;
}}

void gtmap_free( gtmap_h handle ) {
{
  if (handle == NULL) { return; }
  igena_avl_subtree_free( handle->tree_root );
  free( handle );
}}

/******************************************************************************/

size_t gtmap_count( gtmap_h handle ) {
{
  assert( handle != NULL );
  return handle->count;
}}

gena_bool gtmap_empty( gtmap_h handle ) {
{
  assert( handle != NULL );
  return (handle->count == 0);
}}

/******************************************************************************/

gena_bool gtmap_begin( gtmap_h handle, gena_bool reversed,
  gena_iterator_p OUT_object )
{
  igena_avl_node_p node;
{
  assert( handle != NULL );
  node = reversed ? handle->tree_rightmost : handle->tree_leftmost;
  return init_iterator( handle, reversed, node, OUT_object );
}}

gena_bool gtmap_end( gtmap_h handle, gena_bool reversed,
  gena_iterator_p OUT_object )
{
  igena_avl_node_p node;
{
  assert( handle != NULL );
  node = reversed ? handle->tree_leftmost : handle->tree_rightmost;
  return init_iterator( handle, reversed, node, OUT_object );
}}

gena_bool gtmap_at( gtmap_h handle, size_t position, gena_bool reversed,
  gena_iterator_p OUT_object )
{
  igena_avl_node_p node, begin_node, end_node;
{
  assert( handle != NULL );

  if (reversed) {
    begin_node = handle->tree_rightmost;
    end_node = handle->tree_leftmost;
    position = -position;
  } else {
    begin_node = handle->tree_leftmost;
    end_node = handle->tree_rightmost;
  }

  node = igena_avl_node_step( begin_node, position, end_node );
  return init_iterator( handle, reversed, node, OUT_object );
}}
