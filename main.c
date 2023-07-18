#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ed/binary_tree.h"
#include "ed/vector.h"
#include "person.h"


int int_cmp(void *key1, void *key2) {
    int *i1 = (int *)key1;
    int *i2 = (int *)key2;
    return *i1 - *i2;
}

void int_destroy(void *key) {
    int *i = (int *)key;
    free(i);
}

void name_destroy(void *key) {
    char* name = (char*)key;
    if(name != NULL) free(name);
}

int main(void) {
    BinaryTree *bt = binary_tree_construct(person_cmp, name_destroy, person_destroy);

    int n, i, age;
    float height;
    char cmd[20], nome[20];
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("\n%s", cmd);

        if (!strcmp(cmd, "SET")) {
            scanf("%s %d %f", nome, &age, &height);

            Person *person = person_construct(nome, age, height);

            char* name = malloc(strlen(nome) + 1);
            strcpy(name, nome);

            binary_tree_add(bt, name, person);
            
        }
        else if (!strcmp(cmd, "GET")) {
            scanf("%s", nome);

            Person *person = binary_tree_get(bt, nome);
            if (person == NULL) {
                printf("CHAVE INEXISTENTE \n");
            }
            else {
                person_print(person);
            }
        }

        else if (!strcmp(cmd, "POP")) {
            scanf("%s", nome);
            binary_tree_remove(bt, nome);
        }

        else if (!strcmp(cmd, "MIN")) {
            KeyValPair key_val_par_min = binary_tree_min(bt);
            Person* person_min = key_val_par_min.value;
            person_print(person_min);
        }

        else if (!strcmp(cmd, "MAX")) {
            KeyValPair key_val_par_max = binary_tree_max(bt);
            Person* person_max = key_val_par_max.value;
            person_print(person_max);
        }

        else if (!strcmp(cmd, "POP_MIN")) {
            KeyValPair* key_val_par_popped_min = binary_tree_pop_min(bt);
            if(key_val_par_popped_min != NULL) {
                Person* person_min = key_val_par_popped_min->value;
                person_print(person_min);
                key_val_pair_destroy(key_val_par_popped_min, name_destroy, person_destroy);
            }
            else {
                printf("ARVORE VAZIA\n");
            }
        }

        else if (!strcmp(cmd, "POP_MAX")) {
            KeyValPair* key_val_par_popped_max = binary_tree_pop_max(bt);
            if(key_val_par_popped_max != NULL) {
                Person* person_max = key_val_par_popped_max->value;
                person_print(person_max);
                key_val_pair_destroy(key_val_par_popped_max, name_destroy, person_destroy);
            }
            else {
                printf("ARVORE VAZIA\n");
            }
        }
    }

    Vector* inorder_traversal_iterative = binary_tree_postorder_traversal_recursive(bt);
    
    while(vector_size(inorder_traversal_iterative) > 0) {
        Node* current = vector_pop_front(inorder_traversal_iterative);
        KeyValPair *kay_val_pair = current->key_val_pair;
        Person* current_person = kay_val_pair->value;
        person_print(current_person);
    }

    vector_destroy(inorder_traversal_iterative);

    binary_tree_destroy(bt);
    return 0;
}
