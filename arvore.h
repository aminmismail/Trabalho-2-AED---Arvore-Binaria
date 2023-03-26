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

//Cadastra as infos na struct de um produto
//Pre-condicao: Nenhuma
//Pos-condicao: Infos inseridas na struct produto
void cadastraProduto();

//Insere o produto no arquivo binário
//Pre-condicao: Produto com infos ja cadastradas
//Pos-condicao: Produto inserido no arquivo binario
void insereProduto();

//Realiza remoção de um produto
//Pre-condicao: ID do produto existente a ser removido
//Pos-condicao: Produto removido e nó liberado
void removeProduto();

//Retorna o menor valor dos maiores da sub arvore
//Pre-condicao: Arquivo binario aberto e um produto existente
//Pos-condicao: Produto que seja o menor valor dos maiores da sub arvore
Produto *menorMaior();

//Retorna o maior valor dos menores da sub arvore
//Pre-condicao: Arquivo binario aberto e um produto existente
//Pos-condicao: Produto que seja o maior valor dos menores da sub arvore
Produto *maiorMenor();

//Imprime os nós livres existentes
//Pre-condicao: nós livres de produtos removidos
//Pos-condicao: impressão de todos os nós livres
void imprimeLivres();

//Imprime os produtos da arvore binária por nivel
//Pre-condicao: Produtos já cadastrados no arquivo
//Pos-condicao: Impressao da arvore por nivel
void imprimePorNivel();
//Verifica se existe produtos cadastrados e precede a função "lerProdutos_rec"
//Pre-condicao: Produtos cadastrados no arquivo binario
//Pos-condicao: Imprime a árvore in-ordem
void lerProdutos();

//Realiza a impressão da arvore in-ordem
//Pre-condicao: Produtos cadastrados no arquivo binario
//Pos-condicao: Impressão da arvore in-ordem
void lerProdutos_rec();

//Imprime as informaçoes de um produto especifico
//Pre-condicao: Produto cadastrado no arquivo binario
//Pos-condicao: Infos do produto impressas
void imprimeProduto();

//Busca um produto pelo ID no arquivo
//Pre-condicao: Arquivo binario aberto e ID de um produto existente
//Pos-condicao: Infos do produto carregada no struct produto
Produto *buscaProduto();

//Busca o nó pai de um produto
//Pre-condicao: Produtos cadastrados, ID a ser buscado e raiz da arvore
//Pos-condicao: Nó anterior ao produto com ID fornecido
Produto *buscaNoAnt();

//Obtem novo estoque
//Pre-condicao: Produto existente no arquivo
//Pos-condicao: Estoque do produto alterado
void getInfoEstoque();

//Obtem novo preco
//Pre-condicao: Produto existente no arquivo
//Pos-condicao: Preco do produto alterado
void getInfoPreco();

//Modifica o estoque de um produto
//Pre-condicao: Produto existente e novo valor do estoque
//Pos-condicao: Produto com estoque atualizado
void atualizaEstoque(int info, int stock);

//Modifica o preco de um produto
//Pre-condicao: Produto existente e novo valor do preco
//Pos-condicao: Produto com preco atualizado
void atualizaPreco(int info, double price);

//Realiza inclusoes em lote
//Pre-condicao: Arquivo txt com comandos e informacoes aberto
//Pos-condicao: Inclusoes, alteracoes e remocoes do arquivo efetuadas
void incluiLote();


#endif //ARVORE_H