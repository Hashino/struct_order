#ifndef TESTSLIB
#define TESTSLIB

#include "../include/cad.h"
#include "../include/order.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define UNORDERED_DATA                                                         \
  {                                                                            \
      {.nome = "Iam", .cpf = 666, .end = "Ravara"},                            \
      {.nome = "Gabriel", .cpf = 567, .end = "Coelho"},                        \
      {.nome = "Samuel", .cpf = 294, .end = "Brum"},                           \
      {.nome = "Gileade", .cpf = 361, .end = "Valente"},                       \
      {.nome = "Inaue", .cpf = 879, .end = "NaoSei"},                          \
      {.nome = "Marcos", .cpf = 193, .end = "NaoLembro"},                      \
      {.nome = "Fernando", .cpf = 772, .end = "NaoLembro"},                    \
  }

#define ORDERED_NOME_ASC                                                       \
  (Cadastro[7]) {                                                              \
    {.nome = "Fernando", .cpf = 772, .end = "NaoLembro"},                      \
        {.nome = "Gabriel", .cpf = 567, .end = "Coelho"},                      \
        {.nome = "Gileade", .cpf = 361, .end = "Valente"},                     \
        {.nome = "Iam", .cpf = 666, .end = "Ravara"},                          \
        {.nome = "Inaue", .cpf = 879, .end = "NaoSei"},                        \
        {.nome = "Marcos", .cpf = 193, .end = "NaoLembro"},                    \
        {.nome = "Samuel", .cpf = 294, .end = "Brum"},                         \
  }

#define ORDERED_NOME_DES                                                       \
  (Cadastro[7]) {                                                              \
    {.nome = "Samuel", .cpf = 294, .end = "Brum"},                             \
        {.nome = "Marcos", .cpf = 193, .end = "NaoLembro"},                    \
        {.nome = "Inaue", .cpf = 879, .end = "NaoSei"},                        \
        {.nome = "Iam", .cpf = 666, .end = "Ravara"},                          \
        {.nome = "Gileade", .cpf = 361, .end = "Valente"},                     \
        {.nome = "Gabriel", .cpf = 567, .end = "Coelho"},                      \
        {.nome = "Fernando", .cpf = 772, .end = "NaoLembro"},                  \
  }

#define ORDERED_CPF_ASC                                                        \
  (Cadastro[7]) {                                                              \
    {.nome = "Marcos", .cpf = 193, .end = "NaoLembro"},                        \
        {.nome = "Samuel", .cpf = 294, .end = "Brum"},                         \
        {.nome = "Gileade", .cpf = 361, .end = "Valente"},                     \
        {.nome = "Gabriel", .cpf = 567, .end = "Coelho"},                      \
        {.nome = "Iam", .cpf = 666, .end = "Ravara"},                          \
        {.nome = "Fernando", .cpf = 772, .end = "NaoLembro"},                  \
        {.nome = "Inaue", .cpf = 879, .end = "NaoSei"},                        \
  }

#define ORDERED_CPF_DES                                                        \
  (Cadastro[7]) {                                                              \
    {.nome = "Inaue", .cpf = 879, .end = "NaoSei"},                            \
        {.nome = "Fernando", .cpf = 772, .end = "NaoLembro"},                  \
        {.nome = "Iam", .cpf = 666, .end = "Ravara"},                          \
        {.nome = "Gabriel", .cpf = 567, .end = "Coelho"},                      \
        {.nome = "Gileade", .cpf = 361, .end = "Valente"},                     \
        {.nome = "Samuel", .cpf = 294, .end = "Brum"},                         \
        {.nome = "Marcos", .cpf = 193, .end = "NaoLembro"},                    \
  }

void runTests();

#endif
