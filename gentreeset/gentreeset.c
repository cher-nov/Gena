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

static GENA_INLINE void init_iterator( void* handle, gena_tag_z tag,
  size_t entry_size, gena_bool reversed, void* data,
  gena_iterator_p OUT_object ) {
{
  OUT_object->internal.func_data = &iterator_data;
  OUT_object->internal.func_key = &iterator_entry;
  OUT_object->internal.func_value = &iterator_entry;
  OUT_object->internal.func_compare = NULL;

  OUT_object->internal.data = data;

  OUT_object->handle = handle;
  OUT_object->tag = tag;
  OUT_object->key_size = entry_size;
  OUT_object->value_size = entry_size;
  OUT_object->reversed = reversed;
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
  return (handle->tree_root == NULL);
}}

/******************************************************************************/

gena_bool gtset_begin( gtset_h handle, gena_bool reversed,
  gena_iterator_p OUT_object ) {
{
  assert( handle != NULL );
  assert( OUT_object != NULL );

  if (handle->tree_leftmost == NULL) { return GENA_FALSE; }

  init_iterator( handle, handle->tag, handle->entry_size, reversed,
    handle->tree_leftmost, OUT_object );

  return GENA_TRUE;
}}

gena_bool gtset_end( gtset_h handle, gena_bool reversed,
  gena_iterator_p OUT_object ) {
{
  assert( handle != NULL );
  assert( OUT_object != NULL );

  if (handle->tree_rightmost == NULL) { return GENA_FALSE; }

  init_iterator( handle, handle->tag, handle->entry_size, reversed,
    handle->tree_rightmost, OUT_object );

  return GENA_TRUE;
}}

gena_bool gtset_at( gtset_h handle, size_t position, gena_bool reversed,
  gena_iterator_p OUT_object )
{
  igena_avl_node_p node;
{
  assert( handle != NULL );
  assert( OUT_object != NULL );

  if (handle->tree_leftmost == NULL) { return GENA_FALSE; }
  node = igena_avl_node_step( handle->tree_leftmost, position,
    handle->tree_rightmost );
  if (node == NULL) { return GENA_FALSE; }

  init_iterator( handle, handle->tag, handle->entry_size, reversed, node,
    OUT_object );

  return GENA_TRUE;
}}
