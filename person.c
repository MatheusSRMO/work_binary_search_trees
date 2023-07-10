#include "person.h"

Person *person_construct(char *name, int age, float height) {
    Person *person = malloc(sizeof(Person));
    person->name = malloc(strlen(name) + 1);
    strcpy(person->name, name);
    person->age = age;
    person->height = height;
    return person;
}

void person_print(Person *person) {
    printf("%s %d %.2f\n", person->name, person->age, person->height);
}

void person_destroy(void *person) {
    Person *person_ = (Person *)person;
    free(person_->name);
    free(person_);
}
