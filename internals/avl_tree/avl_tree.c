/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#include "avl_tree.h"

#include <stdlib.h>

#define MIN2(a, b) ((a < b) ? (a) : (b))
#define MAX2(a, b) ((a > b) ? (a) : (b))

static const igena_avl_node_head_s leaf_node_c = { NULL, NULL, 0 };

/******************************************************************************/

static void rotate_node_left( igena_avl_node_head_p* pnode ) {
  igena_avl_node_head_p new_root;
{
  new_root = (*pnode)->right;
  (*pnode)->right = new_root->left;
  new_root->left = *pnode;
  (*pnode)->factor -= 1 + MAX2( 0, new_root->factor );
  new_root->factor -= 1 - MIN2( 0, (*pnode)->factor );
  *pnode = new_root;
}}

static void rotate_node_right( igena_avl_node_head_p* pnode ) {
  igena_avl_node_head_p new_root;
{
  new_root = (*pnode)->left;
  (*pnode)->left = new_root->right;
  new_root->right = *pnode;
  (*pnode)->factor += 1 - MIN2( 0, new_root->factor );
  new_root->factor += 1 + MAX2( 0, (*pnode)->factor );
  *pnode = new_root;
}}

static igena_avl_retstate_e detach_max_from_subleft(
  igena_avl_node_head_p* pnode, igena_avl_node_head_p* OUT_detached_node )
{
  igena_avl_retstate_e result;
{
  if ( (*pnode)->right == NULL ) {
    /* maximum is reached */
    *OUT_detached_node = *pnode;
    *pnode = (*pnode)->left;
    return IGENA_AVL_RETST_BALANCE;
  }

  result = detach_max_from_subleft( &(*pnode)->right, OUT_detached_node );
  if ( result == IGENA_AVL_RETST_BALANCE ) {
    --((*pnode)->factor);
    igena_avl_node_balance( pnode );
    if ( (*pnode)->factor != 0 ) { result = IGENA_AVL_RETST_RETURN; }
  }

  return result;
}}

static igena_avl_retstate_e detach_min_from_subright(
  igena_avl_node_head_p* pnode, igena_avl_node_head_p* OUT_detached_node )
{
  igena_avl_retstate_e result;
{
  if ( (*pnode)->left == NULL ) {
    /* minimum is reached */
    *OUT_detached_node = *pnode;
    *pnode = (*pnode)->right;
    return IGENA_AVL_RETST_BALANCE;
  }

  result = detach_min_from_subright( &(*pnode)->left, OUT_detached_node );
  if (result == IGENA_AVL_RETST_BALANCE) {
    ++((*pnode)->factor);
    igena_avl_node_balance( pnode );
    if ( (*pnode)->factor != 0 ) { result = IGENA_AVL_RETST_RETURN; }
  }

  return result;
}}

/******************************************************************************/

igena_avl_node_head_p igena_avl_node_create( size_t key_size,
  size_t value_size )
{
  void* buffer;
{
  buffer = malloc( sizeof(igena_avl_node_head_s) + key_size + value_size );
  if (buffer == NULL) { return NULL; }

  *(igena_avl_node_head_p)buffer = leaf_node_c;
  return buffer;
}}

gena_bool igena_avl_node_discard( igena_avl_node_head_p* pnode ) {
  igena_avl_retstate_e retstate;
  igena_avl_node_head_p orphan;
  gena_bool one_child = GENA_TRUE;
{
  if ( (*pnode)->left == NULL ) {
    orphan = (*pnode)->right;
  } else if ( (*pnode)->right == NULL ) {
    orphan = (*pnode)->left;
  } else {
    one_child = GENA_FALSE;

    if ( (*pnode)->left->factor + (*pnode)->right->factor < 0 ) {
      /* right->left subtree is longer */
      retstate = detach_min_from_subright( &(*pnode)->right, &orphan );
      if (retstate == IGENA_AVL_RETST_BALANCE) { --((*pnode)->factor); }
    } else {
      /* left->right subtree is longer / same height */
      retstate = detach_max_from_subleft( &(*pnode)->left, &orphan );
      if (retstate == IGENA_AVL_RETST_BALANCE) { ++((*pnode)->factor); }
    }

    orphan->left = (*pnode)->left;
    orphan->right = (*pnode)->right;
    orphan->factor = (*pnode)->factor;
  }

  free( *pnode );
  *pnode = orphan;

  return one_child;
}}

void igena_avl_node_balance( igena_avl_node_head_p* pnode ) {
{
  switch ( (*pnode)->factor ) {
    case -2:
      if ( (*pnode)->left->factor == 1 ) {
        rotate_node_left( &(*pnode)->left );
      }
      rotate_node_right( pnode );
    break;

    case 2:
      if ( (*pnode)->right->factor == -1 ) {
        rotate_node_right( &(*pnode)->right );
      }
      rotate_node_left( pnode );
    break;
  }
}}

/******************************************************************************/

void igena_avl_subtree_free( igena_avl_node_head_p node ) {
{
  if (node == NULL) { return; }
  igena_avl_subtree_free( node->left );
  igena_avl_subtree_free( node->right );
  free( node );
}}
