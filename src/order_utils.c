
#include "../include/order.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool eqANY(void *bin1, void *bin2, int byte_size) {
  return memcmp(bin1, bin2, byte_size) == 0;
}

/// binary functions
bool ltBIN_STR(void *bin1, void *bin2) { return strcmp(bin1, bin2) < 0; }
bool gtBIN_STR(void *bin1, void *bin2) { return strcmp(bin1, bin2) > 0; }

/* @return true if int1 > int2 (as integers) */
bool gtINT(void *int1, void *int2) { return *(int *)int1 > *(int *)int2; }
/* @return true if int1 < int2 (as integers) */
bool ltINT(void *int1, void *int2) { return *(int *)int1 < *(int *)int2; }
/* @return true if int1 == int2 (as integers) */
bool eqINT(void *int1, void *int2) { return *(int *)int1 == *(int *)int2; }

/* @return true if str1 == str2 (as char*) */
bool eqSTR(void *str1, void *str2) { return strcmp(str1, str2) == 0; }

/* @return true if str1 > str2 (as char* with internal lexographical order) */
bool gtSTR(void *str1, void *str2) {
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

bool ltSTR(void *str1, void *str2) {
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

/// nth functions
void *nthKEY(OrderStruct order, int n) {
  return order.data + (n * order.data_entry_size) + order.key_mem_offset;
}
void *nthENTRY(OrderStruct order, int n) {
  return order.data + (n * order.data_entry_size);
}

void *getMax(OrderStruct order, cmpFn cmp) {
  void *max = nthKEY(order, 0);
  for (int i = 1; i < order.data_len; i++) {
    void *curr = nthKEY(order, i);
    if (cmp(curr, max))
      max = curr;
  }
  return max;
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

void prefixSTR(void *bucket, void *res) {
  sprintf(res, "%c", ((char *)bucket)[0]);
}

void prefixINT(void *bucket, void *res) {
  char number_str[8];
  int number_int = *(int *)bucket;

  sprintf(number_str, "%d", number_int);
  number_str[1] = '\0';

  number_int = atoi(number_str);
  memcpy(res, &number_int, sizeof(int));
}

