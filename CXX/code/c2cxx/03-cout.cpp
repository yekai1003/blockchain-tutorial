//
// Created by yekai on 2020-09-11.
//
#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
    int a = 10;
    string s = "hello world";
    cout<<a<<","<<s<<endl;

    //c风格打印
    printf("%d\n", a);
    printf("%s\n", s.c_str());
    //精确化打印
    //16进制 hex
    hex(cout);//此后的cout输出按照16进制
    cout<<a<<endl;
    //8进制 oct
    cout<<oct<<a<<endl;
    //10进制
    dec(cout);
    cout<<a<<endl;

    //接收标准输入
    cin>>a;
    cout<<a<<endl;
    cin>>s;
    cout<<s<<endl;

    return 0;
}

