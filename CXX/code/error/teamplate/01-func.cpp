//
//模版函数
//
#include <iostream>
using  namespace std;

//实际上编译器需要2次编译，第一次确定模版函数类型，第二次根据类型重新展开模版函数
template <class  T>
T mymax(T &a, T &b)
{
    return  a > b ? a : b;
}

int main()
{
    int a = 10, b = 20;
    double a1 = 3.16, b1 = 5.28;
    char c1 = 'a', c2 = 'b';
    cout<<mymax<int>(a, b)<<endl;
    cout<<mymax<double>(a1, b1)<<endl;
    cout<<mymax<char>(c1, c2)<<endl;
    return 0;
}

