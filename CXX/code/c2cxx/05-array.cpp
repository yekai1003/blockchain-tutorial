//
// 数组和字符串
//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

int main()
{
    //1. 数组的使用
    //int arr[5];
    int arr[5] = {1,2,3,4,5};
    arr[2]  = 300;
    cout<<arr[2]<<endl;
    //循环语句 循环因子
    for(int i = 0; i < 5; i ++) {
        cout<<"i = "<<i<<",val = "<<arr[i]<<endl;
    }
    float arr2[5] {1.0, 2.0, 3.0, 4.0, 5.0};
    double arr3[] = {9.0, 2.0, 3.0};

    //2. 字符串的使用
    char name[30];
    strcpy(name, "yekai");
    string str1 = "hello";
    string str2 = "world";
    str1 += str2;
    cout<<str1<<endl;
    //c_str转化为c风格的字符串
    strcpy(name, str1.c_str());
    cout<<name<<endl;

    return 0;
}

