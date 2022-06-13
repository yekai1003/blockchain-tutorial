//
// 多态演示
//
//类的继承
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
    //虚函数，类会存在一个虚函数表记录这2个函数地址
    virtual void show_name() {
        cout<<"name:"<<name<<endl;
    }
    virtual void show_all() {
        cout<<"name:"<<name<<",age:"<<age<<",sex:"<<sex<<endl;
    }
private:
    string name;
    int age;
    char sex;
};

//SuperMan is Person ,公有继承
class SuperMan :public Person {
private:
    int fight;
    string ability;//超能力
public:
    SuperMan(const char *n, int a, char s, int f, string ab):Person(n,a,s),fight(f) {
        //name = n; //不允许
        //fight = f;
        ability = ab;
    }
    //show_all覆盖基类的方法，虚函数表地址会变化
    virtual void show_all() {
        Person::show_all();
        cout<<",fight:"<<fight<<",ability:"<<ability<<endl;
    }
    void fighting() {
        cout<<"begin fighting"<<endl;
    }
};

int main()
{
    SuperMan s1("yekai", 30, 'Y', 10000, "sleep");
    s1.show_name();
    s1.show_all();
    s1.fighting();
    cout<<"---------"<<endl;
    Person *p = &s1; // 基类指向派生类对象
    p->show_all(); //多态
    p->show_name();
    return 0;
}