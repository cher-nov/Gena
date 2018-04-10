# genvector – Generalized Vector

An implementation of *vector* – dynamic linear array – in pure C89.
This one is competently generalized with macros (*pseudo-templated*), so you can create vector of **any** datatype supported in C – i.e. primitive types, structs and unions. Just preliminarily instantiate it for needed types and you're on.
Interface is based mostly on the design of `std::vector` from C++11.

## Table of contents

* [Features in a nutshell](#features-in-a-nutshell)
* [Example (C99)](#example-c99)
* [Design notes](#design-notes)
* [Usage](#usage)
  - [Static approach](#static-approach)
  - [Modular approach](#modular-approach)
    * [Typesets](#typesets)
* [Functions](#functions)
  - [Functions to manage `gvec_h`, and specialized versions of them](#functions-to-manage-gvec_h-and-specialized-versions-of-them)
  - [Specialized-only functions](#specialized-only-functions)
  - [General-purpose functions](#general-purpose-functions)
* [Library adjustment using optional defines](#library-adjustment-using-optional-defines)
  - [Before header inclusion](#before-header-inclusion)
  - [At compile-time](#at-compile-time)

## Features in a nutshell

1. Access vector elements just like plain C arrays: `vec[k]`.
2. Support of multidimensional vectors (aka vector of vectors of...). Accessing them is Cpp-like too: `vec[i][j]`, `vec[x][y][z]`, and so on.
3. It's possible to copy one vector into another, even if they contain values of different types.
4. It's easy to instantiate necessary vector types once in a separate module, instead of doing this every time you needed a vector.
5. You can choose how to pass values into a vector and how to receive them from it: by value or by reference.
6. No code reduplication: only functions that take or return values of user type are specialized.

## Example (C99)

```c
#include <stdlib.h>
#include <stdio.h>

#include "genvector/genvector.h"

typedef struct {
  char Name[32];
  int Age;
} person_s;

#define C_PERSON(name, age) ( (person_s){ .Name=name, .Age=age } )

GVEC_INSTANTIATE( person_s, society, GENA_USE_VAL, GENA_USE_REF );

int main() {
  gvec_society_h family = gvec_society_new(0);
  if (family == NULL) { return EXIT_FAILURE; }

  gvec_society_push( &family, C_PERSON("Alice", 30) );
  gvec_society_push( &family, C_PERSON("Bob", 32) );
  gvec_society_push( &family, C_PERSON("Kate", 10) );

  printf( "%zu\n", gvec_count( family ) );
  while ( gvec_count( family ) > 0 ) {
    person_s member = *gvec_society_back( family );
    printf( "name %s, age %d\n", member.Name, member.Age );
    gvec_pop( family );
  }

  gvec_free( family );
  return EXIT_SUCCESS;
}
```

## Design notes

1. All indices and positions are zero-based.
2. Functions validate their input arguments using only standard C89 `assert()` from *assert.h*.
3. Non-specialized functions always return a defined result.
4. If an error occurrs, the vector remains valid and unchanged.
5. A vector storage never gets reduced, unless `gvec_shrink()` is called.
6. A *reference* is just a pointer.
7. So-called *"vector of void"* type, `gvec_h`, is just a vector of untyped memory chunks.

## Usage

By default, library provides only the next set of functions:

1. Functions to manage `gvec_h`. They are basic for functions that will be specialized.
2. General-purpose functions (i.e. those that don't take or return values of user type, like as `gvec_erase()` and `gvec_free()`).
3. Instantiation macros.

To create a type *"vector of T"* and specialize management functions for it, you should *instantiate* it using instantiation macros.
These are two and a half approaches in instantiation: *static* and *modular*, supplied with *typesets*.
Let's examine them more closely.

### Static approach

This approach is good when vector is used only in one translation unit (*module*). It is easier and set by default.
Just include library header into module source and instantiate vector for types you need, using `GVEC_INSTANTIATE()`:
```c
GVEC_INSTANTIATE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy );
```
* *tpTypeInfo* – type for which vector should be instantiated
* *tpVecName* – unique vector name that will be placed into names of specialized functions, for example: `gvec_mystruct_new()`
* *tpPassBy* – specifies how values should be passed to specialized functions
* *tpReturnBy* – specifies how values should be returned from specialized functions

Possible values both for *tpPassBy* and *tpReturnBy* are:
* `GENA_USE_VAL` – pass/receive by value
* `GENA_USE_REF` – pass/receive by reference

It is also a good practice to place library header inclusion and vector types instantiation in a separate header.

### Modular approach

The main disadvantage about static approach is that vector type and it's corresponding specialized functions will be instantiated every time you use `GVEC_INSTANTIATE()`. This is bad if same vector type is used in different modules – it will be instantiated for all of them, increasing output code size.
To prevent this problem, a modular approach should be used. Its idea is derived from the recommendation about separate header in the static approach: let's instantiate necessary vector types in a separate wrapper module, and use it instead of library itself every time you need a vector.
For the next code template let's assume that wrapper module is called *gvec_wrapper*.

***gvec_wrapper.h***
```c
#define GVEC_MODULAR_APPROACH
#include "genvector.h"

GVEC_H_DECLARE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy );
```

***gvec_wrapper.c***
```c
#include "gvec_wrapper.h"

GVEC_C_DEFINE( tpTypeInfo, tpVecName, tpPassBy, tpReturnBy );
```

The arguments for `GVEC_H_DECLARE()` and `GVEC_C_DEFINE()` are the same as for `GVEC_INSTANTIATE()`.
Please note that modular approach is disabled by default, so you must define `GVEC_MODULAR_APPROACH` before inclusion of the library header.

#### Typesets

As you might have noticed, arguments for every pair of `GVEC_H_DECLARE()` and `GVEC_C_DEFINE()` are always the same. It's a sort of code duplication that may be considered undesirable.
To prevent this, *typesets* were introduced. Let's consider them using the modified version of the previous code template:

***gvec_wrapper.h***
```c
#define GVEC_MODULAR_APPROACH
#include "genvector.h"

#define ZZ_GVEC_TYPESET_VECNAME \
  (tpTypeInfo, tpVecName, tpPassBy, tpReturnBy)

GENA_APPLY_TYPESET( GVEC_H_DECLARE, ZZ_GVEC_TYPESET_VECNAME );
```

***gvec_wrapper.c***
```c
#include "gvec_wrapper.h"

GENA_APPLY_TYPESET( GVEC_C_DEFINE, ZZ_GVEC_TYPESET_VECNAME );
```

## Functions

**Please note:** `gena_bool` type is fully compatible with `bool` from *stdbool.h* in C99 and later, so it's preferred not to use `gena_bool` if possible.

### Functions to manage `gvec_h`, and specialized versions of them

Notation:
* `NAME`: value of `tpVecName`
* `PASSVAL`: `tpTypeInfo` if `tpPassBy` is `GENA_USE_VAL`, and `tpTypeInfo*` otherwise
* `RETVAL`: `tpTypeInfo` if `tpReturnBy` is `GENA_USE_VAL`, and `tpTypeInfo*` otherwise

```c
gvec_h igvec_new( size_t min_count, size_t entry_size )
gvec_NAME_h gvec_NAME_new( size_t min_count )
```
Create a vector.

* *min_count* – a minimum count of elements that can be stored without storage relocation
* ***entry_size*** – a size of one element

*Return value:* a handle to the new vector, or `NULL` on error

```c
gena_bool gvec_resize( gvec_h* phandle, size_t new_count )
gena_bool gvec_NAME_resize( gvec_NAME_h* phandle, size_t new_count, const PASSVAL value )
```
Resize a vector.
*It's recommended to use `gvec_resize()` for reducing the size, and `gvec_NAME_resize()` for increasing.*

* *phandle* – a reference to the handle to a vector
* *new_count* – a new count of elements in a vector
* *value* – a value to be assigned to new elements

*Return value:* `GENA_TRUE` if operation was performed successfully, `GENA_FALSE` otherwise

```c
gena_bool igvec_insert( gvec_h* phandle, size_t pos, size_t count )
gena_bool gvec_NAME_insert( gvec_NAME_h* phandle, size_t pos, size_t count, const PASSVAL value )
```
Insert elements into a vector.

* *phandle* – a reference to the handle to a vector
* *pos* – a position of the first element to be inserted
* *count* – a count of elements to be inserted
* *value* – a value to be assigned to elements

*Return value:* `GENA_TRUE` if operation was performed successfully, `GENA_FALSE` otherwise

```c
gena_bool igvec_push( gvec_h* phandle )
gena_bool gvec_NAME_push( gvec_NAME_h* phandle, const PASSVAL value )
```
Add an element to the end of a vector.

* *phandle* – a reference to the handle to a vector
* *value* – a value to be assigned to the element

*Return value:* `GENA_TRUE` if operation was performed successfully, `GENA_FALSE` otherwise

```c
void* gvec_at( gvec_h handle, size_t pos )
tpTypeInfo* gvec_NAME_at( gvec_h handle, size_t pos )
```
Get a reference to the element at specified position in a vector, with bounds checking.

* *handle* – a handle to a vector
* *pos* – a position of the element

*Return value:* a reference to the element, or `NULL` if `pos` is not within the range of a vector

### Specialized-only functions

```c
gena_bool gvec_NAME_assign( gvec_NAME_h* phandle, size_t count, const PASSVAL value )
```
Resize a vector to specified count of elements and assign a value to them all.

* *phandle* – a reference to the handle to a vector
* *count* – a new count of elements in a vector
* *value* – a value to be assigned to elements

*Return value:* see `gvec_NAME_resize()`

```c
RETVAL gvec_NAME_front( gvec_NAME_h handle )
```
Get the first element of a vector.

* *handle* – a handle to a vector

*Return value:*
* `tpReturnBy` is `GENA_USE_VAL`: a value of the element (if vector is empty, it's undefined)
* `tpReturnBy` is `GENA_USE_REF`: a reference to the element, or `NULL` if vector is empty

```c
RETVAL gvec_NAME_back( gvec_NAME_h handle )
```
Get the last element of a vector.

* *handle* – a handle to a vector

*Return value:*
* `tpReturnBy` is `GENA_USE_VAL`: a value of the element (if vector is empty, it's undefined)
* `tpReturnBy` is `GENA_USE_REF`: a reference to the element, or `NULL` if vector is empty

### General-purpose functions

```c
gvec_h gvec_set( gvec_h* phandle, gvec_h source )
```
Copy-assign one vector to another. Sizes of the elements in both arrays must coincide. On error, the destination vector remains untouched.

* *phandle* – a reference to the handle to a destination vector (handle can be `NULL`)
* *source* – a handle to a source vector

*Return value:* a handle to the destination vector, or `NULL` on error

```c
gvec_h gvec_copy( gvec_h handle )
```
Duplicate a vector.

* *handle* – a handle to a source vector

*Return value:* a handle to the vector duplicate, or `NULL` on error

```c
void gvec_free( gvec_h handle )
```
Free a vector.

* *handle* – a handle to a vector (if `NULL`, nothing will occur)

```c
gena_bool gvec_reserve( gvec_h* phandle, size_t count )
```
Reserve a space in a vector storage, at least for specified count of elements.

* *phandle* – a reference to the handle to a vector
* *count* – a minimum count of elements that vector should accept without any relocation of its storage

*Return value:* `GENA_TRUE` if operation was performed successfully, `GENA_FALSE` otherwise

```c
gena_bool gvec_shrink( gvec_h* phandle )
```
Free memory that isn't used by a vector now.

* *phandle* – a reference to the handle to a vector

*Return value:* `GENA_TRUE` if operation was performed successfully, `GENA_FALSE` otherwise

```c
void gvec_erase( gvec_h handle, size_t pos, size_t count )
```
Erase elements from a vector.

* *handle* – a handle to a vector
* *pos* – a position of the first element to be erased
* *count* – a count of elements to be erased

```c
void gvec_pop( gvec_h handle )
```
Erase the last element from a vector.

* *handle* – a handle to a vector

```c
void* gvec_front( gvec_h handle )
```
Get a reference to the first element of a vector.

* *handle* – a handle to a vector

*Return value:* a reference to the element, or `NULL` if vector is empty

```c
void* gvec_back( gvec_h handle )
```
Get a reference to the last element of a vector.

* *handle* – a handle to a vector

*Return value:* a reference to the element, or `NULL` if vector is empty

```c
size_t gvec_count( gvec_h handle )
```
Get count of elements in a vector.

* *handle* – a handle to a vector

*Return value:* count of elements

```c
size_t gvec_size( gvec_h handle )
```
Get size of a vector storage.

* *handle* – a handle to a vector

*Return value:* current size of a vector storage

```c
gena_bool gvec_empty( gvec_h handle )
```
Shorthand for `gvec_count( handle ) == 0`.

```c
void gvec_clear( gvec_h handle )
```
Shorthand for `gvec_resize( &handle, 0 )`.

## Library adjustment using optional defines

### Before header inclusion

* `GVEC_MODULAR_APPROACH`
Read ***Usage / Modular approach*** section above.

### At compile-time

* `GVEC_GROWTH_FACTOR` (1.5 by default)
Growth factor of vectors storages.

* `GVEC_CALC_SIZE_MATH`
Use math function for size calculation, instead of loop-based.

* `GVEC_INSERT_NO_REALLOC`
Don't perform storage relocation using `realloc()` on elements insertion.
This prevents excess memory copying when inserting elements not at the end of a vector.

It's also recommended to compile with `NDEBUG` defined, to disable assertion checks.
