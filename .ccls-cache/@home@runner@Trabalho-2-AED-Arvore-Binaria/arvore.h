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
  int esq;
  int dir;
}Produto;

void insereProduto();

void cadastraProduto();

void lerProdutos();

Produto* buscaProduto();

void imprimeProduto();

Produto *buscaNoAnt();

void getInfoEstoque();

void getInfoPreco();

void atualizaPreco();

void atualizaEstoque();

void incluiLote();

void imprimePorNivel();

void lerProdutos_rec();

Produto* menorMaior();

Produto* maiorMenor();

void removeProduto();

void imprimeLivres();


#endif //ARVORE_H