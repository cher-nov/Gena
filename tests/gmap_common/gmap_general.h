#ifndef __GMAP_GENERAL_H__
#define __GMAP_GENERAL_H__

#include "../../genmap/genmap.h"

#include "../genatest_common.h"

#define __GMAPTEST_TYPESET_NAIVE_INT_VAL \
  (int, int, \
   naive, GENA_COMPARE_NAIVE, \
   GENA_USE_VAL, GENA_USE_VAL)

#define __GMAPTEST_TYPESET_MEMCMP_STRUCT_REF \
  (genatest_skey_s, genatest_svalue_s, \
   memcmp, GENA_COMPARE_MEMCMP, \
   GENA_USE_REF, GENA_USE_REF)

#define __GMAPTEST_TYPESET_CALLBACK_STRUCT_REF \
  (genatest_skey_s, genatest_svalue_s, \
   callback, genatest_skey_compare_cb, \
   GENA_USE_REF, GENA_USE_REF)

#define __GMAPTEST_TYPESET_EX_STRING_BUF \
  (genatest_str_t, genatest_str_t, string, \
   genatest_str_assign_cb, genatest_str_assign_cb, genatest_str_compare_cb, \
   GENA_USE_BUF, GENA_USE_BUF)

#define __GMAPTEST_TYPESET_EX_ARRAY_BUF \
  (genatest_buf_t, genatest_buf_t, array, \
   GENA_ASSIGN_MEMCPY, GENA_ASSIGN_MEMCPY, GENA_COMPARE_MEMCMP, \
   GENA_USE_BUF, GENA_USE_BUF)

#endif /*__GMAP_GENERAL_H__*/
