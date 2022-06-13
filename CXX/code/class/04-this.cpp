//类的构造函数
#include <iostream>
using namespace std;

class  Person
{
public:

    Person(const char *name, int age, char sex)
    {
        //区分不明显
        this->name = name;
        this->age = age;
        this->sex = sex;
    }
    //初始化列表
    //与成员变量顺序、参数定义顺序无关
    Person(const char *n, char s) :sex(s),name(n),age(30)
    {
//        this->name = n;
//        this->age = 30;
//        this->sex = s;
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
    Person p1("yekai", 'Y');
    p1.show();
    return 0;
}



