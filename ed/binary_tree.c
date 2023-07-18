#include "binary_tree.h"

// Constroi um par chave-valor
KeyValPair *key_val_pair_construct(void *key, void *val) {
    KeyValPair *key_val_pair = malloc(sizeof(KeyValPair));
    key_val_pair->key = key;
    key_val_pair->value = val;
    return key_val_pair;
}

void key_val_pair_destroy(KeyValPair *kvp, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn) {
    if (kvp == NULL) return;
    if (key_destroy_fn != NULL) key_destroy_fn(kvp->key);
    if (val_destroy_fn != NULL) val_destroy_fn(kvp->value);
    free(kvp);
}

Node *node_construct(void *key, void *value, Node *left, Node *right) {
    Node *node = malloc(sizeof(Node));
    node->key_val_pair = key_val_pair_construct(key, value);
    node->left = left;
    node->right = right;
    return node;
}

void node_destroy(Node *node, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn) {
    if (node == NULL) return;
    node_destroy(node->left, key_destroy_fn, val_destroy_fn);
    node_destroy(node->right, key_destroy_fn, val_destroy_fn);
    key_val_pair_destroy(node->key_val_pair, key_destroy_fn, val_destroy_fn);
    free(node);
}

// Constroi uma arvore binaria
BinaryTree *binary_tree_construct(CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn) {
    BinaryTree *binary_tree = malloc(sizeof(BinaryTree));
    binary_tree->root = NULL;
    binary_tree->cmp_fn = cmp_fn;
    binary_tree->key_destroy_fn = key_destroy_fn;
    binary_tree->val_destroy_fn = val_destroy_fn;
    return binary_tree;
}

// Adiciona um par chave-valor na arvore, se ja existir, substitui o valor
void binary_tree_add(BinaryTree *bt, void *key, void *value) {
    Node *current = bt->root;
    Node *parent = NULL;
    while (current != NULL) {
        if (bt->cmp_fn(key, current->key_val_pair->key) == 0) {
            key_val_pair_destroy(current->key_val_pair, bt->key_destroy_fn, bt->val_destroy_fn);
            current->key_val_pair = key_val_pair_construct(key, value);
            return;
        }
        parent = current;
        if (bt->cmp_fn(key, current->key_val_pair->key) < 0) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    Node *new_node = node_construct(key, value, NULL, NULL);
    if (parent == NULL) {
        bt->root = new_node;
    }
    else if (bt->cmp_fn(key, parent->key_val_pair->key) < 0) {
        parent->left = new_node;
    }
    else {
        parent->right = new_node;
    }
}

int binary_tree_empty(BinaryTree *bt) {
    return bt->root == NULL;
}

void binary_tree_remove(BinaryTree *bt, void *key) {
    Node *current = bt->root;
    Node *parent = NULL;
    while (current != NULL) {
        if (bt->cmp_fn(key, current->key_val_pair->key) == 0) {
            break;
        }
        parent = current;
        if (bt->cmp_fn(key, current->key_val_pair->key) < 0) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    // não encontrou
    if (current == NULL) {
        return;
    }
    // Caso 1: Se z não tem nenhum filho, então simplesmente o removemos modificando seu pai de modo a substituir z por NULL como seu filho.
    if (current->left == NULL && current->right == NULL) {
        if (parent == NULL) {
            bt->root = NULL;
        }
        else if (parent->left == current) {
            parent->left = NULL;
        }
        else {
            parent->right = NULL;
        }
        key_val_pair_destroy(current->key_val_pair, bt->key_destroy_fn, bt->val_destroy_fn);
        free(current);
    }
    else if (current->left == NULL) {
        if (parent == NULL) {
            bt->root = current->right;
        }
        else if (parent->left == current) {
            parent->left = current->right;
        }
        else {
            parent->right = current->right;
        }
        key_val_pair_destroy(current->key_val_pair, bt->key_destroy_fn, bt->val_destroy_fn);
        free(current);
    }
    else if (current->right == NULL) {
        if (parent == NULL) {
            bt->root = current->left;
        }
        else if (parent->left == current) {
            parent->left = current->left;
        }
        else {
            parent->right = current->left;
        }
        key_val_pair_destroy(current->key_val_pair, bt->key_destroy_fn, bt->val_destroy_fn);
        free(current);
    }
    else {
        Node *successor = current->right;
        Node *successor_parent = current;
        while (successor->left != NULL) {
            successor_parent = successor;
            successor = successor->left;
        }
        if (successor_parent->left == successor) {
            successor_parent->left = successor->right;
        }
        else {
            successor_parent->right = successor->right;
        }
        current->key_val_pair = successor->key_val_pair;
        node_destroy(successor, bt->key_destroy_fn, bt->val_destroy_fn);
    }
}

KeyValPair binary_tree_min(BinaryTree *bt) {
    Node *current = bt->root;
    while (current->left != NULL) {
        current = current->left;
    }
    return *current->key_val_pair;
}

KeyValPair binary_tree_max(BinaryTree *bt) {
    Node *current = bt->root;
    while (current->right != NULL) {
        current = current->right;
    }
    return *current->key_val_pair;
}

KeyValPair* binary_tree_pop_min(BinaryTree *bt) {
    if(bt->root == NULL) {
        return NULL;
    }
    Node *current = bt->root;
    Node *parent = NULL;
    while (current->left != NULL) {
        parent = current;
        current = current->left;
    }
    KeyValPair* kvp = current->key_val_pair;
    if (parent == NULL) {
        bt->root = current->right;
    }
    else {
        parent->left = current->right;
    }

    free(current);
    
    return kvp;
}

KeyValPair* binary_tree_pop_max(BinaryTree *bt) {
    if(bt->root == NULL) {
        return NULL;
    }
    Node *current = bt->root;
    Node *parent = NULL;
    while (current->right != NULL) {
        parent = current;
        current = current->right;
    }
    
    KeyValPair* kvp = current->key_val_pair;
    if (parent == NULL) {
        bt->root = current->left;
    }
    else {
        parent->right = current->left;
    }

    free(current);

    return kvp;
}

void *binary_tree_get(BinaryTree *bt, void *key) {
    Node *current = bt->root;
    while (current != NULL) {
        if (bt->cmp_fn(key, current->key_val_pair->key) == 0) {
            return current->key_val_pair->value;
        }
        else if (bt->cmp_fn(key, current->key_val_pair->key) < 0) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return NULL;
}

void binary_tree_destroy(BinaryTree *bt) {
    node_destroy(bt->root, bt->key_destroy_fn, bt->val_destroy_fn);
    free(bt);
}

Vector *binary_tree_inorder_traversal(BinaryTree *bt) {
    Vector* out_vec = vector_construct();

    // Cria uma pilha
    Stack* stack = stack_construct();

    // Defina o no atual como a raiz
    Node* current = bt->root;

    // enquanto não terminar
    while(1) {
        // Enquanto o no atual não for nulo:
        while(current != NULL) {
            // Adicione o nó na pilha
            stack_push(stack, current);
            // Faça o nó ser o da esquerda
            current = current->left;
        }

        // Se a pilha estiver vazia:
        if(stack_empty(stack)) {
            // Defina que o processo terminou
            break;
        }
        // Caso contrário:
        else {
            // Remova um nó da pilha
            Node* popped = stack_pop(stack);
            // Adicione o nó na saída
            vector_push_back(out_vec, popped);
            // Faça o nó atual ser o da direita
            current = popped->right;
        }
    }
    stack_destroy(stack);

    return out_vec;
}

Vector *binary_tree_preorder_traversal(BinaryTree *bt) {
    Vector* out_vec = vector_construct();

    // Cria uma pilha
    Stack* stack = stack_construct();

    // Adicione o nó raiz na pilha
    stack_push(stack, bt->root);

    // Enquanto a pilha não estiver vazia:
    while(!stack_empty(stack)) {
        // Retire um item da pilha
        Node* popped = stack_pop(stack);
        // Adicione o item na saída
        vector_push_back(out_vec, popped);

        if(popped->right != NULL) {
            stack_push(stack, popped->right);
        }
        if(popped->left != NULL) {
            stack_push(stack, popped->left);
        }
    }
    stack_destroy(stack);

    return out_vec;
}

Vector *binary_tree_postorder_traversal(BinaryTree *bt) {
    Vector* out_vec = vector_construct();

    /*
        Crie duas pilhas Q1 e Q2
        Adicione a raiz em Q1
        Enquanto Q1 não estiver vazia
            Remova um nó de Q1
            Adicione o esquerdo em Q1
            Adicione o direito em Q1
            Adicione o nó em Q2
        Adicione os itens de Q2 na saída
    */

    // Cria duas pilhas Q1 e Q2
    Stack* q1 = stack_construct();
    Stack* q2 = stack_construct();

    // Adicione a raiz em Q1
    stack_push(q1, bt->root);

    // Enquanto Q1 não estiver vazia
    while(!stack_empty(q1)) {
        // Remova um nó de Q1
        Node* popped = stack_pop(q1);
        // Adicione o esquerdo em Q1
        if(popped->left != NULL) {
            stack_push(q1, popped->left);
        }
        // Adicione o direito em Q1
        if(popped->right != NULL) {
            stack_push(q1, popped->right);
        }
        // Adicione o nó em Q2
        stack_push(q2, popped);
    }

    // Adicione os itens de Q2 na saída
    while(!stack_empty(q2)) {
        Node* popped = stack_pop(q2);
        vector_push_back(out_vec, popped);
    }

    stack_destroy(q1);
    stack_destroy(q2);

    return out_vec;
}

Vector *binary_tree_levelorder_traversal(BinaryTree *bt) {
    /*
    crie uma fila
    adicione a raiz na fila
    enquanto a fila não estiver vazia:
        remove um nó da fila
        se o nó não for nulo:
            adicione o nó na saída
            adicione o esquerdo na fila
            adicione o direito na fila
    */
    Vector* out_vec = vector_construct();

    // Cria uma fila
    CircularArray* queue = circular_array_construct(10, true);

    // Adicione a raiz na fila
    circular_array_push(queue, bt->root);

    // enquanto a fila não estiver vazia:
    while(!circular_array_is_empty(queue)) {
        // remove um nó da fila
        Node* popped = circular_array_pop(queue);
        // se o nó não for nulo:
        if(popped != NULL) {
            // adicione o nó na saída
            vector_push_back(out_vec, popped);
            // adicione o esquerdo na fila
            circular_array_push(queue, popped->left);
            // adicione o direito na fila
            circular_array_push(queue, popped->right);
        }
    }

    circular_array_destruct(queue);

    return out_vec;
}

static void inorder_recursive(Node* current, Vector* out_vec) {

    /*
    inorder(node)
    begin
        if node is null, return;
        inorder(node.left);
        print(tree.root);
        inorder(node.right);
    end
    */

    // Se o nó atual for nulo:
    if(current == NULL) {
        // Termine
        return;
    }
    // Chame a função recursiva para o nó da esquerda
    inorder_recursive(current->left, out_vec);
    // Adicione o nó atual na saída
    vector_push_back(out_vec, current);
    // Chame a função recursiva para o nó da direita
    inorder_recursive(current->right, out_vec);
}

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt) {
    Vector* out_vec = vector_construct();

    // Chame a função recursiva
    inorder_recursive(bt->root, out_vec);

    return out_vec;
}

static void preorder_recursive(Node* current, Vector* out_vec) {

    /*
    preorder(node)
    begin
        if node is null, return;
        print(tree.root);
        preorder(node.left);
        preorder(node.right);
    end
    */

    // Se o nó atual for nulo:
    if(current == NULL) {
        // Termine
        return;
    }
    // Adicione o nó atual na saída
    vector_push_back(out_vec, current);
    // Chame a função recursiva para o nó da esquerda
    preorder_recursive(current->left, out_vec);
    // Chame a função recursiva para o nó da direita
    preorder_recursive(current->right, out_vec);
}

Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt) {
    Vector* out_vec = vector_construct();

    // Chame a função recursiva
    preorder_recursive(bt->root, out_vec);

    return out_vec;
}

static void postorder_recursive(Node* current, Vector* out_vec) {

    /*
    postorder(node)
    begin
        if node is null, return;
        postorder(node.left);
        postorder(node.right);
        print(tree.root);
    end
    */

    // Se o nó atual for nulo:
    if(current == NULL) {
        // Termine
        return;
    }
    // Chame a função recursiva para o nó da esquerda
    postorder_recursive(current->left, out_vec);
    // Chame a função recursiva para o nó da direita
    postorder_recursive(current->right, out_vec);
    // Adicione o nó atual na saída
    vector_push_back(out_vec, current);
}

Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt) {
    Vector* out_vec = vector_construct();

    // Chame a função recursiva
    postorder_recursive(bt->root, out_vec);

    return out_vec;
}
