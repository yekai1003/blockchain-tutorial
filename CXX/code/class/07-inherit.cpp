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
    const char *getName()
    {
        return  name.c_str();
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
};

int main()
{
    SuperMan s1("yekai", 30, 'Y', 10000, "sleep");
    cout<<s1.getName()<<endl;
    return 0;
}