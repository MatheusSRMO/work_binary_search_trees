#include <stdlib.h>
#include "vector.h"


Vector *vector_construct() {
    Vector* v = malloc(sizeof(Vector));
    v->size = 0;
    v->allocated = 10;
    v->data = malloc(sizeof(data_type)*10);
    return v;
}

void vector_destroy(Vector *v) {
    free(v->data);
    free(v);
}

void vector_push_back(Vector *v, data_type val) {
    if(v->size == v->allocated) {
        v->allocated *= 2;
        v->data = realloc(v->data, v->allocated * sizeof(data_type));
    }
    v->data[v->size] = val;
    v->size++;
}

data_type vector_get(Vector *v, int i) {
    return v->data[i];
}
void vector_set(Vector *v, int i, data_type val) {
    v->data[i] = val;
}

int vector_size(Vector *v) {
    return v->size;
}

int vector_find(Vector *v, data_type val) {
    int find = -1;
    for(int i = 0; i < vector_size(v); i++) {
        if(v->data[i] == val) return i;
    }
    return find;
}


// Remove o i-ésimo elemento do vetor.
data_type vector_remove(Vector *v, int i) {
    data_type val = v->data[i];
    for(int j = i; j < v->size - 1; j++) {
        v->data[j] = v->data[j+1];
    }
    v->size--;
    return val;
}


// Remove o primeiro elemento
data_type vector_pop_front(Vector *v) {
    return vector_remove(v, 0);
}

// Remove o ultimo elemento
data_type vector_pop_back(Vector *v) {
    return vector_remove(v, v->size - 1);
}


// Insere o elemento na i-esima posicao
void vector_insert(Vector *v, int i, data_type val) {
    if(v->size == v->allocated) {
        v->allocated *= 2;
        v->data = realloc(v->data, v->allocated * sizeof(data_type));
    }
    for(int j = v->size; j > i; j--) {
        v->data[j] = v->data[j-1];
    }
    v->data[i] = val;
    v->size++;
}

// Troca os elementos das posições i e j (i vira j e j vira i)
void vector_swap(Vector *v, int i, int j) {
    data_type aux = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = aux;
}

// Ordena o vetor in-place (sem criar um novo vetor)
void vector_sort(Vector *v) {
    for(int i = 0; i < v->size; i++) {
        for(int j = i + 1; j < v->size; j++) {
            if(v->data[i] > v->data[j]) {
                vector_swap(v, i, j);
            }
        }
    }
}

// Retorna o indice de val usando busca binaria. Retorna -1 se nao encontrado.
int vector_binary_search(Vector *v, data_type val) {
    int left = 0;
    int right = v->size - 1;
    int mid;
    while(left <= right) {
        mid = (left + right)/2;
        if(v->data[mid] == val) return mid;
        else if(v->data[mid] < val) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Inverte o vetor in-place (sem criar um novo vetor)
void vector_reverse(Vector *v) {
    for(int i = 0; i < v->size/2; i++) {
        vector_swap(v, i, v->size - i - 1);
    }
}

// Cria uma cópia do vector e dos valores de seus atributos.
Vector *vector_copy(Vector *v) {
    Vector* v2 = malloc(sizeof(Vector));
    v2->size = v->size;
    v2->allocated = v->allocated;
    v2->data = malloc(sizeof(data_type)*v->allocated);
    for(int i = 0; i < v->size; i++) {
        v2->data[i] = v->data[i];
    }
    return v2;
}

// Remove todos os elementos de v
void vector_clear(Vector *v) {
    free(v->data);
    free(v);
}
