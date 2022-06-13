//
// 类型转换
//
#include <iostream>

using  namespace std;

struct Data
{
    int num;
};

int main()
{
    const Data d  = {10};
    //d.num = 20;
    //const_cast<Type &> (var_name);
    Data &dd = const_cast<Data &> (d);
    dd.num = 200;
    cout<<d.num<<endl;
    return 0;
}
