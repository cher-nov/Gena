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
  gena_bool result;
  int i, k;
  size_t storage_size;
{
  /********************************************************************/
  vec_int = gvec_int_new(0);

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    munit_assert( gvec_int_push( &vec_int, GENATEST_INT_SET[i] ) );
    munit_assert_size( gvec_count(vec_int), ==, i+1 );
    munit_assert_size( gvec_size(vec_int), >=, i+1 );
    munit_assert( !gvec_empty(vec_int) );
    munit_assert_memory_equal( sizeof(int) * (i+1), vec_int, GENATEST_INT_SET );
  }
  storage_size = gvec_size( vec_int );

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    result = gvec_int_insert( &vec_int, i*2, 1, GENATEST_INT_SET[i] );
    munit_assert_true( result );
    munit_assert_size( gvec_count(vec_int), ==, GENATEST_INT_SET_LEN+i+1 );
    munit_assert_size( gvec_size(vec_int), >=, GENATEST_INT_SET_LEN+i+1 );
    munit_assert( !gvec_empty(vec_int) );
    for (k = 0; k < i*2; k += 2) {
      munit_assert_int( vec_int[k], ==, vec_int[k+1] );
    }
  }

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    gvec_remove( vec_int, i, 1 );
    munit_assert_size( gvec_count(vec_int), ==, GENATEST_INT_SET_LEN*2-i-1 );
    munit_assert( !gvec_empty(vec_int) );
  }
  munit_assert_size( gvec_count(vec_int), ==, GENATEST_INT_SET_LEN );
  munit_assert( !gvec_empty(vec_int) );
  munit_assert_memory_equal( GENATEST_INT_SET_SIZE, vec_int, GENATEST_INT_SET );

  result = gvec_int_insert( &vec_int, GENATEST_INT_SET_LEN,
    GENATEST_INT_SET_LEN, GENATEST_CUSTOM_INT_1 );
  munit_assert_true( result );
  result = gvec_int_resize( &vec_int,
    gvec_count(vec_int) + GENATEST_INT_SET_LEN, GENATEST_CUSTOM_INT_2 );
  munit_assert_true( result );
  munit_assert_size( gvec_count(vec_int), ==, GENATEST_INT_SET_LEN*3 );
  munit_assert( !gvec_empty(vec_int) );
  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    munit_assert_int( vec_int[GENATEST_INT_SET_LEN+i], ==,
      GENATEST_CUSTOM_INT_1 );
  }
  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    munit_assert_int( vec_int[GENATEST_INT_SET_LEN*2+i], ==,
      GENATEST_CUSTOM_INT_2 );
  }

  gvec_reduce( vec_int, gvec_count(vec_int) - GENATEST_INT_SET_LEN );
  munit_assert_size( gvec_count(vec_int), ==, GENATEST_INT_SET_LEN*2 );
  munit_assert( !gvec_empty(vec_int) );
  munit_assert_size( gvec_size(vec_int), >=, GENATEST_INT_SET_LEN*3 );

  munit_assert( gvec_remove( vec_int, GENATEST_INT_SET_LEN,
    GENATEST_INT_SET_LEN ) );
  munit_assert_size( gvec_count(vec_int), ==, GENATEST_INT_SET_LEN );
  munit_assert( !gvec_empty(vec_int) );
  munit_assert_size( gvec_size(vec_int), >=, GENATEST_INT_SET_LEN*3 );

  munit_assert( gvec_int_reserve( &vec_int, GENATEST_INT_SET_LEN*4 ) );
  munit_assert_size( gvec_size(vec_int), >=, GENATEST_INT_SET_LEN*4 );
  munit_assert( gvec_int_shrink(&vec_int) );
  munit_assert_size( gvec_size(vec_int), ==, storage_size );
  munit_assert_memory_equal( GENATEST_INT_SET_SIZE, vec_int, GENATEST_INT_SET );

  gvec_clear( vec_int );
  munit_assert_size( gvec_count(vec_int), ==, 0 );
  munit_assert( gvec_empty(vec_int) );

  munit_assert( gvec_int_insert( &vec_int, 0, 1, GENATEST_CUSTOM_INT_1 ) );
  munit_assert( gvec_int_push( &vec_int, GENATEST_CUSTOM_INT_2 ) );
  munit_assert_int( gvec_int_pop(vec_int), ==, GENATEST_CUSTOM_INT_2 );
  munit_assert( gvec_drop(vec_int) );
  munit_assert( gvec_empty(vec_int) );

  gvec_free( vec_int );

  /********************************************************************/
  vec_struct = gvec_struct_new(0);

  munit_assert( gvec_struct_reserve( &vec_struct, GENATEST_INT_SET_LEN ) );
  munit_assert_size( gvec_size(vec_struct), >=, GENATEST_INT_SET_LEN );
  storage_size = gvec_size( vec_struct );

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    result = gvec_struct_push( &vec_struct,
      &GENATEST_C_SVALUE(GENATEST_INT_SET[i]) );
    munit_assert_true( result );
    munit_assert_size( gvec_count(vec_struct), ==, i+1 );
    munit_assert( !gvec_empty(vec_struct) );
    munit_assert_memory_equal( sizeof(int) * (i+1), vec_struct,
      GENATEST_INT_SET );
  }

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    result = gvec_struct_insert( &vec_struct, i*2, 1,
      &GENATEST_C_SVALUE(GENATEST_INT_SET[i]) );
    munit_assert_true( result );
    munit_assert_size( gvec_count(vec_struct), ==, GENATEST_INT_SET_LEN+i+1 );
    munit_assert_size( gvec_size(vec_struct), >=, GENATEST_INT_SET_LEN+i+1 );
    munit_assert( !gvec_empty(vec_struct) );
    for (k = 0; k < i*2; k += 2) {
      munit_assert_memory_equal( sizeof(int), &vec_struct[k],
        &vec_struct[k+1] );
    }
  }

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    gvec_remove( vec_struct, i, 1 );
    munit_assert_size( gvec_count(vec_struct), ==, GENATEST_INT_SET_LEN*2-i-1 );
    munit_assert( !gvec_empty(vec_struct) );
  }
  munit_assert_size( gvec_count(vec_struct), ==, GENATEST_INT_SET_LEN );
  munit_assert( !gvec_empty(vec_struct) );
  munit_assert_memory_equal( GENATEST_INT_SET_SIZE, vec_struct,
    GENATEST_INT_SET );

  result = gvec_struct_insert( &vec_struct, GENATEST_INT_SET_LEN,
    GENATEST_INT_SET_LEN, &GENATEST_C_SVALUE(GENATEST_CUSTOM_INT_1) );
  munit_assert_true( result );
  result = gvec_struct_resize( &vec_struct,
    gvec_count(vec_struct) + GENATEST_INT_SET_LEN,
    &GENATEST_C_SVALUE(GENATEST_CUSTOM_INT_2) );
  munit_assert_true( result );
  munit_assert_size( gvec_count(vec_struct), ==, GENATEST_INT_SET_LEN*3 );
  munit_assert( !gvec_empty(vec_struct) );
  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    munit_assert_memory_equal( sizeof(int),
      &vec_struct[GENATEST_INT_SET_LEN+i],
      &GENATEST_C_SVALUE(GENATEST_CUSTOM_INT_1) );
  }
  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    munit_assert_memory_equal( sizeof(int),
      &vec_struct[GENATEST_INT_SET_LEN*2+i],
      &GENATEST_C_SVALUE(GENATEST_CUSTOM_INT_2) );
  }

  gvec_reduce( vec_struct, gvec_count(vec_struct) - GENATEST_INT_SET_LEN );
  munit_assert_size( gvec_count(vec_struct), ==, GENATEST_INT_SET_LEN*2 );
  munit_assert( !gvec_empty(vec_struct) );
  munit_assert_size( gvec_size(vec_struct), >=, GENATEST_INT_SET_LEN*3 );

  result = gvec_remove( vec_struct, GENATEST_INT_SET_LEN,
    GENATEST_INT_SET_LEN );
  munit_assert_true( result );
  munit_assert_size( gvec_count(vec_struct), ==, GENATEST_INT_SET_LEN );
  munit_assert( !gvec_empty(vec_struct) );
  munit_assert_size( gvec_size(vec_struct), >=, GENATEST_INT_SET_LEN*3 );

  munit_assert( gvec_struct_reserve( &vec_struct, GENATEST_INT_SET_LEN*4 ) );
  munit_assert_size( gvec_size(vec_struct), >=, GENATEST_INT_SET_LEN*4 );
  munit_assert( gvec_struct_shrink( &vec_struct ) );
  munit_assert_size( gvec_size(vec_struct), ==, storage_size );
  munit_assert_memory_equal( GENATEST_INT_SET_SIZE, vec_struct,
    GENATEST_INT_SET );

  gvec_clear( vec_struct );
  munit_assert_size( gvec_count(vec_struct), ==, 0 );
  munit_assert( gvec_empty(vec_struct) );

  result = gvec_struct_insert( &vec_struct, 0, 1,
    &GENATEST_C_SVALUE(GENATEST_CUSTOM_INT_1) );
  munit_assert_true( result );
  result = gvec_struct_push( &vec_struct,
    &GENATEST_C_SVALUE(GENATEST_CUSTOM_INT_2) );
  munit_assert_true( result );
  munit_assert_memory_equal( sizeof(int), gvec_struct_pop(vec_struct),
    &GENATEST_C_SVALUE(GENATEST_CUSTOM_INT_2) );
  munit_assert( gvec_drop(vec_struct) );
  munit_assert( gvec_empty(vec_struct) );

  gvec_free( vec_struct );

  /********************************************************************/
  vec_string = gvec_string_new( GENATEST_STR_SET_LEN );

  munit_assert_size( gvec_size(vec_string), >=, GENATEST_STR_SET_LEN );
  storage_size = gvec_size( vec_string );

  for (i = 0; i < (int)GENATEST_STR_SET_LEN; ++i) {
    munit_assert( gvec_string_push( &vec_string, GENATEST_STR_SET[i] ) );
    munit_assert_size( gvec_count(vec_string), ==, i+1 );
    munit_assert( !gvec_empty(vec_string) );
    munit_assert_string_equal( vec_string[i], GENATEST_STR_SET[i] );
  }

  for (i = 0; i < (int)GENATEST_STR_SET_LEN; ++i) {
    result = gvec_string_insert( &vec_string, i*2, 1, GENATEST_STR_SET[i] );
    munit_assert_true( result );
    munit_assert_size( gvec_count(vec_string), ==, GENATEST_STR_SET_LEN+i+1 );
    munit_assert_size( gvec_size(vec_string), >=, GENATEST_STR_SET_LEN+i+1 );
    munit_assert( !gvec_empty(vec_string) );
    for (k = 0; k < i*2; k += 2) {
      munit_assert_string_equal( vec_string[k], vec_string[k+1] );
    }
  }

  for (i = 0; i < (int)GENATEST_STR_SET_LEN; ++i) {
    munit_assert( gvec_remove( vec_string, i, 1 ) );
    munit_assert_size( gvec_count(vec_string), ==, GENATEST_STR_SET_LEN*2-i-1 );
    munit_assert( !gvec_empty(vec_string) );
  }
  munit_assert_size( gvec_count(vec_string), ==, GENATEST_STR_SET_LEN );
  munit_assert( !gvec_empty(vec_string) );
  munit_assert_memory_equal( GENATEST_STR_SET_SIZE, vec_string,
    GENATEST_STR_SET );

  result = gvec_string_insert( &vec_string, GENATEST_STR_SET_LEN,
    GENATEST_STR_SET_LEN, GENATEST_CUSTOM_STR_1 );
  munit_assert_true( result );
  result = gvec_string_resize( &vec_string,
    gvec_count(vec_string) + GENATEST_STR_SET_LEN, GENATEST_CUSTOM_STR_2 );
  munit_assert_true( result );
  munit_assert_size( gvec_count(vec_string), ==, GENATEST_STR_SET_LEN*3 );
  munit_assert( !gvec_empty(vec_string) );
  for (i = 0; i < (int)GENATEST_STR_SET_LEN; ++i) {
    munit_assert_string_equal( vec_string[GENATEST_STR_SET_LEN+i],
      GENATEST_CUSTOM_STR_1 );
  }
  for (i = 0; i < (int)GENATEST_STR_SET_LEN; ++i) {
    munit_assert_string_equal( vec_string[GENATEST_STR_SET_LEN*2+i],
      GENATEST_CUSTOM_STR_2 );
  }

  gvec_reduce( vec_string, gvec_count(vec_string) - GENATEST_STR_SET_LEN );
  munit_assert_size( gvec_count(vec_string), ==, GENATEST_STR_SET_LEN*2 );
  munit_assert( !gvec_empty(vec_string) );
  munit_assert_size( gvec_size(vec_string), >=, GENATEST_STR_SET_LEN*3 );

  result = gvec_remove( vec_string, GENATEST_STR_SET_LEN,
    GENATEST_STR_SET_LEN );
  munit_assert_true( result );
  munit_assert_size( gvec_count(vec_string), ==, GENATEST_STR_SET_LEN );
  munit_assert( !gvec_empty(vec_string) );
  munit_assert_size( gvec_size(vec_string), >=, GENATEST_STR_SET_LEN*3 );

  munit_assert( gvec_string_reserve( &vec_string, GENATEST_STR_SET_LEN*4 ) );
  munit_assert_size( gvec_size(vec_string), >=, GENATEST_STR_SET_LEN*4 );
  munit_assert( gvec_string_shrink( &vec_string ) );
  munit_assert_size( gvec_size(vec_string), ==, storage_size );
  munit_assert_memory_equal( GENATEST_STR_SET_LEN, vec_string,
    GENATEST_STR_SET );

  munit_assert( gvec_remove( vec_string, 0, GENATEST_STR_SET_LEN ) );
  munit_assert_size( gvec_count(vec_string), ==, 0 );
  munit_assert( gvec_empty(vec_string) );

  result = gvec_string_insert( &vec_string, 0, 1, GENATEST_CUSTOM_STR_1 );
  munit_assert_true( result );
  result = gvec_string_push( &vec_string, GENATEST_CUSTOM_STR_2 );
  munit_assert_true( result );
  munit_assert_string_equal( gvec_string_pop(vec_string),
    GENATEST_CUSTOM_STR_2 );
  munit_assert( gvec_drop(vec_string) );
  munit_assert( gvec_empty(vec_string) );

  gvec_free( vec_string );

  /********************************************************************/
  vec_array = gvec_array_new( GENATEST_BUF_SET_LEN );
  storage_size = gvec_size( vec_array );
  munit_assert( gvec_array_shrink( &vec_array ) );
  munit_assert_size( gvec_size(vec_array), <, storage_size );

  for (i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i) {
    munit_assert( gvec_array_push( &vec_array, GENATEST_BUF_SET[i] ) );
    munit_assert_size( gvec_count(vec_array), ==, i+1 );
    munit_assert( !gvec_empty(vec_array) );
    munit_assert_memory_equal( sizeof(genatest_buf_x), vec_array[i],
      GENATEST_BUF_SET[i] );
  }

  for (i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i) {
    result = gvec_array_insert( &vec_array, i*2, 1, GENATEST_BUF_SET[i] );
    munit_assert_true( result );
    munit_assert_size( gvec_count(vec_array), ==, GENATEST_BUF_SET_LEN+i+1 );
    munit_assert_size( gvec_size(vec_array), >=, GENATEST_BUF_SET_LEN+i+1 );
    munit_assert( !gvec_empty(vec_array) );
    for (k = 0; k < i*2; k += 2) {
      munit_assert_memory_equal( sizeof(genatest_buf_x), &vec_array[k],
        &vec_array[k+1] );
    }
  }

  for (i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i) {
    munit_assert( gvec_remove( vec_array, i, 1 ) );
    munit_assert_size( gvec_count(vec_array), ==, GENATEST_BUF_SET_LEN*2-i-1 );
    munit_assert( !gvec_empty(vec_array) );
  }
  munit_assert_size( gvec_count(vec_array), ==, GENATEST_BUF_SET_LEN );
  munit_assert( !gvec_empty(vec_array) );
  munit_assert_memory_equal( GENATEST_BUF_SET_SIZE, vec_array,
    GENATEST_BUF_SET );

  result = gvec_array_insert( &vec_array, GENATEST_BUF_SET_LEN,
    GENATEST_BUF_SET_LEN, GENATEST_CUSTOM_BUF_1 );
  munit_assert_true( result );
  result = gvec_array_resize( &vec_array,
    gvec_count(vec_array) + GENATEST_BUF_SET_LEN, GENATEST_CUSTOM_BUF_2 );
  munit_assert_true( result );
  munit_assert_size( gvec_count(vec_array), ==, GENATEST_BUF_SET_LEN*3 );
  munit_assert( !gvec_empty(vec_array) );
  for (i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i) {
    munit_assert_memory_equal( sizeof(genatest_buf_x),
      &vec_array[GENATEST_BUF_SET_LEN+i],
      GENATEST_CUSTOM_BUF_1 );
  }
  for (i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i) {
    munit_assert_memory_equal( sizeof(genatest_buf_x),
      &vec_array[GENATEST_BUF_SET_LEN*2+i],
      GENATEST_CUSTOM_BUF_2 );
  }

  gvec_reduce( vec_array, gvec_count(vec_array) - GENATEST_BUF_SET_LEN );
  munit_assert_size( gvec_count(vec_array), ==, GENATEST_BUF_SET_LEN*2 );
  munit_assert( !gvec_empty(vec_array) );
  munit_assert_size( gvec_size(vec_array), >=, GENATEST_BUF_SET_LEN*3 );

  result = gvec_remove( vec_array, GENATEST_BUF_SET_LEN, GENATEST_BUF_SET_LEN );
  munit_assert_true( result );
  munit_assert_size( gvec_count(vec_array), ==, GENATEST_BUF_SET_LEN );
  munit_assert( !gvec_empty(vec_array) );
  munit_assert_size( gvec_size(vec_array), >=, GENATEST_BUF_SET_LEN*3 );

  munit_assert( gvec_array_reserve( &vec_array, GENATEST_BUF_SET_LEN*4 ) );
  munit_assert_size( gvec_size(vec_array), >=, GENATEST_BUF_SET_LEN*4 );
  munit_assert( gvec_array_shrink( &vec_array ) );
  munit_assert_size( gvec_size(vec_array), ==, storage_size );
  munit_assert_memory_equal( GENATEST_BUF_SET_LEN, vec_array,
    GENATEST_BUF_SET );

  gvec_remove( vec_array, 0, GENATEST_BUF_SET_LEN );
  munit_assert_size( gvec_count(vec_array), ==, 0 );
  munit_assert( gvec_empty(vec_array) );

  munit_assert( gvec_array_insert( &vec_array, 0, 1, GENATEST_CUSTOM_BUF_1 ) );
  munit_assert( gvec_array_push( &vec_array, GENATEST_CUSTOM_BUF_2 ) );
  munit_assert_memory_equal( sizeof(genatest_buf_x),
    gvec_array_pop(vec_array), GENATEST_CUSTOM_BUF_2 );
  munit_assert( gvec_drop(vec_array) );
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
{
  /********************************************************************/
  vec_int = gvec_int_new(0);

  munit_assert( gvec_int_reserve( &vec_int, GENATEST_INT_SET_LEN ) );
  memcpy( vec_int, GENATEST_INT_SET, GENATEST_INT_SET_SIZE );
  vec_int = igvec_resize( vec_int, GENATEST_INT_SET_LEN );

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

  munit_assert( gvec_string_reserve( &vec_string1, GENATEST_STR_SET_LEN ) );
  memcpy( vec_string1, GENATEST_STR_SET, GENATEST_STR_SET_SIZE );
  vec_string1 = igvec_resize( vec_string1, GENATEST_STR_SET_LEN );

  vec_string2 = gvec_copy(vec_string1);
  munit_assert_not_null(vec_string2);
  munit_assert_size( gvec_count(vec_string2), ==, GENATEST_STR_SET_LEN );
  munit_assert( !gvec_empty(vec_string2) );
  munit_assert_size( gvec_size(vec_string2), >=, GENATEST_STR_SET_LEN );
  munit_assert_memory_equal( GENATEST_INT_SET_SIZE, vec_string2,
    GENATEST_STR_SET );

  vec_string1 = gvec_assign( vec_string1, vec_string2 );
  munit_assert_not_null(vec_string1);
  munit_assert_size( gvec_count(vec_string1), ==, GENATEST_STR_SET_LEN );
  munit_assert( !gvec_empty(vec_string1) );
  munit_assert_size( gvec_size(vec_string1), >=, GENATEST_STR_SET_LEN );
  munit_assert_memory_equal( GENATEST_STR_SET_SIZE, vec_string1,
    GENATEST_STR_SET );

  gvec_free(vec_string1);
  gvec_free(vec_string2);

  /********************************************************************/
  vec_array1 = gvec_array_new(0);

  munit_assert( gvec_array_reserve( &vec_array1, GENATEST_BUF_SET_LEN ) );
  memcpy( vec_array1, GENATEST_BUF_SET, GENATEST_BUF_SET_SIZE );
  vec_array1 = igvec_resize( vec_array1, GENATEST_BUF_SET_LEN );

  vec_array2 = gvec_array_new(GENATEST_BUF_SET_LEN);
  vec_array2 = gvec_assign( vec_array2, vec_array1 );
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

/******************************************************************************/

MunitResult gvectests_4_iterate() {
  gvec_int_h vec_int;
  gvec_struct_h vec_struct;
  gvec_string_h vec_string;
  gvec_array_h vec_array;
  gena_iterator_o iter1, iter2, iter3, riter1, riter2, riter3;
  gena_bool result;
  int i, k;
{
  /********************************************************************/
  vec_int = gvec_int_new(0);

  munit_assert( !gvec_begin( vec_int, GENA_FALSE, &iter1 ) );
  munit_assert( !gvec_end( vec_int, GENA_FALSE, &iter2 ) );
  munit_assert( !gvec_begin( vec_int, GENA_TRUE, &riter1 ) );
  munit_assert( !gvec_end( vec_int, GENA_TRUE, &riter2 ) );

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    munit_assert( gvec_int_push( &vec_int, GENATEST_INT_SET[i] ) );

    munit_assert( gvec_begin( vec_int, GENA_FALSE, &iter1 ) );
    munit_assert( gvec_end( vec_int, GENA_FALSE, &iter2 ) );
    munit_assert( gvec_begin( vec_int, GENA_TRUE, &riter1 ) );
    munit_assert( gvec_end( vec_int, GENA_TRUE, &riter2 ) );

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

    munit_assert( gena_iterator_compare( &iter1, 0, &riter2, 0 ) == 0 );
    munit_assert( gena_iterator_compare( &iter1, i, &iter2, -i ) >= 0 );
    munit_assert( gena_iterator_compare( &riter1, i, &riter2, -i ) <= 0 );

    for (k = 0; k < i; ++k) {
      munit_assert_int( gvec_int_value( &iter1, 0 ), ==, GENATEST_INT_SET[k] );
      munit_assert_int( gvec_int_value( &riter2, 0 ), ==, GENATEST_INT_SET[k] );

      munit_assert_int( gvec_int_value( &iter2, k ), ==,
        GENATEST_INT_SET[i] );
      munit_assert_int( gvec_int_value( &riter1, -k ), ==,
        GENATEST_INT_SET[i] );

      munit_assert( gena_iterator_next( &iter1 ) );
      munit_assert( gena_iterator_prior( &iter2 ) );

      munit_assert( gena_iterator_next( &riter1 ) );
      munit_assert( gena_iterator_prior( &riter2 ) );

      munit_assert( gvec_at( vec_int, k, GENA_FALSE, &iter3 ) );
      munit_assert( gvec_at( vec_int, k, GENA_TRUE, &riter3 ) );

      munit_assert_int( gvec_int_value( &iter3, i-k ), ==,
        GENATEST_INT_SET[i] );
      munit_assert_int( gvec_int_value( &riter3, 0 ), ==,
        GENATEST_INT_SET[i-k] );
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

    munit_assert( gena_iterator_compare( &iter2, 0, &riter1, 0 ) == 0 );
    munit_assert( gena_iterator_compare( &iter2, i, &iter1, -i ) >= 0 );
    munit_assert( gena_iterator_compare( &riter2, i, &riter1, -i ) <= 0 );
  }

  gvec_free( vec_int );

  /********************************************************************/
  vec_struct = gvec_struct_new(0);

  munit_assert( !gvec_begin( vec_struct, GENA_FALSE, &iter1 ) );
  munit_assert( !gvec_end( vec_struct, GENA_FALSE, &iter2 ) );
  munit_assert( !gvec_begin( vec_struct, GENA_TRUE, &riter1 ) );
  munit_assert( !gvec_end( vec_struct, GENA_TRUE, &riter2 ) );

  for (i = 0; i < (int)GENATEST_INT_SET_LEN; ++i) {
    result = gvec_struct_push( &vec_struct,
      &GENATEST_C_SVALUE(GENATEST_INT_SET[i]) );
    munit_assert_true( result );

    munit_assert( gvec_begin( vec_struct, GENA_FALSE, &iter1 ) );
    munit_assert( gvec_end( vec_struct, GENA_FALSE, &iter2 ) );
    munit_assert( gvec_begin( vec_struct, GENA_TRUE, &riter1 ) );
    munit_assert( gvec_end( vec_struct, GENA_TRUE, &riter2 ) );

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

    munit_assert( gena_iterator_compare( &iter1, 0, &riter2, 0 ) == 0 );
    munit_assert( gena_iterator_compare( &iter1, i, &iter2, -i ) >= 0 );
    munit_assert( gena_iterator_compare( &riter1, i, &riter2, -i ) <= 0 );

    for (k = 0; k < i; ++k) {
      munit_assert_memory_equal( sizeof(int), gvec_struct_value( &iter1, 0 ),
        &GENATEST_C_SVALUE(GENATEST_INT_SET[k]) );
      munit_assert_memory_equal( sizeof(int), gvec_struct_value( &riter2, 0 ),
        &GENATEST_C_SVALUE(GENATEST_INT_SET[k]) );

      munit_assert_memory_equal( sizeof(int), gvec_struct_value( &iter2, k ),
        &GENATEST_C_SVALUE(GENATEST_INT_SET[i]) );
      munit_assert_memory_equal( sizeof(int), gvec_struct_value( &riter1, -k ),
        &GENATEST_C_SVALUE(GENATEST_INT_SET[i]) );

      munit_assert( gena_iterator_next( &iter1 ) );
      munit_assert( gena_iterator_prior( &iter2 ) );

      munit_assert( gena_iterator_next( &riter1 ) );
      munit_assert( gena_iterator_prior( &riter2 ) );

      munit_assert( gvec_at( vec_struct, k, GENA_FALSE, &iter3 ) );
      munit_assert( gvec_at( vec_struct, k, GENA_TRUE, &riter3 ) );

      munit_assert_memory_equal( sizeof(int), gvec_struct_value( &iter3, i-k ),
        &GENATEST_C_SVALUE(GENATEST_INT_SET[i]) );
      munit_assert_memory_equal( sizeof(int), gvec_struct_value( &riter3, 0 ),
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

    munit_assert( gena_iterator_compare( &iter2, 0, &riter1, 0 ) == 0 );
    munit_assert( gena_iterator_compare( &iter2, i, &iter1, -i ) >= 0 );
    munit_assert( gena_iterator_compare( &riter2, i, &riter1, -i ) <= 0 );
  }

  gvec_free( vec_struct );

  /********************************************************************/
  vec_string = gvec_string_new(0);

  munit_assert( !gvec_begin( vec_string, GENA_FALSE, &iter1 ) );
  munit_assert( !gvec_end( vec_string, GENA_FALSE, &iter2 ) );
  munit_assert( !gvec_begin( vec_string, GENA_TRUE, &riter1 ) );
  munit_assert( !gvec_end( vec_string, GENA_TRUE, &riter2 ) );

  for (i = 0; i < (int)GENATEST_STR_SET_LEN; ++i) {
    result = gvec_string_push( &vec_string, GENATEST_STR_SET[i] );
    munit_assert_true( result );

    munit_assert( gvec_begin( vec_string, GENA_FALSE, &iter1 ) );
    munit_assert( gvec_end( vec_string, GENA_FALSE, &iter2 ) );
    munit_assert( gvec_begin( vec_string, GENA_TRUE, &riter1 ) );
    munit_assert( gvec_end( vec_string, GENA_TRUE, &riter2 ) );

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

    munit_assert( gena_iterator_compare( &iter1, 0, &riter2, 0 ) == 0 );
    munit_assert( gena_iterator_compare( &iter1, i, &iter2, -i ) >= 0 );
    munit_assert( gena_iterator_compare( &riter1, i, &riter2, -i ) <= 0 );

    for (k = 0; k < i; ++k) {
      munit_assert_string_equal( gvec_string_value( &iter1, 0 ),
        GENATEST_STR_SET[k] );
      munit_assert_string_equal( gvec_string_value( &riter2, 0 ),
        GENATEST_STR_SET[k] );

      munit_assert_string_equal( gvec_string_value( &iter2, k ),
        GENATEST_STR_SET[i] );
      munit_assert_string_equal( gvec_string_value( &riter1, -k ),
        GENATEST_STR_SET[i] );

      munit_assert( gena_iterator_next( &iter1 ) );
      munit_assert( gena_iterator_prior( &iter2 ) );

      munit_assert( gena_iterator_next( &riter1 ) );
      munit_assert( gena_iterator_prior( &riter2 ) );

      munit_assert( gvec_at( vec_string, k, GENA_FALSE, &iter3 ) );
      munit_assert( gvec_at( vec_string, k, GENA_TRUE, &riter3 ) );

      munit_assert_string_equal( gvec_string_value( &iter3, i-k ),
        GENATEST_STR_SET[i] );
      munit_assert_string_equal( gvec_string_value( &riter3, 0 ),
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

    munit_assert( gena_iterator_compare( &iter2, 0, &riter1, 0 ) == 0 );
    munit_assert( gena_iterator_compare( &iter2, i, &iter1, -i ) >= 0 );
    munit_assert( gena_iterator_compare( &riter2, i, &riter1, -i ) <= 0 );
  }

  gvec_free( vec_string );

  /********************************************************************/
  vec_array = gvec_array_new(0);

  munit_assert( !gvec_begin( vec_array, GENA_FALSE, &iter1 ) );
  munit_assert( !gvec_end( vec_array, GENA_FALSE, &iter2 ) );
  munit_assert( !gvec_begin( vec_array, GENA_TRUE, &riter1 ) );
  munit_assert( !gvec_end( vec_array, GENA_TRUE, &riter2 ) );

  for (i = 0; i < (int)GENATEST_BUF_SET_LEN; ++i) {
    result = gvec_array_push( &vec_array, GENATEST_BUF_SET[i] );
    munit_assert_true( result );

    munit_assert( gvec_begin( vec_array, GENA_FALSE, &iter1 ) );
    munit_assert( gvec_end( vec_array, GENA_FALSE, &iter2 ) );
    munit_assert( gvec_begin( vec_array, GENA_TRUE, &riter1 ) );
    munit_assert( gvec_end( vec_array, GENA_TRUE, &riter2 ) );

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

    munit_assert( gena_iterator_compare( &iter1, 0, &riter2, 0 ) == 0 );
    munit_assert( gena_iterator_compare( &iter1, i, &iter2, -i ) >= 0 );
    munit_assert( gena_iterator_compare( &riter1, i, &riter2, -i ) <= 0 );

    for (k = 0; k < i; ++k) {
      munit_assert_memory_equal( sizeof(genatest_buf_x),
        gvec_array_value( &iter1, 0 ), GENATEST_BUF_SET[k] );
      munit_assert_memory_equal( sizeof(genatest_buf_x),
        gvec_array_value( &riter2, 0 ), GENATEST_BUF_SET[k] );

      munit_assert_memory_equal( sizeof(genatest_buf_x),
        gvec_array_value( &iter2, k ), GENATEST_BUF_SET[i] );
      munit_assert_memory_equal( sizeof(genatest_buf_x),
        gvec_array_value( &riter1, -k ), GENATEST_BUF_SET[i] );

      munit_assert( gena_iterator_next( &iter1 ) );
      munit_assert( gena_iterator_prior( &iter2 ) );

      munit_assert( gena_iterator_next( &riter1 ) );
      munit_assert( gena_iterator_prior( &riter2 ) );

      munit_assert( gvec_at( vec_array, k, GENA_FALSE, &iter3 ) );
      munit_assert( gvec_at( vec_array, k, GENA_TRUE, &riter3 ) );

      munit_assert_memory_equal( sizeof(genatest_buf_x),
        gvec_array_value( &iter3, i-k ), GENATEST_BUF_SET[i] );
      munit_assert_memory_equal( sizeof(genatest_buf_x),
        gvec_array_value( &riter3, 0 ), GENATEST_BUF_SET[i-k] );
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

    munit_assert( gena_iterator_compare( &iter2, 0, &riter1, 0 ) == 0 );
    munit_assert( gena_iterator_compare( &iter2, i, &iter1, -i ) >= 0 );
    munit_assert( gena_iterator_compare( &riter2, i, &riter1, -i ) <= 0 );
  }

  gvec_free( vec_array );

  /********************************************************************/
  return MUNIT_OK;
}}
