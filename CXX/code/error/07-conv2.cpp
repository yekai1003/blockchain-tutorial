//
// 类型转换
//
#include <iostream>

using  namespace std;

class Parent
{
private:
    string name;
public:
    Parent(string n) :name(n) {}
    virtual  void show() {
        cout<<"parent:"<<name<<endl;
    }
    string &getName() {
        return name;
    }
};

class Child : public  Parent
{
private:
    int age;
public:
    Child(string n, int a) :Parent(n), age(a) {}
    virtual  void show() {
//        cout<<"Child:";
//        Parent::show();
        cout<<"Child:"<<getName()<<endl;
    }
    void showAge() {
        cout<<age<<endl;
    }

};

int main()
{
    int num = 10;
    double dnum  = static_cast<double > (num);
    cout<<dnum<<endl;
    Parent p1("zhangsan");
    Child  c1("lisi", 30);

//    Parent *pc = static_cast<Parent *> (&c1);
//    pc->show();
//    //Child *pp = &p1;
//    Child *pp = static_cast<Child *>(&p1); //不推荐，不鼓励，推荐使用动态转换方式
//    pp->show();
//    pp->showAge();
    //使用动态转换
    Parent *pc = dynamic_cast<Parent *> (&c1); //派生类转换为基类
    pc->show();
    Child  *pp = dynamic_cast<Child *> (&p1); // pp将成为一个NULL指针
    cout<<pp<<endl;
    pp->show();


    return 0;
}