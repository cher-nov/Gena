#include "gtmap_tests.h"

/******************************************************************************/

MunitResult gtmaptests_1_create() {
  gtmap_naive_h map_naive;
  gtmap_memcmp_h map_memcmp;
  gtmap_callback_h map_callback;
  gtmap_string_h map_string;
  gtmap_array_h map_array;
{
  /********************************************************************/
  map_naive = gtmap_naive_new();
  munit_assert_not_null( map_naive );
  munit_assert( gtmap_empty(map_naive) );
  munit_assert_size( gtmap_count(map_naive), ==, 0 );
  gtmap_free( map_naive );

  /********************************************************************/
  map_memcmp = gtmap_memcmp_new();
  munit_assert_not_null( map_memcmp );
  munit_assert( gtmap_empty(map_memcmp) );
  munit_assert_size( gtmap_count(map_memcmp), ==, 0 );
  gtmap_free( map_memcmp );

  /********************************************************************/
  map_callback = gtmap_callback_new();
  munit_assert_not_null( map_callback );
  munit_assert( gtmap_empty(map_callback) );
  munit_assert_size( gtmap_count(map_callback), ==, 0 );
  gtmap_free( map_callback );

  /********************************************************************/
  map_string = gtmap_string_new();
  munit_assert_not_null( map_string );
  munit_assert( gtmap_empty(map_string) );
  munit_assert_size( gtmap_count(map_string), ==, 0 );
  gtmap_free( map_string );

  /********************************************************************/
  map_array = gtmap_array_new();
  munit_assert_not_null( map_array );
  munit_assert( gtmap_empty(map_array) );
  munit_assert_size( gtmap_count(map_array), ==, 0 );
  gtmap_free( map_array );

  /********************************************************************/
  return MUNIT_OK;
}}

/******************************************************************************/

MunitResult gtmaptests_2_modify() {
  gtmap_naive_h map_naive;
  gtmap_memcmp_h map_memcmp;
  gtmap_callback_h map_callback;
  gtmap_string_h map_string;
  gtmap_array_h map_array;
  int *ptr_int, key1_naive, key2_naive;
  const genatest_skey_s *key1_skey, *key2_skey;
  genatest_svalue_p ptr_svalue;
  const char *key1_str, *key2_str;
  char* ptr_str;
  const int *key1_array, *key2_array;
  int* ptr_array;
  int i, compare;
{
  /********************************************************************/
  map_naive = gtmap_naive_new();

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    ptr_int = gtmap_naive_add( map_naive, GENATEST_INT_SET[i], i );
    munit_assert_not_null( ptr_int );
    munit_assert_int( *ptr_int, ==, i );

    munit_assert_size( gtmap_count(map_naive), ==, i+1 );
    munit_assert( !gtmap_empty(map_naive) );

    gtmap_naive_first( map_naive, &key1_naive );
    gtmap_naive_last( map_naive, &key2_naive );

    munit_assert_int( key1_naive, <=, key2_naive );
    munit_assert_int( key1_naive, <=, GENATEST_INT_SET[i] );
    munit_assert_int( key2_naive, >=, GENATEST_INT_SET[i] );
  }

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    ptr_int = gtmap_naive_add( map_naive, GENATEST_INT_SET[i],
      GENATEST_CUSTOM_INT_1 );
    munit_assert_not_null( ptr_int );
    munit_assert_int( *ptr_int, ==, i );

    munit_assert_size( gtmap_count(map_naive), ==, GENATEST_INT_SET_LEN );
    munit_assert( !gtmap_empty(map_naive) );

    gtmap_naive_first( map_naive, &key1_naive );
    gtmap_naive_last( map_naive, &key2_naive );
    munit_assert_int( key1_naive, <=, key2_naive );
  }

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    ptr_int = gtmap_naive_put( map_naive, GENATEST_CUSTOM_INT_2, i );
    munit_assert_not_null( ptr_int );
    munit_assert_int( *ptr_int, ==, i );

    munit_assert_size( gtmap_count(map_naive), ==, GENATEST_INT_SET_LEN+1 );
    munit_assert( !gtmap_empty(map_naive) );

    gtmap_naive_first( map_naive, &key1_naive );
    gtmap_naive_last( map_naive, &key2_naive );
    munit_assert_int( key1_naive, <=, key2_naive );
  }

  for (i = (int)GENATEST_INT_SET_LEN; i-- > 0;) {
    munit_assert( gtmap_naive_delete( map_naive, GENATEST_INT_SET[i] ) );

    munit_assert_size( gtmap_count(map_naive), ==, i+1 );
    munit_assert( !gtmap_empty(map_naive) );

    gtmap_naive_first( map_naive, &key1_naive );
    gtmap_naive_last( map_naive, &key2_naive );
    munit_assert_int( key1_naive, <=, key2_naive );
  }

  gtmap_clear( map_naive );
  munit_assert_size( gtmap_count(map_naive), ==, 0 );
  munit_assert( gtmap_empty(map_naive) );

  gtmap_free( map_naive );

  /********************************************************************/
  map_memcmp = gtmap_memcmp_new();

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    genatest_skey_s safe_skey;
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );

    ptr_svalue = gtmap_memcmp_add( map_memcmp, &safe_skey,
      &GENATEST_C_SVALUE(i) );
    munit_assert_not_null( ptr_svalue );
    munit_assert_memory_equal( sizeof(genatest_svalue_s), ptr_svalue,
      &GENATEST_C_SVALUE(i) );

    munit_assert_size( gtmap_count(map_memcmp), ==, i+1 );
    munit_assert( !gtmap_empty(map_memcmp) );

    munit_assert_not_null( gtmap_memcmp_first( map_memcmp, &key1_skey ) );
    munit_assert_not_null( gtmap_memcmp_last( map_memcmp, &key2_skey ) );

    compare = memcmp( key1_skey, key2_skey, sizeof(genatest_skey_s) );
    munit_assert_int( compare, <=, 0 );

    compare = memcmp( key1_skey, &safe_skey, sizeof(genatest_skey_s) );
    munit_assert_int( compare, <=, 0 );

    compare = memcmp( key2_skey, &safe_skey, sizeof(genatest_skey_s) );
    munit_assert_int( compare, >=, 0 );
  }

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    genatest_skey_s safe_skey;
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );

    ptr_svalue = gtmap_memcmp_add( map_memcmp, &safe_skey,
      &GENATEST_C_SVALUE(GENATEST_CUSTOM_INT_1) );
    munit_assert_not_null( ptr_svalue );
    munit_assert_memory_equal( sizeof(genatest_svalue_s), ptr_svalue,
      &GENATEST_C_SVALUE(i) );

    munit_assert_size( gtmap_count(map_memcmp), ==, GENATEST_INT_SET_LEN );
    munit_assert( !gtmap_empty(map_memcmp) );

    munit_assert_not_null( gtmap_memcmp_first( map_memcmp, &key1_skey ) );
    munit_assert_not_null( gtmap_memcmp_last( map_memcmp, &key2_skey ) );
    compare = memcmp( key1_skey, key2_skey, sizeof(genatest_skey_s) );
    munit_assert_int( compare, <=, 0 );
  }

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    genatest_skey_s safe_skey;
    genatest_set_skey_safe( &safe_skey, GENATEST_CUSTOM_INT_2 );

    ptr_svalue = gtmap_memcmp_put( map_memcmp, &safe_skey,
      &GENATEST_C_SVALUE(i) );
    munit_assert_not_null( ptr_svalue );
    munit_assert_memory_equal( sizeof(genatest_svalue_s), ptr_svalue,
      &GENATEST_C_SVALUE(i) );

    munit_assert_size( gtmap_count(map_memcmp), ==, GENATEST_INT_SET_LEN+1 );
    munit_assert( !gtmap_empty(map_memcmp) );

    munit_assert_not_null( gtmap_memcmp_first( map_memcmp, &key1_skey ) );
    munit_assert_not_null( gtmap_memcmp_last( map_memcmp, &key2_skey ) );
    compare = memcmp( key1_skey, key2_skey, sizeof(genatest_skey_s) );
    munit_assert_int( compare, <=, 0 );
  }

  for (i = (int)GENATEST_INT_SET_LEN; i-- > 0;) {
    genatest_skey_s safe_skey;
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );

    munit_assert( gtmap_memcmp_delete( map_memcmp, &safe_skey ) );

    munit_assert_size( gtmap_count(map_memcmp), ==, i+1 );
    munit_assert( !gtmap_empty(map_memcmp) );

    munit_assert_not_null( gtmap_memcmp_first( map_memcmp, &key1_skey ) );
    munit_assert_not_null( gtmap_memcmp_last( map_memcmp, &key2_skey ) );
    compare = memcmp( key1_skey, key2_skey, sizeof(genatest_skey_s) );
    munit_assert_int( compare, <=, 0 );
  }

  gtmap_clear( map_memcmp );
  munit_assert_size( gtmap_count(map_memcmp), ==, 0 );
  munit_assert( gtmap_empty(map_memcmp) );
  munit_assert_null( gtmap_memcmp_first( map_memcmp, &key1_skey ) );
  munit_assert_null( gtmap_memcmp_last( map_memcmp, &key2_skey ) );

  gtmap_free( map_memcmp );

  /********************************************************************/
  map_callback = gtmap_callback_new();

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    ptr_svalue = gtmap_callback_add( map_callback,
      &GENATEST_C_SKEY(GENATEST_INT_SET[i]), &GENATEST_C_SVALUE(i) );
    munit_assert_not_null( ptr_svalue );
    munit_assert_int( ptr_svalue->value, ==, i );

    munit_assert_size( gtmap_count(map_callback), ==, i+1 );
    munit_assert( !gtmap_empty(map_callback) );

    munit_assert_not_null( gtmap_callback_first( map_callback, &key1_skey ) );
    munit_assert_not_null( gtmap_callback_last( map_callback, &key2_skey ) );

    compare = genatest_skey_compare_cb( key1_skey, key2_skey,
      sizeof(genatest_skey_s) );
    munit_assert_int( compare, <=, 0 );

    compare = genatest_skey_compare_cb( key1_skey,
      &GENATEST_C_SKEY(GENATEST_INT_SET[i]), sizeof(genatest_skey_s) );
    munit_assert_int( compare, <=, 0 );

    compare = genatest_skey_compare_cb( key2_skey,
      &GENATEST_C_SKEY(GENATEST_INT_SET[i]), sizeof(genatest_skey_s) );
    munit_assert_int( compare, >=, 0 );
  }

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    ptr_svalue = gtmap_callback_add( map_callback,
      &GENATEST_C_SKEY(GENATEST_INT_SET[i]),
      &GENATEST_C_SVALUE(GENATEST_CUSTOM_INT_1) );
    munit_assert_not_null( ptr_svalue );
    munit_assert_int( ptr_svalue->value, ==, i );

    munit_assert_size( gtmap_count(map_callback), ==, GENATEST_INT_SET_LEN );
    munit_assert( !gtmap_empty(map_callback) );

    munit_assert_not_null( gtmap_callback_first( map_callback, &key1_skey ) );
    munit_assert_not_null( gtmap_callback_last( map_callback, &key2_skey ) );
    compare = genatest_skey_compare_cb( key1_skey, key2_skey,
      sizeof(genatest_skey_s) );
    munit_assert_int( compare, <=, 0 );
  }

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    ptr_svalue = gtmap_callback_put( map_callback,
      &GENATEST_C_SKEY(GENATEST_CUSTOM_INT_2),
      &GENATEST_C_SVALUE(i) );
    munit_assert_not_null( ptr_svalue );
    munit_assert_int( ptr_svalue->value, ==, i );

    munit_assert_size( gtmap_count(map_callback), ==, GENATEST_INT_SET_LEN+1 );
    munit_assert( !gtmap_empty(map_callback) );

    munit_assert_not_null( gtmap_callback_first( map_callback, &key1_skey ) );
    munit_assert_not_null( gtmap_callback_last( map_callback, &key2_skey ) );
    compare = genatest_skey_compare_cb( key1_skey, key2_skey,
      sizeof(genatest_skey_s) );
    munit_assert_int( compare, <=, 0 );
  }

  for (i = (int)GENATEST_INT_SET_LEN; i-- > 0;) {
    munit_assert( gtmap_callback_delete( map_callback,
      &GENATEST_C_SKEY(GENATEST_INT_SET[i]) ) );

    munit_assert_size( gtmap_count(map_callback), ==, i+1 );
    munit_assert( !gtmap_empty(map_callback) );

    munit_assert_not_null( gtmap_callback_first( map_callback, &key1_skey ) );
    munit_assert_not_null( gtmap_callback_last( map_callback, &key2_skey ) );
    compare = genatest_skey_compare_cb( key1_skey, key2_skey,
      sizeof(genatest_skey_s) );
    munit_assert_int( compare, <=, 0 );
  }

  gtmap_clear( map_callback );
  munit_assert_size( gtmap_count(map_callback), ==, 0 );
  munit_assert( gtmap_empty(map_callback) );
  munit_assert_null( gtmap_callback_first( map_callback, &key1_skey ) );
  munit_assert_null( gtmap_callback_last( map_callback, &key2_skey ) );

  gtmap_free( map_callback );

  /********************************************************************/
  map_string = gtmap_string_new();

  for (i = 0; i < (int)GENATEST_STR_SET_LEN; ++i) {
    ptr_str = gtmap_string_add( map_string, GENATEST_STR_SET[i],
      GENATEST_STR_SET[i] );
    munit_assert_not_null( ptr_str );
    munit_assert_string_equal( ptr_str, GENATEST_STR_SET[i] );

    munit_assert_size( gtmap_count(map_string), ==, i+1 );
    munit_assert( !gtmap_empty(map_string) );

    munit_assert_not_null( gtmap_string_first( map_string, &key1_str ) );
    munit_assert_not_null( gtmap_string_last( map_string, &key2_str ) );

    compare = strcmp( key1_str, key2_str );
    munit_assert_int( compare, <=, 0 );

    compare = strcmp( key1_str, GENATEST_STR_SET[i] );
    munit_assert_int( compare, <=, 0 );

    compare = strcmp( key2_str, GENATEST_STR_SET[i] );
    munit_assert_int( compare, >=, 0 );
  }

  for (i = 0; i < (int)GENATEST_STR_SET_LEN; ++i) {
    ptr_str = gtmap_string_add( map_string, GENATEST_STR_SET[i],
      GENATEST_CUSTOM_STR_1 );
    munit_assert_not_null( ptr_str );
    munit_assert_string_equal( ptr_str, GENATEST_STR_SET[i] );

    munit_assert_size( gtmap_count(map_string), ==, GENATEST_STR_SET_LEN );
    munit_assert( !gtmap_empty(map_string) );

    munit_assert_not_null( gtmap_string_first( map_string, &key1_str ) );
    munit_assert_not_null( gtmap_string_last( map_string, &key2_str ) );
    compare = strcmp( key1_str, key2_str );
    munit_assert_int( compare, <=, 0 );
  }

  for (i = 0; i < (int)GENATEST_STR_SET_LEN; ++i) {
    ptr_str = gtmap_string_put( map_string, GENATEST_CUSTOM_STR_2,
      GENATEST_STR_SET[i] );
    munit_assert_not_null( ptr_str );
    munit_assert_string_equal( ptr_str, GENATEST_STR_SET[i] );

    munit_assert_size( gtmap_count(map_string), ==, GENATEST_STR_SET_LEN+1 );
    munit_assert( !gtmap_empty(map_string) );

    munit_assert_not_null( gtmap_string_first( map_string, &key1_str ) );
    munit_assert_not_null( gtmap_string_last( map_string, &key2_str ) );
    compare = strcmp( key1_str, key2_str );
    munit_assert_int( compare, <=, 0 );
  }

  for (i = (int)GENATEST_STR_SET_LEN; i-- > 0;) {
    munit_assert( gtmap_string_delete( map_string, GENATEST_STR_SET[i] ) );

    munit_assert_size( gtmap_count(map_string), ==, i+1 );
    munit_assert( !gtmap_empty(map_string) );

    munit_assert_not_null( gtmap_string_first( map_string, &key1_str ) );
    munit_assert_not_null( gtmap_string_last( map_string, &key2_str ) );
    compare = strcmp( key1_str, key2_str );
    munit_assert_int( compare, <=, 0 );
  }

  gtmap_clear( map_string );
  munit_assert_size( gtmap_count(map_string), ==, 0 );
  munit_assert( gtmap_empty(map_string) );
  munit_assert_null( gtmap_string_first( map_string, NULL ) );
  munit_assert_null( gtmap_string_last( map_string, NULL ) );

  gtmap_free( map_string );

  /********************************************************************/
  map_array = gtmap_array_new();

  for (i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i) {
    ptr_array = gtmap_array_add( map_array, GENATEST_BUF_SET[i],
      GENATEST_BUF_SET[i] );
    munit_assert_not_null( ptr_array );
    munit_assert_memory_equal( sizeof(genatest_buf_x), ptr_array,
      GENATEST_BUF_SET[i] );

    munit_assert_size( gtmap_count(map_array), ==, i+1 );
    munit_assert( !gtmap_empty(map_array) );

    munit_assert_not_null( gtmap_array_first( map_array, &key1_array ) );
    munit_assert_not_null( gtmap_array_last( map_array, &key2_array ) );

    compare = memcmp( key1_array, key2_array, sizeof(genatest_buf_x) );
    munit_assert_int( compare, <=, 0 );

    compare = memcmp( key1_array, GENATEST_BUF_SET[i], sizeof(genatest_buf_x) );
    munit_assert_int( compare, <=, 0 );

    compare = memcmp( key2_array, GENATEST_BUF_SET[i], sizeof(genatest_buf_x) );
    munit_assert_int( compare, >=, 0 );
  }

  for (i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i) {
    ptr_array = gtmap_array_add( map_array, GENATEST_BUF_SET[i],
      GENATEST_CUSTOM_BUF_1 );
    munit_assert_not_null( ptr_array );
    munit_assert_memory_equal( sizeof(genatest_buf_x), ptr_array,
      GENATEST_BUF_SET[i] );

    munit_assert_size( gtmap_count(map_array), ==, GENATEST_BUF_SET_LEN );
    munit_assert( !gtmap_empty(map_array) );

    munit_assert_not_null( gtmap_array_first( map_array, &key1_array ) );
    munit_assert_not_null( gtmap_array_last( map_array, &key2_array ) );
    compare = memcmp( key1_array, key2_array, sizeof(genatest_buf_x) );
    munit_assert_int( compare, <=, 0 );
  }

  for (i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i) {
    ptr_array = gtmap_array_put( map_array, GENATEST_CUSTOM_BUF_2,
      GENATEST_BUF_SET[i] );
    munit_assert_not_null( ptr_array );
    munit_assert_memory_equal( sizeof(genatest_buf_x), ptr_array,
      GENATEST_BUF_SET[i] );

    munit_assert_size( gtmap_count(map_array), ==, GENATEST_BUF_SET_LEN+1 );
    munit_assert( !gtmap_empty(map_array) );

    munit_assert_not_null( gtmap_array_first( map_array, &key1_array ) );
    munit_assert_not_null( gtmap_array_last( map_array, &key2_array ) );
    compare = memcmp( key1_array, key2_array, sizeof(genatest_buf_x) );
    munit_assert_int( compare, <=, 0 );
  }

  for (i = (int)GENATEST_BUF_SET_LEN; i-- > 0;) {
    munit_assert( gtmap_array_delete( map_array, GENATEST_BUF_SET[i] ) );

    munit_assert_size( gtmap_count(map_array), ==, i+1 );
    munit_assert( !gtmap_empty(map_array) );

    munit_assert_not_null( gtmap_array_first( map_array, &key1_array ) );
    munit_assert_not_null( gtmap_array_last( map_array, &key2_array ) );
    compare = memcmp( key1_array, key2_array, sizeof(genatest_buf_x) );
    munit_assert_int( compare, <=, 0 );
  }

  gtmap_clear( map_array );
  munit_assert_size( gtmap_count(map_array), ==, 0 );
  munit_assert( gtmap_empty(map_array) );
  munit_assert_null( gtmap_array_first( map_array, NULL ) );
  munit_assert_null( gtmap_array_last( map_array, NULL ) );

  gtmap_free( map_array );

  /********************************************************************/
  return MUNIT_OK;
}}

/******************************************************************************/

MunitResult gtmaptests_3_lookup() {
  gtmap_naive_h map_naive;
  gtmap_memcmp_h map_memcmp;
  gtmap_callback_h map_callback;
  gtmap_string_h map_string;
  gtmap_array_h map_array;
  int* ptr_int;
  genatest_svalue_p ptr_svalue;
  char* ptr_str;
  int* ptr_array;
  int i, k;
  genatest_skey_s safe_skey;
{
  /********************************************************************/
  map_naive = gtmap_naive_new();

  ptr_int = gtmap_naive_find( map_naive, 0 );
  munit_assert_null( ptr_int );

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    gtmap_naive_add( map_naive, GENATEST_INT_SET[i], i );
    for (k = 0; k <= i; ++k) {
      ptr_int = gtmap_naive_find( map_naive, GENATEST_INT_SET[k] );
      munit_assert_not_null( ptr_int );
      munit_assert_int( *ptr_int, ==, k );
    }
  }

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; i += 2) {
    gtmap_naive_delete( map_naive, GENATEST_INT_SET[i] );
    for (k = 0; k <= i; ++k) {
      ptr_int = gtmap_naive_find( map_naive, GENATEST_INT_SET[k] );
      if (k % 2 == 0) {
        munit_assert_null( ptr_int );
      } else {
        munit_assert_not_null( ptr_int );
        munit_assert_int( *ptr_int, ==, k );
      }
    }
  }

  gtmap_clear( map_naive );
  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    ptr_int = gtmap_naive_find( map_naive, GENATEST_INT_SET[i] );
    munit_assert_null( ptr_int );
  }

  gtmap_free( map_naive );

  /********************************************************************/
  map_memcmp = gtmap_memcmp_new();

  genatest_set_skey_safe( &safe_skey, 0 );
  ptr_svalue = gtmap_memcmp_find( map_memcmp, &safe_skey );
  munit_assert_null( ptr_svalue );

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );
    gtmap_memcmp_add( map_memcmp, &safe_skey, &GENATEST_C_SVALUE(i) );
    for (k = 0; k <= i; ++k) {
      genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[k] );
      ptr_svalue = gtmap_memcmp_find( map_memcmp, &safe_skey );
      munit_assert_not_null( ptr_svalue );
      munit_assert_int( ptr_svalue->value, ==, k );
    }
  }

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; i += 2) {
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );
    gtmap_memcmp_delete( map_memcmp, &safe_skey );
    for (k = 0; k <= i; ++k) {
      genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[k] );
      ptr_svalue = gtmap_memcmp_find( map_memcmp, &safe_skey );
      if (k % 2 == 0) {
        munit_assert_null( ptr_svalue );
      } else {
        munit_assert_not_null( ptr_svalue );
        munit_assert_int( ptr_svalue->value, ==, k );
      }
    }
  }

  gtmap_clear( map_memcmp );
  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );
    ptr_svalue = gtmap_memcmp_find( map_memcmp, &safe_skey );
    munit_assert_null( ptr_svalue );
  }

  gtmap_free( map_memcmp );

  /********************************************************************/
  map_callback = gtmap_callback_new();

  ptr_svalue = gtmap_callback_find( map_callback, &GENATEST_C_SKEY(0) );
  munit_assert_null( ptr_svalue );

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    gtmap_callback_add( map_callback, &GENATEST_C_SKEY(GENATEST_INT_SET[i]),
      &GENATEST_C_SVALUE(i) );
    for (k = 0; k <= i; ++k) {
      ptr_svalue = gtmap_callback_find( map_callback,
        &GENATEST_C_SKEY(GENATEST_INT_SET[k]) );
      munit_assert_not_null( ptr_svalue );
      munit_assert_int( ptr_svalue->value, ==, k );
    }
  }

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; i += 2) {
    gtmap_callback_delete( map_callback,
      &GENATEST_C_SKEY(GENATEST_INT_SET[i]) );
    for (k = 0; k <= i; ++k) {
      ptr_svalue = gtmap_callback_find( map_callback,
        &GENATEST_C_SKEY(GENATEST_INT_SET[k]) );
      if (k % 2 == 0) {
        munit_assert_null( ptr_svalue );
      } else {
        munit_assert_not_null( ptr_svalue );
        munit_assert_int( ptr_svalue->value, ==, k );
      }
    }
  }

  gtmap_clear( map_callback );
  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    ptr_svalue = gtmap_callback_find( map_callback,
      &GENATEST_C_SKEY(GENATEST_INT_SET[i]) );
    munit_assert_null( ptr_svalue );
  }

  gtmap_free( map_callback );

  /********************************************************************/
  map_string = gtmap_string_new();

  ptr_str = gtmap_string_find( map_string, "a" );
  munit_assert_null( ptr_str );

  for (i = 0; i < (int)GENATEST_STR_SET_LEN; ++i) {
    gtmap_string_add( map_string, GENATEST_STR_SET[i], GENATEST_STR_SET[i] );
    for (k = 0; k <= i; ++k) {
      ptr_str = gtmap_string_find( map_string, GENATEST_STR_SET[k] );
      munit_assert_not_null( ptr_str );
      munit_assert_string_equal( ptr_str, GENATEST_STR_SET[k] );
    }
  }

  for (i = 0; i < (int)GENATEST_STR_SET_LEN; i += 2) {
    gtmap_string_delete( map_string, GENATEST_STR_SET[i] );
    for (k = 0; k <= i; ++k) {
      ptr_str = gtmap_string_find( map_string, GENATEST_STR_SET[k] );
      if (k % 2 == 0) {
        munit_assert_null( ptr_str );
      } else {
        munit_assert_not_null( ptr_str );
        munit_assert_string_equal( ptr_str, GENATEST_STR_SET[k] );
      }
    }
  }

  gtmap_clear( map_string );
  for (i = 0; i < (int)GENATEST_STR_SET_LEN; ++i) {
    ptr_str = gtmap_string_find( map_string, GENATEST_STR_SET[i] );
    munit_assert_null( ptr_str );
  }

  gtmap_free( map_string );

  /********************************************************************/
  map_array = gtmap_array_new();

  ptr_array = gtmap_array_find( map_array, (genatest_buf_x){0,0,0,0} );
  munit_assert_null( ptr_array );

  for (i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i) {
    gtmap_array_add( map_array, GENATEST_BUF_SET[i], GENATEST_BUF_SET[i] );
    for (k = 0; k <= i; ++k) {
      ptr_array = gtmap_array_find( map_array, GENATEST_BUF_SET[k] );
      munit_assert_not_null( ptr_array );
      munit_assert_memory_equal( sizeof(genatest_buf_x), ptr_array,
        GENATEST_BUF_SET[k] );
    }
  }

  for (i = 0; i < (int)GENATEST_BUF_SET_LEN; i += 2) {
    gtmap_array_delete( map_array, GENATEST_BUF_SET[i] );
    for (k = 0; k <= i; ++k) {
      ptr_array = gtmap_array_find( map_array, GENATEST_BUF_SET[k] );
      if (k % 2 == 0) {
        munit_assert_null( ptr_array );
      } else {
        munit_assert_not_null( ptr_array );
        munit_assert_memory_equal( sizeof(genatest_buf_x), ptr_array,
          GENATEST_BUF_SET[k] );
      }
    }
  }

  gtmap_clear( map_array );
  for (i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i) {
    ptr_array = gtmap_array_find( map_array, GENATEST_BUF_SET[i] );
    munit_assert_null( ptr_array );
  }

  gtmap_free( map_array );

  /********************************************************************/
  return MUNIT_OK;
}}

/******************************************************************************/

MunitResult gtmaptests_4_iterate() {
  gtmap_naive_h map_naive;
  gtmap_callback_h map_struct;
  gtmap_string_h map_string;
  gtmap_array_h map_array;
  gena_iterator_o iter1, iter2, iter3, riter1, riter2, riter3;
  int key_naive;
  int* ptr_naive;
  const genatest_skey_s* key_struct;
  genatest_svalue_p ptr_struct;
  const char* key_string;
  char* ptr_string;
  const int* key_array;
  int* ptr_array;
  gena_bool result;
  int i, k, compare;
{
  /********************************************************************/
  map_naive = gtmap_naive_new();

  munit_assert( !gtmap_begin( map_naive, GENA_FALSE, &iter1 ) );
  munit_assert( !gtmap_end( map_naive, GENA_FALSE, &iter2 ) );
  munit_assert( !gtmap_begin( map_naive, GENA_TRUE, &riter1 ) );
  munit_assert( !gtmap_end( map_naive, GENA_TRUE, &riter2 ) );

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    result = gtmap_naive_add( map_naive, i + GENATEST_CUSTOM_INT_1,
      i + GENATEST_CUSTOM_INT_2 );
    munit_assert_true( result );

    munit_assert( gtmap_begin( map_naive, GENA_FALSE, &iter1 ) );
    munit_assert( gtmap_end( map_naive, GENA_FALSE, &iter2 ) );
    munit_assert( gtmap_begin( map_naive, GENA_TRUE, &riter1 ) );
    munit_assert( gtmap_end( map_naive, GENA_TRUE, &riter2 ) );

    munit_assert( gena_iterator_front( &iter1, 0 ) );
    munit_assert( gena_iterator_back( &iter1, i ) );

    munit_assert( gena_iterator_front( &iter2, -i ) );
    munit_assert( gena_iterator_back( &iter2, 0 ) );

    munit_assert( gena_iterator_front( &riter1, 0 ) );
    munit_assert( gena_iterator_back( &riter1, i ) );

    munit_assert( gena_iterator_front( &riter2, -i ) );
    munit_assert( gena_iterator_back( &riter2, 0 ) );

    munit_assert( !gena_iterator_prior( &iter1 ) );
    munit_assert( !gena_iterator_next( &iter2 ) );

    munit_assert( !gena_iterator_prior( &riter1 ) );
    munit_assert( !gena_iterator_next( &riter2 ) );

    munit_assert( gena_iterator_equal( &iter1, 0, &riter2, 0 ) );
    munit_assert( gena_iterator_equal( &iter2, 0, &riter1, 0 ) );
    munit_assert( gena_iterator_equal( &iter1, i, &riter1, 0 ) );
    munit_assert( gena_iterator_equal( &iter2, 0, &riter2, -i ) );

    munit_assert( gena_iterator_equal( &iter1, 0, &riter1, 0 ) != (i > 0) );
    munit_assert( gena_iterator_equal( &iter2, 0, &riter2, 0 ) != (i > 0) );

    for (k = 0; k < i; ++k) {
      munit_assert_int( gtmap_naive_key( &iter1, 0 ), ==,
        k + GENATEST_CUSTOM_INT_1 );
      munit_assert_int( gtmap_naive_value( &iter1, 0 ), ==,
        k + GENATEST_CUSTOM_INT_2 );

      munit_assert_int( gtmap_naive_key( &riter1, -k ), ==,
        i + GENATEST_CUSTOM_INT_1 );
      munit_assert_int( gtmap_naive_value( &riter1, -k ), ==,
        i + GENATEST_CUSTOM_INT_2 );

      munit_assert_int( gtmap_naive_entry( &iter2, k, &key_naive ), ==,
        i + GENATEST_CUSTOM_INT_2 );
      munit_assert_int( key_naive, ==, i + GENATEST_CUSTOM_INT_1 );

      munit_assert_int( gtmap_naive_entry( &riter2, 0, &key_naive ), ==,
        k + GENATEST_CUSTOM_INT_2 );
      munit_assert_int( key_naive, ==, k + GENATEST_CUSTOM_INT_1 );

      munit_assert( gena_iterator_next( &iter1 ) );
      munit_assert( gena_iterator_prior( &iter2 ) );

      munit_assert( gena_iterator_next( &riter1 ) );
      munit_assert( gena_iterator_prior( &riter2 ) );

      munit_assert( gtmap_at( map_naive, k, GENA_FALSE, &iter3 ) );
      munit_assert( gtmap_at( map_naive, k, GENA_TRUE, &riter3 ) );

      munit_assert_int( gtmap_naive_key( &iter3, 0 ), ==,
        k + GENATEST_CUSTOM_INT_1 );
      munit_assert_int( gtmap_naive_value( &iter3, i-k ), ==,
        i + GENATEST_CUSTOM_INT_2 );

      munit_assert_int( gtmap_naive_key( &riter3, i-k*2 ), ==,
        k + GENATEST_CUSTOM_INT_1 );
      munit_assert_int( gtmap_naive_value( &riter3, 0 ), ==,
        i-k + GENATEST_CUSTOM_INT_2 );
    }

    munit_assert( gena_iterator_back( &iter1, 0 ) );
    munit_assert( gena_iterator_front( &iter1, -i ) );

    munit_assert( gena_iterator_back( &iter2, i ) );
    munit_assert( gena_iterator_front( &iter2, 0 ) );

    munit_assert( gena_iterator_back( &riter1, 0 ) );
    munit_assert( gena_iterator_front( &riter1, -i ) );

    munit_assert( gena_iterator_back( &riter2, i ) );
    munit_assert( gena_iterator_front( &riter2, 0 ) );

    munit_assert( !gena_iterator_next( &iter1 ) );
    munit_assert( !gena_iterator_prior( &iter2 ) );

    munit_assert( !gena_iterator_next( &riter1 ) );
    munit_assert( !gena_iterator_prior( &riter2 ) );

    munit_assert( gena_iterator_equal( &iter1, 0, &riter2, 0 ) );
    munit_assert( gena_iterator_equal( &iter2, 0, &riter1, 0 ) );
    munit_assert( gena_iterator_equal( &iter1, 0, &riter1, -i ) );
    munit_assert( gena_iterator_equal( &iter2, i, &riter2, 0 ) );

    munit_assert( gena_iterator_equal( &iter1, 0, &riter1, 0 ) != (i > 0) );
    munit_assert( gena_iterator_equal( &iter2, 0, &riter2, 0 ) != (i > 0) );
  }

  ptr_naive = gtmap_naive_emplace( &iter1, 0, GENATEST_CUSTOM_INT_1 );
  munit_assert_not_null( ptr_naive );
  munit_assert_int( *ptr_naive, ==, GENATEST_CUSTOM_INT_1 );
  munit_assert_int( gtmap_naive_value( &iter2, i-1 ), ==,
    GENATEST_CUSTOM_INT_1 );

  ptr_naive = gtmap_naive_emplace( &iter2, i-1, GENATEST_CUSTOM_INT_2 );
  munit_assert_not_null( ptr_naive );
  munit_assert_int( *ptr_naive, ==, GENATEST_CUSTOM_INT_2 );
  munit_assert_int( gtmap_naive_value( &iter1, 0 ), ==,
    GENATEST_CUSTOM_INT_2 );

  ptr_naive = gtmap_naive_emplace( &riter1, -i+1, -GENATEST_CUSTOM_INT_1 );
  munit_assert_not_null( ptr_naive );
  munit_assert_int( *ptr_naive, ==, -GENATEST_CUSTOM_INT_1 );
  munit_assert_int( gtmap_naive_value( &riter2, 0 ), ==,
    -GENATEST_CUSTOM_INT_1 );

  ptr_naive = gtmap_naive_emplace( &riter2, 0, -GENATEST_CUSTOM_INT_2 );
  munit_assert_not_null( ptr_naive );
  munit_assert_int( *ptr_naive, ==, -GENATEST_CUSTOM_INT_2 );
  munit_assert_int( gtmap_naive_value( &riter1, -i+1 ), ==,
    -GENATEST_CUSTOM_INT_2 );

  gtmap_free( map_naive );

  /********************************************************************/
  map_struct = gtmap_callback_new();

  munit_assert( !gtmap_begin( map_struct, GENA_FALSE, &iter1 ) );
  munit_assert( !gtmap_end( map_struct, GENA_FALSE, &iter2 ) );
  munit_assert( !gtmap_begin( map_struct, GENA_TRUE, &riter1 ) );
  munit_assert( !gtmap_end( map_struct, GENA_TRUE, &riter2 ) );

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    result = gtmap_callback_add( map_struct, &GENATEST_C_SKEY(i),
      &GENATEST_C_SVALUE(GENATEST_INT_SET[i]) );
    munit_assert_true( result );

    munit_assert( gtmap_begin( map_struct, GENA_FALSE, &iter1 ) );
    munit_assert( gtmap_end( map_struct, GENA_FALSE, &iter2 ) );
    munit_assert( gtmap_begin( map_struct, GENA_TRUE, &riter1 ) );
    munit_assert( gtmap_end( map_struct, GENA_TRUE, &riter2 ) );

    munit_assert( gena_iterator_front( &iter1, 0 ) );
    munit_assert( gena_iterator_back( &iter1, i ) );

    munit_assert( gena_iterator_front( &iter2, -i ) );
    munit_assert( gena_iterator_back( &iter2, 0 ) );

    munit_assert( gena_iterator_front( &riter1, 0 ) );
    munit_assert( gena_iterator_back( &riter1, i ) );

    munit_assert( gena_iterator_front( &riter2, -i ) );
    munit_assert( gena_iterator_back( &riter2, 0 ) );

    munit_assert( !gena_iterator_prior( &iter1 ) );
    munit_assert( !gena_iterator_next( &iter2 ) );

    munit_assert( !gena_iterator_prior( &riter1 ) );
    munit_assert( !gena_iterator_next( &riter2 ) );

    munit_assert( gena_iterator_equal( &iter1, 0, &riter2, 0 ) );
    munit_assert( gena_iterator_equal( &iter2, 0, &riter1, 0 ) );
    munit_assert( gena_iterator_equal( &iter1, i, &riter1, 0 ) );
    munit_assert( gena_iterator_equal( &iter2, 0, &riter2, -i ) );

    munit_assert( gena_iterator_equal( &iter1, 0, &riter1, 0 ) != (i > 0) );
    munit_assert( gena_iterator_equal( &iter2, 0, &riter2, 0 ) != (i > 0) );

    for (k = 0; k < i; ++k) {
      compare = genatest_skey_compare_cb( gtmap_callback_key( &iter1, 0 ),
        &GENATEST_C_SKEY(k), sizeof(genatest_skey_s) );
      munit_assert_int( compare, ==, 0 );
      munit_assert_memory_equal( sizeof(int), gtmap_callback_value( &iter1, 0 ),
        &GENATEST_C_SVALUE(GENATEST_INT_SET[k]) );

      compare = genatest_skey_compare_cb( gtmap_callback_key( &riter1, -k ),
        &GENATEST_C_SKEY(i), sizeof(genatest_skey_s) );
      munit_assert_int( compare, ==, 0 );
      munit_assert_memory_equal( sizeof(int),
        gtmap_callback_value( &riter1, -k ),
        &GENATEST_C_SVALUE(GENATEST_INT_SET[i]) );

      munit_assert_memory_equal( sizeof(int),
        gtmap_callback_entry( &iter2, k, &key_struct ),
        &GENATEST_C_SVALUE(GENATEST_INT_SET[i]) );
      compare = genatest_skey_compare_cb( key_struct, &GENATEST_C_SKEY(i),
        sizeof(genatest_skey_s) );
      munit_assert_int( compare, ==, 0 );

      munit_assert_memory_equal( sizeof(int),
        gtmap_callback_entry( &riter2, 0, &key_struct ),
        &GENATEST_C_SVALUE(GENATEST_INT_SET[k]) );
      compare = genatest_skey_compare_cb( key_struct, &GENATEST_C_SKEY(k),
        sizeof(genatest_skey_s) );
      munit_assert_int( compare, ==, 0 );

      munit_assert( gena_iterator_next( &iter1 ) );
      munit_assert( gena_iterator_prior( &iter2 ) );

      munit_assert( gena_iterator_next( &riter1 ) );
      munit_assert( gena_iterator_prior( &riter2 ) );

      munit_assert( gtmap_at( map_struct, k, GENA_FALSE, &iter3 ) );
      munit_assert( gtmap_at( map_struct, k, GENA_TRUE, &riter3 ) );

      compare = genatest_skey_compare_cb( gtmap_callback_key( &iter3, 0 ),
        &GENATEST_C_SKEY(k), sizeof(genatest_skey_s) );
      munit_assert_int( compare, ==, 0 );
      munit_assert_memory_equal( sizeof(int),
        gtmap_callback_value( &iter3, i-k ),
        &GENATEST_C_SVALUE(GENATEST_INT_SET[i]) );

      compare = genatest_skey_compare_cb( gtmap_callback_key( &riter3, i-k*2 ),
        &GENATEST_C_SKEY(k), sizeof(genatest_skey_s) );
      munit_assert_int( compare, ==, 0 );
      munit_assert_memory_equal( sizeof(int),
        gtmap_callback_value( &riter3, 0 ),
        &GENATEST_C_SVALUE(GENATEST_INT_SET[i-k]) );
    }

    munit_assert( gena_iterator_back( &iter1, 0 ) );
    munit_assert( gena_iterator_front( &iter1, -i ) );

    munit_assert( gena_iterator_back( &iter2, i ) );
    munit_assert( gena_iterator_front( &iter2, 0 ) );

    munit_assert( gena_iterator_back( &riter1, 0 ) );
    munit_assert( gena_iterator_front( &riter1, -i ) );

    munit_assert( gena_iterator_back( &riter2, i ) );
    munit_assert( gena_iterator_front( &riter2, 0 ) );

    munit_assert( !gena_iterator_next( &iter1 ) );
    munit_assert( !gena_iterator_prior( &iter2 ) );

    munit_assert( !gena_iterator_next( &riter1 ) );
    munit_assert( !gena_iterator_prior( &riter2 ) );

    munit_assert( gena_iterator_equal( &iter1, 0, &riter2, 0 ) );
    munit_assert( gena_iterator_equal( &iter2, 0, &riter1, 0 ) );
    munit_assert( gena_iterator_equal( &iter1, 0, &riter1, -i ) );
    munit_assert( gena_iterator_equal( &iter2, i, &riter2, 0 ) );

    munit_assert( gena_iterator_equal( &iter1, 0, &riter1, 0 ) != (i > 0) );
    munit_assert( gena_iterator_equal( &iter2, 0, &riter2, 0 ) != (i > 0) );
  }

  ptr_struct = gtmap_callback_emplace( &iter1, 0,
    &GENATEST_C_SVALUE(GENATEST_CUSTOM_INT_1) );
  munit_assert_not_null( ptr_struct );
  munit_assert_memory_equal( sizeof(int), gtmap_callback_value( &iter2, i-1 ),
    &GENATEST_C_SVALUE(GENATEST_CUSTOM_INT_1) );

  ptr_struct = gtmap_callback_emplace( &iter2, i-1,
    &GENATEST_C_SVALUE(GENATEST_CUSTOM_INT_2) );
  munit_assert_not_null( ptr_struct );
  munit_assert_memory_equal( sizeof(int), gtmap_callback_value( &iter1, 0 ),
    &GENATEST_C_SVALUE(GENATEST_CUSTOM_INT_2) );

  ptr_struct = gtmap_callback_emplace( &riter1, -i+1,
    &GENATEST_C_SVALUE(-GENATEST_CUSTOM_INT_1) );
  munit_assert_not_null( ptr_struct );
  munit_assert_memory_equal( sizeof(int), gtmap_callback_value( &riter2, 0 ),
    &GENATEST_C_SVALUE(-GENATEST_CUSTOM_INT_1) );

  ptr_struct = gtmap_callback_emplace( &riter2, 0,
    &GENATEST_C_SVALUE(-GENATEST_CUSTOM_INT_2) );
  munit_assert_not_null( ptr_struct );
  munit_assert_memory_equal( sizeof(int), gtmap_callback_value( &riter1, -i+1 ),
    &GENATEST_C_SVALUE(-GENATEST_CUSTOM_INT_2) );

  gtmap_free( map_struct );

  /********************************************************************/
  map_string = gtmap_string_new();

  munit_assert( !gtmap_begin( map_string, GENA_FALSE, &iter1 ) );
  munit_assert( !gtmap_end( map_string, GENA_FALSE, &iter2 ) );
  munit_assert( !gtmap_begin( map_string, GENA_TRUE, &riter1 ) );
  munit_assert( !gtmap_end( map_string, GENA_TRUE, &riter2 ) );

  for (i = 0; i < (int)GENATEST_STR_SET_LEN; ++i) {
    result = gtmap_string_add( map_string, GENATEST_STR_SET[i],
      GENATEST_STR_SET[i] );
    munit_assert_true( result );

    munit_assert( gtmap_begin( map_string, GENA_FALSE, &iter1 ) );
    munit_assert( gtmap_end( map_string, GENA_FALSE, &iter2 ) );
    munit_assert( gtmap_begin( map_string, GENA_TRUE, &riter1 ) );
    munit_assert( gtmap_end( map_string, GENA_TRUE, &riter2 ) );

    munit_assert( gena_iterator_front( &iter1, 0 ) );
    munit_assert( gena_iterator_back( &iter1, i ) );

    munit_assert( gena_iterator_front( &iter2, -i ) );
    munit_assert( gena_iterator_back( &iter2, 0 ) );

    munit_assert( gena_iterator_front( &riter1, 0 ) );
    munit_assert( gena_iterator_back( &riter1, i ) );

    munit_assert( gena_iterator_front( &riter2, -i ) );
    munit_assert( gena_iterator_back( &riter2, 0 ) );

    munit_assert( !gena_iterator_prior( &iter1 ) );
    munit_assert( !gena_iterator_next( &iter2 ) );

    munit_assert( !gena_iterator_prior( &riter1 ) );
    munit_assert( !gena_iterator_next( &riter2 ) );

    munit_assert( gena_iterator_equal( &iter1, 0, &riter2, 0 ) );
    munit_assert( gena_iterator_equal( &iter2, 0, &riter1, 0 ) );
    munit_assert( gena_iterator_equal( &iter1, i, &riter1, 0 ) );
    munit_assert( gena_iterator_equal( &iter2, 0, &riter2, -i ) );

    munit_assert( gena_iterator_equal( &iter1, 0, &riter1, 0 ) != (i > 0) );
    munit_assert( gena_iterator_equal( &iter2, 0, &riter2, 0 ) != (i > 0) );

    for (k = 0; k < i; ++k) {
      munit_assert_string_equal( gtmap_string_key( &iter1, 0 ),
        GENATEST_STR_SET[k] );
      munit_assert_string_equal( gtmap_string_value( &iter1, 0 ),
        GENATEST_STR_SET[k] );

      munit_assert_string_equal( gtmap_string_key( &riter1, -k ),
        GENATEST_STR_SET[i] );
      munit_assert_string_equal( gtmap_string_value( &riter1, -k ),
        GENATEST_STR_SET[i] );

      munit_assert_string_equal( gtmap_string_entry( &iter2, k, &key_string ),
        GENATEST_STR_SET[i] );
      munit_assert_string_equal( key_string, GENATEST_STR_SET[i] );

      munit_assert_string_equal( gtmap_string_entry( &riter2, 0, &key_string ),
        GENATEST_STR_SET[k] );
      munit_assert_string_equal( key_string, GENATEST_STR_SET[k] );

      munit_assert( gena_iterator_next( &iter1 ) );
      munit_assert( gena_iterator_prior( &iter2 ) );

      munit_assert( gena_iterator_next( &riter1 ) );
      munit_assert( gena_iterator_prior( &riter2 ) );

      munit_assert( gtmap_at( map_string, k, GENA_FALSE, &iter3 ) );
      munit_assert( gtmap_at( map_string, k, GENA_TRUE, &riter3 ) );

      munit_assert_string_equal( gtmap_string_key( &iter3, 0 ),
        GENATEST_STR_SET[k] );
      munit_assert_string_equal( gtmap_string_value( &iter3, i-k ),
        GENATEST_STR_SET[i] );

      munit_assert_string_equal( gtmap_string_key( &riter3, i-k*2 ),
        GENATEST_STR_SET[k] );
      munit_assert_string_equal( gtmap_string_value( &riter3, 0 ),
        GENATEST_STR_SET[i-k] );
    }

    munit_assert( gena_iterator_back( &iter1, 0 ) );
    munit_assert( gena_iterator_front( &iter1, -i ) );

    munit_assert( gena_iterator_back( &iter2, i ) );
    munit_assert( gena_iterator_front( &iter2, 0 ) );

    munit_assert( gena_iterator_back( &riter1, 0 ) );
    munit_assert( gena_iterator_front( &riter1, -i ) );

    munit_assert( gena_iterator_back( &riter2, i ) );
    munit_assert( gena_iterator_front( &riter2, 0 ) );

    munit_assert( !gena_iterator_next( &iter1 ) );
    munit_assert( !gena_iterator_prior( &iter2 ) );

    munit_assert( !gena_iterator_next( &riter1 ) );
    munit_assert( !gena_iterator_prior( &riter2 ) );

    munit_assert( gena_iterator_equal( &iter1, 0, &riter2, 0 ) );
    munit_assert( gena_iterator_equal( &iter2, 0, &riter1, 0 ) );
    munit_assert( gena_iterator_equal( &iter1, 0, &riter1, -i ) );
    munit_assert( gena_iterator_equal( &iter2, i, &riter2, 0 ) );

    munit_assert( gena_iterator_equal( &iter1, 0, &riter1, 0 ) != (i > 0) );
    munit_assert( gena_iterator_equal( &iter2, 0, &riter2, 0 ) != (i > 0) );
  }

  ptr_string = gtmap_string_emplace( &iter1, 0, GENATEST_CUSTOM_STR_1 );
  munit_assert_not_null( ptr_string );
  munit_assert_string_equal( ptr_string, GENATEST_CUSTOM_STR_1 );
  munit_assert_string_equal( gtmap_string_value( &iter2, i-1 ),
    GENATEST_CUSTOM_STR_1 );

  ptr_string = gtmap_string_emplace( &iter2, i-1, GENATEST_CUSTOM_STR_2 );
  munit_assert_not_null( ptr_string );
  munit_assert_string_equal( ptr_string, GENATEST_CUSTOM_STR_2 );
  munit_assert_string_equal( gtmap_string_value( &iter1, 0 ),
    GENATEST_CUSTOM_STR_2 );

  ptr_string = gtmap_string_emplace( &riter1, -i+1, GENATEST_CUSTOM_STR_1 );
  munit_assert_not_null( ptr_string );
  munit_assert_string_equal( ptr_string, GENATEST_CUSTOM_STR_1 );
  munit_assert_string_equal( gtmap_string_value( &riter2, 0 ),
    GENATEST_CUSTOM_STR_1 );

  ptr_string = gtmap_string_emplace( &riter2, 0, GENATEST_CUSTOM_STR_2 );
  munit_assert_not_null( ptr_string );
  munit_assert_string_equal( ptr_string, GENATEST_CUSTOM_STR_2 );
  munit_assert_string_equal( gtmap_string_value( &riter1, -i+1 ),
    GENATEST_CUSTOM_STR_2 );

  gtmap_free( map_string );

  /********************************************************************/
  map_array = gtmap_array_new();

  munit_assert( !gtmap_begin( map_array, GENA_FALSE, &iter1 ) );
  munit_assert( !gtmap_end( map_array, GENA_FALSE, &iter2 ) );
  munit_assert( !gtmap_begin( map_array, GENA_TRUE, &riter1 ) );
  munit_assert( !gtmap_end( map_array, GENA_TRUE, &riter2 ) );

  for (i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i) {
    result = gtmap_array_add( map_array, GENATEST_BUF_SET[i],
      GENATEST_BUF_SET[i] );
    munit_assert_true( result );

    munit_assert( gtmap_begin( map_array, GENA_FALSE, &iter1 ) );
    munit_assert( gtmap_end( map_array, GENA_FALSE, &iter2 ) );
    munit_assert( gtmap_begin( map_array, GENA_TRUE, &riter1 ) );
    munit_assert( gtmap_end( map_array, GENA_TRUE, &riter2 ) );

    munit_assert( gena_iterator_front( &iter1, 0 ) );
    munit_assert( gena_iterator_back( &iter1, i ) );

    munit_assert( gena_iterator_front( &iter2, -i ) );
    munit_assert( gena_iterator_back( &iter2, 0 ) );

    munit_assert( gena_iterator_front( &riter1, 0 ) );
    munit_assert( gena_iterator_back( &riter1, i ) );

    munit_assert( gena_iterator_front( &riter2, -i ) );
    munit_assert( gena_iterator_back( &riter2, 0 ) );

    munit_assert( !gena_iterator_prior( &iter1 ) );
    munit_assert( !gena_iterator_next( &iter2 ) );

    munit_assert( !gena_iterator_prior( &riter1 ) );
    munit_assert( !gena_iterator_next( &riter2 ) );

    munit_assert( gena_iterator_equal( &iter1, 0, &riter2, 0 ) );
    munit_assert( gena_iterator_equal( &iter2, 0, &riter1, 0 ) );
    munit_assert( gena_iterator_equal( &iter1, i, &riter1, 0 ) );
    munit_assert( gena_iterator_equal( &iter2, 0, &riter2, -i ) );

    munit_assert( gena_iterator_equal( &iter1, 0, &riter1, 0 ) != (i > 0) );
    munit_assert( gena_iterator_equal( &iter2, 0, &riter2, 0 ) != (i > 0) );

    for (k = 0; k < i; ++k) {
      munit_assert_memory_equal( sizeof(genatest_buf_x),
        gtmap_array_key( &iter1, 0 ), GENATEST_BUF_SET[k] );
      munit_assert_memory_equal( sizeof(genatest_buf_x),
        gtmap_array_value( &iter1, 0 ), GENATEST_BUF_SET[k] );

      munit_assert_memory_equal( sizeof(genatest_buf_x),
        gtmap_array_key( &riter1, -k ), GENATEST_BUF_SET[i] );
      munit_assert_memory_equal( sizeof(genatest_buf_x),
        gtmap_array_value( &riter1, -k ), GENATEST_BUF_SET[i] );

      munit_assert_memory_equal( sizeof(genatest_buf_x),
        gtmap_array_entry( &iter2, k, &key_array ), GENATEST_BUF_SET[i] );
      munit_assert_memory_equal( sizeof(genatest_buf_x),
        key_array, GENATEST_BUF_SET[i] );

      munit_assert_memory_equal( sizeof(genatest_buf_x),
        gtmap_array_entry( &riter2, 0, &key_array ), GENATEST_BUF_SET[k] );
      munit_assert_memory_equal( sizeof(genatest_buf_x),
        key_array, GENATEST_BUF_SET[k] );

      munit_assert( gena_iterator_next( &iter1 ) );
      munit_assert( gena_iterator_prior( &iter2 ) );

      munit_assert( gena_iterator_next( &riter1 ) );
      munit_assert( gena_iterator_prior( &riter2 ) );

      munit_assert( gtmap_at( map_array, k, GENA_FALSE, &iter3 ) );
      munit_assert( gtmap_at( map_array, k, GENA_TRUE, &riter3 ) );

      munit_assert_memory_equal( sizeof(genatest_buf_x),
        gtmap_array_key( &iter3, 0 ), GENATEST_BUF_SET[k] );
      munit_assert_memory_equal( sizeof(genatest_buf_x),
        gtmap_array_value( &iter3, i-k ), GENATEST_BUF_SET[i] );

      munit_assert_memory_equal( sizeof(genatest_buf_x),
        gtmap_array_key( &riter3, i-k*2 ), GENATEST_BUF_SET[k] );
      munit_assert_memory_equal( sizeof(genatest_buf_x),
        gtmap_array_value( &riter3, 0 ), GENATEST_BUF_SET[i-k] );
    }

    munit_assert( gena_iterator_back( &iter1, 0 ) );
    munit_assert( gena_iterator_front( &iter1, -i ) );

    munit_assert( gena_iterator_back( &iter2, i ) );
    munit_assert( gena_iterator_front( &iter2, 0 ) );

    munit_assert( gena_iterator_back( &riter1, 0 ) );
    munit_assert( gena_iterator_front( &riter1, -i ) );

    munit_assert( gena_iterator_back( &riter2, i ) );
    munit_assert( gena_iterator_front( &riter2, 0 ) );

    munit_assert( !gena_iterator_next( &iter1 ) );
    munit_assert( !gena_iterator_prior( &iter2 ) );

    munit_assert( !gena_iterator_next( &riter1 ) );
    munit_assert( !gena_iterator_prior( &riter2 ) );

    munit_assert( gena_iterator_equal( &iter1, 0, &riter2, 0 ) );
    munit_assert( gena_iterator_equal( &iter2, 0, &riter1, 0 ) );
    munit_assert( gena_iterator_equal( &iter1, 0, &riter1, -i ) );
    munit_assert( gena_iterator_equal( &iter2, i, &riter2, 0 ) );

    munit_assert( gena_iterator_equal( &iter1, 0, &riter1, 0 ) != (i > 0) );
    munit_assert( gena_iterator_equal( &iter2, 0, &riter2, 0 ) != (i > 0) );
  }

  ptr_array = gtmap_array_emplace( &iter1, 0, GENATEST_CUSTOM_BUF_1 );
  munit_assert_not_null( ptr_array );
  munit_assert_memory_equal( sizeof(genatest_buf_x), ptr_array,
    GENATEST_CUSTOM_BUF_1 );
  munit_assert_memory_equal( sizeof(genatest_buf_x),
    gtmap_array_value( &iter2, i-1 ), GENATEST_CUSTOM_BUF_1 );

  ptr_array = gtmap_array_emplace( &iter2, i-1, GENATEST_CUSTOM_BUF_2 );
  munit_assert_not_null( ptr_array );
  munit_assert_memory_equal( sizeof(genatest_buf_x), ptr_array,
    GENATEST_CUSTOM_BUF_2 );
  munit_assert_memory_equal( sizeof(genatest_buf_x),
    gtmap_array_value( &iter1, 0 ), GENATEST_CUSTOM_BUF_2 );

  ptr_array = gtmap_array_emplace( &riter1, -i+1, GENATEST_CUSTOM_BUF_1 );
  munit_assert_not_null( ptr_array );
  munit_assert_memory_equal( sizeof(genatest_buf_x), ptr_array,
    GENATEST_CUSTOM_BUF_1 );
  munit_assert_memory_equal( sizeof(genatest_buf_x),
    gtmap_array_value( &riter2, 0 ), GENATEST_CUSTOM_BUF_1 );

  ptr_array = gtmap_array_emplace( &riter2, 0, GENATEST_CUSTOM_BUF_2 );
  munit_assert_not_null( ptr_array );
  munit_assert_memory_equal( sizeof(genatest_buf_x), ptr_array,
    GENATEST_CUSTOM_BUF_2 );
  munit_assert_memory_equal( sizeof(genatest_buf_x),
    gtmap_array_value( &riter1, -i+1 ), GENATEST_CUSTOM_BUF_2 );

  gtmap_free( map_array );

  /********************************************************************/
  return MUNIT_OK;
}}
