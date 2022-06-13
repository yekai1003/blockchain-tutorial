//循环语句
#include <iostream>
using namespace std;

int main()
{
    //1. 计算1+2+3。。。+100
    int i = 0;//定义循环因子
    int sum = 0;//累加器
    for(i =1; i <= 100; i ++) {
        sum += i;
    }
    cout<<sum<<endl;
    //2。 循环打印 hello-world
    for(i =0; i < 20; i ++) {
        cout<<"hello-world"<<endl;
    }
    //3. 使用while do-while支持累计
    sum = 0;
    i = 1;
    do {
       sum += i;
       ++i;
    } while (i <=100);
    cout<<sum<<endl;

    i = 1;
    sum = 0;
    while (i <= 100) {
        sum += i;
        ++i;
    }
    cout<<sum<<endl;
    return 0;
}