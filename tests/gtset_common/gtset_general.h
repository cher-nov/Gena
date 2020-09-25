#ifndef ZZ_GTSET_GENERAL_H_IG
#define ZZ_GTSET_GENERAL_H_IG

#include "../../gentreeset/gentreeset.h"

#include "../genatest_common.h"

#define ZZ_GTSETTEST_TYPESET_NAIVE_INT_VAL \
  ( int, naive, \
    GENA_USE_SAMPLE, \
    GENA_COMPARE_NAIVE )

#define ZZ_GTSETTEST_TYPESET_MEMCMP_STRUCT_REF \
  ( genatest_skey_s, memcmp, \
    GENA_USE_ENTITY, \
    GENA_COMPARE_MEMORY )

#define ZZ_GTSETTEST_TYPESET_CALLBACK_STRUCT_REF \
  ( genatest_skey_s, callback, \
    GENA_USE_ENTITY, \
    genatest_skey_compare_cb )

#define ZZ_GTSETTEST_TYPESET_EX_STRING_PTR \
  ( (char, GENATEST_STR_LEN), string, \
    GENA_USE_BUFFER, GENA_USE_BUFFER, \
    genatest_str_compare_cb, genatest_str_assign_cb )

#define ZZ_GTSETTEST_TYPESET_EX_ARRAY_ARR \
  ( (genatest_buf_x, int), array, \
    GENA_USE_ARRAY, GENA_USE_ARRAY, \
    GENA_COMPARE_MEMORY, GENA_ASSIGN_MEMORY )

#endif /* ZZ_GTSET_GENERAL_H_IG */
