#include "gvec_tests.h"

/******************************************************************************/

MunitResult gvectests_1_create() {
  gvec_int_h vec_int;
  gvec_struct_h vec_struct;
  gvec_string_h vec_string;
  gvec_array_h vec_array;
{
  /********************************************************************/
  vec_int = gvec_int_new(0);
  munit_assert_not_null( vec_int );
  munit_assert( gvec_empty(vec_int) );
  munit_assert_size( gvec_count(vec_int), ==, 0 );
  gvec_free( vec_int );

  /********************************************************************/
  vec_struct = gvec_struct_new( GENATEST_INT_SET_LEN );
  munit_assert_not_null( vec_struct );
  munit_assert( gvec_empty(vec_struct) );
  munit_assert_size( gvec_count(vec_struct), ==, 0 );
  munit_assert_size( gvec_size(vec_struct), >=, GENATEST_INT_SET_LEN );
  gvec_free( vec_struct );

  /********************************************************************/
  vec_string = gvec_string_new( GENATEST_STR_SET_LEN );
  munit_assert_not_null( vec_string );
  munit_assert( gvec_empty(vec_string) );
  munit_assert_size( gvec_count(vec_string), ==, 0 );
  munit_assert_size( gvec_size(vec_string), >=, GENATEST_STR_SET_LEN );
  gvec_free( vec_string );

  /********************************************************************/
  vec_array = gvec_array_new( GENATEST_BUF_SET_LEN );
  munit_assert_not_null( vec_array );
  munit_assert( gvec_empty(vec_array) );
  munit_assert_size( gvec_count(vec_array), ==, 0 );
  munit_assert_size( gvec_size(vec_array), >=, GENATEST_BUF_SET_LEN );
  gvec_free( vec_array );

  /********************************************************************/
  return MUNIT_OK;
}}

/******************************************************************************/

MunitResult gvectests_2_modify() {
  gvec_int_h vec_int;
  gvec_struct_h vec_struct;
  gvec_string_h vec_string;
  gvec_array_h vec_array;
  gena_error_e errorcode;
  int i, k;
  size_t storage_size;
{
  /********************************************************************/
  vec_int = gvec_int_new(0);

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    errorcode = gvec_int_push( &vec_int, GENATEST_INT_SET[i] );
    munit_assert( errorcode == GENA_ERR_NO );
    munit_assert_size( gvec_count(vec_int), ==, i+1 );
    munit_assert_size( gvec_size(vec_int), >=, i+1 );
    munit_assert( !gvec_empty(vec_int) );
    munit_assert_memory_equal( sizeof(int) * (i+1), vec_int, GENATEST_INT_SET );
  }
  storage_size = gvec_size( vec_int );

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    errorcode = gvec_int_insert( &vec_int, i*2, 1, GENATEST_INT_SET[i] );
    munit_assert( errorcode == GENA_ERR_NO );
    munit_assert_size( gvec_count(vec_int), ==, GENATEST_INT_SET_LEN+i+1 );
    munit_assert_size( gvec_size(vec_int), >=, GENATEST_INT_SET_LEN+i+1 );
    munit_assert( !gvec_empty(vec_int) );
    for( k = 0; k < i*2; k += 2 ) {
      munit_assert_int( vec_int[k], ==, vec_int[k+1] );
      munit_assert_int( *gvec_int_at( vec_int, k ), ==,
        *gvec_int_at( vec_int, k+1 ) );
    }
  }

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    gvec_erase( vec_int, i, 1 );
    munit_assert_size( gvec_count(vec_int), ==, GENATEST_INT_SET_LEN*2-i-1 );
    munit_assert( !gvec_empty(vec_int) );
  }
  munit_assert_size( gvec_count(vec_int), ==, GENATEST_INT_SET_LEN );
  munit_assert( !gvec_empty(vec_int) );
  munit_assert_memory_equal( GENATEST_INT_SET_SIZE, vec_int, GENATEST_INT_SET );

  errorcode = gvec_int_insert( &vec_int, GENATEST_INT_SET_LEN,
    GENATEST_INT_SET_LEN, GENATEST_CUSTOM_INT_1 );
  munit_assert( errorcode == GENA_ERR_NO );
  errorcode = gvec_int_resize( &vec_int,
    gvec_count(vec_int) + GENATEST_INT_SET_LEN, GENATEST_CUSTOM_INT_2 );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_size( gvec_count(vec_int), ==, GENATEST_INT_SET_LEN*3 );
  munit_assert( !gvec_empty(vec_int) );
  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    munit_assert_int( vec_int[GENATEST_INT_SET_LEN+i], ==,
      GENATEST_CUSTOM_INT_1 );
    munit_assert_int( *gvec_int_at( vec_int, GENATEST_INT_SET_LEN+i ), ==,
      GENATEST_CUSTOM_INT_1 );
  }
  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    munit_assert_int( vec_int[GENATEST_INT_SET_LEN*2+i], ==,
      GENATEST_CUSTOM_INT_2 );
    munit_assert_int( *gvec_int_at( vec_int, GENATEST_INT_SET_LEN*2+i ), ==,
      GENATEST_CUSTOM_INT_2 );
  }

  errorcode = gvec_resize( &vec_int,
    gvec_count(vec_int) - GENATEST_INT_SET_LEN );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_size( gvec_count(vec_int), ==, GENATEST_INT_SET_LEN*2 );
  munit_assert( !gvec_empty(vec_int) );
  munit_assert_size( gvec_size(vec_int), >=, GENATEST_INT_SET_LEN*3 );

  gvec_erase( vec_int, GENATEST_INT_SET_LEN, GENATEST_INT_SET_LEN );
  munit_assert_size( gvec_count(vec_int), ==, GENATEST_INT_SET_LEN );
  munit_assert( !gvec_empty(vec_int) );
  munit_assert_size( gvec_size(vec_int), >=, GENATEST_INT_SET_LEN*3 );

  gvec_reserve( &vec_int, GENATEST_INT_SET_LEN );
  munit_assert_size( gvec_size(vec_int), >=, GENATEST_INT_SET_LEN*4 );
  errorcode = gvec_shrink( &vec_int );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_size( gvec_size(vec_int), ==, storage_size );
  munit_assert_memory_equal( GENATEST_INT_SET_SIZE, vec_int, GENATEST_INT_SET );

  gvec_erase( vec_int, 0, GENATEST_INT_SET_LEN );
  munit_assert_size( gvec_count(vec_int), ==, 0 );
  munit_assert( gvec_empty(vec_int) );
  munit_assert_null( gvec_int_at(vec_int, 0) );

  errorcode = gvec_int_insert( &vec_int, 0, 1, GENATEST_CUSTOM_INT_1 );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_int( gvec_int_front(vec_int), ==, gvec_int_back(vec_int) );
  errorcode = gvec_int_push( &vec_int, GENATEST_CUSTOM_INT_2 );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_int( gvec_int_front(vec_int), ==, GENATEST_CUSTOM_INT_1 );
  munit_assert_int( gvec_int_back(vec_int), ==, GENATEST_CUSTOM_INT_2 );

  gvec_pop( vec_int );
  munit_assert_int( gvec_int_front(vec_int), ==, gvec_int_back(vec_int) );
  gvec_clear( vec_int );
  munit_assert( gvec_empty(vec_int) );

  gvec_free( vec_int );

  /********************************************************************/
  vec_struct = gvec_struct_new(0);

  errorcode = gvec_reserve( &vec_struct, GENATEST_INT_SET_LEN );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_size( gvec_size(vec_struct), >=, GENATEST_INT_SET_LEN );
  storage_size = gvec_size( vec_struct );

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    errorcode = gvec_struct_push( &vec_struct,
      &GENATEST_C_SVALUE(GENATEST_INT_SET[i]) );
    munit_assert( errorcode == GENA_ERR_NO );
    munit_assert_size( gvec_count(vec_struct), ==, i+1 );
    munit_assert( !gvec_empty(vec_struct) );
    munit_assert_memory_equal( sizeof(int) * (i+1), vec_struct,
      GENATEST_INT_SET );
  }

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    errorcode = gvec_struct_insert( &vec_struct, i*2, 1,
      &GENATEST_C_SVALUE(GENATEST_INT_SET[i]) );
    munit_assert( errorcode == GENA_ERR_NO );
    munit_assert_size( gvec_count(vec_struct), ==, GENATEST_INT_SET_LEN+i+1 );
    munit_assert_size( gvec_size(vec_struct), >=, GENATEST_INT_SET_LEN+i+1 );
    munit_assert( !gvec_empty(vec_struct) );
    for( k = 0; k < i*2; k += 2 ) {
      munit_assert_memory_equal( sizeof(int), gvec_struct_at( vec_struct, k ),
        gvec_struct_at( vec_struct, k+1 ) );
    }
  }

  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    gvec_erase( vec_struct, i, 1 );
    munit_assert_size( gvec_count(vec_struct), ==, GENATEST_INT_SET_LEN*2-i-1 );
    munit_assert( !gvec_empty(vec_struct) );
  }
  munit_assert_size( gvec_count(vec_struct), ==, GENATEST_INT_SET_LEN );
  munit_assert( !gvec_empty(vec_struct) );
  munit_assert_memory_equal( GENATEST_INT_SET_SIZE, vec_struct,
    GENATEST_INT_SET );

  errorcode = gvec_struct_insert( &vec_struct, GENATEST_INT_SET_LEN,
    GENATEST_INT_SET_LEN, &GENATEST_C_SVALUE(GENATEST_CUSTOM_INT_1) );
  munit_assert( errorcode == GENA_ERR_NO );
  errorcode = gvec_struct_resize( &vec_struct,
    gvec_count(vec_struct) + GENATEST_INT_SET_LEN,
    &GENATEST_C_SVALUE(GENATEST_CUSTOM_INT_2) );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_size( gvec_count(vec_struct), ==, GENATEST_INT_SET_LEN*3 );
  munit_assert( !gvec_empty(vec_struct) );
  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    munit_assert_memory_equal( sizeof(int),
      gvec_struct_at( vec_struct, GENATEST_INT_SET_LEN+i ),
      &GENATEST_C_SVALUE(GENATEST_CUSTOM_INT_1) );
  }
  for( i = 0; i < (int)GENATEST_INT_SET_LEN; ++i ) {
    munit_assert_memory_equal( sizeof(int),
      gvec_struct_at( vec_struct, GENATEST_INT_SET_LEN*2+i ),
      &GENATEST_C_SVALUE(GENATEST_CUSTOM_INT_2) );
  }

  errorcode = gvec_resize( &vec_struct,
    gvec_count(vec_struct) - GENATEST_INT_SET_LEN );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_size( gvec_count(vec_struct), ==, GENATEST_INT_SET_LEN*2 );
  munit_assert( !gvec_empty(vec_struct) );
  munit_assert_size( gvec_size(vec_struct), >=, GENATEST_INT_SET_LEN*3 );

  gvec_erase( vec_struct, GENATEST_INT_SET_LEN, GENATEST_INT_SET_LEN );
  munit_assert_size( gvec_count(vec_struct), ==, GENATEST_INT_SET_LEN );
  munit_assert( !gvec_empty(vec_struct) );
  munit_assert_size( gvec_size(vec_struct), >=, GENATEST_INT_SET_LEN*3 );

  gvec_reserve( &vec_struct, GENATEST_INT_SET_LEN );
  munit_assert_size( gvec_size(vec_struct), >=, GENATEST_INT_SET_LEN*4 );
  errorcode = gvec_shrink( &vec_struct );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_size( gvec_size(vec_struct), ==, storage_size );
  munit_assert_memory_equal( GENATEST_INT_SET_SIZE, vec_struct,
    GENATEST_INT_SET );

  gvec_erase( vec_struct, 0, GENATEST_INT_SET_LEN );
  munit_assert_size( gvec_count(vec_struct), ==, 0 );
  munit_assert( gvec_empty(vec_struct) );
  munit_assert_null( gvec_struct_at(vec_struct, 0) );

  errorcode = gvec_struct_insert( &vec_struct, 0, 1,
    &GENATEST_C_SVALUE(GENATEST_CUSTOM_INT_1) );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_ptr_equal( gvec_struct_front(vec_struct),
    gvec_struct_back(vec_struct) );
  errorcode = gvec_struct_push( &vec_struct,
    &GENATEST_C_SVALUE(GENATEST_CUSTOM_INT_2) );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_ptr_not_equal( gvec_struct_front(vec_struct),
    gvec_struct_back(vec_struct) );

  gvec_pop( vec_struct );
  munit_assert_ptr_equal( gvec_struct_front(vec_struct),
    gvec_struct_back(vec_struct) );
  gvec_clear( vec_struct );
  munit_assert( gvec_empty(vec_struct) );

  gvec_free( vec_struct );

  /********************************************************************/
  vec_string = gvec_string_new(GENATEST_STR_SET_LEN);

  munit_assert_size( gvec_size(vec_string), >=, GENATEST_STR_SET_LEN );
  storage_size = gvec_size( vec_string );

  for( i = 0; i < (int)GENATEST_STR_SET_LEN; ++i ) {
    errorcode = gvec_string_push( &vec_string, GENATEST_STR_SET[i] );
    munit_assert( errorcode == GENA_ERR_NO );
    munit_assert_size( gvec_count(vec_string), ==, i+1 );
    munit_assert( !gvec_empty(vec_string) );
    munit_assert_string_equal( vec_string[i], GENATEST_STR_SET[i] );
  }

  for( i = 0; i < (int)GENATEST_STR_SET_LEN; ++i ) {
    errorcode = gvec_string_insert( &vec_string, i*2, 1, GENATEST_STR_SET[i] );
    munit_assert( errorcode == GENA_ERR_NO );
    munit_assert_size( gvec_count(vec_string), ==, GENATEST_STR_SET_LEN+i+1 );
    munit_assert_size( gvec_size(vec_string), >=, GENATEST_STR_SET_LEN+i+1 );
    munit_assert( !gvec_empty(vec_string) );
    for( k = 0; k < i*2; k += 2 ) {
      munit_assert_string_equal( gvec_string_at( vec_string, k ),
        gvec_string_at( vec_string, k+1 ) );
    }
  }

  for( i = 0; i < (int)GENATEST_STR_SET_LEN; ++i ) {
    gvec_erase( vec_string, i, 1 );
    munit_assert_size( gvec_count(vec_string), ==, GENATEST_STR_SET_LEN*2-i-1 );
    munit_assert( !gvec_empty(vec_string) );
  }
  munit_assert_size( gvec_count(vec_string), ==, GENATEST_STR_SET_LEN );
  munit_assert( !gvec_empty(vec_string) );
  munit_assert_memory_equal( GENATEST_STR_SET_SIZE, vec_string,
    GENATEST_STR_SET );

  errorcode = gvec_string_insert( &vec_string, GENATEST_STR_SET_LEN,
    GENATEST_STR_SET_LEN, GENATEST_CUSTOM_STR_1 );
  munit_assert( errorcode == GENA_ERR_NO );
  errorcode = gvec_string_resize( &vec_string,
    gvec_count(vec_string) + GENATEST_STR_SET_LEN, GENATEST_CUSTOM_STR_2 );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_size( gvec_count(vec_string), ==, GENATEST_STR_SET_LEN*3 );
  munit_assert( !gvec_empty(vec_string) );
  for( i = 0; i < (int)GENATEST_STR_SET_LEN; ++i ) {
    munit_assert_string_equal(
      gvec_string_at( vec_string, GENATEST_STR_SET_LEN+i ),
      GENATEST_CUSTOM_STR_1 );
  }
  for( i = 0; i < (int)GENATEST_STR_SET_LEN; ++i ) {
    munit_assert_string_equal(
      gvec_string_at( vec_string, GENATEST_STR_SET_LEN*2+i ),
      GENATEST_CUSTOM_STR_2 );
  }

  errorcode = gvec_resize( &vec_string,
    gvec_count(vec_string) - GENATEST_STR_SET_LEN );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_size( gvec_count(vec_string), ==, GENATEST_STR_SET_LEN*2 );
  munit_assert( !gvec_empty(vec_string) );
  munit_assert_size( gvec_size(vec_string), >=, GENATEST_STR_SET_LEN*3 );

  gvec_erase( vec_string, GENATEST_STR_SET_LEN, GENATEST_STR_SET_LEN );
  munit_assert_size( gvec_count(vec_string), ==, GENATEST_STR_SET_LEN );
  munit_assert( !gvec_empty(vec_string) );
  munit_assert_size( gvec_size(vec_string), >=, GENATEST_STR_SET_LEN*3 );

  gvec_reserve( &vec_string, GENATEST_STR_SET_LEN );
  munit_assert_size( gvec_size(vec_string), >=, GENATEST_STR_SET_LEN*4 );
  errorcode = gvec_shrink( &vec_string );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_size( gvec_size(vec_string), ==, storage_size );
  munit_assert_memory_equal( GENATEST_STR_SET_LEN, vec_string,
    GENATEST_STR_SET );

  gvec_erase( vec_string, 0, GENATEST_STR_SET_LEN );
  munit_assert_size( gvec_count(vec_string), ==, 0 );
  munit_assert( gvec_empty(vec_string) );
  munit_assert_null( gvec_string_at(vec_string, 0) );

  errorcode = gvec_string_insert( &vec_string, 0, 1, GENATEST_CUSTOM_STR_1 );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_ptr_equal( gvec_string_front(vec_string),
    gvec_string_back(vec_string) );
  errorcode = gvec_string_push( &vec_string, GENATEST_CUSTOM_STR_2 );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_ptr_not_equal( gvec_string_front(vec_string),
    gvec_string_back(vec_string) );

  gvec_pop( vec_string );
  munit_assert_ptr_equal( gvec_string_front(vec_string),
    gvec_string_back(vec_string) );
  gvec_clear( vec_string );
  munit_assert( gvec_empty(vec_string) );

  gvec_free( vec_string );

  /********************************************************************/
  vec_array = gvec_array_new(GENATEST_BUF_SET_LEN);
  storage_size = gvec_size( vec_array );
  errorcode = gvec_shrink( &vec_array );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_size( gvec_size(vec_array), <, storage_size );

  for( i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i ) {
    errorcode = gvec_array_push( &vec_array, GENATEST_BUF_SET[i] );
    munit_assert( errorcode == GENA_ERR_NO );
    munit_assert_size( gvec_count(vec_array), ==, i+1 );
    munit_assert( !gvec_empty(vec_array) );
    munit_assert_memory_equal( sizeof(genatest_buf_x), vec_array[i],
      GENATEST_BUF_SET[i] );
  }

  for( i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i ) {
    errorcode = gvec_array_insert( &vec_array, i*2, 1, GENATEST_BUF_SET[i] );
    munit_assert( errorcode == GENA_ERR_NO );
    munit_assert_size( gvec_count(vec_array), ==, GENATEST_BUF_SET_LEN+i+1 );
    munit_assert_size( gvec_size(vec_array), >=, GENATEST_BUF_SET_LEN+i+1 );
    munit_assert( !gvec_empty(vec_array) );
    for( k = 0; k < i*2; k += 2 ) {
      munit_assert_memory_equal( sizeof(genatest_buf_x),
        gvec_array_at( vec_array, k ), gvec_array_at( vec_array, k+1 ) );
    }
  }

  for( i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i ) {
    gvec_erase( vec_array, i, 1 );
    munit_assert_size( gvec_count(vec_array), ==, GENATEST_BUF_SET_LEN*2-i-1 );
    munit_assert( !gvec_empty(vec_array) );
  }
  munit_assert_size( gvec_count(vec_array), ==, GENATEST_BUF_SET_LEN );
  munit_assert( !gvec_empty(vec_array) );
  munit_assert_memory_equal( GENATEST_BUF_SET_SIZE, vec_array,
    GENATEST_BUF_SET );

  errorcode = gvec_array_insert( &vec_array, GENATEST_BUF_SET_LEN,
    GENATEST_BUF_SET_LEN, GENATEST_CUSTOM_BUF_1 );
  munit_assert( errorcode == GENA_ERR_NO );
  errorcode = gvec_array_resize( &vec_array,
    gvec_count(vec_array) + GENATEST_BUF_SET_LEN, GENATEST_CUSTOM_BUF_2 );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_size( gvec_count(vec_array), ==, GENATEST_BUF_SET_LEN*3 );
  munit_assert( !gvec_empty(vec_array) );
  for( i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i ) {
    munit_assert_memory_equal( sizeof(genatest_buf_x),
      gvec_array_at( vec_array, GENATEST_BUF_SET_LEN+i ),
      GENATEST_CUSTOM_BUF_1 );
  }
  for( i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i ) {
    munit_assert_memory_equal( sizeof(genatest_buf_x),
      gvec_array_at( vec_array, GENATEST_BUF_SET_LEN*2+i ),
      GENATEST_CUSTOM_BUF_2 );
  }

  errorcode = gvec_resize( &vec_array,
    gvec_count(vec_array) - GENATEST_BUF_SET_LEN );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_size( gvec_count(vec_array), ==, GENATEST_BUF_SET_LEN*2 );
  munit_assert( !gvec_empty(vec_array) );
  munit_assert_size( gvec_size(vec_array), >=, GENATEST_BUF_SET_LEN*3 );

  gvec_erase( vec_array, GENATEST_BUF_SET_LEN, GENATEST_BUF_SET_LEN );
  munit_assert_size( gvec_count(vec_array), ==, GENATEST_BUF_SET_LEN );
  munit_assert( !gvec_empty(vec_array) );
  munit_assert_size( gvec_size(vec_array), >=, GENATEST_BUF_SET_LEN*3 );

  gvec_reserve( &vec_array, GENATEST_BUF_SET_LEN );
  munit_assert_size( gvec_size(vec_array), >=, GENATEST_BUF_SET_LEN*4 );
  gvec_shrink( &vec_array );
  munit_assert_size( gvec_size(vec_array), ==, storage_size );
  munit_assert_memory_equal( GENATEST_BUF_SET_LEN, vec_array,
    GENATEST_BUF_SET );

  gvec_erase( vec_array, 0, GENATEST_BUF_SET_LEN );
  munit_assert_size( gvec_count(vec_array), ==, 0 );
  munit_assert( gvec_empty(vec_array) );
  munit_assert_null( gvec_array_at(vec_array, 0) );

  errorcode = gvec_array_insert( &vec_array, 0, 1, GENATEST_CUSTOM_BUF_1 );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_ptr_equal( gvec_array_front(vec_array),
    gvec_array_back(vec_array) );
  errorcode = gvec_array_push( &vec_array, GENATEST_CUSTOM_BUF_2 );
  munit_assert( errorcode == GENA_ERR_NO );
  munit_assert_ptr_not_equal( gvec_array_front(vec_array),
    gvec_array_back(vec_array) );

  gvec_pop( vec_array );
  munit_assert_ptr_equal( gvec_array_front(vec_array),
    gvec_array_back(vec_array) );
  gvec_clear( vec_array );
  munit_assert( gvec_empty(vec_array) );

  gvec_free( vec_array );

  /********************************************************************/
  return MUNIT_OK;
}}

/******************************************************************************/

MunitResult gvectests_3_manage() {
  gvec_int_h vec_int;
  gvec_struct_h vec_struct;
  gvec_string_h vec_string1;
  gvec_string_h vec_string2;
  gvec_array_h vec_array1;
  gvec_array_h vec_array2;
  gena_error_e errorcode;
{
  /********************************************************************/
  vec_int = gvec_int_new(0);

  errorcode = gvec_resize( &vec_int, GENATEST_INT_SET_LEN );
  munit_assert( errorcode == GENA_ERR_NO );
  memcpy( vec_int, GENATEST_INT_SET, GENATEST_INT_SET_SIZE );

  vec_struct = gvec_copy(vec_int);
  munit_assert_not_null(vec_struct);
  munit_assert_size( gvec_count(vec_struct), ==, GENATEST_INT_SET_LEN );
  munit_assert( !gvec_empty(vec_struct) );
  munit_assert_size( gvec_size(vec_struct), >=, GENATEST_INT_SET_LEN );
  munit_assert_memory_equal( GENATEST_INT_SET_SIZE, vec_struct,
    GENATEST_INT_SET );

  gvec_free(vec_int);
  gvec_free(vec_struct);

  /********************************************************************/
  vec_string1 = gvec_string_new(GENATEST_STR_SET_LEN);

  errorcode = gvec_resize( &vec_string1, GENATEST_STR_SET_LEN );
  munit_assert( errorcode == GENA_ERR_NO );
  memcpy( vec_string1, GENATEST_STR_SET, GENATEST_STR_SET_SIZE );

  vec_string2 = NULL;
  vec_string2 = gvec_set( &vec_string2, vec_string1 );
  munit_assert_not_null(vec_string2);
  munit_assert_size( gvec_count(vec_string2), ==, GENATEST_STR_SET_LEN );
  munit_assert( !gvec_empty(vec_string2) );
  munit_assert_size( gvec_size(vec_string2), >=, GENATEST_STR_SET_LEN );
  munit_assert_memory_equal( GENATEST_STR_SET_SIZE, vec_string2,
    GENATEST_STR_SET );

  gvec_free(vec_string1);
  gvec_free(vec_string2);

  /********************************************************************/
  vec_array1 = gvec_array_new(0);

  errorcode = gvec_resize( &vec_array1, GENATEST_BUF_SET_LEN );
  munit_assert( errorcode == GENA_ERR_NO );
  memcpy( vec_array1, GENATEST_BUF_SET, GENATEST_BUF_SET_SIZE );

  vec_array2 = gvec_array_new(GENATEST_BUF_SET_LEN);
  vec_array2 = gvec_set( &vec_array2, vec_array1 );
  munit_assert_not_null(vec_array2);
  munit_assert_size( gvec_count(vec_array2), ==, GENATEST_BUF_SET_LEN );
  munit_assert( !gvec_empty(vec_array2) );
  munit_assert_size( gvec_size(vec_array2), >=, GENATEST_BUF_SET_LEN );
  munit_assert_memory_equal( GENATEST_BUF_SET_SIZE, vec_array2,
    GENATEST_BUF_SET );

  gvec_free(vec_array1);
  gvec_free(vec_array2);

  /********************************************************************/
  return MUNIT_OK;
}}
