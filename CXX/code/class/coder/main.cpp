//
// Created by yekai on 2020-10-30.
//

#include "codertester.h"

int main()
{
    CoderTester ct;
    ct.workhard(); //多重继承
    ct.eating();
    //Worker w; //不允许 ，虚基类不允许构造对象
    //Coder c; //不允许 ，派生类如果未实现纯虚函数，它也是一个新的虚基类
    return 0;
}
