# genvector – Generalized Vector

An implementation of *vector* – dynamic linear array – in pure C89.  
This one is competently generalized with macros (*pseudo-templated*), so you can create vector of **any** datatype supported in C – i.e. primitive types, structs and unions. Just preliminarily instantiate it for needed types and you're on.  
Interface is based mostly on the design of `std::vector` from C++11.

## Features in a nutshell

1. Access vector elements just like plain C arrays: `vec[k]`.
2. Support of multidimensional vectors (aka vector of vectors of...). Accessing them is Cpp-like too: `vec[i][j]`, `vec[x][y][z]`, and so on.
3. It's possible to copy one vector into another, even if they contain values of different types.
4. It's easy to instantiate necessary vector types once in a separate module, instead of doing this every time you needed a vector.
5. You can choose how to pass values into a vector and how to receive them from it: by value or by reference.
6. No code reduplication: only functions that take or return values of user type are specialized.

## Design notes

1. All indices and positions are zero-based.
2. Functions validate their input arguments using only standard C89 `assert()` from *assert.h*.
3. Non-specialized functions always return a defined result.
4. If an error occurrs, the vector remains valid and unchanged.
5. A vector storage never gets reduced, unless `gvec_shrink()` is called.
6. A *reference* is just a pointer.
7. So-called *"vector of void"* type, `gvec_t`, is just a vector of untyped memory chunks.

## Usage

By default, library provides only the next set of functions:

1. Functions to manage `gvec_t`. They are basic for functions that will be specialized.
2. General-purpose functions (i.e. those that don't take or return values of user type, like as `gvec_erase()` and `gvec_free()`).
3. Shorthand macros, for example `gvec_count()` or `GVEC_NO_ERROR()`.
4. Instantiation macros.

To create a type *"vector of T"* and specialize management functions for it, you should *instantiate* it using instantiation macros.
These are two and a half approaches in instantiation: *static* and *modular*, supplied with *typesets*.
Let's examine them more closely.

### Static approach

This approach is good when vector is used only in one translation unit (*module*). It is easier and set by default.  
Just include library header into module source and instantiate vector for types you need, using `GVEC_INSTANTIATE()`:
```c
GVEC_INSTANTIATE( gvTypename, gvVecName, gvPassBy, gvRetBy );
```
* *gvTypename* – type for which vector should be instantiated
* *gvVecName* – unique vector name that will be placed into names of specialized functions, for example: `gvec_mystruct_new()`
* *gvPassBy* – specifies how values should be passed to specialized functions
* *gvRetBy* – specifies how values should be returned from specialized functions

Possible values both for *gvPassBy* and *gvRetBy* are:
* `GVEC_USE_VAL` – pass by value
* `GVEC_USE_REF` – pass by reference

It is also a good practice to place library header inclusion and vector types instantiation in a separate header.

### Modular approach

The main disadvantage about static approach is that vector type and it's corresponding specialized functions will be instantiated every time you use `GVEC_INSTANTIATE()`. This is bad if same vector type is used in different modules – it will be instantiated for all of them, increasing output code size.  
To prevent this problem, a modular approach should be used. Its idea is derived from the recommendation about separate header in the static approach: let's instantiate necessary vector types in a separate wrapper module, and use it instead of library itself every time you need a vector.  
For the next code template let's assume that wrapper module is called *gvec_wrapper*.

***gvec_wrapper.h***
```c
#define GVEC_MODULAR_APPROACH
#include "genvector.h"

GVEC_H_DECLARE( gvTypename, gvVecName, gvPassBy, gvRetBy );
```

***gvec_wrapper.c***
```c
#include "gvec_wrapper.h"

GVEC_C_DEFINE( gvTypename, gvVecName, gvPassBy, gvRetBy );
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

#define __GVEC_TYPESET_VECNAME \
  (gvTypename, gvVecName, gvPassBy, gvRetBy)

GVEC_APPLY_TYPESET( GVEC_H_DECLARE, __GVEC_TYPESET_VECNAME );
```
  
***gvec_wrapper.c***
```c
#include "gvec_wrapper.h"

GVEC_APPLY_TYPESET( GVEC_C_DEFINE, __GVEC_TYPESET_VECNAME );
```

## Functions

### 1. Functions to manage `gvec_t`, and specialized versions of them

Notation:
* `NAME`: value of `gvVecName`
* `PASSVAR`: `gvTypename` if `gvPassBy` is `GVEC_USE_VAL`, and `gvTypename*` otherwise
* `RETVAR`: `gvTypename` if `gvRetBy` is `GVEC_USE_VAL`, and `gvTypename*` otherwise

```c
gvec_t gvec_new( size_t min_count, size_t unitsz )
gvec_NAME_t gvec_NAME_new( size_t min_count )
```
Create a vector.

* *min_count* – a minimum count of elements that can be stored without storage relocation
* ***unitsz*** – a size of one element

*Return value:* a handle to the new vector, or `NULL` on error  
*Error codes:* none

```c
gvec_t gvec_resize( gvec_t hgvec, size_t new_count )
gvec_NAME_t gvec_NAME_resize( gvec_NAME_t hgvec, size_t new_count, const PASSVAR value )
```
Resize a vector.

* *hgvec* – a handle to a vector
* *count* – a new count of elements in a vector
* *value* – a value to be assigned to new elements

*Return value:* a new handle to a vector  
*Error codes:*
* `GVEC_ERR_IDLE`: `count` is equal to the current count of elements
* `GVEC_ERR_MEMORY`: a vector wasn't resized due to a memory error

```c
gvec_t gvec_insert( gvec_t hgvec, size_t pos, size_t count )
gvec_NAME_t gvec_NAME_insert( gvec_NAME_t hgvec, size_t pos, size_t count, const PASSVAR value )
```
Insert elements into a vector.

* *hgvec* – a handle to a vector
* *pos* – a position of the first element to be inserted
* *count* – a count of elements to be inserted
* *value* – a value to be assigned to elements

*Return value:* a new handle to a vector  
*Error codes:*
* `GVEC_ERR_IDLE`: `count` is 0
* `GVEC_ERR_MEMORY`: elements weren't inserted due to a memory error

```c
gvec_t gvec_push( gvec_t hgvec )
gvec_NAME_t gvec_NAME_push( gvec_NAME_t hgvec, const PASSVAR value )
```
Add an element to the end of a vector.

* *hgvec* – a handle to a vector
* *value* – a value to be assigned to the element

*Return value:* a new handle to a vector  
*Error codes:*
* `GVEC_ERR_MEMORY`: element wasn't added due to a memory error

#### Specialized-only functions

```c
gvec_NAME_t gvec_NAME_assign( gvec_NAME_t hgvec, size_t count, const PASSVAR value )
```
Resize a vector to specified count of elements and assign a value to them all.

* *hgvec* – a handle to a vector
* *count* – a new count of elements in a vector
* *value* – a value to be assigned to elements

*Return value:* a new handle to a vector  
*Error codes:* see `gvec_resize()`

```c
RETVAL gvec_NAME_front( gvec_NAME_t hgvec )
```
Get the first element of a vector.

* *hgvec* – a handle to a vector

*Return value:*
* `gvRetVal` is `GVEC_USE_VAL`: a value of the element (if vector is empty, it's undefined)
* `gvRetVal` is `GVEC_USE_REF`: a reference to the element, or `NULL` if vector is empty

*Error codes:* none.

```c
RETVAL gvec_NAME_back( gvec_NAME_t hgvec )
```
Get the last element of a vector.

* *hgvec* – a handle to a vector

*Return value:*
* `gvRetVal` is `GVEC_USE_VAL`: a value of the element (if vector is empty, it's undefined)
* `gvRetVal` is `GVEC_USE_REF`: a reference to the element, or `NULL` if vector is empty

*Error codes:* none.

### 2. General-purpose functions

```c
gvec_t gvec_set( gvec_t hgvec_dest, gvec_t hgvec_src )
```
Copy-assign a one vector to another.

* *hgvec_dest* – a handle to a destination vector
* *hgvec_src* – a handle to a source vector (if `NULL`, a destination vector will be freed and `NULL` will be returned)

*Return value:* a new handle to a destination vector  
*Error codes:* none

```c
gvec_t gvec_copy( gvec_t hgvec )
```
Duplicate a vector.

* *hgvec* – a handle to a source vector

*Return value:* a handle to the vector duplicate, or `NULL` on error  
*Error codes:* none

```c
void gvec_free( gvec_t hgvec )
```
Free a vector.

* *hgvec* – a handle to a vector (if `NULL`, nothing will occur)

*Return value:* none  
*Error codes:* none

```c
gvec_t gvec_reserve( gvec_t hgvec, size_t count )
```
Reserve a space in a vector storage, at least for specified count of elements.

* *hgvec* – a handle to a vector
* *count* – a minimum count of elements that vector should accept without any relocation of its storage

*Return value:* a new handle to a vector  
*Error codes:*
* `GVEC_ERR_IDLE`: `count` is 0
* `GVEC_ERR_MEMORY`: chunks weren't reserved due to a memory error

```c
gvec_t gvec_shrink( gvec_t hgvec )
```
Free memory that isn't used by a vector now.

* *hgvec* – a handle to a vector

*Return value:* a new handle to a vector  
*Error codes:*
* `GVEC_ERR_IDLE`: a size of a vector storage is already the minimum possible
* `GVEC_ERR_MEMORY`: a size wasn't reduced due to a memory error

```c
void gvec_erase( gvec_t hgvec, size_t pos, size_t count )
```
Erase elements from a vector.

* *hgvec* – a handle to a vector
* *pos* – a position of the first element to be erased
* *count* – a count of elements to be erased

*Return value:* none  
*Error codes:*
* `GVEC_ERR_IDLE`: `count` is 0

```c
void gvec_pop( gvec_t hgvec )
```
Erase the last element from a vector.

* *hgvec* – a handle to a vector

*Return value:* none  
*Error codes:* none

```c
void* gvec_at( gvec_t hgvec, size_t pos )
```
Get a reference to the element at specified position in a vector, with bounds checking.

* *hgvec* – a handle to a vector
* *pos* – a position of the element

*Return value:* a reference to the element, or `NULL` if `pos` is not within the range of a vector  
*Error codes:*
* `GVEC_ERR_IDLE`: `pos` is not within the range of a vector

```c
void* gvec_front( gvec_t hgvec )
```
Get a reference to the first element of a vector.

* *hgvec* – a handle to a vector

*Return value:* a reference to the element, or `NULL` if vector is empty  
*Error codes:* none.

```c
void* gvec_back( gvec_t hgvec )
```
Get a reference to the last element of a vector.

* *hgvec* – a handle to a vector

*Return value:* a reference to the element, or `NULL` if vector is empty  
*Error codes:* none.

### 3. Shorthand macros

```c
gvec_count( hgvec )
```
Returns `size_t`: count of elements in a vector.

* *hgvec* – a handle to a vector

```c
gvec_size( hgvec )
```
Returns `size_t`: size of a vector storage.

* *hgvec* – a handle to a vector

```c
gvec_error( hgvec )
```
Returns `gvec_error_e`: current error code of a vector.

* *hgvec* – a handle to a vector

```c
gvec_empty( hgvec )
```
Shorthand for `gvec_count( hgvec ) == 0`.

```c
gvec_clear( hgvec )
```
Shorthand for `gvec_resize( hgvec, 0 )`.

```c
GVEC_HDR( hgvec )
```
*Not recommended.*  
Returns `gvhead_p`: pointer to the header structure of a vector.

* *hgvec* – a handle to a vector

```c
GVEC_ERROR_SAFE( error )
```
Returns `true` if error is either `GVEC_ERR_NO` or `GVEC_ERR_IDLE`, and `false` otherwise.

* *error* – an error code.

```c
GVEC_NO_ERROR( hgvec )
```
Shorthand for `GVEC_ERROR_SAFE( gvec_error( hgvec ) )`.

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

## License

This library is free software; you can redistribute it and/or modify it under the terms of the MIT license.  
See [LICENSE](LICENSE) for details.
