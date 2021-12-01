#include <iostream>

using  std::cout;
using  std::endl;
void swap(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}

void swap2(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int a= 10, b = 20;
    swap(a, b);
    cout<<"a = "<<a<<",b = "<<b<<endl;
    swap2(a, b);
    cout<<"a = "<<a<<",b = "<<b<<endl;
    return 0;
}



