#ifndef ZZ_GMAP_GENERAL_H_IG
#define ZZ_GMAP_GENERAL_H_IG

#include "../../genmap/genmap.h"

#include "../genatest_common.h"

#define ZZ_GMAPTEST_TYPESET_NAIVE_INT_VAL \
  (int, int, \
   naive, GENA_COMPARE_NAIVE, \
   GENA_USE_VAL, GENA_USE_VAL)

#define ZZ_GMAPTEST_TYPESET_MEMCMP_STRUCT_REF \
  (genatest_skey_s, genatest_svalue_s, \
   memcmp, GENA_COMPARE_MEMCMP, \
   GENA_USE_REF, GENA_USE_REF)

#define ZZ_GMAPTEST_TYPESET_CALLBACK_STRUCT_REF \
  (genatest_skey_s, genatest_svalue_s, \
   callback, genatest_skey_compare_cb, \
   GENA_USE_REF, GENA_USE_REF)

#define ZZ_GMAPTEST_TYPESET_EX_STRING_BUF \
  ((char, GENATEST_STR_LEN), (char, GENATEST_STR_LEN), string, \
   genatest_str_assign_cb, genatest_str_assign_cb, genatest_str_compare_cb, \
   GENA_USE_BUF, GENA_USE_BUF)

#define ZZ_GMAPTEST_TYPESET_EX_ARRAY_BUF \
  ((int, GENATEST_BUF_LEN), (int, GENATEST_BUF_LEN), array, \
   GENA_ASSIGN_MEMCPY, GENA_ASSIGN_MEMCPY, GENA_COMPARE_MEMCMP, \
   GENA_USE_BUF, GENA_USE_BUF)

#endif /* ZZ_GMAP_GENERAL_H_IG */
