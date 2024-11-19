#include "../include/cad.h"
#include <stdio.h>
#include <string.h>

char buf[211];

char *toString(Cadastro cad) {
  sprintf(buf, "nome:%s,\tcpf:%d,\tend:%s", cad.nome, cad.cpf, cad.end);
  return buf;
}

bool eqCAD(Cadastro c1, Cadastro c2) {
  return strcmp(c1.nome, c2.nome) == 0 && c1.cpf == c2.cpf &&
         strcmp(c1.end, c2.end) == 0;
}

bool eqCAD_ARR(Cadastro *arr1, Cadastro *arr2, size_t len) {
  for (int i = 0; i < len; i++) {
    if (!eqCAD(arr1[i], arr2[i])) {
      return false;
    }
  }
  return true;
}
