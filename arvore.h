#ifndef ARVORE_H
#define ARVORE_H
#include "binario.h"

typedef struct no {
  int id;
  char nome[51];
  char marca[31];
  char categoria[51];
  int estoque;
  double preco;
  struct no* esq;
  struct no* dir;
}Produto;

void insereProduto();
void cadastraProduto();


#endif //ARVORE_H