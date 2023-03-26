# Trabalho-2-AED---Arvore-Binaria

Alunos: Amin Mhamad Ismail 
        Juliet A. de O. Rigoti 
        Matheus Prokopowiski dos Santos

O programa tem como propósito funcionar como um software gerenciador de produtos de uma loja, onde cada produto tem as seguintes informações:
- ID: número de identificação de cada produto
- Nome: nome do produto
- Marca: marca do produto
- Categoria: descreve a categoria do produto
- Estoque: unidades disponíveis dos produtos no estoque
- Preço: preço do produto

Os produtos cadastrados são todos armazenados em arquivo binário, utilizando a ideia de arvore binaria, onde cada produto seria considerado um nó e tendo um nó a direita e a esquerda (ou não).

As funcionalidades disponíveis são:
- Cadastrar produto: Cadastra um produto com ID, nome, marca, categoria, estoque e preço, fornecida pelo usuário.
- Remover produto: Remove um produto do cadastro, a partir do ID do produto
- Atualizar preço: Atualiza o preço do produto do cadastro, a partir do ID do produto
- Atualizar estoque: Atualizar o estoque do produto do cadastro, a partir do ID do produto
- Imprimir produto: Imprime as informações do produto do cadastro, a partir do ID do produto
- Imprimir lista de todos os produtos: Imprime as informações dos produtos como o ID e o nome, mas in-ordem da arvore binaria 
- Imprimir arvore binária: Imprime os ID's dos produtos no modo de uma árvore binária
- Imprimir lista de livres: Imprime a lista de nós livres da árvore devido às remoções
- Realizar operacoes em lote: Realiza operações de inserção, alteração e remoção a partir do arquivo texto
