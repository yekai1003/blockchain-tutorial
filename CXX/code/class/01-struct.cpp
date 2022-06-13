//再次讨论struct
#include <iostream>
using namespace std;

struct  Person
{
private:
    string name;
    int age;
    string sex;
public:
    void show()
    {
        cout<<"name:"<<name<<",age:"<<age<<",sex:"<<sex<<endl;
    }
    void set(const char *n, int a, const char* s);
};

void Person::set(const char *n, int a, const char* s)
{
    age = a;
    name = n;
    sex = s;
}

int main()
{
    Person p1;
    p1.set("yekai", 25, "man");
    p1.show();
    return 0;
}
