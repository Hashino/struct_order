# struct_order

A C library for agnostically ordering arrays of structs by a member value.

It provides a small `OrderStruct` abstraction plus helper macros so you can sort static or dynamic arrays without writing type-specific glue code each time.

## Features

- Sort arrays of structs by any field
- Works with static arrays and dynamically allocated arrays
- Multiple sorting algorithms:
  - `selectionSort`
  - `quickSort`
  - `quickSortInd`
  - `bucketSort`
  - `radixSort`
- Comparison helpers for:
  - integers
  - strings
  - binary strings
- Prefix helpers for bucket/radix-style sorting

## Installation

Clone the repository and build it with `make`:

```bash
git clone https://github.com/Hashino/struct_order.git
cd struct_order
make
```

## Quick Start

Include the main header and create an `OrderStruct` with `makeORDER` or `makeORDER_DYN`.

```c
#include "include/order.h"

typedef struct {
    char name[50];
    int age;
} Person;

Person people[] = {
    {"Alice", 30},
    {"Bob", 25},
    {"Carol", 35}
};

selectionSort(makeORDER(people, age), ltINT);
```

## Static Arrays

Use `makeORDER(array, field)` for fixed-size arrays:

```c
typedef struct {
    char title[50];
    int priority;
} Task;

Task tasks[] = {
    {"Task A", 3},
    {"Task B", 1},
    {"Task C", 2}
};

quickSort(makeORDER(tasks, priority), ltINT);
```

## Dynamic Arrays

Use `makeORDER_DYN(ptr, field, count)` for heap-allocated arrays:

```c
typedef struct {
    char title[50];
    float rating;
} Movie;

Movie *movies = malloc(sizeof(Movie) * 3);
// populate movies...

quickSort(makeORDER_DYN(movies, rating, 3), gtINT);
```

## Comparison Functions

Available comparison helpers:

- Integers: `ltINT`, `gtINT`, `eqINT`
- Strings: `ltSTR`, `gtSTR`, `eqSTR`
- Binary strings: `ltBIN_STR`, `gtBIN_STR`

## Sorting Algorithms

### `selectionSort(order, cmp)`
Simple O(n²) sorting algorithm. Good for small arrays.

### `quickSort(order, cmp)`
Fast average-case O(n log n) sorting.

### `quickSortInd(order, cmp)`
Indirect quicksort that reorders pointers instead of the underlying data.

### `bucketSort(order, eq, prfx, prefixes, n_prefixes, prefix_size, cmp)`
Groups data into buckets using a prefix function, then sorts each bucket.

### `radixSort(order, type, asc)`
Specialized radix sort for integers and strings.

- `type = 'i'` for integers
- `type = 's'` for strings
- `asc = true` for ascending order
- `asc = false` for descending order

## Helper Macros

- `makeORDER(entries, value)`
- `makeORDER_DYN(entries, value, n_entries)`
- `makePRFX_INT_ASC()`
- `makePRFX_INT_DES()`
- `makePRFX_STR_ASC()`
- `makePRFX_STR_DES()`

## Examples

Sort by a string field:

```c
typedef struct {
    char name[30];
    int grade;
} Student;

Student students[] = {
    {"Charlie", 85},
    {"Alice", 92},
    {"Bob", 78}
};

selectionSort(makeORDER(students, name), ltSTR);
```

Sort by an integer field in descending order:

```c
typedef struct {
    char name[30];
    int score;
} Player;

Player players[] = {
    {"Ana", 12},
    {"Ben", 25},
    {"Cara", 18}
};

quickSort(makeORDER(players, score), gtINT);
```

## Build & Run Tests

```bash
make test
./tests
```

## License

MIT
