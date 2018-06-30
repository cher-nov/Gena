#ifndef ZZ_GENATEST_COMMON_H_IG
#define ZZ_GENATEST_COMMON_H_IG

#include <string.h>

#include "../routines/global.h"

#define GENATEST_STR_LEN (15+1)
typedef char genatest_str_x[GENATEST_STR_LEN];
#define GENATEST_BUF_LEN (4)
typedef int genatest_buf_x[GENATEST_BUF_LEN];

/* This struct should have alignment bytes to test memcmp() comparison. */
typedef struct {
  char for_alignment;
  int key;
} genatest_skey_s, *genatest_skey_p;
#define GENATEST_C_SVALUE(x) ( (genatest_svalue_s){x} )

/* This struct should contain only one int to allow byte-by-byte comparison
with GENATEST_INT_SET. */
typedef struct {
  int value;
} genatest_svalue_s, *genatest_svalue_p;
#define GENATEST_C_SKEY(x) ( (genatest_skey_s){x, x} )

static GENA_INLINE void genatest_set_skey_safe( genatest_skey_p key, int x ) {
  memset( key, 0, sizeof(genatest_skey_s) );
  key->key = x;
}

/* NOTE: If you do not use the size argument in the assignment/comparison
methods, your compiler may complain about it. To avoid this, the library
provides a special macro GENA_VARIABLE_UNUSED(). But there's also another way:
you can write an ellipsis (...) instead of size argument declaration in the
list of arguments. */

static GENA_INLINE int genatest_skey_compare_cb( const genatest_skey_s* a,
  const genatest_skey_s* b, size_t value_size )
{
  return (a->key) - (b->key);
  GENA_VARIABLE_UNUSED(value_size);
}

/* Yes, genatest_str_assign_cb() / genatest_str_compare_cb() duplicate default
GENA_ASSIGN_STRCPY / GENA_COMPARE_STRCMP methods. They were introduced just to
test invocation of user-defined methods for assignment/comparison. */

/* Both genatest_str_x and char* argument types are provided to show their
interchangeability in case of writing assignment and comparison methods. */

static GENA_INLINE void genatest_str_assign_cb( genatest_str_x dest,
  const char* src, size_t value_size )
{
  GENA_ASSIGN_STRCPY( dest, src, value_size );
}

static GENA_INLINE int genatest_str_compare_cb( const genatest_str_x a,
  const char* b, size_t value_size )
{
  return GENA_COMPARE_STRCMP( a, b, value_size );
  GENA_VARIABLE_UNUSED(value_size);
}

extern const int GENATEST_INT_SET[];
extern const size_t GENATEST_INT_SET_LEN;
#define GENATEST_INT_SET_SIZE ( GENATEST_INT_SET_LEN * sizeof(int) )

extern const int GENATEST_CUSTOM_INT_1;
extern const int GENATEST_CUSTOM_INT_2;

extern const genatest_str_x GENATEST_STR_SET[];
extern const size_t GENATEST_STR_SET_LEN;
#define GENATEST_STR_SET_SIZE ( GENATEST_STR_SET_LEN * sizeof(genatest_str_x) )

extern const genatest_str_x GENATEST_CUSTOM_STR_1;
extern const genatest_str_x GENATEST_CUSTOM_STR_2;

extern const genatest_buf_x GENATEST_BUF_SET[];
extern const size_t GENATEST_BUF_SET_LEN;
#define GENATEST_BUF_SET_SIZE ( GENATEST_BUF_SET_LEN * sizeof(genatest_buf_x) )

extern const genatest_buf_x GENATEST_CUSTOM_BUF_1;
extern const genatest_buf_x GENATEST_CUSTOM_BUF_2;

#endif /* ZZ_GENATEST_COMMON_H_IG */
