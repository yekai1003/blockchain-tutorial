//命名空间
#include <iostream>
using  namespace std;

namespace  NameSpaceA {
    char aa = 'A';
}

namespace  NameSpaceB {
    char aa = 'B';
    namespace  NameSpaceC {
        struct  Person {
            string name;//string是C++的类型
            int fight;
        };
    }
}

int main()
{
    using  namespace NameSpaceA;
    //using  namespace NameSpaceB;
    cout<<aa<<endl;
    cout<<NameSpaceB::aa<<endl;
    //多层命名空间使用
    NameSpaceB::NameSpaceC::Person p1 = {"zhazha", 5};
    cout<<p1.name<<"'s fight is "<<p1.fight<<endl;
    return 0;
}
