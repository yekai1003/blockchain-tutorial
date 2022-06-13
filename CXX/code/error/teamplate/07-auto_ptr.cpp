#include <iostream>
using  namespace std;



class  Student
{
private:
    string name;
    int age;
    string sex;
public:
    Student(string n, int a, string s):name(n),age(a),sex(s) {}
    ~Student() {
        cout<<"~Student() is called"<<endl;
    }
};

int main()
{
    Student *ps = new Student("yekai", 30, "man");
    //auto_ptr<Student> autoStu = auto_ptr<Student>(ps); //智能指针赋值
    return 0;
}