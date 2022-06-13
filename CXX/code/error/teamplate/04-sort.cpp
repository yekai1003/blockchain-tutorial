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

class  Student
{
private:
    string name;
    int age;
    string sex;
public:
    Student(string n, int a, string s):name(n),age(a),sex(s) {}
    friend bool operator<(const Student &s1, const Student &s2);
    friend ostream&operator<<(ostream &out , const Student &s);
};

bool operator<(const Student &s1, const Student &s2)
{
    //比较逻辑自己确定
    return s1.age < s2.age;
}

ostream&operator<<(ostream &out , const Student &s)
{
    out<<s.name<<","<<s.age<<","<<s.sex<<endl;
    return out;
}


int main() {

    vector<int> values = {11, 2, 33, 14, 5};  // -std=c++11

    sort(values.begin(), values.end());

    for_each(values.begin(), values.end(), show<int>);
    // vector存放student数据类型
    vector<Student> students;
    students.push_back(Student("yekai", 30, "man"));
    students.push_back(Student("yekai2", 20, "man"));
    students.push_back(Student("yekai3", 40, "man"));
    students.push_back(Student("yekai6", 10, "man"));
    sort(students.begin(), students.end()); //sort需要明确student的大小比较方式
    for_each(students.begin(), students.end(), show<Student>);

    return 0;
}