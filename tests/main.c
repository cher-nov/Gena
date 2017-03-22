/* Please note that test framework written in C99, when genvector is C89
by design, so these tests don't check standard compliance.
To check it, compile with GVTEST_CHECK_ONLY_C89 defined. */

#ifndef GVTEST_CHECK_ONLY_C89
  #include "munit/munit.h"
#else
  #include <stdlib.h>
  #include <stdio.h>
#endif

#ifdef GVEC_MODULAR_APPROACH
  #define GVTEST_TYPE "MODULAR"
  #include "gvec_modular.h"
#else
  #define GVTEST_TYPE "STATIC"
  #include "gvec_static.h"
#endif

/******************************************************************************/
#ifdef GVTEST_CHECK_ONLY_C89

int main() {
{
  puts(GVTEST_TYPE);
  puts("genvector successfully compiled and seems to be C89 compliant.");
  return EXIT_SUCCESS;
}}

/******************************************************************************/
#else /* GVTEST_CHECK_ONLY_C89 */

#define GVTEST_UNUSED(var) (void)var

/* a shuffled set of 116 integers, from 0 to 115 */
static const int TEST_SET[] = {
  59,88,16,29,108,12,42,63,0,35,4,111,61,113,109,50,15,30,56,107,82,2,58,
  23,80,38,7,13,76,52,100,67,21,18,9,87,66,6,70,11,60,65,72,73,48,79,57,49,
  101,51,32,8,31,40,115,99,74,17,3,53,84,41,94,20,62,85,110,47,54,96,33,25,
  69,78,77,64,98,93,86,89,39,71,103,75,102,91,105,24,10,45,44,27,68,104,5,
  19,46,43,97,36,37,55,106,90,22,92,26,114,14,112,81,34,1,95,28,83
};

static const size_t TEST_SET_LEN = sizeof(TEST_SET) / sizeof(TEST_SET[0]);

static const int CUSTOM_VALUE_1 = 234;
static const int CUSTOM_VALUE_2 = 749;

/******************************************************************************/

MunitResult gvt1( const MunitParameter params[], void* user_data_or_fixture ) {
  gvec_intv_t v_val;
  gvec_intr_t v_ref;
  size_t i;
  int* rpint;
  gvec_error_e errorcode;
  GVTEST_UNUSED(params);
  GVTEST_UNUSED(user_data_or_fixture);
{
  v_val = gvec_intv_new( TEST_SET_LEN );
  munit_assert_not_null( v_val );
  v_ref = gvec_intr_new( TEST_SET_LEN );
  munit_assert_not_null( v_ref );

  errorcode = gvec_intv_assign( &v_val, TEST_SET_LEN, CUSTOM_VALUE_1 );
  munit_assert_true( errorcode == GVEC_ERR_NO );
  gvec_set( &v_ref, v_val );

  munit_assert_size( gvec_count(v_val), ==, gvec_count(v_ref) );
  munit_assert_size( gvec_size(v_val), ==, gvec_size(v_ref) );
  munit_assert_size( GVEC_GET_HEADER(v_val)->unitsz, ==, GVEC_GET_HEADER(v_ref)->unitsz );

  munit_assert_memory_equal( sizeof(TEST_SET), v_val, v_ref );

  for(i = 0; i < TEST_SET_LEN; ++i) {
    gvec_pop( v_ref );
    munit_assert_size( gvec_count(v_ref), ==, TEST_SET_LEN-i-1 );
  }

  errorcode = gvec_shrink(&v_ref);
  munit_assert_true( errorcode == GVEC_ERR_NO );
  munit_assert_size( gvec_size(v_ref), ==, 1 );
  errorcode = gvec_reserve( &v_ref, TEST_SET_LEN-gvec_size(v_ref) );
  munit_assert_true( errorcode == GVEC_ERR_NO );

  for(i = 0; i < TEST_SET_LEN; ++i) {
    errorcode = gvec_intr_push( &v_ref, &CUSTOM_VALUE_2 );
    munit_assert_true( errorcode == GVEC_ERR_NO );
    munit_assert_size( gvec_count(v_ref), ==, i+1 );
  }

  gvec_erase( v_val, 0, TEST_SET_LEN );
  munit_assert_size( gvec_count(v_val), ==, 0 );
  errorcode = gvec_shrink(&v_val);
  munit_assert_size( gvec_size(v_val), ==, 1 );
  munit_assert_true( errorcode == GVEC_ERR_NO );
  errorcode = gvec_intv_resize( &v_val, TEST_SET_LEN, CUSTOM_VALUE_2 );
  munit_assert_true( errorcode == GVEC_ERR_NO );
  munit_assert_size( gvec_count(v_val), ==, TEST_SET_LEN );
  munit_assert_memory_equal( sizeof(TEST_SET), v_val, v_ref );

  gvec_set( &v_val, NULL );
  v_val = gvec_copy(v_ref);

  for(i = 0; i < TEST_SET_LEN; ++i) {
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

  gvec_set( &v_val, NULL );
  gvec_free(v_ref);
  return MUNIT_OK;
}}

/******************************************************************************/

MunitTest tests[] = {
  { "/gvt1_general", gvt1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  "/gvectest", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main( int argc, char* const argv[] ) {
{
  munit_log( MUNIT_LOG_INFO, "\n"GVTEST_TYPE"\n" );
  munit_logf( MUNIT_LOG_INFO, "\nTest set length: %"MUNIT_SIZE_MODIFIER"u\n", TEST_SET_LEN );
  return munit_suite_main( &suite, NULL, argc, argv );
}}

/******************************************************************************/
#endif /* GVTEST_CHECK_ONLY_C89 */
