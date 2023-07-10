#ifndef _PERSON_H_
#define _PERSON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int age;
    float height;
} Person;

Person *person_construct(char *name, int age, float height);

int person_cmp(void* a, void* b);

void person_print(Person *person);

void person_destroy(void* person);

#endif // _PERSON_H_