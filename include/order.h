/*!
  @file: order.h
  @author: Iam Ravara

  agnostic struct ordering by member value

  example for static size array:
    struct Data {
      char value[100];
      int key;
    };
    struct Data entries[10] = {
      // ... populates entries
    }
    // orders entries by values, ascending with selectionSort
    selectionSort(makeORDER(entries, value), ltStr);

  example for dynamic size array:
    typedef struct Data {
      char value[100];
      int key;
    } Data;

    struct Data *entries = malloc(sizeof(Data) * 6);

    // ... populates entries

    // orders entries by values, descending with radixsort
    radixSort(makeORDER_DYNAMIC(entries, value, 6), gtStr);

  specialized sorting algorithms need more arguments. macros are provided for
  ease of use. examples on how to use these macros are given in order.c in
  code region 'examples'
 */
#ifndef ORDERSTRUCT
#define ORDERSTRUCT

#include <stdbool.h>
#include <stddef.h>

/**
 * @typedef OrderStruct
 * @brief holds needed data needed to agnostically order data.
 * should be built with makeORDER macro for ease of use
 */
typedef struct Order {
  unsigned long key_mem_offset; // memory offset of value to sort array by use
                                // stddef/offsetf to get/!< Brief description
                                // after the member

  int key_size; // size of value to sort array by

  void *data;          // array with data to be sorted
  int data_entry_size; // size in bytes of each entry in array
  int data_len;        // number of entries in array
} OrderStruct;

// creates ordering structure with just a static array and the name of the value
// to sort by
#define makeORDER(entries, value)                                              \
  (OrderStruct) {                                                              \
    .key_mem_offset = offsetof(typeof(entries[0]), value),                     \
    .key_size = sizeof(typeof(entries[0].value)), .data = entries,             \
    .data_entry_size = sizeof(typeof(entries[0])),                             \
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

#define INT_PREFIXES_ASC (void *)(int[10]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
#define INT_PREFIXES_DES (void *)(int[10]){9, 8, 7, 6, 5, 4, 3, 2, 1, 0}
#define INT_P_N_ENTRIES 10
#define INT_P_ENTRY_SIZE sizeof(int)

#define makePREFIXES_INT_ASC()                                                 \
  eqINT, prefixINT, INT_PREFIXES_ASC, INT_P_N_ENTRIES, INT_P_ENTRY_SIZE
#define makePREFIXES_INT_DES()                                                 \
  eqINT, prefixINT, INT_PREFIXES_DES, INT_P_N_ENTRIES, INT_P_ENTRY_SIZE

#define STR_PREFIXES_ASC                                                       \
  " !\"#$%&'()*+,-./"                                                          \
  "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"                         \
  "abcdefghijklmnopqrstuvwxyz{|}~"
#define STR_PREFIXES_DES                                                       \
  "~}|{zyxwvutsrqponmlkjihgfedcba`_^]\\[ZYXWVUTSRQPONMLKJIHGFEDCBA@?>=<;:"     \
  "9876543210/.-,+*)('&%$#\"!"
#define STR_B_N_ENTRIES 128
#define STR_B_ENTRY_SIZE sizeof(char)

#define makePREFIXES_STR_ASC()                                                 \
  eqSTR, prefixSTR, STR_PREFIXES_ASC, STR_B_N_ENTRIES, STR_B_ENTRY_SIZE
#define makePREFIXES_STR_DES()                                                 \
  eqSTR, prefixSTR, STR_PREFIXES_DES, STR_B_N_ENTRIES, STR_B_ENTRY_SIZE

typedef bool (*cmpFn)(void *, void *);
typedef void (*prefixFn)(void *, void *);

/// nth functions
void *nthKEY(OrderStruct order, int n);
void *nthENTRY(OrderStruct order, int n) ;
void swap(OrderStruct order, int dest, int source);

/** @brief returns true if any1 == any2 by memcmp */
bool eqANY(void *any1, void *any2, int byte_size);

/** @brief returns true if int1 == int2 */
bool eqINT(void *int1, void *int2);
/** @brief returns true if int1 > int2 */
bool gtINT(void *int1, void *int2);
/** @brief returns true if int1 < int2 */
bool ltINT(void *int1, void *int2);

/** @brief returns true if str1 == str2 (by strcmp) */
bool eqSTR(void *str1, void *str2);
/** @brief returns true if str1 > str2 (by strlen) */
bool gtSTR(void *str1, void *str2);
/** @brief returns true if str1 < str2 (by strlen) */
bool ltSTR(void *str1, void *str2);

/** @brief uses memcmp to compare string */
bool ltBIN_STR(void *bin1, void *bin2);
/** @brief uses memcmp to compare string */
bool gtBIN_STR(void *bin1, void *bin2);

/** @brief returns the biggest (by cmp) key */
void *getMax(OrderStruct order, cmpFn cmp);

/** @brief res = first char of string */
void prefixSTR(void *bucket, void *res);
/** @brief res = first digit of integer */
void prefixINT(void *bucket, void *res);

/**
 * @brief orders by selection sort algorithm by cmp function.
 *  recommended to use makeORDER for building function call:
 * > selectionSort(makeORDER(pairs, value), ltSTR);
 * @param order use macro makeORDER for building
 * @param cmp function to use for ordering data
 */
void selectionSort(OrderStruct order, cmpFn cmp);

/**
 * @brief orders by quick sort algorithm by cmp function.
 *  recommended to use makeORDER for building function call:
 * > quickSort(makeORDER(cad, cpf), ltINT, eqINT);
 * @param order use macro makeORDER for building
 * @param cmp return true if arg1 > arg2
 */
void quickSort(OrderStruct order, cmpFn cmp);

/**
 *  @brief orders by bucket sort algorithm with selection sort for sorting
 *  buckets.
 *  recommended to use makeORDER and makeBUCKET_TYPE for building function call:
 *  > bucketSort(makeORDER(pairs, key), makePREFIXES_INT_ASC(), ltINT);
 *
 *  @param order use macro makeORDER for building
 *  @param eq function to compare data inside order.data (with key offset)
 *  @param prfx function to cut the prefix of the data
 *  @param b_prefixes the prefixes to group data by. should be an array of same
 *  typed data
 *  @param n_prefixes how many prefixes to group data
 *  @param prefix_size memory size in bytes of the prefix data type (use sizeof)
 *  @param cmp function to use for ordering data
 */
void bucketSort(OrderStruct order, cmpFn eq, prefixFn prfx, void *b_prefixes,
                int n_prefixes, int prefix_size, cmpFn cmp);

/**
 * @brief orders by radix sort algorithm. because radix is a specialized
 * algorithm, using it is different from other sorting algorithms in library
 * > radixSort(makeORDER(pairs, key), 'i', true);
 *
 * @param order use macro makeORDER for building
 * @param type 's'|'i' for string (char*) and integer, respectively
 * @param asc if true, orders ascending, if false, descending
 */
void radixSort(OrderStruct order, char type, bool asc);
#endif
