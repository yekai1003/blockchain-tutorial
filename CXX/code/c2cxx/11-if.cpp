//if语句
#include <iostream>
using namespace std;

int main()
{
    int score;
    cout<<"Please input a score"<<endl;
    cin>>score;
    char ch;
    if(score < 60) {
        ch = 'D';
    } else if(score >= 60 && score < 75) {
        ch = 'C';
    } else if(score >=75 && score < 85) {
        ch = 'B';
    } else {
        ch = 'A';
    }
    cout<<ch<<endl;
    //通过switch-case的方式输出优秀，良好，及格，不及格
    switch (ch) {
        case 'A':
            cout<<"优秀"<<endl;
            break;
        case 'B':
            cout<<"良好"<<endl;
            break;
        case 'C':
            cout<<"及格"<<endl;
            break;
        case 'D':
            cout<<"不及格"<<endl;
            break;
        default:
            cout<<"崩溃"<<endl;
            break;
    }


    return 0;
}