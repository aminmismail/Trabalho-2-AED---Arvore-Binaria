#include <stdio.h>
#include "arvore.h"
#include "binario.h"

int main() {
  FILE* frw;
  int opcao;

  //Cria o arquivo se ele nao existir
  frw = openBin("./dados.bin");
  fclose(frw);
  
  do {
      printf("Menu:\n");
      printf("1 - Cadastrar produto\n");
      printf("2 - Remover produto\n");
      printf("3 - Atualizar preco\n");
      printf("4 - Atualizar estoque\n");
      printf("5 - Imprimir informacoes de um produto\n");
      printf("6 - Imprimir lista de todos os produtos\n");
      printf("7 - Imprimir arvore binária\n");
      printf("8 - Imprimir lista de livres\n");
      printf("9 - Realizar operacoes em lote\n");
      printf("0 - Sair\n");
      printf("Escolha uma opcao: ");
      scanf("%d", &opcao);
      
      switch (opcao) {
          case 1: //cadastra
              cadastraProduto();
              break;
          case 2: //remove
              
              break;
          case 3: //atualiza preco
              
              break;
          case 4: //atualiza estoque
              
              break;
          case 5: //imprime info
              
              break;
          case 6: //imprime todos produtor
              
              break;
          case 7: //imprime arvore binaria
              
              break;
          case 8: //imprime lista de livres

              break;
          case 9: //

              break;
          case 0:
              printf("Saindo...\n");
              break;
          default:
              printf("Opcao invalida. Tente novamente.\n");
      }
  } while (opcao != 0);
  
  return 0;
}