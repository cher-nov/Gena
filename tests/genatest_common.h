#ifndef __GENATEST_COMMON_H__
#define __GENATEST_COMMON_H__

#include <string.h>

#include "../internals/coredefs.h"

#define GENATEST_UNUSED(var) (void)var

#define GENATEST_STR_LEN (15+1)
typedef char genatest_str_t[GENATEST_STR_LEN];
#define GENATEST_BUF_LEN (4)
typedef int genatest_buf_t[GENATEST_BUF_LEN];

/* This struct should have alignment bytes to test memcmp() comparison */
typedef struct {
  char for_alignment;
  int key;
} genatest_skey_s, *genatest_skey_p;
#define GENATEST_C_SVALUE(x) ( (genatest_svalue_s){x} )

/* This struct should contain only one int to allow byte-by-byte comparison
with GENATEST_INT_SET */
typedef struct {
  int value;
} genatest_svalue_s, *genatest_svalue_p;
#define GENATEST_C_SKEY(x) ( (genatest_skey_s){x, x} )

static inline void genatest_set_skey_safe( genatest_skey_p key, int x ) {
  memset( key, 0, sizeof(genatest_skey_s) );
  key->key = x;
}

/* NOTE: If you don't use size argument in assignment/comparison methods, a
compiler may claim about it. To avoid it, GENATEST_UNUSED() macro introduced in
tests. But there's also another way: you can write an ellipsis (...) instead of
size argument declaration in the list of arguments. */

static inline int genatest_skey_compare_cb( const genatest_skey_s* a,
  const genatest_skey_s* b, size_t value_size )
{
  return (a->key) - (b->key);
  GENATEST_UNUSED(value_size);
}

/* Yes, genatest_str_assign_cb() / genatest_str_compare_cb() duplicate default
GENA_ASSIGN_STRCPY / GENA_COMPARE_STRCMP methods. They were introduced just to
test invocation of user-defined methods for assignment/comparison. */

/* Both genatest_str_t and char* argument types are provided to show their
interchangeability in case of writing assignment and comparison methods. */

static inline void genatest_str_assign_cb( genatest_str_t dest,
  const char* src, size_t value_size )
{
  __IGENA_ASSIGN_STRCPY( dest, src, value_size );
}

static inline int genatest_str_compare_cb( const genatest_str_t a,
  const char* b, size_t value_size )
{
  return __IGENA_COMPARE_STRCMP( a, b, value_size );
  GENATEST_UNUSED(value_size);
}

extern const int GENATEST_INT_SET[];
extern const size_t GENATEST_INT_SET_LEN;
#define GENATEST_INT_SET_SIZE ( GENATEST_INT_SET_LEN * sizeof(int) )

extern const int GENATEST_CUSTOM_INT_1;
extern const int GENATEST_CUSTOM_INT_2;

extern const genatest_str_t GENATEST_STR_SET[];
extern const size_t GENATEST_STR_SET_LEN;
#define GENATEST_STR_SET_SIZE ( GENATEST_STR_SET_LEN * sizeof(genatest_str_t) )

extern const genatest_str_t GENATEST_CUSTOM_STR_1;
extern const genatest_str_t GENATEST_CUSTOM_STR_2;

extern const genatest_buf_t GENATEST_BUF_SET[];
extern const size_t GENATEST_BUF_SET_LEN;
#define GENATEST_BUF_SET_SIZE ( GENATEST_BUF_SET_LEN * sizeof(genatest_buf_t) )

extern const genatest_buf_t GENATEST_CUSTOM_BUF_1;
extern const genatest_buf_t GENATEST_CUSTOM_BUF_2;

#endif /*__GENATEST_COMMON_H__*/
