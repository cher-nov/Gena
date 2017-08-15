#ifndef __GENATEST_COMMON_H__
#define __GENATEST_COMMON_H__

#include <stddef.h>

#define GENATEST_UNUSED(var) (void)var

typedef char genatest_str_t[15+1];
typedef int genatest_buf_t[4];

extern const int GENATEST_INT_SET[];
extern const size_t GENATEST_INT_SET_LEN;
#define GENATEST_INT_SET_SIZE ( GENATEST_INT_SET_LEN * sizeof(int) )

extern const int GENATEST_CUSTOM_INT_1;
extern const int GENATEST_CUSTOM_INT_2;

extern const genatest_str_t GENATEST_STR_SET[];
extern const size_t GENATEST_STR_SET_LEN;
#define GENATEST_STR_SET_SIZE ( GENATEST_STR_SET_LEN * sizeof(genatest_str_t) )

extern const genatest_buf_t GENATEST_BUF_SET[];
extern const size_t GENATEST_BUF_SET_LEN;
#define GENATEST_BUF_SET_SIZE ( GENATEST_BUF_SET_LEN * sizeof(genatest_buf_t) )

#endif /*__GENATEST_COMMON_H__*/
