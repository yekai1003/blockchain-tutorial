//
// 继承exception
//
#include <iostream>
#include <exception>

using  namespace std;

class Demo
{
private:
    string name;
public:
    Demo(const char * n) :name(n) {

        cout<<name<<"'s Demo is created"<<endl;
    }
    ~Demo() {
        cout<<name<<"'s Demo is deleting"<<endl;
    }
    void show() {
        cout<<name<<"'s Demo is show"<<endl;
    }
};
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

//计算（hmean+gmean）/2
double  means(double x, double y)
{
    Demo d2("d2");
    double a1;
    double a2;
    try {
        a1 = hmean(x, y);
        a2 = gmean(x, y);
    }
    catch (exception & b) {
        cout<<"means catch err"<<endl;
        throw ; // 直接继续向上抛出
    }

    d2.show();
    return  (a1 + a2) / 2.0;
}




int main()
{
    double a, b;
    {
        double result;
        Demo d1("d1");
        cout<<"enter new pair:";
        while(cin >> a >> b) {
            try {

                result = means(a , b); //这句话抛出异常之后，执行什么？可以跳到catch
                cout<<"means's result is "<<result<<endl;
                cout<<"enter new pair:";
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
        d1.show();
    }

    return 0;
}
