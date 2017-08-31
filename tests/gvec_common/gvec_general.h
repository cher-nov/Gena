#ifndef __GVEC_GENERAL_H__
#define __GVEC_GENERAL_H__

#include "../../genvector/genvector.h"

#include "../genatest_common.h"

#define __GVECTEST_TYPESET_INT_VAL \
  (int, int, \
   GENA_USE_VAL, GENA_USE_VAL)

#define __GVECTEST_TYPESET_STRUCT_REF \
  (genatest_svalue_s, struct, \
   GENA_USE_REF, GENA_USE_REF)

#define __GVECTEST_TYPESET_EX_STRING_BUF \
  ((char, GENATEST_STR_LEN), string, \
   genatest_str_assign_cb, \
   GENA_USE_BUF, GENA_USE_BUF)

#define __GVECTEST_TYPESET_EX_ARRAY_BUF \
  ((int, GENATEST_BUF_LEN), array, \
   GENA_ASSIGN_MEMCPY, \
   GENA_USE_BUF, GENA_USE_BUF)

#endif /*__GVEC_GENERAL_H__*/
