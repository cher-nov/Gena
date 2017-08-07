/*
  Copyright (c) 2017, Dmitry D. Chernov
*/

#ifndef __GENA_COREDEFS_H__
#define __GENA_COREDEFS_H__

/******************************************************************************/

#include <stddef.h>

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
  #define inline
#endif

/******************************************************************************/

typedef enum {
  GENA_ERR_NO,
  GENA_ERR_MEMORY
} gena_error_e;

/******************************************************************************/

#define GENA_USE_VAL __IGENA_VAL_
#define GENA_USE_REF __IGENA_REF_

/* OP - operation, IOP - inverse operation */
#define __IGENA_VAL_OP
#define __IGENA_REF_OP *
#define __IGENA_VAL_IOP *
#define __IGENA_REF_IOP

/******************************************************************************/

#define GENA_APPLY_TYPESET(macro, typeset) macro typeset

/******************************************************************************/

#define __IGENA_VOIDP_ADD(x, a) ((void*)((char*)x + a))
#define __IGENA_VOIDP_SUB(x, a) ((void*)((char*)x - a))

/******************************************************************************/

#define _impl_IGENA_MACRO_CONCAT(x, y) x##y
#define __IGENA_MACRO_CONCAT(x, y) _impl_IGENA_MACRO_CONCAT(x, y)

/******************************************************************************/

#define __IGENA_BLOCK_REQUIRE_SEMICOLON(block) \
  do {block} while(0)

#define __IGENA_REQUIRE_SEMICOLON_OUTDOOR \
  extern void \
  __IGENA_MACRO_CONCAT(__THIS_REQUIRES_A_SEMICOLON_, __LINE__) \
  (void)

#endif /*__GENA_COREDEFS_H__*/
