#include "binary_tree.h"

// Constroi um par chave-valor
KeyValPair *key_val_pair_construct(void *key, void *val) {
    KeyValPair *key_val_pair = malloc(sizeof(KeyValPair));
    key_val_pair->key = key;
    key_val_pair->value = val;
    return key_val_pair;
}

void key_val_pair_destroy(KeyValPair *kvp) {
    free(kvp);
}

Node *node_construct(void *key, void *value, Node *left, Node *right) {
    Node *node = malloc(sizeof(Node));
    node->key_val_pair = key_val_pair_construct(key, value);
    node->left = left;
    node->right = right;
    return node;
}

void node_destroy(Node *node) {
    if (node == NULL) return;
    node_destroy(node->left);
    node_destroy(node->right);
    key_val_pair_destroy(node->key_val_pair);
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

// Adiciona um par chave-valor na arvore
void binary_tree_add(BinaryTree *bt, void *key, void *value) {
    Node *node = node_construct(key, value, NULL, NULL);
    if (bt->root == NULL) {
        bt->root = node;
        return;
    }
    Node *current = bt->root;
    while (1) {
        if (bt->cmp_fn(key, current->key_val_pair->key) < 0) {
            if (current->left == NULL) {
                current->left = node;
                return;
            }
            current = current->left;
        }
        else {
            if (current->right == NULL) {
                current->right = node;
                return;
            }
            current = current->right;
        }
    }
}

int binary_tree_empty(BinaryTree *bt) {
    return bt->root == NULL;
}

void binary_tree_remove(BinaryTree *bt, void *key) {

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
    Node *current = bt->root;
    Node *parent = NULL;
    while (current->left != NULL) {
        parent = current;
        current = current->left;
    }
    KeyValPair *kvp = current->key_val_pair;
    if (parent == NULL) {
        bt->root = current->right;
    }
    else {
        parent->left = current->right;
    }
    node_destroy(current);
    return kvp;
}

KeyValPair* binary_tree_pop_min(BinaryTree *bt) {
    Node *current = bt->root;
    Node *parent = NULL;
    while (current->right != NULL) {
        parent = current;
        current = current->right;
    }
    KeyValPair *kvp = current->key_val_pair;
    if (parent == NULL) {
        bt->root = current->left;
    }
    else {
        parent->right = current->left;
    }
    node_destroy(current);
    return kvp;
}

KeyValPair* binary_tree_pop_max(BinaryTree *bt) {
    Node *current = bt->root;
    Node *parent = NULL;
    while (current->right != NULL) {
        parent = current;
        current = current->right;
    }
    KeyValPair *kvp = current->key_val_pair;
    if (parent == NULL) {
        bt->root = current->left;
    }
    else {
        parent->right = current->left;
    }
    node_destroy(current);
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
    node_destroy(bt->root);
    free(bt);
}
