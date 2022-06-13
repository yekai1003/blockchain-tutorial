//
// Created by yekai on 2020-11-09.
//

#include <iostream>
#include <vector>

using  namespace std;

//void show(int num)
////{
////    cout<<num<<endl;
////}

template <typename T>
void show(T num)
{
    cout<<num<<endl;
}


int main()
{
    //vector<int> values  {1, 2, 3, 4, 5}; // -std=c++11
    vector<int> values = {1, 2, 3, 4, 5};  // -std=c++11


    for(int i = 0; i < 5 ; i ++) {
        cout<<values[i]<<endl;
    }

    cout<<values.size()<<endl;
    values.push_back(100);
    cout<<values.size()<<endl;
    cout<<"--------"<<endl;
    for(vector<int>::iterator it = values.begin(); it != values.end() ; it ++) {
        cout<<*it<<endl;
    }

    //for_each
    for_each(values.begin(), values.end(), show<int>);

    return 0;
}
