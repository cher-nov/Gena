#include "gtset_tests.h"

/******************************************************************************/

MunitResult gtsettests_1_create() {
  gtset_naive_h set_naive;
  gtset_memcmp_h set_memcmp;
  gtset_callback_h set_callback;
  gtset_string_h set_string;
  gtset_array_h set_array;
{
  /********************************************************************/
  set_naive = gtset_naive_new();
  munit_assert_not_null( set_naive );
  munit_assert( gtset_empty(set_naive) );
  munit_assert_size( gtset_count(set_naive), ==, 0 );
  gtset_free( set_naive );

  /********************************************************************/
  set_memcmp = gtset_memcmp_new();
  munit_assert_not_null( set_memcmp );
  munit_assert( gtset_empty(set_memcmp) );
  munit_assert_size( gtset_count(set_memcmp), ==, 0 );
  gtset_free( set_memcmp );

  /********************************************************************/
  set_callback = gtset_callback_new();
  munit_assert_not_null( set_callback );
  munit_assert( gtset_empty(set_callback) );
  munit_assert_size( gtset_count(set_callback), ==, 0 );
  gtset_free( set_callback );

  /********************************************************************/
  set_string = gtset_string_new();
  munit_assert_not_null( set_string );
  munit_assert( gtset_empty(set_string) );
  munit_assert_size( gtset_count(set_string), ==, 0 );
  gtset_free( set_string );

  /********************************************************************/
  set_array = gtset_array_new();
  munit_assert_not_null( set_array );
  munit_assert( gtset_empty(set_array) );
  munit_assert_size( gtset_count(set_array), ==, 0 );
  gtset_free( set_array );

  /********************************************************************/
  return MUNIT_OK;
}}

/******************************************************************************/

MunitResult gtsettests_2_modify() {
  gtset_naive_h set_naive;
  gtset_memcmp_h set_memcmp;
  gtset_callback_h set_callback;
  gtset_string_h set_string;
  gtset_array_h set_array;
  gena_bool exists;
  int key1_naive, key2_naive;
  const genatest_skey_s *key1_skey, *key2_skey;
  const char *key1_str, *key2_str;
  const int *key1_array, *key2_array;
  int i, compare;
{
  /********************************************************************/
  set_naive = gtset_naive_new();

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    munit_assert( gtset_naive_add( set_naive, GENATEST_INT_SET[i], &exists ) );
    munit_assert_false( exists );
    munit_assert( gtset_naive_add( set_naive, GENATEST_INT_SET[i], &exists ) );
    munit_assert_true( exists );

    munit_assert_size( gtset_count(set_naive), ==, i+1 );
    munit_assert( !gtset_empty(set_naive) );

    key1_naive = gtset_naive_first( set_naive );
    key2_naive = gtset_naive_last( set_naive );

    munit_assert_int( key1_naive, <=, key2_naive );
    munit_assert_int( key1_naive, <=, GENATEST_INT_SET[i] );
    munit_assert_int( key2_naive, >=, GENATEST_INT_SET[i] );
  }

  for (i = (int)GENATEST_INT_SET_LEN; --i > 0;) {
    munit_assert( gtset_naive_delete( set_naive, GENATEST_INT_SET[i] ) );

    munit_assert_size( gtset_count(set_naive), ==, i );
    munit_assert( !gtset_empty(set_naive) );

    key1_naive = gtset_naive_first( set_naive );
    key2_naive = gtset_naive_last( set_naive );
    munit_assert_int( key1_naive, <=, key2_naive );
  }

  gtset_clear( set_naive );
  munit_assert_size( gtset_count(set_naive), ==, 0 );
  munit_assert( gtset_empty(set_naive) );

  gtset_free( set_naive );

  /********************************************************************/
  set_memcmp = gtset_memcmp_new();

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    genatest_skey_s safe_skey;
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );

    munit_assert( gtset_memcmp_add( set_memcmp, &safe_skey, &exists ) );
    munit_assert_false( exists );
    munit_assert( gtset_memcmp_add( set_memcmp, &safe_skey, &exists ) );
    munit_assert_true( exists );

    munit_assert_size( gtset_count(set_memcmp), ==, i+1 );
    munit_assert( !gtset_empty(set_memcmp) );

    key1_skey = gtset_memcmp_first( set_memcmp );
    munit_assert_not_null( key1_skey );
    key2_skey = gtset_memcmp_last( set_memcmp );
    munit_assert_not_null( key2_skey );

    compare = memcmp( key1_skey, key2_skey, sizeof(genatest_skey_s) );
    munit_assert_int( compare, <=, 0 );
    compare = memcmp( key1_skey, &safe_skey, sizeof(genatest_skey_s) );
    munit_assert_int( compare, <=, 0 );
    compare = memcmp( key2_skey, &safe_skey, sizeof(genatest_skey_s) );
    munit_assert_int( compare, >=, 0 );
  }

  for (i = (int)GENATEST_INT_SET_LEN; --i > 0;) {
    genatest_skey_s safe_skey;
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );

    munit_assert( gtset_memcmp_delete( set_memcmp, &safe_skey ) );

    munit_assert_size( gtset_count(set_memcmp), ==, i );
    munit_assert( !gtset_empty(set_memcmp) );

    key1_skey = gtset_memcmp_first( set_memcmp );
    munit_assert_not_null( key1_skey );
    key2_skey = gtset_memcmp_last( set_memcmp );
    munit_assert_not_null( key2_skey );

    compare = memcmp( key1_skey, key2_skey, sizeof(genatest_skey_s) );
    munit_assert_int( compare, <=, 0 );
  }

  gtset_clear( set_memcmp );
  munit_assert_size( gtset_count(set_memcmp), ==, 0 );
  munit_assert( gtset_empty(set_memcmp) );
  munit_assert_null( gtset_memcmp_first(set_memcmp) );
  munit_assert_null( gtset_memcmp_last(set_memcmp) );

  gtset_free( set_memcmp );

  /********************************************************************/
  set_callback = gtset_callback_new();

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    munit_assert( gtset_callback_add( set_callback,
      &GENATEST_C_SKEY(GENATEST_INT_SET[i]), &exists ) );
    munit_assert_false( exists );
    munit_assert( gtset_callback_add( set_callback,
      &GENATEST_C_SKEY(GENATEST_INT_SET[i]), &exists ) );
    munit_assert_true( exists );

    munit_assert_size( gtset_count(set_callback), ==, i+1 );
    munit_assert( !gtset_empty(set_callback) );

    key1_skey = gtset_callback_first( set_callback );
    munit_assert_not_null( key1_skey );
    key2_skey = gtset_callback_last( set_callback );
    munit_assert_not_null( key2_skey );

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

  for (i = (int)GENATEST_INT_SET_LEN; --i > 0;) {
    munit_assert( gtset_callback_delete( set_callback,
      &GENATEST_C_SKEY(GENATEST_INT_SET[i]) ) );

    munit_assert_size( gtset_count(set_callback), ==, i );
    munit_assert( !gtset_empty(set_callback) );

    key1_skey = gtset_callback_first( set_callback );
    munit_assert_not_null( key1_skey );
    key2_skey = gtset_callback_last( set_callback );
    munit_assert_not_null( key2_skey );

    compare = genatest_skey_compare_cb( key1_skey, key2_skey,
      sizeof(genatest_skey_s) );
    munit_assert_int( compare, <=, 0 );
  }

  gtset_clear( set_callback );
  munit_assert_size( gtset_count(set_callback), ==, 0 );
  munit_assert( gtset_empty(set_callback) );
  munit_assert_null( gtset_callback_first(set_callback) );
  munit_assert_null( gtset_callback_last(set_callback) );

  gtset_free( set_callback );

  /********************************************************************/
  set_string = gtset_string_new();

  for (i = 0; i < (int)GENATEST_STR_SET_LEN; ++i) {
    munit_assert( gtset_string_add( set_string, GENATEST_STR_SET[i],
      &exists ) );
    munit_assert_false( exists );
    munit_assert( gtset_string_add( set_string, GENATEST_STR_SET[i],
      &exists ) );
    munit_assert_true( exists );

    munit_assert_size( gtset_count(set_string), ==, i+1 );
    munit_assert( !gtset_empty(set_string) );

    key1_str = gtset_string_first( set_string );
    munit_assert_not_null( key1_str );
    key2_str = gtset_string_last( set_string );
    munit_assert_not_null( key2_str );

    compare = strcmp( key1_str, key2_str );
    munit_assert_int( compare, <=, 0 );
    compare = strcmp( key1_str, GENATEST_STR_SET[i] );
    munit_assert_int( compare, <=, 0 );
    compare = strcmp( key2_str, GENATEST_STR_SET[i] );
    munit_assert_int( compare, >=, 0 );
  }

  for (i = (int)GENATEST_STR_SET_LEN; --i > 0;) {
    munit_assert( gtset_string_delete( set_string, GENATEST_STR_SET[i] ) );

    munit_assert_size( gtset_count(set_string), ==, i );
    munit_assert( !gtset_empty(set_string) );

    key1_str = gtset_string_first( set_string );
    munit_assert_not_null( key1_str );
    key2_str = gtset_string_last( set_string );
    munit_assert_not_null( key2_str );

    compare = strcmp( key1_str, key2_str );
    munit_assert_int( compare, <=, 0 );
  }

  gtset_clear( set_string );
  munit_assert_size( gtset_count(set_string), ==, 0 );
  munit_assert( gtset_empty(set_string) );
  munit_assert_null( gtset_string_first(set_string) );
  munit_assert_null( gtset_string_last(set_string) );

  gtset_free( set_string );

  /********************************************************************/
  set_array = gtset_array_new();

  for (i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i) {
    munit_assert( gtset_array_add( set_array, GENATEST_BUF_SET[i], &exists ) );
    munit_assert_false( exists );
    munit_assert( gtset_array_add( set_array, GENATEST_BUF_SET[i], &exists ) );
    munit_assert_true( exists );

    munit_assert_size( gtset_count(set_array), ==, i+1 );
    munit_assert( !gtset_empty(set_array) );

    key1_array = gtset_array_first( set_array );
    munit_assert_not_null( key1_array );
    key2_array = gtset_array_last( set_array );
    munit_assert_not_null( key2_array );

    compare = memcmp( key1_array, key2_array, sizeof(genatest_buf_x) );
    munit_assert_int( compare, <=, 0 );
    compare = memcmp( key1_array, GENATEST_BUF_SET[i], sizeof(genatest_buf_x) );
    munit_assert_int( compare, <=, 0 );
    compare = memcmp( key2_array, GENATEST_BUF_SET[i], sizeof(genatest_buf_x) );
    munit_assert_int( compare, >=, 0 );
  }

  for (i = (int)GENATEST_BUF_SET_LEN; --i > 0;) {
    munit_assert( gtset_array_delete( set_array, GENATEST_BUF_SET[i] ) );

    munit_assert_size( gtset_count(set_array), ==, i );
    munit_assert( !gtset_empty(set_array) );

    key1_array = gtset_array_first( set_array );
    munit_assert_not_null( key1_array );
    key2_array = gtset_array_last( set_array );
    munit_assert_not_null( key2_array );

    compare = memcmp( key1_array, key2_array, sizeof(genatest_buf_x) );
    munit_assert_int( compare, <=, 0 );
  }

  gtset_clear( set_array );
  munit_assert_size( gtset_count(set_array), ==, 0 );
  munit_assert( gtset_empty(set_array) );
  munit_assert_null( gtset_array_first(set_array) );
  munit_assert_null( gtset_array_last(set_array) );

  gtset_free( set_array );

  /********************************************************************/
  return MUNIT_OK;
}}

/******************************************************************************/

MunitResult gtsettests_3_lookup() {
  gtset_naive_h set_naive;
  gtset_memcmp_h set_memcmp;
  gtset_callback_h set_callback;
  gtset_string_h set_string;
  gtset_array_h set_array;
  gena_bool exists;
  int i, k;
  genatest_skey_s safe_skey;
{
  /********************************************************************/
  set_naive = gtset_naive_new();

  munit_assert( !gtset_naive_check( set_naive, 0 ) );

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    gtset_naive_add( set_naive, GENATEST_INT_SET[i], NULL );
    for (k = 0; k < (int)GENATEST_INT_SET_LEN; ++k) {
      exists = gtset_naive_check( set_naive, GENATEST_INT_SET[k] );
      munit_assert( exists == (k <= i) );
    }
  }

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; i += 2) {
    gtset_naive_delete( set_naive, GENATEST_INT_SET[i] );
    for (k = 0; k <= i; ++k) {
      exists = gtset_naive_check( set_naive, GENATEST_INT_SET[k] );
      munit_assert( exists == (k % 2 != 0) );
    }
  }

  gtset_clear( set_naive );
  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    munit_assert( !gtset_naive_check( set_naive, GENATEST_INT_SET[i] ) );
  }

  gtset_free( set_naive );

  /********************************************************************/
  set_memcmp = gtset_memcmp_new();

  genatest_set_skey_safe( &safe_skey, 0 );
  munit_assert( !gtset_memcmp_check( set_memcmp, &safe_skey ) );

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );
    gtset_memcmp_add( set_memcmp, &safe_skey, NULL );
    for (k = 0; k < (int)GENATEST_INT_SET_LEN; ++k) {
      genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[k] );
      exists = gtset_memcmp_check( set_naive, &safe_skey );
      munit_assert( exists == (k <= i) );
    }
  }

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; i += 2) {
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );
    gtset_memcmp_delete( set_memcmp, &safe_skey );
    for (k = 0; k <= i; ++k) {
      genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[k] );
      exists = gtset_memcmp_check( set_memcmp, &safe_skey );
      munit_assert( exists == (k % 2 != 0) );
    }
  }

  gtset_clear( set_memcmp );
  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );
    munit_assert( !gtset_memcmp_check( set_memcmp, &safe_skey ) );
  }

  gtset_free( set_memcmp );

  /********************************************************************/
  set_callback = gtset_callback_new();

  munit_assert( !gtset_callback_check( set_callback, &GENATEST_C_SKEY(0) ) );

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    gtset_callback_add( set_callback, &GENATEST_C_SKEY(GENATEST_INT_SET[i]),
      NULL );
    for (k = 0; k < (int)GENATEST_INT_SET_LEN; ++k) {
      exists = gtset_callback_check( set_callback,
        &GENATEST_C_SKEY(GENATEST_INT_SET[k]) );
      munit_assert( exists == (k <= i) );
    }
  }

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; i += 2) {
    gtset_callback_delete( set_callback,
      &GENATEST_C_SKEY(GENATEST_INT_SET[i]) );
    for (k = 0; k <= i; ++k) {
      exists = gtset_callback_check( set_callback,
        &GENATEST_C_SKEY(GENATEST_INT_SET[k]) );
      munit_assert( exists == (k % 2 != 0) );
    }
  }

  gtset_clear( set_callback );
  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    munit_assert( !gtset_callback_check( set_callback,
      &GENATEST_C_SKEY(GENATEST_INT_SET[i]) ) );
  }

  gtset_free( set_callback );

  /********************************************************************/
  set_string = gtset_string_new();

  munit_assert( !gtset_string_check( set_string, "a" ) );

  for (i = 0; i < (int)GENATEST_STR_SET_LEN; ++i) {
    gtset_string_add( set_string, GENATEST_STR_SET[i], NULL );
    for (k = 0; k < (int)GENATEST_INT_SET_LEN; ++k) {
      exists = gtset_string_check( set_string, GENATEST_STR_SET[k] );
      munit_assert( exists == (k <= i) );
    }
  }

  for (i = 0; i < (int)GENATEST_STR_SET_LEN; i += 2) {
    gtset_string_delete( set_string, GENATEST_STR_SET[i] );
    for (k = 0; k <= i; ++k) {
      exists = gtset_string_check( set_string, GENATEST_STR_SET[k] );
      munit_assert( exists == (k % 2 != 0) );
    }
  }

  gtset_clear( set_string );
  for (i = 0; i < (int)GENATEST_STR_SET_LEN; ++i) {
    munit_assert( !gtset_string_check( set_string, GENATEST_STR_SET[i] ) );
  }

  gtset_free( set_string );

  /********************************************************************/
  set_array = gtset_array_new();

  munit_assert( !gtset_array_check( set_array, (genatest_buf_x){0,0,0,0} ) );

  for (i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i) {
    gtset_array_add( set_array, GENATEST_BUF_SET[i], NULL );
    for (k = 0; k < (int)GENATEST_INT_SET_LEN; ++k) {
      exists = gtset_array_check( set_array, GENATEST_BUF_SET[k] );
      munit_assert( exists == (k <= i) );
    }
  }

  for (i = 0; i < (int)GENATEST_BUF_SET_LEN; i += 2) {
    gtset_array_delete( set_array, GENATEST_BUF_SET[i] );
    for (k = 0; k <= i; ++k) {
      exists = gtset_array_check( set_array, GENATEST_BUF_SET[k] );
      munit_assert( exists == (k % 2 != 0) );
    }
  }

  gtset_clear( set_array );
  for (i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i) {
    munit_assert( !gtset_array_check( set_array, GENATEST_BUF_SET[i] ) );
  }

  gtset_free( set_array );

  /********************************************************************/
  return MUNIT_OK;
}}

MunitResult gtsettests_4_iterate() {
  gtset_naive_h set_naive;
  gtset_callback_h set_struct;
  gtset_string_h set_string;
  gtset_array_h set_array;
  gena_iterator_o iter1, iter2, iter3, riter1, riter2, riter3;
  gena_bool result;
  int i, k, compare;
{
  /********************************************************************/
  set_naive = gtset_naive_new();

  munit_assert( !gtset_begin( set_naive, GENA_FALSE, &iter1 ) );
  munit_assert( !gtset_end( set_naive, GENA_FALSE, &iter2 ) );
  munit_assert( !gtset_begin( set_naive, GENA_TRUE, &riter1 ) );
  munit_assert( !gtset_end( set_naive, GENA_TRUE, &riter2 ) );

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    result = gtset_naive_add( set_naive, i + GENATEST_CUSTOM_INT_1, NULL );
    munit_assert_true( result );

    munit_assert( gtset_begin( set_naive, GENA_FALSE, &iter1 ) );
    munit_assert( gtset_end( set_naive, GENA_FALSE, &iter2 ) );
    munit_assert( gtset_begin( set_naive, GENA_TRUE, &riter1 ) );
    munit_assert( gtset_end( set_naive, GENA_TRUE, &riter2 ) );

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
      munit_assert_int( gtset_naive_value( &iter1, 0 ), ==,
        k + GENATEST_CUSTOM_INT_1 );
      munit_assert_int( gtset_naive_value( &riter1, -k ), ==,
        i + GENATEST_CUSTOM_INT_1 );

      munit_assert( gena_iterator_next( &iter1 ) );
      munit_assert( gena_iterator_prior( &iter2 ) );

      munit_assert( gena_iterator_next( &riter1 ) );
      munit_assert( gena_iterator_prior( &riter2 ) );

      munit_assert( gtset_at( set_naive, k, GENA_FALSE, &iter3 ) );
      munit_assert( gtset_at( set_naive, k, GENA_TRUE, &riter3 ) );

      munit_assert_int( gtset_naive_value( &iter3, i-k ), ==,
        i + GENATEST_CUSTOM_INT_1 );
      munit_assert_int( gtset_naive_value( &riter3, 0 ), ==,
        i-k + GENATEST_CUSTOM_INT_1 );
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

  gtset_free( set_naive );

  /********************************************************************/
  set_struct = gtset_callback_new();

  munit_assert( !gtset_begin( set_struct, GENA_FALSE, &iter1 ) );
  munit_assert( !gtset_end( set_struct, GENA_FALSE, &iter2 ) );
  munit_assert( !gtset_begin( set_struct, GENA_TRUE, &riter1 ) );
  munit_assert( !gtset_end( set_struct, GENA_TRUE, &riter2 ) );

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    result = gtset_callback_add( set_struct, &GENATEST_C_SKEY(i), NULL );
    munit_assert_true( result );

    munit_assert( gtset_begin( set_struct, GENA_FALSE, &iter1 ) );
    munit_assert( gtset_end( set_struct, GENA_FALSE, &iter2 ) );
    munit_assert( gtset_begin( set_struct, GENA_TRUE, &riter1 ) );
    munit_assert( gtset_end( set_struct, GENA_TRUE, &riter2 ) );

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
      compare = genatest_skey_compare_cb( gtset_callback_value( &iter1, 0 ),
        &GENATEST_C_SKEY(k), sizeof(genatest_skey_s) );
      munit_assert_int( compare, ==, 0 );

      compare = genatest_skey_compare_cb( gtset_callback_value( &riter1, -k ),
        &GENATEST_C_SKEY(i), sizeof(genatest_skey_s) );
      munit_assert_int( compare, ==, 0 );

      munit_assert( gena_iterator_next( &iter1 ) );
      munit_assert( gena_iterator_prior( &iter2 ) );

      munit_assert( gena_iterator_next( &riter1 ) );
      munit_assert( gena_iterator_prior( &riter2 ) );

      munit_assert( gtset_at( set_struct, k, GENA_FALSE, &iter3 ) );
      munit_assert( gtset_at( set_struct, k, GENA_TRUE, &riter3 ) );

      compare = genatest_skey_compare_cb( gtset_callback_value( &iter3, 0 ),
        &GENATEST_C_SKEY(k), sizeof(genatest_skey_s) );
      munit_assert_int( compare, ==, 0 );

      compare = genatest_skey_compare_cb(
        gtset_callback_value( &riter3, i-k*2 ), &GENATEST_C_SKEY(k),
        sizeof(genatest_skey_s) );
      munit_assert_int( compare, ==, 0 );
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

  gtset_free( set_struct );

  /********************************************************************/
  set_string = gtset_string_new();

  munit_assert( !gtset_begin( set_string, GENA_FALSE, &iter1 ) );
  munit_assert( !gtset_end( set_string, GENA_FALSE, &iter2 ) );
  munit_assert( !gtset_begin( set_string, GENA_TRUE, &riter1 ) );
  munit_assert( !gtset_end( set_string, GENA_TRUE, &riter2 ) );

  for (i = 0; i < (int)GENATEST_STR_SET_LEN; ++i) {
    result = gtset_string_add( set_string, GENATEST_STR_SET[i], NULL );
    munit_assert_true( result );

    munit_assert( gtset_begin( set_string, GENA_FALSE, &iter1 ) );
    munit_assert( gtset_end( set_string, GENA_FALSE, &iter2 ) );
    munit_assert( gtset_begin( set_string, GENA_TRUE, &riter1 ) );
    munit_assert( gtset_end( set_string, GENA_TRUE, &riter2 ) );

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
      munit_assert_string_equal( gtset_string_value( &iter1, 0 ),
        GENATEST_STR_SET[k] );
      munit_assert_string_equal( gtset_string_value( &riter1, -k ),
        GENATEST_STR_SET[i] );

      munit_assert( gena_iterator_next( &iter1 ) );
      munit_assert( gena_iterator_prior( &iter2 ) );

      munit_assert( gena_iterator_next( &riter1 ) );
      munit_assert( gena_iterator_prior( &riter2 ) );

      munit_assert( gtset_at( set_string, k, GENA_FALSE, &iter3 ) );
      munit_assert( gtset_at( set_string, k, GENA_TRUE, &riter3 ) );

      munit_assert_string_equal( gtset_string_value( &iter3, i-k ),
        GENATEST_STR_SET[i] );
      munit_assert_string_equal( gtset_string_value( &riter3, 0 ),
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

  gtset_free( set_string );

  /********************************************************************/
  set_array = gtset_array_new();

  munit_assert( !gtset_begin( set_array, GENA_FALSE, &iter1 ) );
  munit_assert( !gtset_end( set_array, GENA_FALSE, &iter2 ) );
  munit_assert( !gtset_begin( set_array, GENA_TRUE, &riter1 ) );
  munit_assert( !gtset_end( set_array, GENA_TRUE, &riter2 ) );

  for (i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i) {
    result = gtset_array_add( set_array, GENATEST_BUF_SET[i], NULL );
    munit_assert_true( result );

    munit_assert( gtset_begin( set_array, GENA_FALSE, &iter1 ) );
    munit_assert( gtset_end( set_array, GENA_FALSE, &iter2 ) );
    munit_assert( gtset_begin( set_array, GENA_TRUE, &riter1 ) );
    munit_assert( gtset_end( set_array, GENA_TRUE, &riter2 ) );

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
        gtset_array_value( &iter1, 0 ), GENATEST_BUF_SET[k] );
      munit_assert_memory_equal( sizeof(genatest_buf_x),
        gtset_array_value( &riter1, -k ), GENATEST_BUF_SET[i] );

      munit_assert( gena_iterator_next( &iter1 ) );
      munit_assert( gena_iterator_prior( &iter2 ) );

      munit_assert( gena_iterator_next( &riter1 ) );
      munit_assert( gena_iterator_prior( &riter2 ) );

      munit_assert( gtset_at( set_array, k, GENA_FALSE, &iter3 ) );
      munit_assert( gtset_at( set_array, k, GENA_TRUE, &riter3 ) );

      munit_assert_memory_equal( sizeof(genatest_buf_x),
        gtset_array_value( &iter3, i-k ), GENATEST_BUF_SET[i] );
      munit_assert_memory_equal( sizeof(genatest_buf_x),
        gtset_array_value( &riter3, 0 ), GENATEST_BUF_SET[i-k] );
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

  gtset_free( set_array );

  /********************************************************************/
  return MUNIT_OK;
}}
