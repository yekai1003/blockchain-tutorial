//
// 异常处理
//
#include <iostream>
#include <cstdlib>

using  namespace std;

//double hmean(double x, double y)
//{
//    if(x == -y) {
//        abort();
//    }
//    return  2.0 * x * y / (x + y);
//}

bool hmean(double x, double y, double *result)
{
    if(x == -y) {
        return false;
    }
    *result = 2.0 * x * y / (x + y);
    return  true;
}

int main()
{
    double a, b;
    double result;
    while(cin >> a >> b) {
        //cout << hmean(a, b)<<endl;
        if(hmean(a, b, &result )) {
            cout<<result<<endl;
        } else {
            break;
        }
    }
    return 0;
}

