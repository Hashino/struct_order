#ifndef CADASTRO
#define CADASTRO

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct Cadastro {
  char nome[10];
  uint32_t cpf;
  char end[10];
} Cadastro;

char *toString(Cadastro cad);

bool eqCAD(Cadastro c1, Cadastro c2);
bool eqCAD_ARR(Cadastro *arr1, Cadastro *arr2, size_t len);

void exemploCadastro();
#endif
