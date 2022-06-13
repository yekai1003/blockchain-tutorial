//
// Created by yekai on 2020-10-29.
//
#include <iostream>
using  namespace std;

//设置一个同龄人的类
class  Person
{
public:

    Person(const char *n, int a, char s)
    {
        name = n;
        age = a;
        sex = s;
    }
    //const 放置在函数声明后，不能修改成员变量
    void setName(const char * n) const {
        //name = n;
        cout<<"name:"<<name<<",age:"<<age<<endl;
    }
    static  int getAge() {
        return age;
    }
    static void setAge(int a) {
        age = a;
    }
private:
    string name;
    static int age; //同龄人
    char sex;
};

//必须类外初始化
int Person::age  = 10;


int main()
{
    Person p1("yekai", 30, 'Y');
    cout<<p1.getAge()<<endl;
    Person p2("fu", 35, 'Y');
    p2.setAge(100);
    Person::setAge(300);
    cout<<p1.getAge()<<endl;
    cout<<p2.getAge()<<endl;
    return 0;
}

