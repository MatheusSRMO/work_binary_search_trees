#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"
#include "vector.h"
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

int main(void) {
    BinaryTree *bt = binary_tree_construct(int_cmp, int_destroy, person_destroy);

    int n, i, age, key;
    float height;
    char cmd[20], nome[20];
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("\n%s", cmd);

        if (!strcmp(cmd, "SET")) {
            scanf("%d %s %d %f", &key, nome, &age, &height);

            Person *person = person_construct(nome, age, height);
            int *_key = malloc(sizeof(int));
            *_key = key;
            binary_tree_add(bt, _key, person);
            
        }
        else if (!strcmp(cmd, "GET")) {
            scanf("%d", &key);

            Person *person = binary_tree_get(bt, &key);
            if (person == NULL) {
                printf("CHAVE INEXISTENTE \n");
            }
            else {
                person_print(person);
            }
        }

        else if (!strcmp(cmd, "POP")) {
            scanf("%d", &key);
            binary_tree_remove(bt, &key);
        }
    }

    binary_tree_destroy(bt);
    return 0;
}
