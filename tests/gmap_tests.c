#include "gmap_tests.h"

#include <string.h>

#define C_SKEY(x) ( (gmaptest_key_s){x, x} )
#define C_SVALUE(x) ( (gmaptest_value_s){x} )

static void set_key_safe( gmaptest_key_p key, int x ) {
  memset( key, 0, sizeof(gmaptest_key_s) );
  key->key = x;
}

/******************************************************************************/

MunitResult gmaptests_1_create() {
  gmap_naive_t map_naive;
  gmap_memcmp_t map_memcmp;
  gmap_callback_t map_callback;
{
  /********************************************************************/
  map_naive = gmap_new();
  munit_assert_not_null( map_naive );
  munit_assert( gmap_empty(map_naive) );
  munit_assert_size( gmap_count(map_naive), ==, 0 );
  gmap_free( map_naive );

  /********************************************************************/
  map_memcmp = gmap_new();
  munit_assert_not_null( map_memcmp );
  munit_assert( gmap_empty(map_memcmp) );
  munit_assert_size( gmap_count(map_memcmp), ==, 0 );
  gmap_free( map_memcmp );

  /********************************************************************/
  map_callback = gmap_new();
  munit_assert_not_null( map_callback );
  munit_assert( gmap_empty(map_callback) );
  munit_assert_size( gmap_count(map_callback), ==, 0 );
  gmap_free( map_callback );

  /********************************************************************/
  return MUNIT_OK;
}}

/******************************************************************************/

MunitResult gmaptests_2_modify() {
  gmap_naive_t map_naive;
  gmap_memcmp_t map_memcmp;
  gmap_callback_t map_callback;
  gena_bool del_result;
  int* ptr_int;
  gmaptest_value_p ptr_svalue;
  int i;
{
  /********************************************************************/
  map_naive = gmap_new();

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    ptr_int = gmap_naive_add( map_naive, GENATEST_INT_SET[i], i );
    munit_assert_not_null( ptr_int );
    munit_assert_int( *ptr_int, ==, i );
    munit_assert_size( gmap_count(map_naive), ==, i+1 );
    munit_assert( !gmap_empty(map_naive) );
  }

  for( i = (int)GENATEST_INT_SET_LEN; i-- > 1; ) {
    del_result = gmap_naive_delete( map_naive, GENATEST_INT_SET[i] );
    munit_assert( del_result );
    munit_assert_size( gmap_count(map_naive), ==, i );
    munit_assert( !gmap_empty(map_naive) );
  }

  gmap_clear( map_naive );
  munit_assert_size( gmap_count(map_naive), ==, 0 );
  munit_assert( gmap_empty(map_naive) );

  gmap_free( map_naive );

  /********************************************************************/
  map_memcmp = gmap_new();

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    gmaptest_key_s safe_skey;
    set_key_safe( &safe_skey, GENATEST_INT_SET[i] );

    ptr_svalue = gmap_memcmp_add( map_memcmp, &safe_skey, &C_SVALUE(i) );
    munit_assert_not_null( ptr_svalue );
    munit_assert_memory_equal( sizeof(gmaptest_value_s), ptr_svalue,
      &C_SVALUE(i) );
    munit_assert_size( gmap_count(map_memcmp), ==, i+1 );
    munit_assert( !gmap_empty(map_memcmp) );
  }

  for( i = (int)GENATEST_INT_SET_LEN; i-- > 1; ) {
    gmaptest_key_s safe_skey;
    set_key_safe( &safe_skey, GENATEST_INT_SET[i] );

    del_result = gmap_memcmp_delete( map_memcmp, &safe_skey );
    munit_assert( del_result );
    munit_assert_size( gmap_count(map_memcmp), ==, i );
    munit_assert( !gmap_empty(map_memcmp) );
  }

  gmap_clear( map_memcmp );
  munit_assert_size( gmap_count(map_memcmp), ==, 0 );
  munit_assert( gmap_empty(map_memcmp) );

  gmap_free( map_memcmp );

  /********************************************************************/
  map_callback = gmap_new();

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    ptr_svalue = gmap_callback_add( map_callback, &C_SKEY(GENATEST_INT_SET[i]),
      &C_SVALUE(i) );
    munit_assert_not_null( ptr_svalue );
    munit_assert_int( ptr_svalue->value, ==, i );
    munit_assert_size( gmap_count(map_callback), ==, i+1 );
    munit_assert( !gmap_empty(map_callback) );
  }

  for( i = (int)GENATEST_INT_SET_LEN; i-- > 1; ) {
    del_result = gmap_callback_delete( map_callback,
      &C_SKEY(GENATEST_INT_SET[i]) );
    munit_assert( del_result );
    munit_assert_size( gmap_count(map_callback), ==, i );
    munit_assert( !gmap_empty(map_callback) );
  }

  gmap_clear( map_callback );
  munit_assert_size( gmap_count(map_callback), ==, 0 );
  munit_assert( gmap_empty(map_callback) );

  gmap_free( map_callback );

  /********************************************************************/
  return MUNIT_OK;
}}

/******************************************************************************/

MunitResult gmaptests_3_lookup() {
  gmap_naive_t map_naive;
  gmap_memcmp_t map_memcmp;
  gmap_callback_t map_callback;
  int* ptr_int;
  gmaptest_value_p ptr_svalue;
  int i, k;
  gmaptest_key_s safe_skey;
{
  /********************************************************************/
  map_naive = gmap_new();

  ptr_int = gmap_naive_find( map_naive, 0 );
  munit_assert_null( ptr_int );

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    gmap_naive_add( map_naive, GENATEST_INT_SET[i], i );
    for( k = 0; k <= i; ++k ) {
      ptr_int = gmap_naive_find( map_naive, GENATEST_INT_SET[k] );
      munit_assert_not_null( ptr_int );
      munit_assert_int( *ptr_int, ==, k );
    }
  }

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; i += 2 ) {
    gmap_naive_delete( map_naive, GENATEST_INT_SET[i] );
    for( k = 0; k <= i; ++k ) {
      ptr_int = gmap_naive_find( map_naive, GENATEST_INT_SET[k] );
      if (k % 2 == 0) {
        munit_assert_null( ptr_int );
      } else {
        munit_assert_not_null( ptr_int );
        munit_assert_int( *ptr_int, ==, k );
      }
    }
  }

  gmap_clear( map_naive );
  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    ptr_int = gmap_naive_find( map_naive, GENATEST_INT_SET[i] );
    munit_assert_null( ptr_int );
  }

  gmap_free( map_naive );

  /********************************************************************/
  map_memcmp = gmap_new();

  set_key_safe( &safe_skey, 0 );
  ptr_svalue = gmap_memcmp_find( map_memcmp, &safe_skey );
  munit_assert_null( ptr_svalue );

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    set_key_safe( &safe_skey, GENATEST_INT_SET[i] );
    gmap_memcmp_add( map_memcmp, &safe_skey, &C_SVALUE(i) );
    for( k = 0; k <= i; ++k ) {
      set_key_safe( &safe_skey, GENATEST_INT_SET[k] );
      ptr_svalue = gmap_memcmp_find( map_memcmp, &safe_skey );
      munit_assert_not_null( ptr_svalue );
      munit_assert_int( ptr_svalue->value, ==, k );
    }
  }

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; i += 2 ) {
    set_key_safe( &safe_skey, GENATEST_INT_SET[i] );
    gmap_memcmp_delete( map_memcmp, &safe_skey );
    for( k = 0; k <= i; ++k ) {
      set_key_safe( &safe_skey, GENATEST_INT_SET[k] );
      ptr_svalue = gmap_memcmp_find( map_memcmp, &safe_skey );
      if (k % 2 == 0) {
        munit_assert_null( ptr_svalue );
      } else {
        munit_assert_not_null( ptr_svalue );
        munit_assert_int( ptr_svalue->value, ==, k );
      }
    }
  }

  gmap_clear( map_memcmp );
  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    set_key_safe( &safe_skey, GENATEST_INT_SET[i] );
    ptr_svalue = gmap_memcmp_find( map_memcmp, &safe_skey );
    munit_assert_null( ptr_svalue );
  }

  gmap_free( map_memcmp );

  /********************************************************************/
  map_callback = gmap_new();

  ptr_svalue = gmap_callback_find( map_callback, &C_SKEY(0) );
  munit_assert_null( ptr_svalue );

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    gmap_callback_add( map_callback, &C_SKEY(GENATEST_INT_SET[i]),
      &C_SVALUE(i) );
    for( k = 0; k <= i; ++k ) {
      ptr_svalue = gmap_callback_find( map_callback,
        &C_SKEY(GENATEST_INT_SET[k]) );
      munit_assert_not_null( ptr_svalue );
      munit_assert_int( ptr_svalue->value, ==, k );
    }
  }

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; i += 2 ) {
    gmap_callback_delete( map_callback, &C_SKEY(GENATEST_INT_SET[i]) );
    for( k = 0; k <= i; ++k ) {
      ptr_svalue = gmap_callback_find( map_callback,
        &C_SKEY(GENATEST_INT_SET[k]) );
      if (k % 2 == 0) {
        munit_assert_null( ptr_svalue );
      } else {
        munit_assert_not_null( ptr_svalue );
        munit_assert_int( ptr_svalue->value, ==, k );
      }
    }
  }

  gmap_clear( map_callback );
  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    ptr_svalue = gmap_callback_find( map_callback,
      &C_SKEY(GENATEST_INT_SET[i]) );
    munit_assert_null( ptr_svalue );
  }

  gmap_free( map_callback );

  /********************************************************************/
  return MUNIT_OK;
}}
