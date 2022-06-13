#include <iostream>

using  namespace std;


int main()
{
    double *pd = new double (3.14);
    int *pi = new int (100);
    float *pf = new float [20]; // 20*float
    cout<<pd<<","<<*pd<<","<<pi<<","<<*pi<<endl;
    delete  pd;
    delete pi;
    delete []pf;
    return  0;
}

