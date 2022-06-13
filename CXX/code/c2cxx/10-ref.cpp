//引用
#include <iostream>
using namespace std;

//定义个函数,参数为引用方式
int swap(int &a, int &b)
{
    int temp  = a;
    a = b;
    b = temp;
    cout<<"swap:"<<a<<","<<b<<endl;
    return  0;
}



int main()
{
    //引用如何定义
    double pi = 3.14;
    double &pi2 = pi;//定义引用，pi2是pi的引用
    cout<<pi2<<endl;
    pi2 = 6.18;
    cout<<pi<<endl;
    int a = 10, b = 20;
    swap(a,b);
    cout<<a<<","<<b<<endl;
    return 0;
}

