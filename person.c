#include "person.h"

Person *person_construct(char *name, int age, int height) {
    Person *person = malloc(sizeof(Person));
    person->name = malloc(strlen(name) + 1);
    strcpy(person->name, name);
    person->age = age;
    person->height = height;
    return person;
}

void person_print(Person *person) {
    printf("%s %d %d\n", person->name, person->age, person->height);
}

void person_destroy(Person *person) {
    free(person->name);
    free(person);
}
