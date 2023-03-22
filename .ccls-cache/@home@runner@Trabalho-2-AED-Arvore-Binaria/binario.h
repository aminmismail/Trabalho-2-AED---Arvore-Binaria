#ifndef BINARIO_H
#define BINARIO_H
#include <stdio.h>
#include "arvore.h"


typedef struct {
    int pos_cabeca; //posicao do inicio da lista
    int pos_topo; // 1a posicao nao usada no fim do arquivo
    int pos_livre; // posicao do inıcio da lista de nos livres
} cabecalho;

struct nof {
int info;
struct nof* prox;
};

typedef struct {
struct nof* inicio;
struct nof* fim;
}Fila;

//Le o cabecalho do arquivo contendo as informacoes da lista
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//Pos-condicao: retorna o ponteiro para o cabecalho lido
cabecalho* le_cabecalho(FILE * arq);

//Cria uma lista nova em arquivo
//Pre-condicao: arquivo aberto para leitura/escrita
//Pos-condicao: arquivo inicializado com uma lista vazia
void cria_lista_vazia(FILE* arq);

//Escreve no arquivo o cabecalho contendo as informacoes da lista
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//Pos-condicao: cabecalho escrito no arquivo
void escreve_cabecalho(FILE* arq, cabecalho* cab);

//Le o caminho do arquivo passado por input, e cadastra os itens nele
//Pre-condicao: Um caminho para um arquivo existente
//Pos-condicao: Registro dos itens nos arquivos binarios
void loadPath();

//Abre o arquivo binario "dados.bin"
//Pre-condicao: Um caminho para um arquivo existente
//Pos-condicao: Retorna o ponteiro para o arquivo binario
FILE* openBin();


#endif //BINARIO_H