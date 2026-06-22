# struct_order

A small C library for sorting arrays of structs by one chosen field.

## Build and run

```bash
make
make run
```

Optional:

```bash
make valgrind
make clean
```

## Quick Start

```c
#include <stdlib.h> // malloc/free for dynamic-array example below
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

selectionSort(makeORDER(people, age), ltINT); // static array

Person *heap_people = malloc(sizeof(Person) * 3);
heap_people[0] = (Person){"Alice", 30};
heap_people[1] = (Person){"Bob", 25};
heap_people[2] = (Person){"Carol", 35};
quickSort(makeORDER_DYN(heap_people, age, 3), gtINT); // dynamic array
free(heap_people);
```

## API (implemented in `src/`)

- `selectionSort(order, cmp)`
- `quickSort(order, cmp)`
- `bucketSort(order, eq, prfx, b_prefixes, n_prefixes, prefix_size, cmp)`
- `radixSort(order, type, asc)` where:
  - `type = 'i'` for integer keys
  - `type = 's'` for string keys
  - `asc = true` ascending, `false` descending

`quickSortInd` is declared in `include/order.h` but not implemented in `src/` yet.

## Comparison helpers

Implemented helpers:

- Int: `ltINT`, `gtINT`, `eqINT`
- String: `ltSTR`, `gtSTR`, `eqSTR`
- "Binary string" helpers (`ltBIN_STR`, `gtBIN_STR`) are historical API names used by
  `radixSort(..., 's', ...);` both of these helpers currently delegate to `strcmp`.

The long helpers (`ltLNG`, `gtLNG`, `eqLNG`) are declared in `include/order.h` but are not implemented in `src/` yet.
If you need long-key sorting (sorting by `long` fields) today, pass your own `cmpFn` implementation.
There is no `eqBIN_STR` helper in the current implementation.

## Helper macros in `include/order.h`

- `makeORDER(entries, value)`
- `makeORDER_DYN(entries, value, n_entries)`
- `makePRFX_INT_ASC()`
- `makePRFX_INT_DES()`
- `makePRFX_LNG_ASC()`
- `makePRFX_LNG_DES()`
- `makePRFX_STR_ASC()`
- `makePRFX_STR_DES()`

## Bucket sort usage

Use the exact signature:

```c
bucketSort(order, eq, prfx, b_prefixes, n_prefixes, prefix_size, cmp);
```

Example with explicit arguments:

```c
/* using Person people[] from Quick Start */
bucketSort(makeORDER(people, age), eqINT, prefixINT, INT_PRFX_ASC,
           INT_P_N_ENTRIES, INT_P_ENTRY_SIZE, ltINT);
bucketSort(makeORDER(people, name), eqSTR, prefixSTR, STR_PRFX_DES,
           STR_B_N_ENTRIES, STR_B_ENTRY_SIZE, gtSTR);
```

The names above match `include/order.h` exactly:
- `*_PRFX_*`: prefix value tables (`INT_PRFX_ASC`, `STR_PRFX_DES`, ...)
- `INT_P_*`: integer prefix metadata (`INT_P_N_ENTRIES`, `INT_P_ENTRY_SIZE`)
- `STR_B_*`: string bucket metadata (`STR_B_N_ENTRIES`, `STR_B_ENTRY_SIZE`)

Shorthand macros in `include/order.h` expand to those extra arguments:

```c
bucketSort(makeORDER(people, age), makePRFX_INT_ASC());
bucketSort(makeORDER(people, name), makePRFX_STR_DES());
```

## License

MIT
