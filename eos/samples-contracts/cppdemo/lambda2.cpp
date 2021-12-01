#include <iostream>

using namespace std;

struct Person {
    string name;
    uint age;
    Person & init(string n, uint age) {
        this->name = n;
        this->age = age;
        return *this;
    }
};

int main()
{
    Person p ;
    p.init("yekai", 30);
    cout<<p.name<<":"<<p.age<<endl;
    [=] () mutable  { p.name = "zhangsan";  }(); 
    
    cout<<p.name<<":"<<p.age<<endl;
    return 0;
}