#include <stdio.h>
#include <stdlib.h>

#include "../include/order.h"

int main(int argc, char *argv[]) {
  struct Data {
    char value[100];
    int key;
  };

  struct Data entries[6] = {
      {"Iam", 6},     {"Gabriel", 1}, {"Samuel", 5},
      {"Gileade", 2}, {"Inaue", 4},   {"Marcos", 3},
  };

  fprintf(stdout, "BEFORE SORT\n");
  for (int i = 0; i < 6; i++) {
    fprintf(stdout, "key:%d,\tvalue:%s\n", entries[i].key, entries[i].value);
  }

  selectionSort(makeORDER(entries, key), ltInt);

  fprintf(stdout, "AFTER SORT\n");
  for (int i = 0; i < 6; i++) {
    fprintf(stdout, "key:%d,\tvalue:%s\n", entries[i].key, entries[i].value);
  }

  exit(EXIT_SUCCESS);
}
