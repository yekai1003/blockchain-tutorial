//
// 形参默认值
//

#include <iostream>
using namespace std;

//计算长方体体积
int volume(int length, int width = 10, int hight = 20);

int main()
{
    //有默认值的函数，如果传参了，使用传参的实际参数值，如果没有，使用默认值
    cout<<volume(10)<<endl;
    cout<<volume(10,5)<<endl;
    cout<<volume(10, 10, 10)<<endl;
    //cout<<volume()<<endl;
    return 0;
}

int volume(int length, int width , int hight )
{
    return  length * width * hight;
}
