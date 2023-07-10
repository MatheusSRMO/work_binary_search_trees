
#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include "person.h"
#include "vector.h"
#include "stack.h"

typedef int (*CmpFn)(void *, void *);
typedef void (*KeyDestroyFn)(void *);
typedef void (*ValDestroyFn)(void *);

typedef struct {
    void *key;
    void *value;
} KeyValPair;

typedef struct Node {
    KeyValPair* key_val_pair;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    Node *root;
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy_fn;
    ValDestroyFn val_destroy_fn;
} BinaryTree;

/// @brief  Cria um par chave-valor
/// @param key 
/// @param val 
/// @return KeyValPair*
KeyValPair *key_val_pair_construct(void *key, void *val);

/// @brief  Destroi um par chave-valor
/// @param kvp  Par chave-valor
/// @return void
void key_val_pair_destroy(KeyValPair *kvp, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn);

/// @brief Cria um no
/// @param key Chave
/// @param value Valor
/// @param left no esquerdo 
/// @param right no direito
/// @return Node*
Node *node_construct(void *key, void *value, Node *left, Node *right);

/// @brief  Destroi um no
/// @param node No
/// @return void
void node_destroy(Node *node, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn);

/// @brief Cria uma arvore binaria
/// @param cmp_fn Funcao de comparacao
/// @param key_destroy_fn Funcao de destruicao da chave
/// @param val_destroy_fn Funcao de destruicao do valor
/// @return BinaryTree*
BinaryTree *binary_tree_construct(CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn);

/// @brief  Adiciona um nó à árvore
/// @param bt Arvore binaria
/// @param key Chave
/// @param value Valor
/// @return void
void binary_tree_add(BinaryTree *bt, void *key, void *value);

/// @brief  Adiciona um nó à árvore de forma recursiva
/// @param bt Arvore binaria
/// @param key Chave
/// @param value Valor
/// @return void
void binary_tree_add_recursive(BinaryTree *bt, void *key, void *value);

/// @brief  Verifica se a árvore está vazia
/// @param bt Arvore binaria
/// @return int Retorna 1 se a árvore estiver vazia, caso contrário retorna 0
int binary_tree_empty(BinaryTree *bt);

/// @brief  Remove um nó da árvore
/// @param bt Arvore binaria
/// @param key Chave do nó a ser removido
/// @return void
void binary_tree_remove(BinaryTree *bt, void *key);

/// @brief  Retorna o par chave-valor mínimo da árvore
/// @param bt Arvore binaria
/// @return KeyValPair Retorna o par chave-valor mínimo
KeyValPair binary_tree_min(BinaryTree *bt);

/// @brief  Retorna o par chave-valor máximo da árvore
/// @param bt Arvore binaria
/// @return KeyValPair Retorna o par chave-valor máximo
KeyValPair binary_tree_max(BinaryTree *bt);

/// @brief  Remove e retorna o par chave-valor mínimo da árvore
/// @param bt Arvore binaria
/// @return KeyValPair Retorna o par chave-valor mínimo removido
KeyValPair* binary_tree_pop_min(BinaryTree *bt);

/// @brief  Remove e retorna o par chave-valor máximo da árvore
/// @param bt Arvore binaria
/// @return KeyValPair Retorna o par chave-valor máximo removido
KeyValPair* binary_tree_pop_max(BinaryTree *bt);

/// @brief  Retorna o valor associado à chave especificada
/// @param bt Arvore binaria
/// @param key Chave
/// @return void* Retorna o valor associado à chave, ou NULL se a chave não existir na árvore
void *binary_tree_get(BinaryTree *bt, void *key);

/// @brief  Destroi a árvore binaria
/// @param bt Arvore binaria
/// @return void
void binary_tree_destroy(BinaryTree *bt);

/// @brief  Realiza uma travessia inorder na árvore e retorna um vetor com os pares chave-valor na ordem
/// @param bt Arvore binaria
/// @return Vector* Vetor contendo os pares chave-valor na ordem da travessia inorder
Vector *binary_tree_inorder_traversal(BinaryTree *bt);

/// @brief  Realiza uma travessia preorder na árvore e retorna um vetor com os pares chave-valor na ordem
/// @param bt Arvore binaria
/// @return Vector* Vetor contendo os pares chave-valor na ordem da travessia preorder
Vector *binary_tree_preorder_traversal(BinaryTree *bt);

/// @brief  Realiza uma travessia postorder na árvore e retorna um vetor com os pares chave-valor na ordem
/// @param bt Arvore binaria
/// @return Vector* Vetor contendo os pares chave-valor na ordem da travessia postorder
Vector *binary_tree_postorder_traversal(BinaryTree *bt);

/// @brief  Realiza uma travessia levelorder na árvore e retorna um vetor com os pares chave-valor na ordem
/// @param bt Arvore binaria
/// @return Vector* Vetor contendo os pares chave-valor na ordem da travessia levelorder
Vector *binary_tree_levelorder_traversal(BinaryTree *bt);

/// @brief  Realiza uma travessia inorder recursiva na árvore e retorna um vetor com os pares chave-valor na ordem
/// @param bt Arvore binaria
/// @return Vector* Vetor contendo os pares chave-valor na ordem da travessia inorder recursiva
Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt);

/// @brief  Realiza uma travessia preorder recursiva na árvore e retorna um vetor com os pares chave-valor na ordem
/// @param bt Arvore binaria
/// @return Vector* Vetor contendo os pares chave-valor na ordem da travessia preorder recursiva
Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt);

/// @brief  Realiza uma travessia postorder recursiva na árvore e retorna um vetor com os pares chave-valor na ordem
/// @param bt Arvore binaria
/// @return Vector* Vetor contendo os pares chave-valor na ordem da travessia postorder recursiva
Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt);

#endif
