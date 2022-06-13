//
// 函数重载
//
#include <iostream>
using namespace std;

void func(int a)
{
    cout<<"void func(int a)"<<endl;
    cout<<a<<endl;
}

//void func(char a)
//{
//    cout<<"void func(char a)"<<endl;
//    cout<<a<<endl;
//}

void func(int a, char b)
{
    cout<<"void func(int a, char b)"<<endl;
    cout<<a<<":"<<b<<endl;
}

void func(char a, int b)
{
    cout<<"void func(char a, int b)"<<endl;
    cout<<a<<":"<<b<<endl;
}

//不能通过返回值区分不同的函数
//char func(int a)
//{
//    cout<<a<<endl;
//}

int main()
{
    func(10);
    func(10, 'A');
    func('A');
    return 0;
}