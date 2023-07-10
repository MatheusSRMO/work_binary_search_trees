#ifndef _PERSON_H_
#define _PERSON_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *name;
    int age;
    int height;
} Person;

Person *person_construct(char *name, int age, int height);

void person_print(Person *person);

void person_destroy(Person *person);

#endif // _PERSON_H_