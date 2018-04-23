#ifndef ZZ_GVEC_GENERAL_H_IG
#define ZZ_GVEC_GENERAL_H_IG

#include "../../genvector/genvector.h"

#include "../genatest_common.h"

#define ZZ_GVECTEST_TYPESET_INT_VAL \
  ( int, int, \
    GENA_USE_VALUE, GENA_USE_VALUE )

#define ZZ_GVECTEST_TYPESET_STRUCT_PTR \
  ( genatest_svalue_s, struct, \
    GENA_USE_POINTER, GENA_USE_POINTER )

#define ZZ_GVECTEST_TYPESET_EX_STRING_BUF \
  ( (char, GENATEST_STR_LEN), string, \
    GENA_USE_BUFFER, GENA_USE_BUFFER, \
    genatest_str_assign_cb )

#define ZZ_GVECTEST_TYPESET_EX_ARRAY_BUF \
  ( (int, GENATEST_BUF_LEN), array, \
    GENA_USE_BUFFER, GENA_USE_BUFFER, \
    GENA_ASSIGN_MEMCPY )

#endif /* ZZ_GVEC_GENERAL_H_IG */
