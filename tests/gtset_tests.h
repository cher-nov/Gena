#ifndef ZZ_GTSET_TESTS_H_IG
#define ZZ_GTSET_TESTS_H_IG

#ifdef GENATEST_MODULAR_APPROACH
  #define GTSETTEST_TYPE "MODULAR"
  #include "gtset_common/gtset_modular.h"
#else
  #define GTSETTEST_TYPE "STATIC"
  #include "gtset_common/gtset_static.h"
#endif

#ifndef GENATEST_CHECK_ONLY_C89

#include "munit/munit.h"

extern MunitResult gtsettests_1_create();
extern MunitResult gtsettests_2_modify();
extern MunitResult gtsettests_3_lookup();
extern MunitResult gtsettests_4_iterate();

#endif /* GENATEST_CHECK_ONLY_C89 */

#endif /* ZZ_GTSET_TESTS_H_IG */
