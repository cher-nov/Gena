#ifndef __GVEC_TESTS_H__
#define __GVEC_TESTS_H__

#ifdef GVEC_MODULAR_APPROACH
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

#endif /* GENATEST_CHECK_ONLY_C89 */

#endif /*__GVEC_TESTS_H__*/
