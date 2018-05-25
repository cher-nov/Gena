/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#include "gentreemap.h"

#include <stdlib.h>

/******************************************************************************/

static void* iterator_data( void* handle, void* data, ptrdiff_t offset ) {
{
  return igena_avl_node_step( data, offset );
  GENA_VARIABLE_UNUSED(handle);
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

static GENA_INLINE void init_iterator( void* handle, gena_tag_z tag,
  size_t key_size, size_t value_size, gena_bool reversed, void* data,
  gena_iterator_p OUT_object ) {
{
  OUT_object->internal.func_data = &iterator_data;
  OUT_object->internal.func_key = &iterator_key;
  OUT_object->internal.func_value = &iterator_value;
  OUT_object->internal.func_compare = NULL;

  OUT_object->internal.data = data;

  OUT_object->handle = handle;
  OUT_object->tag = tag;
  OUT_object->key_size = key_size;
  OUT_object->value_size = value_size;
  OUT_object->reversed = reversed;
}}

/******************************************************************************/

gtmap_h igtmap_new( size_t key_size, size_t value_size, gena_tag_z tag ) {
  gtmap_h handle;
{
  handle = malloc( sizeof(igtmap_s) );
  if (handle == NULL) { return NULL; }

  handle->tree_root = NULL;
  handle->count = 0;

  handle->key_size = key_size;
  handle->value_size = value_size;
  handle->tag = tag;

  return handle;
}}

void gtmap_clear( gtmap_h handle ) {
{
  assert( handle != NULL );
  igena_avl_subtree_free( handle->tree_root );
  handle->tree_root = NULL;
  handle->count = 0;
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
  return (handle->tree_root == NULL);
}}

/******************************************************************************/

gena_bool gtmap_begin( gtmap_h handle, gena_bool reversed,
  gena_iterator_p OUT_object )
{
  igena_avl_node_p leftmost;
{
  assert( handle != NULL );
  assert( OUT_object != NULL );

  if (handle->count == 0) { return GENA_FALSE; }

  leftmost = handle->tree_root;
  while (leftmost->left != NULL) {
    leftmost = leftmost->left;
  };

  init_iterator( handle, handle->tag, handle->key_size, handle->value_size,
    reversed, leftmost, OUT_object );

  return GENA_TRUE;
}}

gena_bool gtmap_end( gtmap_h handle, gena_bool reversed,
  gena_iterator_p OUT_object )
{
  igena_avl_node_p rightmost;
{
  assert( handle != NULL );
  assert( OUT_object != NULL );

  if (handle->count == 0) { return GENA_FALSE; }

  rightmost = handle->tree_root;
  while (rightmost->left != NULL) {
    rightmost = rightmost->right;
  };

  init_iterator( handle, handle->tag, handle->key_size, handle->value_size,
    reversed, rightmost, OUT_object );

  return GENA_TRUE;
}}
