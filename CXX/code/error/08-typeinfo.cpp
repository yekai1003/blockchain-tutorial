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
    int num = 100;
    cout<< typeid(num).name()<<endl;
    Parent *p1 = new Parent("zhangsan");
    Child  *c1 = new Child("lisi", 30);

    cout<< typeid(*p1).name()<<endl;
    cout<< typeid(*c1).name()<<endl;
    p1 = dynamic_cast<Parent*> (c1);
    cout<< typeid(*p1).name()<<endl;
    cout<< typeid(Child).name()<<endl;
    return 0;
}
