#include <iostream>
#include <map>

using namespace std;

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

int main()
{
    map<string, Student> mapStus;
    //向map插入元素
    mapStus.insert(make_pair("yekai", Student("yekai", 30, "man")));
    mapStus.insert(make_pair("xiaohong", Student("xiaohong", 30, "man")));
    mapStus.insert(make_pair("xiaohuang", Student("xiaohuang", 30, "man")));
    mapStus.insert(make_pair("zhangsan", Student("lisi", 30, "man")));
    //在map中查找元素
    map<string, Student>::iterator it =  mapStus.find("zhangsan2");
    if (it != mapStus.end()) {
        cout<<it->first<<"->";
        cout<<it->second;
    }
    return 0;
}

