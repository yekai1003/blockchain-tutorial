//
// 函数指针
//
#include <iostream>
using namespace std;

//定义函数指针 pf 实际是一个变量，指针变量，指向函数的地址
int (*pf)(int);

int square(int a)
{
    return a*a;
}
int volume(int a)
{
    return a*a*a;
}

int add(int a, int b)
{
    return a+b;
}

const double * f1(const double ar[], int n)
{
    return ar;
}

const double * f2(const double ar[], int n)
{
    return ar+1;
}

const double * f3(const double ar[], int n)
{
    return ar+2;
}

int callsquare(int a, int (*pfn)(int))
{
    return pfn(a);
}

//const double * (*pdf)(const double *, int );

//使用typedef对函数指针进行简化,pf_func是新的函数指针类型
typedef  const double * (*pf_func)(const double *, int );



int main()
{
    pf = square;//pf指针赋值，pf指向squre函数
    cout<<pf(10)<<endl;
    pf = volume;
    cout<<pf(10)<<endl;
    //pf = add; //不允许，函数原型不匹配
    cout<<(*pf)(10)<<endl;
    //函数指针数组
    const double * (*pdf[3])(const double *, int ) = {f1, f2, f3};
    double  arr[] = {1111.11, 2222.22, 3333.33};
    cout<<"Address  value"<<endl;
    for(int i = 0; i < 3; i ++) {
        cout<<pdf[i](arr, 3)<<":  "<<*pdf[i](arr, 3)<<endl;
    }
    auto pdf3 = f1;
    cout<<pdf3(arr, 3)<<":  "<<*pdf3(arr, 3)<<endl;
    pf_func pdf4 = f2;
    cout<<pdf4(arr, 3)<<":  "<<*pdf4(arr, 3)<<endl;
    pf_func pdf5 = f3;
    cout<<pdf5(arr, 3)<<":  "<<*pdf5(arr, 3)<<endl;
    cout<<callsquare(10, square);
    return 0;
}
