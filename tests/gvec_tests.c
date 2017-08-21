#include "gvec_tests.h"

MunitResult gvectests_1_general() {
  gvec_intv_t v_val;
  gvec_intr_t v_ref;
  size_t i;
  int* rpint;
  gena_error_e errorcode;
{
  v_val = gvec_intv_new( GENATEST_INT_SET_LEN );
  munit_assert_not_null( v_val );
  v_ref = gvec_intr_new( GENATEST_INT_SET_LEN );
  munit_assert_not_null( v_ref );

  errorcode = gvec_intv_assign( &v_val, GENATEST_INT_SET_LEN, GENATEST_CUSTOM_INT_1 );
  munit_assert_true( errorcode == GENA_ERR_NO );
  gvec_set( &v_ref, v_val );

  munit_assert_size( gvec_count(v_val), ==, gvec_count(v_ref) );
  munit_assert_size( gvec_size(v_val), ==, gvec_size(v_ref) );
  munit_assert_size( IGVEC_GET_HEADER(v_val)->entry_size, ==, IGVEC_GET_HEADER(v_ref)->entry_size );

  munit_assert_memory_equal( GENATEST_INT_SET_SIZE, v_val, v_ref );

  for(i = 0; i < GENATEST_INT_SET_LEN; ++i) {
    gvec_pop( v_ref );
    munit_assert_size( gvec_count(v_ref), ==, GENATEST_INT_SET_LEN-i-1 );
  }

  errorcode = gvec_shrink(&v_ref);
  munit_assert_true( errorcode == GENA_ERR_NO );
  munit_assert_size( gvec_size(v_ref), ==, 1 );
  errorcode = gvec_reserve( &v_ref, GENATEST_INT_SET_LEN-gvec_size(v_ref) );
  munit_assert_true( errorcode == GENA_ERR_NO );

  for(i = 0; i < GENATEST_INT_SET_LEN; ++i) {
    errorcode = gvec_intr_push( &v_ref, &GENATEST_CUSTOM_INT_2 );
    munit_assert_true( errorcode == GENA_ERR_NO );
    munit_assert_size( gvec_count(v_ref), ==, i+1 );
  }

  gvec_erase( v_val, 0, GENATEST_INT_SET_LEN );
  munit_assert_size( gvec_count(v_val), ==, 0 );
  errorcode = gvec_shrink(&v_val);
  munit_assert_size( gvec_size(v_val), ==, 1 );
  munit_assert_true( errorcode == GENA_ERR_NO );
  errorcode = gvec_intv_resize( &v_val, GENATEST_INT_SET_LEN, GENATEST_CUSTOM_INT_2 );
  munit_assert_true( errorcode == GENA_ERR_NO );
  munit_assert_size( gvec_count(v_val), ==, GENATEST_INT_SET_LEN );
  munit_assert_memory_equal( GENATEST_INT_SET_SIZE, v_val, v_ref );

  gvec_free( v_val );
  v_val = gvec_copy(v_ref);

  for(i = 0; i < GENATEST_INT_SET_LEN; ++i) {
    rpint = gvec_at(v_ref, i);
    munit_assert_not_null(rpint);
    munit_assert_int( v_val[i], ==, *rpint );
  }

  rpint = gvec_intr_front(v_ref);
  munit_assert_not_null(rpint);
  munit_assert_int( gvec_intv_front(v_val), ==, *rpint );
  rpint = gvec_intr_back(v_ref);
  munit_assert_not_null(rpint);
  munit_assert_int( gvec_intv_back(v_val), ==, *rpint );

  gvec_clear(v_val);
  munit_assert_size( gvec_count(v_val), ==, 0 );

  gvec_free(v_val);
  gvec_free(v_ref);
  return MUNIT_OK;
}}
