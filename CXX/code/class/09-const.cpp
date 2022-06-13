//
// const说明
//

#include <iostream>
using  namespace std;

class  Person
{
public:

    Person(const char *n, int a, char s):age(a)
    {
        name = n;
       // age = a;
        sex = s;
    }
    //const 放置在函数声明后，不能修改成员变量
    void setName(const char * n) const {
        //name = n;
        cout<<"name:"<<name<<",age:"<<age<<endl;
    }
private:
    string name;
    const  int age; //成员变量是const，必须初始化列表初始化
    char sex;
};

int main2()
{
    //1. 下面两种方法一样
    const int a = 120;
    int const b = 10;
    //2. 指向常整形数的指针：c的地址可以变，c地址对应的内容不能变
    const int *c = &a;
    //*c = 10;//不允许
    //c++;//允许
    //3. 常指针:d的地址不能改，但地址内容可以改
    int d3 = 10;
    int *const d = &d3;
    //*d = 20;//允许
    //d++;//不允许
    //4. 指向常整形的常指针：无论地址还是内容都不允许修改
    const int *const e = &a;
    return 0;
}

int main()
{
    Person p("yekai", 30, 'Y');
    p.setName("fuhongxue");
    return 0;
}