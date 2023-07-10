# Árvore Binária

Este é um código de implementação de uma Árvore Binária em linguagem C. Uma Árvore Binária é uma estrutura de dados que consiste em nós, onde cada nó tem no máximo dois filhos: um filho à esquerda e um filho à direita. Cada nó contém um par chave-valor, representado pela estrutura `KeyValPair`.

## Funções

### KeyValPair

- `KeyValPair *key_val_pair_construct(void *key, void *val)`: Cria um par chave-valor com as chaves e valores fornecidos.
- `void key_val_pair_destroy(KeyValPair *kvp, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn)`: Destroi um par chave-valor, liberando a memória alocada para ele. Também pode chamar as funções de destruição da chave e valor, se fornecidas.

### Node

- `Node *node_construct(void *key, void *value, Node *left, Node *right)`: Cria um nó com a chave, valor e nós filhos fornecidos.
- `void node_destroy(Node *node, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn)`: Destroi um nó, liberando a memória alocada para ele e seus nós filhos. Também pode chamar as funções de destruição da chave e valor, se fornecidas.

### BinaryTree

- `BinaryTree *binary_tree_construct(CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn)`: Cria uma nova Árvore Binária vazia.
- `void binary_tree_add(BinaryTree *bt, void *key, void *value)`: Adiciona um par chave-valor à árvore. Se a chave já existir, substitui o valor.
- `int binary_tree_empty(BinaryTree *bt)`: Verifica se a árvore está vazia.
- `void binary_tree_remove(BinaryTree *bt, void *key)`: Remove um nó da árvore com a chave fornecida.
- `KeyValPair binary_tree_min(BinaryTree *bt)`: Retorna o par chave-valor mínimo na árvore.
- `KeyValPair binary_tree_max(BinaryTree *bt)`: Retorna o par chave-valor máximo na árvore.
- `KeyValPair* binary_tree_pop_min(BinaryTree *bt)`: Remove e retorna o par chave-valor mínimo na árvore.
- `KeyValPair* binary_tree_pop_max(BinaryTree *bt)`: Remove e retorna o par chave-valor máximo na árvore.
- `void *binary_tree_get(BinaryTree *bt, void *key)`: Retorna o valor associado à chave fornecida na árvore.
- `void binary_tree_destroy(BinaryTree *bt)`: Destroi a árvore binária, liberando a memória alocada para ela e todos os seus nós.

## Utilização

1. Inclua o arquivo de cabeçalho `binary_tree.h` em seu código-fonte.
2. Crie uma árvore binária usando `binary_tree_construct`, fornecendo a função de comparação (`cmp_fn`) e as funções de destruição da chave e valor (opcionais).
3. Adicione pares chave-valor à árvore usando `binary_tree_add`.
4. Execute operações como remoção de nós, obtenção do mínimo ou máximo, ou obtenção de valores associados às chaves.
5. Libere a memória alocada para a árvore usando `binary_tree_destroy` quando não for mais necessária.

Certifique-se de fornecer as funções de comparação (`cmp_fn`) adequadas para garantir o correto funcionamento da árvore binária com os tipos de chave que você está usando.
