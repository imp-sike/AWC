#include<stdio.h>

struct Person {
    int age;
    void (*set)(struct Person*, int);
    int (*get)(struct Person*);
};

void setAge(struct Person* instance, int age) {
    instance->age = age;
}

int getAge(struct Person* instance) {
    return instance->age;
}

int main() {
    struct Person p1;
    p1.set = setAge;
    p1.get = getAge;

    p1.set(&p1,18);
    printf("The age is: %d", p1.get(&p1));
    return 0;
}