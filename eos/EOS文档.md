开发参考手册：

https://developers.eos.io/manuals/eos/latest/nodeos/index



nodeos节点启动

```sh
 nohup nodeos -e -p eosio --plugin eosio::chain_plugin --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --http-server-address "0.0.0.0:8888" --hard-replay-blockchain --replay-blockchain --contracts-console  >> eos.log &
```

查看区块信息

```sh
cleos get info
```

测试API

```sh
# 查看链信息
curl  "http://127.0.0.1:8888/v1/chain/get_info"

# 查看eosio账户信息
curl  -H "Content-type: application/json" -X POST -d '{"account_name": "eosio"}' "http://127.0.0.1:8888/v1/chain/get_account"


```

eosio私钥信息

```sh
eosio
Public key: EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
Private key: 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3
```



创建钱包

```sh
$ cleos wallet create --to-console
Creating wallet: default
Save password to use in the future to unlock this wallet.
Without password imported keys will not be retrievable.
"PW5KYH8CEN4mCnPnDuYTstLxD2zwqnVZB4YRBwhNRMSQWosuxS8dV"
```

创建keys

```sh
$ cleos wallet create_key
Created new private key with a public key of: "EOS6dkikqxS2E8EBocRJYCTWPv6JUGd1C8QgfNhjzmZX2oJnFxhJE"

$ cleos wallet create_key
Created new private key with a public key of: "EOS6CJ3ypWHFgopH7SEq4deSBeDjNkpMaMZRMFyRsGa3DbXdWgRb4"
```

解锁账户

```sh
[fabric@jbf138 ~]$ cleos wallet  unlock -n mywallet
password: Unlocked: mywallet

```

导入钱包

```sh
[fabric@jbf138 ~]$ cleos wallet import -n mywallet --private-key 5JzNrQGtHUca4gnEhcHwadRATw3J4EC6C128wGfPXmpC6z84Has
imported private key for: EOS6YgpmsRKoRPj33AwPH8btbBqumVCHZnDQBkgqXKDC77RqRH17b
```

将eosio导入钱包

```sh
cleos wallet import --private-key 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3
```





创建hello账户

```sh
cleos create account eosio hello EOS6dkikqxS2E8EBocRJYCTWPv6JUGd1C8QgfNhjzmZX2oJnFxhJE EOS6dkikqxS2E8EBocRJYCTWPv6JUGd1C8QgfNhjzmZX2oJnFxhJE
```





Go语言调用

```go
package main

import (
	"context"
	"encoding/json"
	"fmt"

	eos "github.com/eoscanada/eos-go"
)

func main() {
	api := eos.New("http://127.0.0.1:8888")
	ctx := context.Background()

	infoResp, _:= api.GetInfo(ctx)

	fmt.Println("Chain Info", toJson(infoResp))

	accountResp, _ := api.GetAccount(ctx, "eosio")
	fmt.Println("Account Info", toJson(accountResp))
}

func toJson(v interface{}) string {
	out, _:= json.MarshalIndent(v, "", "  ")

	return string(out)
}

```



安装eosio.cdt，也就是eos智能合约开发工具

```sh
wget https://github.com/eosio/eosio.cdt/releases/download/v1.8.1/eosio.cdt-1.8.1-1.el7.x86_64.rpm
sudo yum install ./eosio.cdt-1.8.1-1.el7.x86_64.rpm
```

参考教程：https://developers.eos.io/welcome/latest/getting-started-guide/hello-world

测试合约:hello.cpp

```c++
#include <eosio/eosio.hpp>
class [[eosio::contract]] hello : public eosio::contract {
  public:
      using eosio::contract::contract;
      [[eosio::action]] void hi( eosio::name user ) {
         print( "Hello, ", user);
      }
};
```

编译hello合约

```sh
eosio-cpp -abigen -o hello.wasm hello.cpp
```

部署合约，在hello的上级目录

```sh
cleos set contract hello ./hello -p hello@active
```

创建yekai账户

```sh
cleos create account eosio yekai EOS6CJ3ypWHFgopH7SEq4deSBeDjNkpMaMZRMFyRsGa3DbXdWgRb4 EOS6CJ3ypWHFgopH7SEq4deSBeDjNkpMaMZRMFyRsGa3DbXdWgRb4
```

调用合约

```sh
cleos push action hello hi '["alice"]' -p yekai@active
```

执行结果

```sh
$ cleos push action hello hi '["zhangsanfeng"]' -p yekai@active
executed transaction: 3d34b41fde86efa83465f278367f04a50d040d3e5856f39514b97553428b6420  104 bytes  147 us
#         hello <= hello::hi                    {"user":"zhangsanfeng"}
>> Hello, zhangsanfeng
warning: transaction executed locally, but may not be confirmed by the network yet         ] 
```



编写合约

