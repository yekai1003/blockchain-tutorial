//
// 运算符重载
//

#include <iostream>
using  namespace std;

class  Complex {
private:
    int x;
    int y;
public:
    Complex(int _x, int _y) :x(_x), y (_y) {}
    //运算符重载其实就是用户自定义对象的运算方式
    Complex& operator+=(const Complex & another) {
        this->x += another.x;
        this->y += another.y;
        return  *this;
    }
    Complex& operator=(const Complex & another) {
        cout<<"call operator="<<endl;
        this->x = another.x;
        this->y = another.y;
        return  *this;
    }
    void show() {
        cout<<"x = "<<this->x<<",y = "<<this->y<<endl;
    }
    friend  Complex& operator++(Complex & c);
    friend  ostream& operator<<(ostream & out, const Complex &c);
    friend  istream& operator>>(istream & in, Complex &c);
};

Complex& operator++(Complex & c)
{
    c.x ++;
    c.y ++;
    return  c;
}
ostream& operator<<(ostream & out, const Complex &c)
{
    out<<"x:"<<c.x<<",y:"<<c.y<<endl;
    return  out;
}
istream& operator>>(istream & in, Complex &c)
{
    in>>c.x>>c.y;
    return  in;
}

int main()
{
    Complex c1(3, 4);
    c1.show();
    Complex c2(6, 7);
    c1 += c2; //c1 和c2进行运算，运算符重载使用
    c1.show();
    c1.operator+=(c2); //其实也是函数调用
    c1.show();
    (++c1).show();
    ++++c1;
    c1.show();
    cout<<"------------"<<endl;
    cin>>c1;
    cout<<c1;
    cout<<"------------"<<endl;
    c1 = c2; //使用等号运算符重载
    cout<<c1;
    return 0;
}


