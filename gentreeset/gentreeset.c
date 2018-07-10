/*
  Copyright (c) 2018, Dmitry D. Chernov
*/

#include "gentreeset.h"

#include <stdlib.h>

/******************************************************************************/

static void* iterator_data( void* handle, void* data, ptrdiff_t offset ) {
  const gtset_h info = handle;
{
  return igena_avl_node_step( data, offset,
    (offset < 0) ? info->tree_leftmost : info->tree_rightmost );
}}

static void* iterator_entry( void* handle, void* data ) {
{
  return IGENA_AVL_NODE_KEY(data);
  GENA_VARIABLE_UNUSED(handle);
}}

static GENA_INLINE gena_bool init_iterator( gtset_h handle, gena_bool reversed,
  igena_avl_node_p node, gena_iterator_p OUT_object ) {
{
  assert( OUT_object != NULL );

  if (handle->count == 0) { return GENA_FALSE; }

  OUT_object->internal.func_data = &iterator_data;
  OUT_object->internal.func_key = &iterator_entry;
  OUT_object->internal.func_value = &iterator_entry;
  OUT_object->internal.func_compare = NULL;

  OUT_object->internal.data = node;

  OUT_object->handle = handle;
  OUT_object->tag = handle->tag;
  OUT_object->key_size = handle->entry_size;
  OUT_object->value_size = handle->entry_size;
  OUT_object->reversed = reversed;

  return GENA_TRUE;
}}

/******************************************************************************/

gtset_h igtset_new( size_t entry_size, gena_tag_z tag ) {
  gtset_h handle;
{
  handle = malloc( sizeof(igtset_s) );
  if (handle == NULL) { return NULL; }

  handle->count = 0;
  handle->tree_root = NULL;
  handle->tree_leftmost = NULL;
  handle->tree_rightmost = NULL;

  handle->entry_size = entry_size;
  handle->tag = tag;

  return handle;
}}

void gtset_clear( gtset_h handle ) {
{
  assert( handle != NULL );
  igena_avl_subtree_free( handle->tree_root );
  handle->count = 0;
  handle->tree_root = NULL;
  handle->tree_leftmost = NULL;
  handle->tree_rightmost = NULL;
}}

void gtset_free( gtset_h handle ) {
{
  if (handle == NULL) { return; }
  igena_avl_subtree_free( handle->tree_root );
  free( handle );
}}

/******************************************************************************/

size_t gtset_count( gtset_h handle ) {
{
  assert( handle != NULL );
  return handle->count;
}}

gena_bool gtset_empty( gtset_h handle ) {
{
  assert( handle != NULL );
  return (handle->count == 0);
}}

/******************************************************************************/

gena_bool gtset_begin( gtset_h handle, gena_bool reversed,
  gena_iterator_p OUT_object )
{
  igena_avl_node_p node;
{
  assert( handle != NULL );
  node = reversed ? handle->tree_rightmost : handle->tree_leftmost;
  return init_iterator( handle, reversed, node, OUT_object );
}}

gena_bool gtset_end( gtset_h handle, gena_bool reversed,
  gena_iterator_p OUT_object )
{
  igena_avl_node_p node;
{
  assert( handle != NULL );
  node = reversed ? handle->tree_leftmost : handle->tree_rightmost;
  return init_iterator( handle, reversed, node, OUT_object );
}}

gena_bool gtset_at( gtset_h handle, size_t position, gena_bool reversed,
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
