#include "binario.h"

//Cria uma lista nova em arquivo
//Pre-condicao: arquivo aberto para leitura/escrita
//Pos-condicao: arquivo e inicializado com uma lista vazia

void cria_lista_vazia(FILE* arq){
  cabecalho * cab = (cabecalho*) malloc(sizeof(cabecalho));
  cab->pos_cabeca = -1;
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
no* le_no(FILE* arq, int pos) {
  no* x = malloc(sizeof(no));
  fseek(arq,sizeof(cabecalho)+ pos*sizeof(no),SEEK_SET);
  fread(x,sizeof(no),1,arq);
  return x;
}

//Escreve um no em uma determinada posicao do arquivo
//Pre-condicao: arquivo deve estar aberto e ser um arquivo de lista
//              pos deve ser uma posicao valida do arquivo
//Pos-condicao: no escrito no arquivo
void escreve_no(FILE* arq, no* x, int pos){
  fseek(arq,sizeof(cabecalho) + pos*sizeof(no), SEEK_SET);
  fwrite(x,sizeof(no),1,arq);
}

//Abre um arquivo binario
//Pre-condicao: Um caminho para um arquivo existente
//Pos-condicao: Retorna o ponteiro para o arquivo binario
FILE* openBin(char* path){
    FILE *fwr;
    do{
        fwr = fopen(path, "a+b");
    }
    while(loadFile(path, fwr));
    return fwr;
}

//Verifica se o arquivo existe
//Pre-condicao: Um caminho para um arquivo
//Pos-condicao: Retorna se o arquivo e valido ou nao
int loadFile(char* path, FILE* file){
    if(file == NULL){
        printf("Falha ao ler arquivo!\n\n");
        return 1;
    }
    else return 0;
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
    while(loadFile(path, fr));
    
    printf("\n");
    fclose(fr);
}
