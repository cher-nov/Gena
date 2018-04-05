/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#include "gentreemap.h"

#include <stdlib.h>
#include <assert.h>

gtmap_h igtmap_new( size_t key_size, size_t value_size ) {
  gtmap_h handle;
{
  handle = malloc( sizeof(igtmap_s) );
  if (handle == NULL) { return NULL; }

  handle->avltree_root = NULL;
  handle->count = 0;

  handle->key_size = key_size;
  handle->value_size = value_size;

  return handle;
}}

void gtmap_clear( gtmap_h handle ) {
{
  assert( handle != NULL );
  igena_avl_subtree_free( handle->avltree_root );
  handle->avltree_root = NULL;
  handle->count = 0;
}}

void gtmap_free( gtmap_h handle ) {
{
  if (handle == NULL) { return; }
  igena_avl_subtree_free( handle->avltree_root );
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
  return (handle->avltree_root == NULL);
}}
