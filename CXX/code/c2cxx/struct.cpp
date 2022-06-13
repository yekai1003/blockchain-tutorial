//结构体使用
#include <iostream>
#include <stdio.h>

using  namespace std;

//全局区
struct  Person {
    char name[30]; //32字节
    unsigned int age;//8字节
    double sal;//8字节
};
//Person就是一个自定义的类型
//Person 实际是8字节对齐

int main()
{
    Person p1 = {"yekai", 30, 100000.00};
    cout<<p1.name<<","<<p1.age<<","<<p1.sal<<endl;
    //考虑字节对齐 sizeof
    cout<< sizeof(Person)<<endl;
//    cout<<&p1<<endl;
//    cout<<&p1.age<<endl;
    printf("age = %ld, p1 = %ld\n", &p1.age, &p1);
    return 0;
}

