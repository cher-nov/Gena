/*
  Copyright (c) 2018, Dmitry D. Chernov
*/

#ifndef ZZ_GENA_GLOBAL_H_IG
#define ZZ_GENA_GLOBAL_H_IG

#include "internal/common.h"

/******************************************************************************/

/* Instantiation modes. */

#define GENA_USE_SAMPLE ZZ_GENA_VAL__  /* plain type, by value */
#define GENA_USE_ENTITY ZZ_GENA_REF__  /* plain type, by reference */
#define GENA_USE_BUFFER ZZ_GENA_PTR__  /* buffer type (string or array) */
#define GENA_USE_ARRAY ZZ_GENA_ARR__   /* index-access type (array) */

/******************************************************************************/

/* Default assignment approaches. */

#define GENA_ASSIGN_NAIVE ZZ_GENA_ASSIGN_NAIVE
#define GENA_ASSIGN_MEMORY ZZ_GENA_ASSIGN_MEMORY
#define GENA_ASSIGN_STRING ZZ_GENA_ASSIGN_STRING

/******************************************************************************/

/* Default comparison approaches. */

#define GENA_COMPARE_NAIVE ZZ_GENA_COMPARE_NAIVE
#define GENA_COMPARE_MEMORY ZZ_GENA_COMPARE_MEMORY
#define GENA_COMPARE_STRING ZZ_GENA_COMPARE_STRING

/******************************************************************************/

/* User-available macros. */

#define GENA_APPLY_TYPESET( macro, typeset ) \
  macro typeset

/******************************************************************************/

#endif /* ZZ_GENA_GLOBAL_H_IG */
