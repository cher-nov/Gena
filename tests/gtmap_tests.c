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
  gena_bool del_result;
  int* ptr_int;
  genatest_svalue_p ptr_svalue;
  char* ptr_str;
  int* ptr_array;
  int i;
{
  /********************************************************************/
  map_naive = gtmap_naive_new();

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    ptr_int = gtmap_naive_add( map_naive, GENATEST_INT_SET[i], i );
    munit_assert_not_null( ptr_int );
    munit_assert_int( *ptr_int, ==, i );
    munit_assert_size( gtmap_count(map_naive), ==, i+1 );
    munit_assert( !gtmap_empty(map_naive) );
  }

  for( i = (int)GENATEST_INT_SET_LEN; i-- > 1; ) {
    del_result = gtmap_naive_delete( map_naive, GENATEST_INT_SET[i] );
    munit_assert( del_result );
    munit_assert_size( gtmap_count(map_naive), ==, i );
    munit_assert( !gtmap_empty(map_naive) );
  }

  gtmap_clear( map_naive );
  munit_assert_size( gtmap_count(map_naive), ==, 0 );
  munit_assert( gtmap_empty(map_naive) );

  gtmap_free( map_naive );

  /********************************************************************/
  map_memcmp = gtmap_memcmp_new();

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    genatest_skey_s safe_skey;
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );

    ptr_svalue = gtmap_memcmp_add( map_memcmp, &safe_skey,
      &GENATEST_C_SVALUE(i) );
    munit_assert_not_null( ptr_svalue );
    munit_assert_memory_equal( sizeof(genatest_svalue_s), ptr_svalue,
      &GENATEST_C_SVALUE(i) );
    munit_assert_size( gtmap_count(map_memcmp), ==, i+1 );
    munit_assert( !gtmap_empty(map_memcmp) );
  }

  for( i = (int)GENATEST_INT_SET_LEN; i-- > 1; ) {
    genatest_skey_s safe_skey;
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );

    del_result = gtmap_memcmp_delete( map_memcmp, &safe_skey );
    munit_assert( del_result );
    munit_assert_size( gtmap_count(map_memcmp), ==, i );
    munit_assert( !gtmap_empty(map_memcmp) );
  }

  gtmap_clear( map_memcmp );
  munit_assert_size( gtmap_count(map_memcmp), ==, 0 );
  munit_assert( gtmap_empty(map_memcmp) );

  gtmap_free( map_memcmp );

  /********************************************************************/
  map_callback = gtmap_callback_new();

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    ptr_svalue = gtmap_callback_add( map_callback,
      &GENATEST_C_SKEY(GENATEST_INT_SET[i]), &GENATEST_C_SVALUE(i) );
    munit_assert_not_null( ptr_svalue );
    munit_assert_int( ptr_svalue->value, ==, i );
    munit_assert_size( gtmap_count(map_callback), ==, i+1 );
    munit_assert( !gtmap_empty(map_callback) );
  }

  for( i = (int)GENATEST_INT_SET_LEN; i-- > 1; ) {
    del_result = gtmap_callback_delete( map_callback,
      &GENATEST_C_SKEY(GENATEST_INT_SET[i]) );
    munit_assert( del_result );
    munit_assert_size( gtmap_count(map_callback), ==, i );
    munit_assert( !gtmap_empty(map_callback) );
  }

  gtmap_clear( map_callback );
  munit_assert_size( gtmap_count(map_callback), ==, 0 );
  munit_assert( gtmap_empty(map_callback) );

  gtmap_free( map_callback );

  /********************************************************************/
  map_string = gtmap_string_new();

  for( i = 0; i < (int)GENATEST_STR_SET_LEN; ++i ) {
    ptr_str = gtmap_string_add( map_string, GENATEST_STR_SET[i],
      GENATEST_STR_SET[i] );
    munit_assert_not_null( ptr_str );
    munit_assert_string_equal( ptr_str, GENATEST_STR_SET[i] );
    munit_assert_size( gtmap_count(map_string), ==, i+1 );
    munit_assert( !gtmap_empty(map_string) );
  }

  for( i = (int)GENATEST_STR_SET_LEN; i-- > 1; ) {
    del_result = gtmap_string_delete( map_string, GENATEST_STR_SET[i] );
    munit_assert( del_result );
    munit_assert_size( gtmap_count(map_string), ==, i );
    munit_assert( !gtmap_empty(map_string) );
  }

  gtmap_clear( map_string );
  munit_assert_size( gtmap_count(map_string), ==, 0 );
  munit_assert( gtmap_empty(map_string) );

  gtmap_free( map_string );

  /********************************************************************/
  map_array = gtmap_array_new();

  for( i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i ) {
    ptr_array = gtmap_array_add( map_array, GENATEST_BUF_SET[i],
      GENATEST_BUF_SET[i] );
    munit_assert_not_null( ptr_array );
    munit_assert_memory_equal( sizeof(genatest_buf_x), ptr_array,
      GENATEST_BUF_SET[i] );
    munit_assert_size( gtmap_count(map_array), ==, i+1 );
    munit_assert( !gtmap_empty(map_array) );
  }

  for( i = (int)GENATEST_BUF_SET_LEN; i-- > 1; ) {
    del_result = gtmap_array_delete( map_array, GENATEST_BUF_SET[i] );
    munit_assert( del_result );
    munit_assert_size( gtmap_count(map_array), ==, i );
    munit_assert( !gtmap_empty(map_array) );
  }

  gtmap_clear( map_array );
  munit_assert_size( gtmap_count(map_array), ==, 0 );
  munit_assert( gtmap_empty(map_array) );

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

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    gtmap_naive_add( map_naive, GENATEST_INT_SET[i], i );
    for( k = 0; k <= i; ++k ) {
      ptr_int = gtmap_naive_find( map_naive, GENATEST_INT_SET[k] );
      munit_assert_not_null( ptr_int );
      munit_assert_int( *ptr_int, ==, k );
    }
  }

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; i += 2 ) {
    gtmap_naive_delete( map_naive, GENATEST_INT_SET[i] );
    for( k = 0; k <= i; ++k ) {
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
  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    ptr_int = gtmap_naive_find( map_naive, GENATEST_INT_SET[i] );
    munit_assert_null( ptr_int );
  }

  gtmap_free( map_naive );

  /********************************************************************/
  map_memcmp = gtmap_memcmp_new();

  genatest_set_skey_safe( &safe_skey, 0 );
  ptr_svalue = gtmap_memcmp_find( map_memcmp, &safe_skey );
  munit_assert_null( ptr_svalue );

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );
    gtmap_memcmp_add( map_memcmp, &safe_skey, &GENATEST_C_SVALUE(i) );
    for( k = 0; k <= i; ++k ) {
      genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[k] );
      ptr_svalue = gtmap_memcmp_find( map_memcmp, &safe_skey );
      munit_assert_not_null( ptr_svalue );
      munit_assert_int( ptr_svalue->value, ==, k );
    }
  }

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; i += 2 ) {
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );
    gtmap_memcmp_delete( map_memcmp, &safe_skey );
    for( k = 0; k <= i; ++k ) {
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
  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    genatest_set_skey_safe( &safe_skey, GENATEST_INT_SET[i] );
    ptr_svalue = gtmap_memcmp_find( map_memcmp, &safe_skey );
    munit_assert_null( ptr_svalue );
  }

  gtmap_free( map_memcmp );

  /********************************************************************/
  map_callback = gtmap_callback_new();

  ptr_svalue = gtmap_callback_find( map_callback, &GENATEST_C_SKEY(0) );
  munit_assert_null( ptr_svalue );

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    gtmap_callback_add( map_callback, &GENATEST_C_SKEY(GENATEST_INT_SET[i]),
      &GENATEST_C_SVALUE(i) );
    for( k = 0; k <= i; ++k ) {
      ptr_svalue = gtmap_callback_find( map_callback,
        &GENATEST_C_SKEY(GENATEST_INT_SET[k]) );
      munit_assert_not_null( ptr_svalue );
      munit_assert_int( ptr_svalue->value, ==, k );
    }
  }

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; i += 2 ) {
    gtmap_callback_delete( map_callback,
      &GENATEST_C_SKEY(GENATEST_INT_SET[i]) );
    for( k = 0; k <= i; ++k ) {
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
  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    ptr_svalue = gtmap_callback_find( map_callback,
      &GENATEST_C_SKEY(GENATEST_INT_SET[i]) );
    munit_assert_null( ptr_svalue );
  }

  gtmap_free( map_callback );

  /********************************************************************/
  map_string = gtmap_string_new();

  ptr_str = gtmap_string_find( map_string, "a" );
  munit_assert_null( ptr_str );

  for( i = 0; i < (int)GENATEST_STR_SET_LEN; ++i ) {
    gtmap_string_add( map_string, GENATEST_STR_SET[i], GENATEST_STR_SET[i] );
    for( k = 0; k <= i; ++k ) {
      ptr_str = gtmap_string_find( map_string, GENATEST_STR_SET[k] );
      munit_assert_not_null( ptr_str );
      munit_assert_string_equal( ptr_str, GENATEST_STR_SET[k] );
    }
  }

  for( i = 0; i < (int)GENATEST_STR_SET_LEN; i += 2 ) {
    gtmap_string_delete( map_string, GENATEST_STR_SET[i] );
    for( k = 0; k <= i; ++k ) {
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
  for( i = 0; i < (int)GENATEST_STR_SET_LEN; ++i ) {
    ptr_str = gtmap_string_find( map_string, GENATEST_STR_SET[i] );
    munit_assert_null( ptr_str );
  }

  gtmap_free( map_string );

  /********************************************************************/
  map_array = gtmap_array_new();

  ptr_array = gtmap_array_find( map_array, (genatest_buf_x){0,0,0,0} );
  munit_assert_null( ptr_array );

  for( i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i ) {
    gtmap_array_add( map_array, GENATEST_BUF_SET[i], GENATEST_BUF_SET[i] );
    for( k = 0; k <= i; ++k ) {
      ptr_array = gtmap_array_find( map_array, GENATEST_BUF_SET[k] );
      munit_assert_not_null( ptr_array );
      munit_assert_memory_equal( sizeof(genatest_buf_x), ptr_array,
        GENATEST_BUF_SET[k] );
    }
  }

  for( i = 0; i < (int)GENATEST_BUF_SET_LEN; i += 2 ) {
    gtmap_array_delete( map_array, GENATEST_BUF_SET[i] );
    for( k = 0; k <= i; ++k ) {
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
  for( i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i ) {
    ptr_array = gtmap_array_find( map_array, GENATEST_BUF_SET[i] );
    munit_assert_null( ptr_array );
  }

  gtmap_free( map_array );

  /********************************************************************/
  return MUNIT_OK;
}}
