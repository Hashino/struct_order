#include "../include/order.h"

#include <stdlib.h>
#include <string.h>

bool eqInt(void *int1, void *int2) { return *(int *)int1 == *(int *)int2; }
bool gtInt(void *int1, void *int2) { return *(int *)int1 > *(int *)int2; }
bool ltInt(void *int1, void *int2) { return *(int *)int1 < *(int *)int2; }

bool eqStr(void *str1, void *str2) {
  return strcmp((char *)str1, (char *)str2);
}

bool gtStr(void *str1, void *str2) {
  char *_str1 = (char *)str1;
  char *_str2 = (char *)str2;

  int common_size =
      (strlen(_str1) > strlen(_str2)) ? strlen(_str2) : strlen(_str1);

  for (int c = 0; c < common_size; c++) {
    if (_str1[c] > _str2[c]) {
      return true;
    } else if (_str1[c] < _str2[c]) {
      return false;
    }
  }

  return strlen(_str1) > strlen(_str2);
}

bool ltStr(void *str1, void *str2) {
  char *_str1 = (char *)str1;
  char *_str2 = (char *)str2;

  int common_size =
      (strlen(_str1) > strlen(_str2)) ? strlen(_str2) : strlen(_str1);

  for (int c = 0; c < common_size; c++) {
    if (_str1[c] < _str2[c]) {
      return true;
    } else if (_str1[c] > _str2[c]) {
      return false;
    }
  }

  return strlen(_str1) < strlen(_str2);
}

void *nthKEY(OrderStruct order, int n) {
  return order.data + (n * order.data_entry_size) + order.key_mem_offset;
}

void *nthENTRY(OrderStruct order, int n) {
  return order.data + (n * order.data_entry_size);
}

void swap(OrderStruct order, int dest, int source) {
  void *tmp = malloc(order.data_entry_size);

  void *s = nthENTRY(order, source);
  void *d = nthENTRY(order, dest);

  memcpy(tmp, d, order.data_entry_size);
  memcpy(d, s, order.data_entry_size);
  memcpy(s, tmp, order.data_entry_size);

  free(tmp);
}

void selectionSort(OrderStruct order, bool (*cmp)(void *, void *)) {
  for (int i = 0; i < order.data_len - 1; i++) {
    int min_idx = i;

    for (int j = i + 1; j < order.data_len; j++) {
      void *curr = nthKEY(order, j);
      void *min = nthKEY(order, min_idx);

      if (cmp(curr, min)) {
        min_idx = j;
      }
    }

    if (i != min_idx)
      swap(order, i, min_idx);
  }
}

void radixSort(OrderStruct order, bool (*cmp)(void *, void *)) {
  // TODO:
};
void bucketSort(OrderStruct order, bool (*cmp)(void *, void *)) {
  // TODO:
};
void quickSortInd(OrderStruct order, bool (*cmp)(void *, void *)) {
  // TODO:
};

void exampleStatic() {
  struct Data {
    char value[100];
    int key;
  };

  struct Data entries[6] = {
      {"Iam", 6},     {"Gabriel", 1}, {"Samuel", 5},
      {"Gileade", 2}, {"Inaue", 4},   {"Marcos", 3},
  };

  selectionSort(makeORDER(entries, value), ltStr);
}

void exampleDynamic() {
  typedef struct Data {
    char value[100];
    int key;
  } Data;

  int entry_size = 6;
  struct Data *entries = malloc(sizeof(Data) * entry_size);

  entries[0] = (Data){"Iam", 6};
  entries[1] = (Data){"Gabriel", 1};
  entries[2] = (Data){"Samuel", 5};
  entries[3] = (Data){"Gileade", 2};
  entries[4] = (Data){"Inaue", 4};
  entries[5] = (Data){"Marcos", 3};

  selectionSort(makeORDER_DYNAMIC(entries, value, 6), gtStr);
}
