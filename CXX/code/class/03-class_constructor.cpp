//类的构造函数
#include <iostream>
using namespace std;

class  Person
{
public:

    Person(const char *n, int a, char s)
    {
        name = n;
        age = a;
        sex = s;
    }
    Person(const char *n, char s)
    {
        name = n;
        age = 30;
        sex = s;
    }
    Person(const char *n)
    {
        name = n;
        age = 30;
        sex = 'Y';
    }
    Person()
    {
        name = "无名氏";
        age = -1;
        sex = 'Y';
    }
    ~Person();
    const char *getName()
    {
        return  name.c_str();
    }
    void show()
    {
        cout<<"name:"<<name<<",age:"<<age<<",sex:"<<sex<<endl;
    }
private:
    string name;
    int age;
    char sex;
};

Person::~Person()
{
    cout<<"~Person() is called"<<endl;
}

int main()
{
    Person p1; //调用了哪个构造函数？
    p1.show();
    Person p2("yekai", 100, 'N');
    p2.show();
    Person *p3 = new Person();
    p3->show();
    delete  p3;//显示调用析构
    return 0;
}



