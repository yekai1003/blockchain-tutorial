//共用体
#include <iostream>
using namespace std;

int main()
{
    //局部定义
    union test_bigend {
        int number;
        char mem[4];
    };
    //num mem首地址相同
    test_bigend t;
    t.number = 0x01020304;
    printf("%x,%x,%x,%x\n", t.mem[0],t.mem[1],t.mem[2], t.mem[3]);
    //cout<<t.mem[0]<<","<<t.mem[1]<<","<<t.mem[2]<<","<<t.mem[3]<<endl;
    //utf8编码 支持汉字，一个汉字对应三个字节
    test_bigend utf888;
    strcpy(utf888.mem, "苦");
    printf("%x\n", utf888.number);
    return 0;
}
