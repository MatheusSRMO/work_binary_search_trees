#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"
#include "vector.h"
#include "person.h"

typedef struct {
    int x;
    int y;
} Point;

Point* point_construct(int x, int y) {
    Point *p = (Point *)malloc(sizeof(Point));
    p->x = x;
    p->y = y;
    return p;
}

void point_destroy(void *key) {
    Point *p = (Point *)key;
    free(p);
}

int point_cmp(void *key1, void *key2) {
    Point *p1 = (Point *)key1;
    Point *p2 = (Point *)key2;
    if(p1->x == p2->x && p1->y == p2->y) {
        return 0;
    }
    else if(p1->x < p2->x || (p1->x == p2->x && p1->y < p2->y)) {
        return -1;
    }
    else {
        return 1;
    }
}

void int_destroy(void *key) {
    int *i = (int *)key;
    free(i);
}

int main(void) {
    BinaryTree *bt = binary_tree_construct(point_cmp, point_destroy, int_destroy);

    int n, i, x, y, val;
    float height;
    char cmd[20], nome[20];
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("\n%s", cmd);

        if (!strcmp(cmd, "SET")) {
            scanf("%d %d %d", &x, &y, &val);

            Point *key = point_construct(x, y);
            int *value = (int *)malloc(sizeof(int));
            *value = val;
            binary_tree_add(bt, key, value);
        }
        else if (!strcmp(cmd, "GET")) {
            scanf("%d %d", &x, &y);

            Point *key = point_construct(x, y);
            int *val = binary_tree_get(bt, key);
            if (val == NULL) {
                printf("Chave nao encontrada\n");
            }
            else {
                printf("%d\n", *val);
            }
            point_destroy(key);
        }
    }

    binary_tree_destroy(bt);
    return 0;
}
