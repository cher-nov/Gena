#ifndef ZZ_GTMAP_TESTS_H_IG
#define ZZ_GTMAP_TESTS_H_IG

#ifdef GTMAP_MODULAR_APPROACH
  #define GTMAPTEST_TYPE "MODULAR"
  #include "gtmap_common/gtmap_modular.h"
#else
  #define GTMAPTEST_TYPE "STATIC"
  #include "gtmap_common/gtmap_static.h"
#endif

#ifndef GENATEST_CHECK_ONLY_C89

#include "munit/munit.h"

extern MunitResult gtmaptests_1_create();
extern MunitResult gtmaptests_2_modify();
extern MunitResult gtmaptests_3_lookup();

#endif /* GENATEST_CHECK_ONLY_C89 */

#endif /* ZZ_GTMAP_TESTS_H_IG */
