#ifndef ARVORE_H
#define ARVORE_H
#include "binario.h"

struct no {
  int id;
  char nome[51];
  char marca[31];
  char categoria[51];
  int estoque;
  double preco;
  struct no* esq;
  struct no* dir;
};

#endif //ARVORE_H