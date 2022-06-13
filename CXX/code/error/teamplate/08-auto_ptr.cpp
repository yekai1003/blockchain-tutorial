#include <iostream>
using  namespace std;

int main1()
{
    auto_ptr<string> p1(new string("auto"));
    auto_ptr<string> p2;
    p2 = p1;//将发生什么？  当p1赋值给p2时，auto_ptr认为p1将失去意义，不再指向原指针变量
    // auto_ptr为什么要解除p1和指针的关系呢？
    // 如果不解除会怎么样？ p1 会析构， p2也会析构,double free
    //智能指针如何用
    //cout<<*p1<<endl;
    cout<<*p2<<endl;
    return 0;
}

//int main2()
//{
//    unique_ptr<string> p1(new string("auto"));
//    unique_ptr<string> p2;
//    p2 = p1;//将发生什么？  当p1赋值给p2时，auto_ptr认为p1将失去意义，不再指向原指针变量
//    // auto_ptr为什么要解除p1和指针的关系呢？
//    // 如果不解除会怎么样？ p1 会析构， p2也会析构,double free
//    //智能指针如何用
//    //cout<<*p1<<endl;
//    cout<<*p2<<endl;
//    return 0;
//}

int main()
{
    shared_ptr<string> p1(new string("auto"));
    shared_ptr<string> p2;
    p2 = p1;//将发生什么？  当p1赋值给p2时，auto_ptr认为p1将失去意义，不再指向原指针变量
    // auto_ptr为什么要解除p1和指针的关系呢？
    // 如果不解除会怎么样？ p1 会析构， p2也会析构,double free
    //智能指针如何用
    cout<<*p1<<endl;
    cout<<*p2<<endl;
    return 0;
}



