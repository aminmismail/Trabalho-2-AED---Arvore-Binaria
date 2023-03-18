#include "arvore.h"
#include "binario.h"
#include <stdio.h>
#include <stdlib.h>

void cadastraProduto(){
  Produto* p = (Produto*) malloc(sizeof(Produto));
  //Verificar se ja existe produto com mesmo ID
  //Utiliza funcao buscarProduto(int id)
  printf("Informe o codigo do produto: ");
  scanf("%d%*c", &p->id);
  printf("Informe o nome do produto: ");
  scanf("%[^\n]%*c", p->nome);
  printf("Informe a marca do produto: ");
  scanf("%[^\n]%*c", p->marca);
  printf("Informe a categoria do produto: ");
  scanf("%[^\n]", p->categoria);
  printf("Informe o estoque do produto: ");
  scanf("%d", &p->estoque);
  printf("Informe o preco do produto (utilize '.' em valores decimais): ");
  scanf("%lf", &p->preco);
  p->dir = -1;
  p->esq = -1;
  insereProduto(p);
  free(p);
}

void insereProduto(Produto* p){
  FILE* f = openBin();
  cabecalho *cab = le_cabecalho(f);
  int pos_reg = 0;
  if(cab->pos_livre != -1){
    pos_reg = cab->pos_livre;
    //atualizar pos_livre com proximo valor ou -1 se n tiver
  }
  else{
    pos_reg = cab->pos_topo;
    cab->pos_topo += 1;
  }
  fseek(f, sizeof(cabecalho) + sizeof(Produto)*pos_reg, SEEK_SET);
  fwrite(p, sizeof(Produto), 1, f);
  if(cab->pos_cabeca == -1) cab->pos_cabeca = 0;
  if(pos_reg != cab->pos_cabeca){
    Produto* aux = (Produto*) malloc(sizeof(Produto));
    //buscaNoAnt e escreve o filho esq ou dir
    aux = buscaNoAnt(f, p->id, cab->pos_cabeca); //ponteiro do f está depois do produto
    fseek(f, 0-sizeof(Produto), SEEK_CUR);
    if(p->id < aux->id){
      aux->esq = pos_reg;
    }
    else if(p->id > aux->id){
      aux->dir = pos_reg;
    }
    fwrite(aux,sizeof(Produto),1,f);
    free(aux);
  }
  escreve_cabecalho(f, cab);
  fclose(f);
  free(cab);
}

void lerProdutos(){
  Produto* p = (Produto*) malloc(sizeof(Produto));
  FILE* f = openBin();
  fseek(f, sizeof(cabecalho), SEEK_SET);
  while(fread(p, sizeof(Produto), 1, f) != 0) {
    printf("\nID: %d\n", p->id);
    printf("Nome: %s\n", p->nome);
    printf("Marca: %s\n", p->marca);
    printf("Categoria: %s\n", p->categoria);
    printf("Estoque: %d\n", p->estoque);
    printf("Preco: %.2lf\n", p->preco);
    printf("Filho a direita: %d\n", p->dir);
    printf("Filho a esquerda: %d\n\n", p->esq);
  }
  free(p);
  fclose(f);
}

void imprimeProduto(int num){
  FILE* f = openBin();
  Produto* p = buscaProduto(f, num);
  if(p != NULL){
    printf("\nID: %d\n", p->id);
    printf("Nome: %s\n", p->nome);
    printf("Marca: %s\n", p->marca);
    printf("Categoria: %s\n", p->categoria);
    printf("Estoque: %d\n", p->estoque);
    printf("Preco: %.2lf\n\n", p->preco);
    free(p);
  }
  else printf("Produto não encontrado! \n");
  fclose(f);
}

Produto *buscaProduto(FILE* f, int info){
  if(feof(f)) return NULL;
  Produto* p = (Produto*) malloc(sizeof(Produto));
  cabecalho* cab = le_cabecalho(f);
  fseek(f, sizeof(Produto)*cab->pos_cabeca, SEEK_CUR);
  fread(p, sizeof(Produto), 1, f);
  while(p->dir != -1 || p->esq != -1){ //mudado de and para or
    if(p->esq != -1 && info < p->id){ //esq
      fseek(f, sizeof(cabecalho) + sizeof(Produto)*p->esq, SEEK_SET);
    }
    else if(p->dir != -1 && info > p->id){ //dir
      fseek(f, sizeof(cabecalho) + sizeof(Produto)*p->dir, SEEK_SET);
    }
    else if(info == p->id){
      return p;
    }
    fread(p, sizeof(Produto), 1, f);
  }
  if(info == p->id) return p;
  free(p);
  free(cab);
  return NULL;  
}

Produto *buscaNoAnt(FILE* f, int info, int raiz){
  if(feof(f)) return NULL;
  Produto* p = (Produto*) malloc(sizeof(Produto));
  fseek(f, sizeof(cabecalho) + sizeof(Produto)*raiz, SEEK_SET);
  fread(p, sizeof(Produto), 1, f);
  while((p->dir != -1 && info > p->id) || (p->esq != -1 && info < p->id)){
    if(p->esq != -1 && info < p->id){ //esq
      fseek(f, sizeof(cabecalho) + sizeof(Produto)*p->esq, SEEK_SET);
    }
    else if(p->dir != -1 && info > p->id){ //dir
      fseek(f, sizeof(cabecalho) + sizeof(Produto)*p->dir, SEEK_SET);
    }
    fread(p, sizeof(Produto), 1, f);
  }
  return p;
}

void atualizaPreco(){
  FILE* f = openBin();
  Produto* p;
  int info;
  printf("Digite o ID do produto a ser editado: ");
  scanf("%d", &info);
  p = buscaProduto(f, info);
  imprimeProduto(info);
  if(p != NULL){
    double price;
    printf("Digite o novo preco (utilize '.' em valores decimais): ");
    scanf("%lf",&price);
    p->preco = price;
    fseek(f, 0-sizeof(Produto), SEEK_CUR);
    fwrite(p, sizeof(Produto), 1, f);
  }
  fclose(f);
  free(p);
}

void atualizaEstoque(){
  FILE* f = openBin();
  Produto* p;
  int info;
  printf("Digite o ID do produto a ser editado: ");
  scanf("%d", &info);
  p = buscaProduto(f, info);
  imprimeProduto(info);
  if(p != NULL){
    int stock;
    printf("Digite o novo estoque: ");
    scanf("%d",&stock);
    p->estoque = stock;
    fseek(f, 0-sizeof(Produto), SEEK_CUR);
    fwrite(p, sizeof(Produto), 1, f);
  }
  fclose(f);
  free(p);
}