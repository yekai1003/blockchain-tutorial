//
// 拷贝构造函数
//
#include <iostream>
using  namespace std;

//设置一个同龄人的类
class  Person
{
public:

    Person(const char *n, int a)
    {
        cout<<"Person() call"<<endl;
        int len = sizeof(n);
        name = new char[len+1];
        strcpy(name , n);
        name[len] = '\0';
        age = a;
    }
    ~Person() {
        if (name != NULL) {
            delete []name;
            name = NULL;
        }
    }
    //自己实现拷贝构造函数，实现深度拷贝
    Person(const Person & p) {
        cout<<"Person(const Person & p) call"<<endl;
        age = p.age;
        int len = sizeof(p.name);
        name = new char[len+1];
        strcpy(name , p.name);
        name[len] = '\0';
    }

private:
    char * name;
    int age;
};

int main()
{
    Person p1("yekai", 30);
    Person p2(p1);//拷贝构造使用
    //p1 p2 都会析构name空间，由于name在堆区,指向同一地址，会释放2次
    return 0;
}
