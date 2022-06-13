//
// 变量类型和声明
//
#include <iostream>
using  namespace std;

int main()
{
    //1. 定义几个变量
    int a;
    float b = 3.14;
    long c = 100L;
    char d = 'A';
    //2. double float 类型的区别
    cout.setf(ios_base::fixed, ios_base::floatfield);
    float f1 = 10.0/3.0;
    double f2 = 10.0/3.0;
    cout<<"f1 = "<<f1<<endl;
    cout<<"f2 = "<<f2<<endl;
    const float million = 1.0E6;
    cout<<"f1*million ="<<f1*million<<endl;
    cout<<"f2*million ="<<f2*million<<endl;
    //3. auto 关键字
    auto r = 100;
    auto pi = 3.14;
    cout<<"area is "<<r*r*pi<<endl;

    return 0;
}
