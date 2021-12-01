#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> va(10);
    va[0] = 100;
    va[1] = 101;

    va.push_back(1000);

    for (int i = 0; i < va.size(); i ++) {
        cout<<"i = "<<i<<", val = "<<va[i]<<endl;
    }

    va.erase(va.begin(), va.end());

    cout<<"size == " << va.size() << endl;
    return 0;
}