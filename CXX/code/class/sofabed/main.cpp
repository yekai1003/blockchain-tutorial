//
// Created by yekai on 2020-10-30.
//
#include <iostream>
#include "sofabed.h"
using  namespace std;

int main()
{
    SofaBed sb(1000);
    sb.sit();
    sb.sleep();
    //访问有冲突的成员变量，需要指定基类名称
    cout<<sb.::Bed::weight<<endl;
}
