

要补充的C++知识：

1. C++基础概念；
2. 何为引用；
3. vector
4. auto 语法
5. 拉姆达表达式



### 1. C++编译和运行

第1个程序

```c++
#include <iostream>

using namespace std;

int main()
{
    cout<<"hello world"<<endl;
    auto ax = 100;
    cout<<"ax = "<<ax<<endl;
    return 0;
}
```

编译合约

```sh
g++ hello.cpp -o hello
```



引用的知识点

```c++
#include <iostream>

using  std::cout;
using  std::endl;
void swap(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}

void swap2(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int a= 10, b = 20;
    swap(a, b);
    cout<<"a = "<<a<<",b = "<<b<<endl;
    swap2(a, b);
    cout<<"a = "<<a<<",b = "<<b<<endl;
    return 0;
}

```





合约相关的API：

```sh
# 1. 身份认证
require_auth(host); //身份认证
# 2. 获取自身
get_self()
# 3. 条件检查
check(bool, string);
# 4. 获取时间，action.h
uint64_t  publication_time( void );
```

