#include <iostream>
using  namespace std;

int global = 10; //全局变量，其他文件也可以访问
static  int one_file = 20; //仅限于本文件内部访问

void func()
{
    static int l_count = 10; //仅限于本函数访问
    l_count++;
    cout<<"func:"<<l_count<<endl;
}

void func2()
{
    //无法访问l_count
   // cout<<"func2:"<<l_count<<endl;
   cout<<one_file<<endl;
}

int main()
{
    func2();
    return 0;
}

