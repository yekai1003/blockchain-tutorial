//
// 异常处理
//
#include <iostream>
#include <cstdlib>

using  namespace std;

double hmean(double x, double y)
{
    if(x == -y) {
        throw "bad hmean() arguments: x = -y not allowed";//跳到catch
    }
    return  2.0 * x * y / (x + y);
}



int main()
{
    double a, b;
    double result;
    while(cin >> a >> b) {
        try {
            result = hmean(a , b); //这句话抛出异常之后，执行什么？可以跳到catch
            cout <<"result:"<< result << endl;
        }
        //catch捕捉throw信息
        catch(const char *msg) {
            cout<<"err:"<<msg<<endl;
            continue; //继续执行while
        }
    }
    return 0;
}

