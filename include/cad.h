#ifndef CADASTRO
#define CADASTRO

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/**
 * @brief Example data structure used by tests and examples.
 */
typedef struct Cadastro {
  char nome[10];
  uint32_t cpf;
  char end[10];
} Cadastro;

/** @brief Formats a Cadastro instance as a static string buffer. */
char *toString(Cadastro cad);

/** @brief Returns true when all Cadastro fields are equal. */
bool eqCAD(Cadastro c1, Cadastro c2);
/** @brief Returns true when both Cadastro arrays have equal elements in order. */
bool eqCAD_ARR(Cadastro *arr1, Cadastro *arr2, size_t len);

/** @brief Runs the sample Cadastro demonstration. */
void exemploCadastro();
#endif
