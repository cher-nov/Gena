/* Please note that the test framework is written in C99, when GENA
is C89 by design, so these tests don't check standard compliance.
To check it, compile with GENATEST_CHECK_ONLY_C89 defined. */

#ifndef GENATEST_CHECK_ONLY_C89
  #include "munit/munit.h"
#else
  #include <stdlib.h>
  #include <stdio.h>
#endif

#include "gvec_tests.h"
#include "gtmap_tests.h"
#include "gtset_tests.h"

/******************************************************************************/
#ifdef GENATEST_CHECK_ONLY_C89

int main() {
{
  puts( "genvector: " GVECTEST_TYPE );
  puts( "gentreemap: " GTMAPTEST_TYPE );
  puts( "gentreeset: " GTSETTEST_TYPE );
  puts( "GENA successfully compiled and seems to be C89 compliant." );
  return EXIT_SUCCESS;
}}

/******************************************************************************/
#else /* GENATEST_CHECK_ONLY_C89 */

#include "genatest_common.h"

static MunitTest tests[] = {
  { "gvec_1_create", gvectests_1_create,
    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "gvec_2_modify", gvectests_2_modify,
    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "gvec_3_manage", gvectests_3_manage,
    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "gvec_4_iterate", gvectests_4_iterate,
    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

  { "gtmap_1_create", gtmaptests_1_create,
    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "gtmap_2_modify", gtmaptests_2_modify,
    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "gtmap_3_lookup", gtmaptests_3_lookup,
    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "gtmap_4_iterate", gtmaptests_4_iterate,
    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

  { "gtset_1_create", gtsettests_1_create,
    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "gtset_2_modify", gtsettests_2_modify,
    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "gtset_3_lookup", gtsettests_3_lookup,
    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "gtset_4_iterate", gtsettests_4_iterate,
    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  NULL, tests, NULL, 1, MUNIT_SUITE_OPTION_NONE,
};

int main( int argc, char* const argv[] ) {
{
  munit_logf( MUNIT_LOG_INFO,
      "\ngenvector: " GVECTEST_TYPE
      "\ngentreemap: " GTMAPTEST_TYPE
      "\ngentreeset: " GTSETTEST_TYPE
      "\nTest set length: %" MUNIT_SIZE_MODIFIER "u\n",
    GENATEST_INT_SET_LEN );
  return munit_suite_main( &suite, NULL, argc, argv );
}}

/******************************************************************************/
#endif /* GENATEST_CHECK_ONLY_C89 */
