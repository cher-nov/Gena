#include "gmap_tests.h"

/******************************************************************************/

MunitResult gmaptests_1_create() {
  gmap_naive_t map_naive;
  gmap_memcmp_t map_memcmp;
  gmap_callback_t map_callback;
  gmap_string_t map_string;
  gmap_array_t map_array;
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
  map_string = gmap_new();
  munit_assert_not_null( map_string );
  munit_assert( gmap_empty(map_string) );
  munit_assert_size( gmap_count(map_string), ==, 0 );
  gmap_free( map_string );

  /********************************************************************/
  map_array = gmap_new();
  munit_assert_not_null( map_array );
  munit_assert( gmap_empty(map_array) );
  munit_assert_size( gmap_count(map_array), ==, 0 );
  gmap_free( map_array );

  /********************************************************************/
  return MUNIT_OK;
}}

/******************************************************************************/

MunitResult gmaptests_2_modify() {
  gmap_naive_t map_naive;
  gmap_memcmp_t map_memcmp;
  gmap_callback_t map_callback;
  gmap_string_t map_string;
  gmap_array_t map_array;
  gena_bool del_result;
  int* ptr_int;
  genatest_svalue_p ptr_svalue;
  genatest_str_t* ptr_str;
  genatest_buf_t* ptr_array;
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
    genatest_skey_s safe_skey;
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );

    ptr_svalue = gmap_memcmp_add( map_memcmp, &safe_skey,
      &GENATEST_C_SVALUE(i) );
    munit_assert_not_null( ptr_svalue );
    munit_assert_memory_equal( sizeof(genatest_svalue_s), ptr_svalue,
      &GENATEST_C_SVALUE(i) );
    munit_assert_size( gmap_count(map_memcmp), ==, i+1 );
    munit_assert( !gmap_empty(map_memcmp) );
  }

  for( i = (int)GENATEST_INT_SET_LEN; i-- > 1; ) {
    genatest_skey_s safe_skey;
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );

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
    ptr_svalue = gmap_callback_add( map_callback,
      &GENATEST_C_SKEY(GENATEST_INT_SET[i]), &GENATEST_C_SVALUE(i) );
    munit_assert_not_null( ptr_svalue );
    munit_assert_int( ptr_svalue->value, ==, i );
    munit_assert_size( gmap_count(map_callback), ==, i+1 );
    munit_assert( !gmap_empty(map_callback) );
  }

  for( i = (int)GENATEST_INT_SET_LEN; i-- > 1; ) {
    del_result = gmap_callback_delete( map_callback,
      &GENATEST_C_SKEY(GENATEST_INT_SET[i]) );
    munit_assert( del_result );
    munit_assert_size( gmap_count(map_callback), ==, i );
    munit_assert( !gmap_empty(map_callback) );
  }

  gmap_clear( map_callback );
  munit_assert_size( gmap_count(map_callback), ==, 0 );
  munit_assert( gmap_empty(map_callback) );

  gmap_free( map_callback );

  /********************************************************************/
  map_string = gmap_new();

  for( i = 0; i < (int)GENATEST_STR_SET_LEN; ++i ) {
    ptr_str = gmap_string_add( map_string, GENATEST_STR_SET[i],
      GENATEST_STR_SET[i] );
    munit_assert_not_null( ptr_str );
    munit_assert_string_equal( *ptr_str, GENATEST_STR_SET[i] );
    munit_assert_size( gmap_count(map_string), ==, i+1 );
    munit_assert( !gmap_empty(map_string) );
  }

  for( i = (int)GENATEST_STR_SET_LEN; i-- > 1; ) {
    del_result = gmap_string_delete( map_string, GENATEST_STR_SET[i] );
    munit_assert( del_result );
    munit_assert_size( gmap_count(map_string), ==, i );
    munit_assert( !gmap_empty(map_string) );
  }

  gmap_clear( map_string );
  munit_assert_size( gmap_count(map_string), ==, 0 );
  munit_assert( gmap_empty(map_string) );

  gmap_free( map_string );

  /********************************************************************/
  map_array = gmap_new();

  for( i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i ) {
    ptr_array = gmap_array_add( map_array, GENATEST_BUF_SET[i],
      GENATEST_BUF_SET[i] );
    munit_assert_not_null( ptr_array );
    munit_assert_memory_equal( sizeof(genatest_buf_t), *ptr_array,
      GENATEST_BUF_SET[i] );
    munit_assert_size( gmap_count(map_array), ==, i+1 );
    munit_assert( !gmap_empty(map_array) );
  }

  for( i = (int)GENATEST_BUF_SET_LEN; i-- > 1; ) {
    del_result = gmap_array_delete( map_array, GENATEST_BUF_SET[i] );
    munit_assert( del_result );
    munit_assert_size( gmap_count(map_array), ==, i );
    munit_assert( !gmap_empty(map_array) );
  }

  gmap_clear( map_array );
  munit_assert_size( gmap_count(map_array), ==, 0 );
  munit_assert( gmap_empty(map_array) );

  gmap_free( map_array );

  /********************************************************************/
  return MUNIT_OK;
}}

/******************************************************************************/

MunitResult gmaptests_3_lookup() {
  gmap_naive_t map_naive;
  gmap_memcmp_t map_memcmp;
  gmap_callback_t map_callback;
  gmap_string_t map_string;
  gmap_array_t map_array;
  int* ptr_int;
  genatest_svalue_p ptr_svalue;
  genatest_str_t* ptr_str;
  genatest_buf_t* ptr_array;
  int i, k;
  genatest_skey_s safe_skey;
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

  genatest_set_skey_safe( &safe_skey, 0 );
  ptr_svalue = gmap_memcmp_find( map_memcmp, &safe_skey );
  munit_assert_null( ptr_svalue );

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );
    gmap_memcmp_add( map_memcmp, &safe_skey, &GENATEST_C_SVALUE(i) );
    for( k = 0; k <= i; ++k ) {
      genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[k] );
      ptr_svalue = gmap_memcmp_find( map_memcmp, &safe_skey );
      munit_assert_not_null( ptr_svalue );
      munit_assert_int( ptr_svalue->value, ==, k );
    }
  }

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; i += 2 ) {
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );
    gmap_memcmp_delete( map_memcmp, &safe_skey );
    for( k = 0; k <= i; ++k ) {
      genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[k] );
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
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );
    ptr_svalue = gmap_memcmp_find( map_memcmp, &safe_skey );
    munit_assert_null( ptr_svalue );
  }

  gmap_free( map_memcmp );

  /********************************************************************/
  map_callback = gmap_new();

  ptr_svalue = gmap_callback_find( map_callback, &GENATEST_C_SKEY(0) );
  munit_assert_null( ptr_svalue );

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    gmap_callback_add( map_callback, &GENATEST_C_SKEY(GENATEST_INT_SET[i]),
      &GENATEST_C_SVALUE(i) );
    for( k = 0; k <= i; ++k ) {
      ptr_svalue = gmap_callback_find( map_callback,
        &GENATEST_C_SKEY(GENATEST_INT_SET[k]) );
      munit_assert_not_null( ptr_svalue );
      munit_assert_int( ptr_svalue->value, ==, k );
    }
  }

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; i += 2 ) {
    gmap_callback_delete( map_callback, &GENATEST_C_SKEY(GENATEST_INT_SET[i]) );
    for( k = 0; k <= i; ++k ) {
      ptr_svalue = gmap_callback_find( map_callback,
        &GENATEST_C_SKEY(GENATEST_INT_SET[k]) );
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
      &GENATEST_C_SKEY(GENATEST_INT_SET[i]) );
    munit_assert_null( ptr_svalue );
  }

  gmap_free( map_callback );

  /********************************************************************/
  map_string = gmap_new();

  ptr_str = gmap_string_find( map_string, "a" );
  munit_assert_null( ptr_str );

  for( i = 0; i < (int)GENATEST_STR_SET_LEN; ++i ) {
    gmap_string_add( map_string, GENATEST_STR_SET[i], GENATEST_STR_SET[i] );
    for( k = 0; k <= i; ++k ) {
      ptr_str = gmap_string_find( map_string, GENATEST_STR_SET[k] );
      munit_assert_not_null( ptr_str );
      munit_assert_string_equal( *ptr_str, GENATEST_STR_SET[k] );
    }
  }

  for( i = 0; i < (int)GENATEST_STR_SET_LEN; i += 2 ) {
    gmap_string_delete( map_string, GENATEST_STR_SET[i] );
    for( k = 0; k <= i; ++k ) {
      ptr_str = gmap_string_find( map_string, GENATEST_STR_SET[k] );
      if (k % 2 == 0) {
        munit_assert_null( ptr_str );
      } else {
        munit_assert_not_null( ptr_str );
        munit_assert_string_equal( *ptr_str, GENATEST_STR_SET[k] );
      }
    }
  }

  gmap_clear( map_string );
  for( i = 0; i < (int)GENATEST_STR_SET_LEN; ++i ) {
    ptr_str = gmap_string_find( map_string, GENATEST_STR_SET[i] );
    munit_assert_null( ptr_str );
  }

  gmap_free( map_string );

  /********************************************************************/
  map_array = gmap_new();

  ptr_array = gmap_array_find( map_array, (genatest_buf_t){0,0,0,0} );
  munit_assert_null( ptr_array );

  for( i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i ) {
    gmap_array_add( map_array, GENATEST_BUF_SET[i], GENATEST_BUF_SET[i] );
    for( k = 0; k <= i; ++k ) {
      ptr_array = gmap_array_find( map_array, GENATEST_BUF_SET[k] );
      munit_assert_not_null( ptr_array );
      munit_assert_memory_equal( sizeof(genatest_buf_t), *ptr_array,
        GENATEST_BUF_SET[k] );
    }
  }

  for( i = 0; i < (int)GENATEST_BUF_SET_LEN; i += 2 ) {
    gmap_array_delete( map_array, GENATEST_BUF_SET[i] );
    for( k = 0; k <= i; ++k ) {
      ptr_array = gmap_array_find( map_array, GENATEST_BUF_SET[k] );
      if (k % 2 == 0) {
        munit_assert_null( ptr_array );
      } else {
        munit_assert_not_null( ptr_array );
        munit_assert_memory_equal( sizeof(genatest_buf_t), *ptr_array,
          GENATEST_BUF_SET[k] );
      }
    }
  }

  gmap_clear( map_array );
  for( i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i ) {
    ptr_array = gmap_array_find( map_array, GENATEST_BUF_SET[i] );
    munit_assert_null( ptr_array );
  }

  gmap_free( map_array );

  /********************************************************************/
  return MUNIT_OK;
}}
