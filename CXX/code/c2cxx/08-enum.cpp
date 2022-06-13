//枚举值
#include <iostream>
using namespace std;

enum jijie {
    spr, sum, aut, win
};

int main()
{
    jijie j = spr;
    cout<<j<<","<<win<<endl;
    int a = j+4;//允许
//    j = 3;//不允许
//    j = sum+1;//不允许
    return 0;
}

