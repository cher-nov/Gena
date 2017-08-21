/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#include "genmap.h"

#include <stdlib.h>
#include <assert.h>

gmap_t igmap_new( size_t key_size, size_t value_size ) {
  gmap_t handle;
{
  handle = malloc( sizeof(gmap_s) );
  if (handle == NULL) { return NULL; }

  handle->avltree_root = NULL;
  handle->count = 0;

  handle->key_size = key_size;
  handle->value_size = value_size;

  return handle;
}}

void gmap_clear( gmap_t handle ) {
{
  assert( handle != NULL );
  igena_avl_subtree_free( handle->avltree_root );
  handle->avltree_root = NULL;
  handle->count = 0;
}}

void gmap_free( gmap_t handle ) {
{
  if (handle == NULL) { return; }
  igena_avl_subtree_free( handle->avltree_root );
  free( handle );
}}

/******************************************************************************/

size_t gmap_count( gmap_t handle ) {
{
  assert( handle != NULL );
  return handle->count;
}}

gena_bool gmap_empty( gmap_t handle ) {
{
  return (handle->avltree_root == NULL);
}}
