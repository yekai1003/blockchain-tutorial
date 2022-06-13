//
// 模版类
//

#include <iostream>
using  namespace std;

//定义一个Stack类，可以存放int，double。。。这些类型的数据
template <typename T>
class  Stack
{
private:
    T *items;
    int max ;//记录最大容量
    int top; //记录stack顶部值
public:
    Stack(int max = 10) {
        this->max = max;
        items = new T[max];
        top = 0;//一定要初始化
    }
    ~Stack() {
        if(items != NULL) {
            delete []items;
        }
    }
    void show() {
        cout<<"max = "<<max<<",top = "<<top<<endl;
    }
    bool isEmpty();
    bool isFull();
    bool push(const T &item);
    bool pop(T &item);
};

template <typename T>
bool Stack<T>::isEmpty()
{
    return top == 0;
}

template <typename T>
bool Stack<T>::isFull()
{
    return top == max;
}

template <typename T>
bool Stack<T>::push(const T &item)
{
    if(isFull()) {
        return false;
    }
    items[top] = item;
    top++;
    return true;
}

template <typename T>
bool Stack<T>::pop(T &item)
{
    if(isEmpty()) {
        return false;
    }
    item = items[top];
    top--;
    return true;
}



int main()
{
    Stack<int> s1;// max = 10
    for(int i = 0 ;i < 15; i ++) {
        s1.push(i);//会成功执行多少次？
    }

    s1.show();
    int item;
    for(int i = 0; i < 15; i ++) {
        if (s1.pop(item) ) {
            cout<<item<<endl;
        }

    }
    return 0;
}