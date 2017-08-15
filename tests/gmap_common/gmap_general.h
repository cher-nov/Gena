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

static inline int gmaptest_compare_cb( const gmaptest_key_s* a,
  const gmaptest_key_s* b )
{
  return (a->key) - (b->key);
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
   callback, gmaptest_compare_cb, \
   GENA_USE_REF, GENA_USE_REF)

#endif /*__GMAP_GENERAL_H__*/
