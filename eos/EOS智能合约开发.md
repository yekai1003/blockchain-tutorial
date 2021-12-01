

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



**Lambda表达式**https://www.cnblogs.com/DswCnblog/p/5629165.html

```sh
[capture list] (params list) mutable exception-> return type { function body }
```

1. capture list：捕获外部变量列表
2. params list：形参列表
3. mutable指示符：用来说用是否可以修改捕获的变量
4. exception：异常设定
5. return type：返回类型
6. function body：函数体



| 序号 | 格式                                                        |
| ---- | ----------------------------------------------------------- |
| 1    | [capture list] (params list) -> return type {function body} |
| 2    | [capture list] (params list) {function body}                |
| 3    | [capture list] {function body}                              |

- 格式1声明了const类型的表达式，这种类型的表达式不能修改捕获列表中的值。
- 格式2省略了返回值类型，但编译器可以根据以下规则推断出Lambda表达式的返回类型： （1）：如果function body中存在return语句，则该Lambda表达式的返回类型由return语句的返回类型确定； （2）：如果function body中没有return语句，则返回值为void类型。
- 格式3中省略了参数列表，类似普通函数中的无参函数。











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



加密相关的API：

https://developers.eos.io/manuals/eosio.cdt/latest/group__crypto





### 2. ubuntu环境准备

https://developers.eos.io/manuals/eos/latest/nodeos/usage/development-environment/local-single-node-testnet-consensus/#1-add-the-development-key-to-the-wallet

创建钱包

```sh
 cleos wallet create --to-console
"/usr/opt/eosio/2.1.0/bin/keosd" launched
Creating wallet: default
Save password to use in the future to unlock this wallet.
Without password imported keys will not be retrievable.
"PW5KKjKgQWinepG4wa8oUgqTYVa1qmdnY9V1kLC2ZTfQ5H3mUbHBt"
```



nodeos version >= 2.1.0

```sh
cleos set contract eosio eosio.boot/ eosio.boot.wasm eosio.boot.abi
```



```sh
echo KV_DATABASE
cleos push action eosio activate '["825ee6288fb1373eab1b5187ec2f04f6eacb39cb3a97f356a07c91622dd61d16"]' -p eosio

echo ACTION_RETURN_VALUE
cleos push action eosio activate '["c3a6138c5061cf291310887c0b5c71fcaffeab90d5deb50d3b9e687cead45071"]' -p eosio

echo CONFIGURABLE_WASM_LIMITS
cleos push action eosio activate '["bf61537fd21c61a60e542a5d66c3f6a78da0589336868307f94a82bccea84e88"]' -p eosio

echo BLOCKCHAIN_PARAMETERS
cleos push action eosio activate '["5443fcf88330c586bc0e5f3dee10e7f63c76c00249c87fe4fbf7f38c082006b4"]' -p eosio

echo GET_SENDER
cleos push action eosio activate '["f0af56d2c5a48d60a4a5b5c903edfb7db3a736a94ed589d0b797df33ff9d3e1d"]' -p eosio

echo FORWARD_SETCODE
cleos push action eosio activate '["2652f5f96006294109b3dd0bbde63693f55324af452b799ee137a81a905eed25"]' -p eosio

echo ONLY_BILL_FIRST_AUTHORIZER
cleos push action eosio activate '["8ba52fe7a3956c5cd3a656a3174b931d3bb2abb45578befc59f283ecd816a405"]' -p eosio

echo RESTRICT_ACTION_TO_SELF
cleos push action eosio activate '["ad9e3d8f650687709fd68f4b90b41f7d825a365b02c23a636cef88ac2ac00c43"]' -p eosio

echo DISALLOW_EMPTY_PRODUCER_SCHEDULE
cleos push action eosio activate '["68dcaa34c0517d19666e6b33add67351d8c5f69e999ca1e37931bc410a297428"]' -p eosio

 echo FIX_LINKAUTH_RESTRICTION
cleos push action eosio activate '["e0fb64b1085cc5538970158d05a009c24e276fb94e1a0bf6a528b48fbc4ff526"]' -p eosio

 echo REPLACE_DEFERRED
cleos push action eosio activate '["ef43112c6543b88db2283a2e077278c315ae2c84719a8b25f25cc88565fbea99"]' -p eosio

echo NO_DUPLICATE_DEFERRED_ID
cleos push action eosio activate '["4a90c00d55454dc5b059055ca213579c6ea856967712a56017487886a4d4cc0f"]' -p eosio

echo ONLY_LINK_TO_EXISTING_PERMISSION
cleos push action eosio activate '["1a99a59d87e06e09ec5b028a9cbb7749b4a5ad8819004365d02dc4379a8b7241"]' -p eosio

echo RAM_RESTRICTIONS
cleos push action eosio activate '["4e7bf348da00a945489b2a681749eb56f5de00b900014e137ddae39f48f69d67"]' -p eosio

echo WEBAUTHN_KEY
cleos push action eosio activate '["4fca8bd82bbd181e714e283f83e1b45d95ca5af40fb89ad3977b653c448f78c2"]' -p eosio

echo WTMSIG_BLOCK_SIGNATURES
cleos push action eosio activate '["299dcb6af692324b899b39f16d5a530a33062804e41f09dc97e9f156b4476707"]' -p eosio
```

