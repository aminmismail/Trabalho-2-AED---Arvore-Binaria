#include "arvore.h"
#include "binario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Cadastra as infos na struct de um produto
//Pre-condicao: Nenhuma
//Pos-condicao: Infos inseridas na struct produto
void cadastraProduto() {
  FILE *f = openBin();
  Produto *p = (Produto *)malloc(sizeof(Produto));
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
  if (buscaProduto(f, p->id) == NULL) { // verifica se ja existe mesmo ID
    fclose(f);
    insereProduto(p);
  } else
    printf("ID já existente! Insira outro ID\n");
  free(p);
}

//Insere o produto no arquivo binário
//Pre-condicao: Produto com infos ja cadastradas
//Pos-condicao: Produto inserido no arquivo binario
void insereProduto(Produto *p) {
  FILE *f = openBin();
  cabecalho *cab = le_cabecalho(f);
  int pos_reg = 0;
  if (cab->pos_livre != -1) {
    Produto *aux = (Produto *)malloc(sizeof(Produto));
    pos_reg = cab->pos_livre;
    fseek(f, sizeof(cabecalho) + sizeof(Produto) * pos_reg, SEEK_SET);
    fread(aux, sizeof(Produto), 1, f);
    cab->pos_livre = aux->esq;
    free(aux);
  } else {
    pos_reg = cab->pos_topo;
    cab->pos_topo += 1;
  }
  fseek(f, sizeof(cabecalho) + sizeof(Produto) * pos_reg, SEEK_SET);
  fwrite(p, sizeof(Produto), 1, f);
  if (cab->pos_cabeca == -1) cab->pos_cabeca = 0;
  if (pos_reg != cab->pos_cabeca) {
    Produto *aux = (Produto *)malloc(sizeof(Produto));
    // buscaNoAnt e escreve o filho esq ou dir
    aux = buscaNoAnt(f, p->id, cab->pos_cabeca); // ponteiro do f está depois do produto
    fseek(f, 0 - sizeof(Produto), SEEK_CUR);
    if (p->id < aux->id) {
      aux->esq = pos_reg;
    } else if (p->id > aux->id) {
      aux->dir = pos_reg;
    }
    fwrite(aux, sizeof(Produto), 1, f);
    free(aux);
  }
  escreve_cabecalho(f, cab);
  fclose(f);
  free(cab);
}

//Realiza remoção de um produto
//Pre-condicao: ID do produto existente a ser removido
//Pos-condicao: Produto removido e nó liberado
void removeProduto(int info) {
  FILE *f = openBin();
  cabecalho *cab = le_cabecalho(f);
  Produto *p = buscaProduto(f, info);
  if (p == NULL) {
    printf("Elemento não encontrado!\n");
    return;
  }
  Produto *aux = buscaNoAnt(f, p->id, cab->pos_cabeca);
  
  if (p->dir == -1 && p->esq == -1 && aux == NULL){ //Raiz sem filhos
    cab->pos_livre = 0;
    cab->pos_cabeca = -1;
  }
    
  else if (p->dir == -1 && p->esq == -1) { // Nó é folha
    p->esq = cab->pos_livre;
    fseek(f, 0 - sizeof(Produto), SEEK_CUR); // Volta ao comeco do produto p
    fwrite(p, sizeof(Produto), 1, f);
    if (p->id > aux->id) { // caso nó removido for menor que o pai
      cab->pos_livre = aux->dir;
      aux->dir = -1;
    }
    if (p->id < aux->id) { // caso nó removido for maior que o pai
      cab->pos_livre = aux->esq;
      aux->esq = -1;
    }
    fseek(f, 0 - sizeof(Produto), SEEK_CUR); // Volta ao comeco do produto aux
    fwrite(aux, sizeof(Produto), 1, f);
    free(aux);
  } 
    
  else { // tem filho a esquerda e/ou a direita
    Produto *aux, *noAnt;
    if (p->esq != -1) {
      aux = maiorMenor(f, p);
      noAnt = buscaNoAnt(f, aux->id, cab->pos_cabeca);

      if (aux->id > noAnt->id) { // caso nó removido for maior que o pai
        cab->pos_livre = noAnt->dir;
        noAnt->dir = aux->esq;
        // reescreve o noAnt em seu lugar
        buscaProduto(f, noAnt->id);
        fseek(f, 0 - sizeof(Produto), SEEK_CUR);
        fwrite(noAnt, sizeof(Produto), 1, f);
        aux->esq = p->esq;
        aux->dir = p->dir;
        buscaProduto(f, p->id);
        fseek(f, 0 - sizeof(Produto), SEEK_CUR);
        fwrite(aux, sizeof(Produto), 1, f);
      }
      if (aux->id < noAnt->id) { // caso nó removido for menor que o pai
        cab->pos_livre = noAnt->esq;
        // considera noAnt como o nó a ser removido
        aux->dir = p->dir;
        buscaProduto(f, p->id);
        fseek(f, 0 - sizeof(Produto), SEEK_CUR);
        fwrite(aux, sizeof(Produto), 1, f);
      }
    }
    else if (p->dir != -1) {
      aux = menorMaior(f, p);
      noAnt = buscaNoAnt(f, aux->id, cab->pos_cabeca);

      if (aux->id > noAnt->id) { // caso nó removido for maior que o pai
        cab->pos_livre = noAnt->dir;
        // considera noAnt como o nó a ser removido
        aux->esq = p->esq;
        buscaProduto(f, p->id);
        fseek(f, 0 - sizeof(Produto), SEEK_CUR);
        fwrite(aux, sizeof(Produto), 1, f);
      }

      if (aux->id < noAnt->id) { // caso nó removido for menor que o pai
        cab->pos_livre = noAnt->esq;
        noAnt->esq = aux->dir;
        buscaProduto(f, noAnt->id);
        fseek(f, 0 - sizeof(Produto), SEEK_CUR);
        fwrite(noAnt, sizeof(Produto), 1, f);
        aux->esq = p->esq;
        aux->dir = p->dir;
        buscaProduto(f, p->id);
        fseek(f, 0 - sizeof(Produto), SEEK_CUR);
        fwrite(aux, sizeof(Produto), 1, f);
      }
      free(aux);
    }
  }
    printf("Produto com ID [%d] removido!\n", info);
    escreve_cabecalho(f, cab);
    free(p);
    free(cab);
    fclose(f);
}

//Retorna o menor valor dos maiores da sub arvore
//Pre-condicao: Arquivo binario aberto e um produto existente
//Pos-condicao: Produto que seja o menor valor dos maiores da sub arvore
Produto *menorMaior(FILE *f, Produto *p) {
  Produto *aux = (Produto *)malloc(sizeof(Produto));
  fseek(f, sizeof(cabecalho) + sizeof(Produto) * p->dir, SEEK_SET);
  fread(aux, sizeof(Produto), 1, f);
  while (aux->esq != -1) {
    fseek(f, sizeof(cabecalho) + sizeof(Produto) * aux->esq, SEEK_SET);
    fread(aux, sizeof(Produto), 1, f);
  }
  return aux;
}

//Retorna o maior valor dos menores da sub arvore
//Pre-condicao: Arquivo binario aberto e um produto existente
//Pos-condicao: Produto que seja o maior valor dos menores da sub arvore
Produto *maiorMenor(FILE *f, Produto *p) {
  Produto *aux = (Produto *)malloc(sizeof(Produto));
  fseek(f, sizeof(cabecalho) + sizeof(Produto) * p->esq, SEEK_SET);
  fread(aux, sizeof(Produto), 1, f);
  while (aux->dir != -1) {
    fseek(f, sizeof(cabecalho) + sizeof(Produto) * aux->dir, SEEK_SET);
    fread(aux, sizeof(Produto), 1, f);
  }
  return aux;
}

//Imprime os nós livres existentes
//Pre-condicao: nós livres de produtos removidos
//Pos-condicao: impressão de todos os nós livres
void imprimeLivres() {
  Produto p;
  FILE *f = openBin();
  cabecalho *cab = le_cabecalho(f);
  if (cab->pos_livre == -1) {
    printf("Não existe nó livre !\n");
    return;
  }
  printf("Nós livre: %d ->", cab->pos_livre);
  fseek(f, sizeof(Produto) * cab->pos_livre, SEEK_CUR);
  fread(&p, sizeof(Produto), 1, f);
  while (p.esq != -1) {
    printf(" %d ->", p.esq);
    fseek(f, sizeof(cabecalho) + sizeof(Produto) * p.esq, SEEK_SET);
    fread(&p, sizeof(Produto), 1, f);
  }
  printf(" -1\n");
  fclose(f);
  free(cab);
}

//Imprime os produtos da arvore binária por nivel
//Pre-condicao: Produtos já cadastrados no arquivo
//Pos-condicao: Impressao da arvore por nivel
void imprimePorNivel() {
  Produto *p = (Produto *)malloc(sizeof(Produto));
  FILE *f = openBin();
  cabecalho *cab = le_cabecalho(f);
  Fila *fila = cria_fila_vazia();
  int curID;
  if (cab->pos_cabeca == -1){
    printf("Não existem produtos !\n");
    return;
  }
  fseek(f, sizeof(Produto) * cab->pos_cabeca, SEEK_CUR);
  fread(p, sizeof(Produto), 1, f);
  enqueue(fila, p->id);
  enqueue(fila, -1);
  while (!vazia(fila)) {
    curID = dequeue(fila);
    if (curID != -1) {
      fseek(f, sizeof(cabecalho) + sizeof(Produto) * curID, SEEK_SET);
      fread(p, sizeof(Produto), 1, f);
      printf(" %d ", p->id);
      if (p->esq != -1) {
        enqueue(fila, p->esq);
      }
      if (p->dir != -1) {
        enqueue(fila, p->dir);
      }
    } else {
      printf("\n");
      if (!vazia(fila))
        enqueue(fila, -1);
    }
  }

  fclose(f);
  free(p);
  free(cab);
  free(fila);
}

//Verifica se existe produtos cadastrados e precede a função "lerProdutos_rec"
//Pre-condicao: Produtos cadastrados no arquivo binario
//Pos-condicao: Imprime a árvore in-ordem
void lerProdutos() {
  Produto p;
  FILE *f = openBin();
  cabecalho *cab = le_cabecalho(f);
  if (cab->pos_cabeca == -1) {
    printf("Nenhum produto cadastrado !\n");
    free(cab);
    fclose(f);
    return;
  }
  fseek(f, sizeof(cabecalho) + sizeof(Produto) * cab->pos_cabeca, SEEK_SET);
  fread(&p, sizeof(Produto), 1, f);
  lerProdutos_rec(&p, f, cab->pos_cabeca);
  free(cab);
  fclose(f);
}

//Realiza a impressão da arvore in-ordem
//Pre-condicao: Produtos cadastrados no arquivo binario
//Pos-condicao: Impressão da arvore in-ordem
void lerProdutos_rec(Produto p, FILE *f, int raiz) {
  if (raiz == -1)
    return;
  fseek(f, sizeof(cabecalho) + sizeof(Produto) * raiz, SEEK_SET);
  fread(&p, sizeof(Produto), 1, f);
  if (p.esq != -1) {
    lerProdutos_rec(p, f, p.esq);
  }
  printf("\nID: %d\n", p.id);
  printf("Nome: %s\n", p.nome);
  printf("Esquerda: %d\n", p.esq);
  printf("Direita: %d\n", p.dir);
  if (p.dir != -1) {
    lerProdutos_rec(p, f, p.dir);
  }
}

//Imprime as informaçoes de um produto especifico
//Pre-condicao: Produto cadastrado no arquivo binario
//Pos-condicao: Infos do produto impressas
void imprimeProduto(int info) {
  FILE *f = openBin();
  Produto *p = buscaProduto(f, info);
  if (p != NULL) {
    printf("\nID: %d\n", p->id);
    printf("Nome: %s\n", p->nome);
    printf("Marca: %s\n", p->marca);
    printf("Categoria: %s\n", p->categoria);
    printf("Estoque: %d\n", p->estoque);
    printf("Preco: %.2lf\n\n", p->preco);
    printf("Esquerda: %d\n", p->esq);
    printf("Direita: %d\n", p->dir);
    free(p);
  } else
    printf("\nProduto com ID [%d] não encontrado! \n", info);
  fclose(f);
}

//Busca um produto pelo ID no arquivo
//Pre-condicao: Arquivo binario aberto e ID de um produto existente
//Pos-condicao: Infos do produto carregada no struct produto
Produto *buscaProduto(FILE *f, int info) {
  cabecalho *cab = le_cabecalho(f);
  if (feof(f) || cab->pos_cabeca == -1)
    return NULL;
  Produto *p = (Produto *)malloc(sizeof(Produto));
  fseek(f, sizeof(Produto) * cab->pos_cabeca, SEEK_CUR);
  fread(p, sizeof(Produto), 1, f);
  if (p->dir == 0 && p->esq == 0) {
    p->dir = -1;
    p->esq = -1;
  }
  while (p->dir != -1 || p->esq != -1) {
    if (p->esq != -1 && info < p->id) { // esq
      fseek(f, sizeof(cabecalho) + sizeof(Produto) * p->esq, SEEK_SET);
      fread(p, sizeof(Produto), 1, f);
    } else if (p->dir != -1 && info > p->id) { // dir
      fseek(f, sizeof(cabecalho) + sizeof(Produto) * p->dir, SEEK_SET);
      fread(p, sizeof(Produto), 1, f);
    } else if (p->dir == -1 && info > p->id || p->esq == -1 && info < p->id)
      break;
    else if (info == p->id) {
      return p;
    }
  }
  if (info == p->id)
    return p;
  free(p);
  free(cab);
  return NULL;
}

//Busca o nó pai de um produto
//Pre-condicao: Produtos cadastrados, ID a ser buscado e raiz da arvore
//Pos-condicao: Nó anterior ao produto com ID fornecido
Produto *buscaNoAnt(FILE *f, int info, int raiz) {
  if (feof(f))
    return NULL;
  int lastReg = 0, lastRegAux = 0;
  Produto *p = (Produto *)malloc(sizeof(Produto));
  fseek(f, sizeof(cabecalho) + sizeof(Produto) * raiz, SEEK_SET);
  fread(p, sizeof(Produto), 1, f);
  if (p->id == info) {
    free(p);
    return NULL;
  }
  while ((p->dir != -1 && info > p->id) || (p->esq != -1 && info < p->id)) {
    if (p->esq != -1 && info < p->id) { // esq
      fseek(f, sizeof(cabecalho) + sizeof(Produto) * p->esq, SEEK_SET);
      lastRegAux = p->esq;
    }
    if (p->dir != -1 && info > p->id) { // dir
      fseek(f, sizeof(cabecalho) + sizeof(Produto) * p->dir, SEEK_SET);
      lastRegAux = p->dir;
    }
    fread(p, sizeof(Produto), 1, f);
    if (p->id != info)
      lastReg = lastRegAux;
    if (p->id == info) { // caso chegue no mesmo nó
      fseek(f, sizeof(cabecalho) + sizeof(Produto) * lastReg, SEEK_SET);
      fread(p, sizeof(Produto), 1, f);
      return p;
    }
  }
  return p;
}

//Obtem novo estoque
//Pre-condicao: Produto existente no arquivo
//Pos-condicao: Estoque do produto alterado
void getInfoEstoque() {
  int num, estq;
  printf("Digite o ID do produto a ser editado: ");
  scanf("%d", &num);
  printf("Digite o novo estoque do produto: ");
  scanf("%d", &estq);
  atualizaEstoque(num, estq);
}

//Obtem novo preco
//Pre-condicao: Produto existente no arquivo
//Pos-condicao: Preco do produto alterado
void getInfoPreco() {
  int num;
  double prc;
  printf("Digite o ID do produto a ser editado: ");
  scanf("%d", &num);
  printf("Digite o novo preco (utilize '.' em valores decimais): ");
  scanf("%lf", &prc);
  atualizaPreco(num, prc);
}

//Modifica o estoque de um produto
//Pre-condicao: Produto existente e novo valor do estoque
//Pos-condicao: Produto com estoque atualizado
void atualizaEstoque(int info, int stock) {
  FILE *f = openBin();
  Produto *p = buscaProduto(f, info);
  if (p != NULL) {
    p->estoque = stock;
    fseek(f, 0 - sizeof(Produto), SEEK_CUR);
    fwrite(p, sizeof(Produto), 1, f);
    imprimeProduto(info);
  } else
    printf("ID [%d] nao existente! \n", info);
  fclose(f);
  free(p);
}

//Modifica o preco de um produto
//Pre-condicao: Produto existente e novo valor do preco
//Pos-condicao: Produto com preco atualizado
void atualizaPreco(int info, double price) {
  FILE *f = openBin();
  Produto *p = buscaProduto(f, info);
  if (p != NULL) {
    p->preco = price;
    fseek(f, 0 - sizeof(Produto), SEEK_CUR);
    fwrite(p, sizeof(Produto), 1, f);
    imprimeProduto(info);
  } else
    printf("ID [%d] nao existente! \n", info);
  fclose(f);
  free(p);
}

//Realiza inclusoes em lote
//Pre-condicao: Arquivo txt com comandos e informacoes aberto
//Pos-condicao: Inclusoes, alteracoes e remocoes do arquivo efetuadas
void incluiLote(FILE *fr) {
  char text[300], *aux = NULL, *pt = NULL;
  Produto *p = (Produto *)malloc(sizeof(Produto));
  while (fscanf(fr, "%[^\n]%*c", text) != EOF) {
    FILE *f = openBin();
    char *token = strtok(text, ";"); // pega o tipo
    if (strcmp(token, "I") == 0) {
      p->id = atoi(strtok(NULL, ";"));
      strcpy(p->nome, strtok(NULL, ";"));
      strcpy(p->marca, strtok(NULL, ";"));
      strcpy(p->categoria, strtok(NULL, ";"));
      p->estoque = atoi(strtok(NULL, ";"));
      for (pt = aux = strtok(NULL, ";"); *aux != 0; aux++)
        if (*aux == ',')
          *aux = '.';
      p->preco = atof(pt);
      p->esq = -1;
      p->dir = -1;
      Produto *aux = buscaProduto(f, p->id);
      fclose(f);
      if (aux == NULL) {
        insereProduto(p);
        printf("Produto com ID [%d] cadastrado!\n", p->id);
      } else
        printf("ID [%d] ja existente! \n", p->id);
      free(aux);
    }

    else if (strcmp(token, "R") == 0) {
      int info;
      info = atoi(strtok(NULL, ";"));
      removeProduto(info);
    }

    else if (strcmp(token, "A") == 0) {
      int info;
      char aux1[16] = "", aux2[16] = "", *ptr = text;
      ptr += 2;
      sscanf(ptr, "%d", &p->id);
      ptr = &ptr[strcspn(ptr, ";") + 1];
      sscanf(ptr, "%[^;]", aux1);
      ptr = &ptr[strcspn(ptr, ";") + 1];
      sscanf(ptr, "%[^\n]", aux2);
      if (strcmp(aux1, "")) {
        atualizaEstoque(p->id, atoi(aux1));
      }
      if (strcmp(aux2, "")) {
        for (ptr = aux2; *ptr != 0; ptr++)
          if (*ptr == ',')
            *ptr = '.';
        atualizaPreco(p->id, atof(aux2));
      }

      fclose(f);
    }

    else {
      printf("Entrada não reconhecida! \n");
      fclose(f);
    }
  }
  free(p);
}