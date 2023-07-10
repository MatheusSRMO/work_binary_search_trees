#include "person.h"

Person *person_construct(char *name, int age, float height) {
    Person *person = malloc(sizeof(Person));
    person->name = malloc(strlen(name) + 1);
    strcpy(person->name, name);
    person->age = age;
    person->height = height;
    return person;
}

int person_cmp(void* a, void* b) {
    char* nome_a = a;
    char* nome_b = b;
    return strcmp(nome_a, nome_b);
}

void person_print(Person *person) {
    printf("%s %d %.2f\n", person->name, person->age, person->height);
}

void person_destroy(void *person) {
    Person *person_ = (Person *)person;
    if(person_ == NULL) return;
    
    if(person_->name != NULL)
        free(person_->name);
    free(person_);
}
