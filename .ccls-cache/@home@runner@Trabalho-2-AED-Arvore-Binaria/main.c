#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "binario.h"

int main() {
  FILE* frw;
  int opcao, num;

  //Cria o arquivo se ele nao existir
  frw = openBin();
  fclose(frw);
  
  do {
      printf("\nMenu:\n");
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
          case 1: //cadastra produto
              cadastraProduto();
              break;
          case 2: //remove produto
              //busca pelo id
              //remove do filho do no pai
              //coloca o reg no cabecalho
              break;
          case 3: //atualiza preco
              getInfoPreco();
              break;
          case 4: //atualiza estoque
              getInfoEstoque();
              break;
          case 5: //imprime info
              printf("Digite o ID do produto a ser buscado: ");
              scanf("%d",&num);
              imprimeProduto(num);
              break;
          case 6: //imprime todos produtos
              lerProdutos();
              break;
          case 7: //imprime arvore binaria por nivel
              imprimePorNivel();
              break;
          case 8: //imprime lista de livres
                //imprime a partir da raiz da arvore dos livres
                //pode utilizar o filho a esq pra indicar prox
              break;
          case 9: //Operacao em lote
              loadPath();
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