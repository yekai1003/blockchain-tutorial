//
// 继承exception
//
#include <iostream>
#include <exception>

using  namespace std;

class Bad_Hmean : public  exception
{
private:
    double x, y;
public:
    Bad_Hmean(double a, double b) :x(a), y(b) {}
    virtual const char* what() const _NOEXCEPT {
        return  "bad hmean argu: x = -y";
    }
};

class Bad_gmean : public  exception
{
private:
    double x, y;
public:
    Bad_gmean(double a, double b) :x(a), y(b) {}
    virtual const char* what() const _NOEXCEPT {
        return  "bad gmean argu: x *y < 0";
    }
};

double hmean(double x, double y)
{
    if(x == -y) {
        throw Bad_Hmean(x, y); //抛出一个错误对象
    }
    return  2.0 * x * y / (x + y);
}

double gmean(double x, double y)
{
    if(x * y < 0) {
        throw Bad_gmean(x, y); //抛出一个错误对象
    }
    return  sqrt(x * y);
}

int main()
{
    double a, b;
    double result;
    while(cin >> a >> b) {
        try {
            result = hmean(a , b); //这句话抛出异常之后，执行什么？可以跳到catch
            cout <<"hmean-result:"<< result << endl;
            result = gmean(a, b);
            cout<<"gmean-result:"<<result<<endl;
        }
            //catch捕捉throw信息
            //虽然exception是引用传递，但是此时仍然是生成对象的副本
            //引用的主要目的是为了多态，指针或引用才可以指向基类对象
        catch(exception & b) {
            //cout<<"err:"<<b.mesg()<<endl;
            cout<<b.what()<<endl;
            continue; //继续执行while
        }

    }
    return 0;
}