#ifndef ZZ_GTMAP_GENERAL_H_IG
#define ZZ_GTMAP_GENERAL_H_IG

#include "../../gentreemap/gentreemap.h"

#include "../genatest_common.h"

#define ZZ_GTMAPTEST_TYPESET_NAIVE_INT_VAL \
  ( int, int, \
    naive, \
    GENA_USE_VALUE, GENA_USE_VALUE, \
    GENA_COMPARE_NAIVE )

#define ZZ_GTMAPTEST_TYPESET_MEMCMP_STRUCT_PTR \
  ( genatest_skey_s, genatest_svalue_s, \
    memcmp, \
    GENA_USE_POINTER, GENA_USE_POINTER, \
    GENA_COMPARE_MEMORY )

#define ZZ_GTMAPTEST_TYPESET_CALLBACK_STRUCT_PTR \
  ( genatest_skey_s, genatest_svalue_s, \
    callback, \
    GENA_USE_POINTER, GENA_USE_POINTER, \
    genatest_skey_compare_cb )

#define ZZ_GTMAPTEST_TYPESET_EX_STRING_BUF \
  ( (char, GENATEST_STR_LEN), (char, GENATEST_STR_LEN), \
    string, \
    GENA_USE_BUFFER, GENA_USE_BUFFER, \
    GENA_USE_BUFFER, GENA_USE_BUFFER, \
    genatest_str_compare_cb, \
    genatest_str_assign_cb, genatest_str_assign_cb )

#define ZZ_GTMAPTEST_TYPESET_EX_ARRAY_REF \
  ( (genatest_buf_x, int), (genatest_buf_x, int), \
    array, \
    GENA_USE_ARRAY, GENA_USE_ARRAY, \
    GENA_USE_ARRAY, GENA_USE_ARRAY, \
    GENA_COMPARE_MEMORY, \
    GENA_ASSIGN_MEMORY, GENA_ASSIGN_MEMORY )

#endif /* ZZ_GTMAP_GENERAL_H_IG */
