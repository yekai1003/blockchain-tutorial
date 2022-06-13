#include <iostream>
#include <list>

using namespace std;
template <typename T>
void show(T num)
{
    cout<<num<<endl;
}

int main()
{
    list<int> lvalues; //定义双向链表
    lvalues.push_back(1000); // 1000
    lvalues.push_front(100); // 100->1000
    lvalues.push_back(200); //  100->1000->200
    cout<<lvalues.size()<<endl;
//    lvalues.clear();
//    cout<<lvalues.size()<<endl;
    for_each(lvalues.begin(), lvalues.end(), show<int>);
    return 0;
}

