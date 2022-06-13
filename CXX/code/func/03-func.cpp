//
// 内联函数
//
#include <iostream>
using namespace std;

//定义求平方的宏
#define  SQUARE(x) (x)*(x)

//使用内联函数更安全
inline int square(int x)
{
    return x*x;
}

int main()
{
    //x*x x = 1+2  ==> 1+2*1+2 == 5
    cout<<SQUARE(1+2)<<endl;
    cout<<SQUARE(3)<<endl;
    int x = 4;
    cout<<SQUARE(x++)<<endl;
    cout<<square(1+3)<<":"<<square(x++)<<endl;
    return 0;
}

