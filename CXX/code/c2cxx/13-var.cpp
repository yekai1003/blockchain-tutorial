#include <iostream>
using namespace std;


int main()
{
    int teledeli = 10;
    {
        //int websight = 20;
        int teledeli = 200; //此时第7行的定义被隐藏
        //cout<<"hello:"<<websight<<" "<<teledeli<<endl;
        cout<<"hello:"<<teledeli<<endl;
    }

    //cout<<websight<<endl;
    cout<<teledeli<<endl;
    return  0;
}