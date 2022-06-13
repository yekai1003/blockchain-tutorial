//指针的使用
#include <iostream>
using namespace std;

//定义个函数
int swap(int a, int b)
{
    int temp  = a;
    a = b;
    b = temp;
    cout<<"swap:"<<a<<","<<b<<endl;
    return  0;
}

//指针的最大意义在于间接赋值
int swap2(int *a, int *b)
{
    int temp  = *a;
    *a = *b;
    *b = temp;
    cout<<"swap:"<<a<<","<<b<<endl;
    return  0;
}

int main()
{
    int a = 10, b = 20;
    swap2(&a, &b);
    //如果成功，a将= 20，b将=10
    cout<<a<<","<<b<<endl;
    return 0;
}

