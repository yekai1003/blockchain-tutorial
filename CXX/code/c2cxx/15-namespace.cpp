#include <iostream>
using namespace std;

//定义了一个命名空间 A
namespace  A {
    int zhangsan = 10;
    string name = "zhangsan";
    namespace  C {
        int wangwu = 30;
        struct  Person {
            string name;
            int age;
        };
    }
}

namespace  B {
    int lisi = 20;
    string name = "lisi";
}

int main()
{
    //using namespace A;
    //using namespace B;

    using B::lisi;
    //cout<<zhangsan<<","<<name<<endl;
    //cout<<zhangsan<<","<<B::name<<endl;
    cout<<A::C::wangwu<<endl;
    A::C::Person p1 = {"yk", 30};
    return 0;
}


