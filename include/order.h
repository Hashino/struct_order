/// agnostic struct ordering by member value
///
/// example for static size array:
///   struct Data {
///     char value[100];
///     int key;
///   };
///   struct Data entries[10] = {
///     // ... populates entries
///   }
///   // orders entries by values, ascending with selectionSort
///   selectionSort(makeORDER(entries, value), ltStr);
///
/// example for dynamic size array:
///   typedef struct Data {
///     char value[100];
///     int key;
///   } Data;
///
///   struct Data *entries = malloc(sizeof(Data) * 6);
///
///   // ... populates entries
///
///   // orders entries by values, descending with radixsort
///   radixSort(makeORDER_DYNAMIC(entries, value, 6), gtStr);
///
/// made by Iam Ravara - 2024

#ifndef ORDERSTRUCT
#define ORDERSTRUCT

#include <stdbool.h>
#include <stddef.h>

typedef struct Order {
  // memory offset of value to sort array by
  // use stddef/offsetf to get
  unsigned long key_mem_offset;
  // size of value to sort array by
  int key_size;

  // array with data to be sorted
  void *data;
  // size in bytes of each entry in array
  int data_entry_size;
  // number of entries in array
  int data_len;
} OrderStruct;

// creates ordering structure with just a static array and the name of the value
// to sort by
#define makeORDER(entries, value)                                              \
  (OrderStruct) {                                                              \
    .key_mem_offset = offsetof(typeof(entries[0]), value),                     \
    .key_size = sizeof(entries[0]), .data = entries,                           \
    .data_entry_size = sizeof(entries[0]),                                     \
    .data_len = sizeof(entries) / sizeof(entries[0]),                          \
  }

// creates ordering structure with just a dynamic array, the name of the value
// to sort by and the number of elements in the array
#define makeORDER_DYNAMIC(entries, value, entry_size)                          \
  (OrderStruct) {                                                              \
    .key_mem_offset = offsetof(typeof(entries[0]), value),                     \
    .key_size = sizeof(entries[0]), .data = entries,                           \
    .data_entry_size = sizeof(entries[0]),                                     \
    .data_len = sizeof(entries[0]) * entry_size / sizeof(entries[0]),          \
  }

bool eqInt(void *int1, void *int2);
bool gtInt(void *int1, void *int2);
bool ltInt(void *int1, void *int2);
bool eqStr(void *int1, void *int2);
bool gtStr(void *int1, void *int2);
bool ltStr(void *int1, void *int2);

void selectionSort(OrderStruct order, bool (*cmp)(void *, void *));

void radixSort(OrderStruct order, bool (*cmp)(void *, void *));
void bucketSort(OrderStruct order, bool (*cmp)(void *, void *));
void quickSortInd(OrderStruct order, bool (*cmp)(void *, void *));

#endif
