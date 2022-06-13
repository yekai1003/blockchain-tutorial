//#ifndef C__BASE_PERSON_H
//#define C__BASE_PERSON_H

#include <iostream>

extern  int zhangsan ; //外部引用

const int zhangsan_age = 100;

struct  Person {
    std::string name;
    int age;
    char sex;
};

void setPerson(Person *p);

//#endif