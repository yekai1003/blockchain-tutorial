#include <iostream>
using std::cout;
using std::endl;

int main()
{
    int a = 123;
    auto f = [=] { cout << a << endl; };    // 值捕获
    f(); // 输出：123
}