
#include "../include/tests.h"

#include <stdbool.h>
#include <stdio.h>

void printResult(char *test_name, bool result) {
  char *res_color = result ? ANSI_COLOR_GREEN : ANSI_COLOR_RED;
  char *res_symbol = result ? "o" : "x";
  char *res_end = ANSI_COLOR_RESET;

  fprintf(stdout, "[%s%s%s] %s%s%s\n", res_color, res_symbol, res_end,
          res_color, test_name, res_end);
}

void testSelectionSort() {
  Cadastro data[7] = UNORDERED_DATA;
  bool res = false;

  selectionSort(makeORDER(data, nome), ltSTR);
  res = eqCAD_ARR(data, ORDERED_NOME_ASC, 7);
  printResult("selectionSort\tby Name\tAscending", res);

  selectionSort(makeORDER(data, nome), gtSTR);
  res = eqCAD_ARR(data, ORDERED_NOME_DES, 7);
  printResult("selectionSort\tby Name\tDescending", res);

  selectionSort(makeORDER(data, cpf), ltINT);
  res = eqCAD_ARR(data, ORDERED_CPF_ASC, 7);
  printResult("selectionSort\tby CPF\tAscending", res);

  selectionSort(makeORDER(data, cpf), gtINT);
  res = eqCAD_ARR(data, ORDERED_CPF_DES, 7);
  printResult("selectionSort\tby CPF\tDescending", res);
}

void testBucketSort() {
  Cadastro data[7] = UNORDERED_DATA;
  bool res = false;

  bucketSort(makeORDER(data, nome), makePREFIXES_STR_ASC(), ltSTR);
  res = eqCAD_ARR(data, ORDERED_NOME_ASC, 7);
  printResult("bucketSort\t\tby Name\tAscending", res);

  bucketSort(makeORDER(data, nome), makePREFIXES_STR_ASC(), gtSTR);
  res = eqCAD_ARR(data, ORDERED_NOME_DES, 7);
  printResult("bucketSort\t\tby Name\tDescending", res);

  bucketSort(makeORDER(data, cpf), makePREFIXES_INT_ASC(), ltINT);
  res = eqCAD_ARR(data, ORDERED_CPF_ASC, 7);
  printResult("bucketSort\t\tby CPF\tAscending", res);

  bucketSort(makeORDER(data, cpf), makePREFIXES_INT_ASC(), gtINT);
  res = eqCAD_ARR(data, ORDERED_CPF_DES, 7);
  printResult("bucketSort\t\tby CPF\tDescending", res);
}

void testQuickSort() {
  Cadastro data[7] = UNORDERED_DATA;
  bool res = false;

  quickSort(makeORDER(data, nome), ltSTR);
  res = eqCAD_ARR(data, ORDERED_NOME_ASC, 7);
  printResult("quickSort\t\tby Name\tAscending", res);

  quickSort(makeORDER(data, nome), gtSTR);
  res = eqCAD_ARR(data, ORDERED_NOME_DES, 7);
  printResult("quickSort\t\tby Name\tDescending", res);

  quickSort(makeORDER(data, cpf), ltINT);
  res = eqCAD_ARR(data, ORDERED_CPF_ASC, 7);
  printResult("quickSort\t\tby CPF\tAscending", res);

  quickSort(makeORDER(data, cpf), gtINT);
  res = eqCAD_ARR(data, ORDERED_CPF_DES, 7);
  printResult("quickSort\t\tby CPF\tDescending", res);
}

void testRadixSort() {
  Cadastro data[7] = UNORDERED_DATA;
  bool res = false;

  radixSort(makeORDER(data, nome), 's', true);
  res = eqCAD_ARR(data, ORDERED_NOME_ASC, 7);
  printResult("radixSort\t\tby Name\tAscending", res);

  radixSort(makeORDER(data, nome), 's', false);
  res = eqCAD_ARR(data, ORDERED_NOME_DES, 7);
  printResult("radixSort\t\tby Name\tDescending", res);

  radixSort(makeORDER(data, cpf), 'i', true);
  res = eqCAD_ARR(data, ORDERED_CPF_ASC, 7);
  printResult("radixSort\t\tby CPF\tAscending", res);

  radixSort(makeORDER(data, cpf), 'i', false);
  res = eqCAD_ARR(data, ORDERED_CPF_DES, 7);
  printResult("radixSort\t\tby CPF\tDescending", res);
}

void runTests() {
  fprintf(stdout, "-------------------------------------------\n");
  fprintf(stdout, "               UNIT TESTS                  \n");
  fprintf(stdout, "-------------------------------------------\n");
  testSelectionSort();
  fprintf(stdout, "\n");
  testBucketSort();
  fprintf(stdout, "\n");
  testQuickSort();
  fprintf(stdout, "\n");
  testRadixSort();
  fprintf(stdout, "-------------------------------------------\n");
}
