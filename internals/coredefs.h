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

/* VAL - value, REF - reference (pointer), BUF - buffer (array) */
#define GENA_USE_VAL __IGENA_VAL_
#define GENA_USE_REF __IGENA_REF_
#define GENA_USE_BUF __IGENA_BUF_

/* TODO: improve naming */
/* OP - operation, IOP - inverse operation, AOF - address of, GET - get */
#define __IGENA_VAL_OP
#define __IGENA_VAL_IOP *
#define __IGENA_VAL_AOF &
#define __IGENA_VAL_GET
#define __IGENA_REF_OP *
#define __IGENA_REF_IOP
#define __IGENA_REF_AOF
#define __IGENA_REF_GET
#define __IGENA_BUF_OP
#define __IGENA_BUF_IOP
#define __IGENA_BUF_AOF
#define __IGENA_BUF_GET *

/******************************************************************************/

#define GENA_ASSIGN_NAIVE __IGENA_ASSIGN_NAIVE
#define GENA_ASSIGN_MEMCPY __IGENA_ASSIGN_MEMCPY
#define GENA_ASSIGN_STRCPY __IGENA_ASSIGN_STRCPY

#define __IGENA_ASSIGN_NAIVE( ptr_destination, ptr_source, data_size ) \
  ( *(ptr_destination) = *(ptr_source) )

#define __IGENA_ASSIGN_MEMCPY( ptr_destination, ptr_source, data_size ) \
  ( memcpy( ptr_destination, ptr_source, data_size ) )

#define __IGENA_ASSIGN_STRCPY( ptr_destination, ptr_source, data_size ) \
  ( strcpy( (char*)ptr_destination, (char*)ptr_source ) )

/******************************************************************************/

#define GENA_COMPARE_NAIVE __IGENA_COMPARE_NAIVE
#define GENA_COMPARE_MEMCMP __IGENA_COMPARE_MEMCMP
#define GENA_COMPARE_STRCMP __IGENA_COMPARE_STRCMP

#define __IGENA_COMPARE_NAIVE( ptr_user_data, ptr_entry_data ) \
  ( (*(ptr_user_data) < *(ptr_entry_data)) ? (-1) \
  : (*(ptr_user_data) > *(ptr_entry_data)) ? (1) \
  : (0) )

#define __IGENA_COMPARE_MEMCMP( ptr_user_data, ptr_entry_data ) \
  ( memcmp( ptr_user_data, ptr_entry_data, sizeof(*ptr_user_data) ) )

#define __IGENA_COMPARE_STRCMP( ptr_user_data, ptr_entry_data ) \
  ( strcmp( (char*)ptr_user_data, (char*)ptr_entry_data ) )

/******************************************************************************/

#define GENA_APPLY_TYPESET(macro, typeset) macro typeset

/******************************************************************************/

#define __IGENA_VOIDP_ADD(x, a) ( (void*)( (char*)(x) + (a) ) )
#define __IGENA_VOIDP_SUB(x, a) ( (void*)( (char*)(x) - (a) ) )

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
