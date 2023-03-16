#include "arvore.h"
#include "binario.h"
#include <stdio.h>
#include <stdlib.h>

void cadastraProduto(){
  Produto* p = (Produto*) malloc(sizeof(Produto));
  printf("Informe o codigo do produto: ");
  scanf("%d%*c", &p->id);
  printf("Informe o nome do produto: ");
  scanf(" %[^\n]%*c", p->nome);
  printf("Informe a marca do produto: ");
  scanf(" %[^\n]%*c", p->marca);
  printf("Informe a categoria do produto: ");
  scanf(" %[^\n]", p->categoria);
  printf("Informe o estoque do produto: ");
  scanf("%d", &p->estoque);
  printf("Informe o preco do produto: ");
  scanf("%lf", &p->preco);
  insereProduto(p);
  free(p);
}

void insereProduto(Produto* p){
  FILE* f;
  f = openBin("./dados.bin");
  cabecalho *cab = le_cabecalho(f);
  if(cab->pos_livre == -1) fseek(f, 0, SEEK_END);
  
  fclose(f);
  free(cab);
}