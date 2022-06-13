//
// 异常处理:抛出对象
//
#include <iostream>
#include <cstdlib>

using  namespace std;

class Bad_Hmean
{
private:
    double x, y;
public:
    Bad_Hmean(double a, double b) :x(a), y(b) {}
    inline void  mesg();
};

inline void  Bad_Hmean::mesg()
{
    cout<<"Hmean err: argumen a = -b"<<endl;
}

class Bad_gmean
{
private:
    double x, y;
public:
    Bad_gmean(double a, double b) :x(a), y(b) {}
    inline const char* mesg();
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

inline const char* Bad_gmean::mesg()
{
    return "bad gmean argumen: x * y < 0";
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
        catch(Bad_Hmean & b) {
            //cout<<"err:"<<b.mesg()<<endl;
            b.mesg();
            continue; //继续执行while
        }
        catch(Bad_gmean & b) {
            cout<<b.mesg()<<endl;
            continue; //继续执行while
        }
    }
    return 0;
}


