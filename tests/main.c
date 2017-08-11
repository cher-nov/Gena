/* Please note that test framework is written in C99, when GENA
is C89 by design, so these tests don't check standard compliance.
To check it, compile with GENATEST_CHECK_ONLY_C89 defined. */

#ifndef GENATEST_CHECK_ONLY_C89
  #include "munit/munit.h"
#else
  #include <stdlib.h>
  #include <stdio.h>
#endif

#include "gvec_tests.h"

/******************************************************************************/
#ifdef GENATEST_CHECK_ONLY_C89

int main() {
{
  puts( "genvector: " GVECTEST_TYPE );
  puts( "GENA successfully compiled and seems to be C89 compliant." );
  return EXIT_SUCCESS;
}}

/******************************************************************************/
#else /* GENATEST_CHECK_ONLY_C89 */

#include "genatest_common.h"

MunitTest tests[] = {
  { "/gvt1_general", gvt1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
  "/gvectest", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

int main( int argc, char* const argv[] ) {
{
  munit_log( MUNIT_LOG_INFO, "\n"GVECTEST_TYPE"\n" );
  munit_logf( MUNIT_LOG_INFO, "\nTest set length: %" MUNIT_SIZE_MODIFIER "u\n",
    GENATEST_INT_SET_LEN );
  return munit_suite_main( &suite, NULL, argc, argv );
}}

/******************************************************************************/
#endif /* GENATEST_CHECK_ONLY_C89 */
