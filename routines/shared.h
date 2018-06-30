/*
  Copyright (c) 2018, Dmitry D. Chernov
*/

#ifndef ZZ_GENA_SHARED_H_IG
#define ZZ_GENA_SHARED_H_IG

#include <stddef.h>
#include <limits.h>
#include <assert.h>

/******************************************************************************/

#if __STDC_VERSION__ < 199901L
  typedef int gena_bool;
  #define GENA_TRUE (1)
  #define GENA_FALSE (0)
#else
  #include <stdbool.h>
  typedef bool gena_bool;
  #define GENA_TRUE (true)
  #define GENA_FALSE (false)
#endif

#if __STDC_VERSION__ < 199901L
  #define GENA_INLINE
#else
  #define GENA_INLINE inline
#endif

typedef const char* gena_tag_z;

/******************************************************************************/

#define GENA_VARIABLE_UNUSED( variable ) \
  (void)(variable)

/******************************************************************************/

#endif /* ZZ_GENA_SHARED_H_IG */
