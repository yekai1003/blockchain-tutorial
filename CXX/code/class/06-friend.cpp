//
// 友元
//

#include <iostream>
using  namespace std;

//前置声明
class  Student;

class Teacher
{
public:
    void dianming(Student& stu);//仅仅做声明
};

class  Student
{
private:
    string name;
    int age;
    string sex;
public:
    Student(string n, int a, string s):name(n),age(a),sex(s) {}
    //定义一个友元
    //友元没有public，private属性，放在哪里都可以，并非是类内部的函数
    friend bool isBigAge(Student stu);
    //声明友元类
    //friend  class Teacher;
    friend void Teacher::dianming(Student& stu);
};


bool isBigAge(Student stu)
{
    return  stu.age > 18;//是否大于18岁
}

//成员函数实现
void Teacher::dianming(Student& stu)
{
    cout<<"dianming:"<<stu.name<<endl;
}


int main()
{
    Student stu("yekai", 19, "man");
    cout<<isBigAge(stu)<<endl;
    Teacher t1;
    t1.dianming(stu);
    return 0;
}
