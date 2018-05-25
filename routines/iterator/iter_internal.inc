/*
  Copyright (c) 2018, Dmitry D. Chernov
*/

#include "../internal/common.h"

typedef void* (*zgena_iterator_manage_f)
  ( void* handle, void* data, ptrdiff_t offset );

typedef void* (*zgena_iterator_access_f)
  ( void* handle, void* data );

typedef int (*zgena_iterator_compare_f)
  ( void* data1, void* data2 );

typedef struct zz_igena_iterator_object_s {
  zgena_iterator_manage_f func_data;
  zgena_iterator_access_f func_key;
  zgena_iterator_access_f func_value;
  zgena_iterator_compare_f func_compare;
  void* data;
} igena_iterator_object_s;

/******************************************************************************/

extern void* igena_iterator_entry( gena_iterator_p object, ptrdiff_t offset,
  void** OUT_key );
