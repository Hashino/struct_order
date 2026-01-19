# struct_order

A C library for agnostically ordering arrays of structs by any member value. Supports multiple sorting algorithms including selection sort, quicksort, bucket sort, and radix sort.

## Quick Start

```c
#include "include/order.h"

struct Person {
    char name[50];
    int age;
};

struct Person people[3] = {
    {"Alice", 30},
    {"Bob", 25},
    {"Carol", 35}
};

// Sort by age (ascending)
selectionSort(makeORDER(people, age), ltINT);
```

## Build & Run

```bash
make
./struct_order
```

## Examples

### Sorting by Integer Field

```c
struct Data {
    char name[20];
    int priority;
};

struct Data tasks[4] = {
    {"Task A", 3},
    {"Task B", 1},
    {"Task C", 2},
    {"Task D", 1}
};

// Sort by priority (ascending)
quickSort(makeORDER(tasks, priority), ltINT);
```

### Sorting by String Field

```c
struct Student {
    char name[30];
    int grade;
};

struct Student students[3] = {
    {"Charlie", 85},
    {"Alice", 92},
    {"Bob", 78}
};

// Sort by name (alphabetical)
selectionSort(makeORDER(students, name), ltSTR);
```

### Dynamic Arrays

```c
typedef struct {
    char title[50];
    float rating;
} Movie;

Movie *movies = malloc(sizeof(Movie) * 3);
// ... populate movies ...

// Sort by rating (descending)
quickSort(makeORDER_DYN(movies, rating, 3), gtINT);
```

## Available Algorithms

- `selectionSort()` - Simple O(n²) algorithm, good for small arrays
- `quickSort()` - Fast O(n log n) average case
- `quickSortInd()` - Indirect sorting (reorders pointers, not data)
- `bucketSort()` - Good for uniformly distributed data
- `radixSort()` - Linear time for integers/strings

## Comparison Functions

- **Integers**: `ltINT`, `gtINT`, `eqINT`
- **Strings**: `ltSTR`, `gtSTR`, `eqSTR`
- **Binary strings**: `ltBIN_STR`, `gtBIN_STR`

## Tutorial

### 1. Basic Sorting

The core concept is the `OrderStruct` which describes how to access and compare your data:

```c
// For static arrays - use makeORDER macro
selectionSort(makeORDER(array, field_name), comparison_function);

// For dynamic arrays - specify size
quickSort(makeORDER_DYN(ptr, field_name, count), comparison_function);
```

### 2. Custom Comparison

TODO: Add section on creating custom comparison functions

### 3. Advanced Algorithms

TODO: Add detailed examples for bucket sort and radix sort with different data types

### 4. Performance Considerations

TODO: Add algorithm complexity comparison and when to use each

## License

MIT
