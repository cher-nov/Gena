#ifndef ZZ_GVEC_TESTS_H_IG
#define ZZ_GVEC_TESTS_H_IG

#ifdef GENATEST_MODULAR_APPROACH
  #define GVECTEST_TYPE "MODULAR"
  #include "gvec_common/gvec_modular.h"
#else
  #define GVECTEST_TYPE "STATIC"
  #include "gvec_common/gvec_static.h"
#endif

#ifndef GENATEST_CHECK_ONLY_C89

#include "munit/munit.h"

extern MunitResult gvectests_1_create();
extern MunitResult gvectests_2_modify();
extern MunitResult gvectests_3_manage();
extern MunitResult gvectests_4_iterate();

#endif /* GENATEST_CHECK_ONLY_C89 */

#endif /* ZZ_GVEC_TESTS_H_IG */
