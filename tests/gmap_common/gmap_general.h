#ifndef __GMAP_GENERAL_H__
#define __GMAP_GENERAL_H__

#include "../../genmap/genmap.h"

#include "../genatest_common.h"

/* This struct should have alignment bytes for testing memcmp() comparison */
typedef struct {
  char for_alignment;
  int key;
} gmaptest_key_s, *gmaptest_key_p;

typedef struct {
  int value;
} gmaptest_value_s, *gmaptest_value_p;

/* NOTE: If you don't use size argument in assignment/comparison methods, a
compiler may claim about it. To avoid it, GENATEST_UNUSED() macro introduced in
tests. But there's also another way: you can write an ellipsis (...) instead of
size argument declaration in the list of arguments. */

static inline int gmaptest_skey_compare_cb( const gmaptest_key_s* a,
  const gmaptest_key_s* b, size_t value_size )
{
  return (a->key) - (b->key);
  GENATEST_UNUSED(value_size);
}

/* Yes, gmaptest_str_assign_cb() / gmaptest_str_compare_cb() duplicate default
GENA_ASSIGN_STRCPY / GENA_COMPARE_STRCMP methods. They were introduced just to
test invocation of user-defined methods for assignment/comparison. */

static inline void gmaptest_str_assign_cb( genatest_str_t dest,
  const genatest_str_t src, size_t value_size )
{
  __IGENA_ASSIGN_STRCPY( dest, src, value_size );
}

static inline int gmaptest_str_compare_cb( const genatest_str_t a,
  const genatest_str_t b, size_t value_size )
{
  return __IGENA_COMPARE_STRCMP( a, b, value_size );
  GENATEST_UNUSED(value_size);
}

#define __GMAPTEST_TYPESET_NAIVE_INT_VAL \
  (int, int, \
   naive, GENA_COMPARE_NAIVE, \
   GENA_USE_VAL, GENA_USE_VAL)

#define __GMAPTEST_TYPESET_MEMCMP_STRUCT_REF \
  (gmaptest_key_s, gmaptest_value_s, \
   memcmp, GENA_COMPARE_MEMCMP, \
   GENA_USE_REF, GENA_USE_REF)

#define __GMAPTEST_TYPESET_CALLBACK_STRUCT_REF \
  (gmaptest_key_s, gmaptest_value_s, \
   callback, gmaptest_skey_compare_cb, \
   GENA_USE_REF, GENA_USE_REF)

#define __GMAPTEST_TYPESET_EX_STRING_BUF \
  (genatest_str_t, genatest_str_t, string, \
   gmaptest_str_assign_cb, gmaptest_str_assign_cb, gmaptest_str_compare_cb, \
   GENA_USE_BUF, GENA_USE_BUF)

#endif /*__GMAP_GENERAL_H__*/
