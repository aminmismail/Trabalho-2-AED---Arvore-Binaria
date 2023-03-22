#include "binario.h"
#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>

//Cria uma lista nova em arquivo
//Pre-condicao: arquivo aberto para leitura/escrita
//Pos-condicao: arquivo e inicializado com uma lista vazia
void cria_lista_vazia(FILE* arq){
  cabecalho * cab = (cabecalho*) malloc(sizeof(cabecalho));
  cab->pos_cabeca = 0;
  cab->pos_topo = 0;
  cab->pos_livre = -1;
  escreve_cabecalho(arq,cab);
  free(cab);
}

//Le o cabecalho do arquivo contendo as informacoes da lista
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//Pos-condicao: retorna o ponteiro para o cabecalho lido
cabecalho* le_cabecalho(FILE * arq) {
  cabecalho * cab = (cabecalho*) malloc(sizeof(cabecalho));
  fseek(arq,0,SEEK_SET); // posiciona no inıcio do arquivo
  fread(cab,sizeof(cabecalho),1,arq);
  return cab;
}
//Escreve no arquivo o cabe¸calho contendo as informacoes da lista
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//Pos-condicao: cabecalho escrito no arquivo
void escreve_cabecalho(FILE* arq, cabecalho* cab){
  fseek(arq,0,SEEK_SET); //posiciona no inıcio do arquivo
  fwrite(cab,sizeof(cabecalho),1,arq);
}

//le um no em uma determinada posicao do arquivo
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//              pos deve ser uma posicao valida da lista
//Pos-condicao: ponteiro para no lido e retornado
struct no* le_no(FILE* arq, int pos) {
  struct no* x = malloc(sizeof(struct no));
  fseek(arq,sizeof(cabecalho)+ pos*sizeof(struct no),SEEK_SET);
  fread(x,sizeof(struct no),1,arq);
  return x;
}

//Escreve um no em uma determinada posicao do arquivo
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//              pos deve ser uma posicao valida do arquivo
//Pos-condicao: no escrito no arquivo
void escreve_no(FILE* arq, struct no* x, int pos){
  fseek(arq,sizeof(cabecalho) + pos*sizeof(struct no), SEEK_SET);
  fwrite(x,sizeof(struct no),1,arq);
}

//Abre um arquivo binario
//Pre-condicao: Um caminho para um arquivo existente
//Pos-condicao: Retorna o ponteiro para o arquivo binario
FILE* openBin(){
    FILE *fwr;
    fwr = fopen("./dados.bin", "rb+");
    if(fwr == NULL){
      fwr = fopen("./dados.bin", "wb+");
      cria_lista_vazia(fwr);
    }
    return fwr;
}

//Le o caminho do arquivo passado por input, e cadastra os itens nele
//Pre-condicao: Um caminho para um arquivo existente
//Pos-condicao: Registro dos itens nos arquivos binarios
void loadPath(){
    FILE *fr;
    char path[50];
    do{
        printf("Nome do arquivo:");
        scanf("%s%*c", path);
        fr = fopen(path, "r");
    }
    while(fr == NULL);
    incluiLote(fr);
    printf("\n");
    fclose(fr);
}

// Testa se a fila esta vazia
int vazia(Fila* f){
  return (f->inicio == f->fim);
}

//Cria uma fila vazia
Fila* cria_fila_vazia() {
  Fila* f = (Fila*) malloc(sizeof(Fila));
  f->inicio = NULL;
  f->fim = NULL;
  return f;
  }

//Enfileira um elemento
void enqueue(Fila* f, int x) {
  struct nof* aux = (struct nof*) malloc(sizeof(struct nof));
  aux->info = x;
  aux->prox = NULL;
  if(vazia(f)) 
    f->inicio = aux;
  else 
    f->fim->prox = aux;
  f->fim = aux;
}

//Desenfileira um elemento
int dequeue(Fila* f) {
  if(!vazia(f)) {
    int x;
    struct nof* aux = f->inicio;
    x = f->inicio->info;
    if(f->inicio == f->fim) // so tem 1 elemento
      f->fim = NULL;
    f->inicio = f->inicio->prox;
    free(aux);
    return x;
    }
  else {
    printf("Fila vazia!\n");
    return -1;  
  }
}