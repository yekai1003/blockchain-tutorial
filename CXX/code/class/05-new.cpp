//验证构造函数与析构函数的执行
#include <iostream>

using namespace std;

class  A
{
private:
public:
    A(){ cout<<"create A()"<<endl; }
    ~ A() { cout <<"delete A"<<endl; }
};

class B
{
private:
    A a;
public:
    B(A pa)
    {
        cout<<"create B()"<<endl;
        a = pa; //隐藏着运算符重载,没有调用构造函数,a成员已经被创建,当b对象退出时，a的生命周期结束，也会指向a析构
    }
    ~ B() { cout <<"delete B"<<endl; }
};

int main()
{
    /*
     * 触发 首尾： create A()
     *
     * */
    A a;
    /*
     * 一次阴性的pa对象创建 create A()
     * B对象构造：         create B()
     * 构造函数结束，pa释放：delete A
     * */
    B *b = new B(a);
    //主动释放B ： delete B
    delete b;
    //推出之前：delete A
    return 0;
}
