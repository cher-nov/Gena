#ifndef __GENATEST_COMMON_H__
#define __GENATEST_COMMON_H__

#include <stddef.h>

#define GENATEST_UNUSED(var) (void)var

extern const int GENATEST_INT_SET[];
extern const size_t GENATEST_INT_SET_LEN;
#define GENATEST_INT_SET_SIZE ( GENATEST_INT_SET_LEN * sizeof(int) )

extern const int GENATEST_CUSTOM_INT_1;
extern const int GENATEST_CUSTOM_INT_2;

#endif /*__GENATEST_COMMON_H__*/
