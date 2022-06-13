//类的初体验
#include <iostream>
using namespace std;

class  Person
{
public:

    void set(const char *n, int a, char s)
    {
        name = n;
        age = a;
        sex = s;
    }
    const char *getName()
    {
        return  name.c_str();
    }
private:
    string name;
    int age;
    char sex;
};

int main()
{
    Person p1;
    //p1.name = "yekai"; //私有成员不允许访问
    p1.set("yekai", 25, 'X');
    cout<<p1.getName()<<endl;
    return 0;
}

