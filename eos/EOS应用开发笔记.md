# EOS应用开发笔记

## 1. 节点准备

开发参考手册：

https://developers.eos.io/manuals/eos/latest/nodeos/index

API文档

https://developers.eos.io/welcome/latest/reference/sdk-api-references

nodeos节点启动

```sh
nohup nodeos -e -p eosio --plugin eosio::chain_plugin --plugin eosio::producer_api_plugin --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --http-server-address "0.0.0.0:8888" --contracts-console --verbose-http-errors --hard-replay-blockchain --replay-blockchain  > eos.log &
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

创建钱包

```sh
 cleos wallet create --to-console
"/usr/opt/eosio/2.1.0/bin/keosd" launched
Creating wallet: default
Save password to use in the future to unlock this wallet.
Without password imported keys will not be retrievable.
"PW5KDsHZGVUhbJjh84dyBXEdB6b8y76MyDqVGDBq1GnVXPUBdsX6V"
```

导入eosio账户

```sh
cleos wallet create_key
Created new private key with a public key of: "EOS5jfQEtmjvFpPSCXzQaXC82jf29cJL2NJTRzTKPTvwrsjjzSW85"
```



```sh
cleos wallet import --private-key 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3
```





eosio私钥信息

```sh
eosio
Public key: EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
Private key: 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3
```





## 2. SDK使用

### 2.1 return-value合约支持

设置

```sh
curl --request POST \
    --url http://127.0.0.1:8888/v1/producer/schedule_protocol_feature_activations \
    -d '{"protocol_features_to_activate": ["0ec7e080177b2c02b278d5088611686b49d739925a92d9bfcacd7fc6b74053bd"]}'
```

部署eosio.boot

```sh
cleos set contract eosio ./bin/ eosio.boot.wasm eosio.boot.abi
```

一系列操作

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



设置完成后，可以解决student发布问题

```sh
cleos set contract student ../student/
```







### 2.2 测试合约准备

student.hpp

```cpp
#include <eosio/eosio.hpp>

using namespace eosio;
using std::string;

class[[eosio::contract("student")]] student : public contract
{
    public:
        using contract::contract;
        student(name receiver, name code, datastream<const char *> ds) : contract(receiver, code, ds) {beginid = 1;}
        uint64_t beginid = 0;
        struct [[eosio::table]] person
        {
            uint64_t  sid;
            string    sname;
            uint8_t   sage;
            auto primary_key() const { return sid; }
            
            EOSLIB_SERIALIZE( person, (sid)(sname)(sage))
        };

        typedef eosio::multi_index<"persons"_n, person> persons;

        [[eosio::action]]
        void add(uint64_t sid, string sname, uint8_t sage);
        [[eosio::action]]
        void get(uint64_t sid);
        [[eosio::action]]
        uint8_t getage(uint64_t sid);
        [[eosio::action]]
        string getname(uint64_t sid);

    private:

};


```

student.cpp

```cpp
#include "student.hpp"

void student::add(uint64_t sid, string sname, uint8_t sage)
{
    persons ps(get_self(), "yekai"_n.value);
    //auto itr = existingHostGames.find(challenger.value);
    //check(itr == existingHostGames.end(), "Game already exists.");

    ps.emplace("yekai"_n, [&](auto &g) {
        g.sid = sid;
        g.sname = sname;
        g.sage = sage;
    });
}
void student::get(uint64_t sid)
{
    persons ps(get_self(), "yekai"_n.value);
    auto itr = ps.find(sid);
    print("sid = ", itr->sid, ",sname = ", itr->sname, ", sage = ", itr->sage);
}


uint8_t student::getage(uint64_t sid)
{
    persons ps(get_self(), "yekai"_n.value);
    auto itr = ps.find(sid);
    return itr->sage;
}
string student::getname(uint64_t sid)
{
    persons ps(get_self(), "yekai"_n.value);
    auto itr = ps.find(sid);
    return itr->sname;
}


```

创建一个student账号

```sh
cleos wallet create_key
cleos create account eosio student EOS5jfQEtmjvFpPSCXzQaXC82jf29cJL2NJTRzTKPTvwrsjjzSW85
```

创建一个yekai账号

```sh
cleos wallet create_key
Created new private key with a public key of: "EOS7Zhdj33PNBywjgaySgSmvMgeD436Ds7TFVc34U9P1pSDYonAjo"

cleos create account eosio yekai EOS7Zhdj33PNBywjgaySgSmvMgeD436Ds7TFVc34U9P1pSDYonAjo
```



测试一下合约

```sh
cleos push action student add '[1001,"yekai",30]' -p yekai@active
cleos push action student add '[1002,"fuhongxue",30]' -p yekai@active
cleos get table student yekai persons
```

测试返回值的情况

```sh
yekai@叶开:~/cppwork/student$ cleos push action student get '[1002]' -p yekai@active
executed transaction: a5c293f39ab2fc51a896cc5241d1de58c66a4ea05b128c06ab9733f3b07770d7  104 bytes  218 us
#       student <= student::get                 {"sid":1002}
>> sid = 1002,sname = fuhongxue, sage = 30
warning: transaction executed locally, but may not be confirmed by the network yet         ]
yekai@叶开:~/cppwork/student$ cleos push action student getage '[1002]' -p yekai@active
executed transaction: 696500fdf28eb931a16c7d42a2b6b8138aa743ccdb5bd79e4fb12d74887aca05  104 bytes  182 us
#       student <= student::getage              {"sid":1002}
=>                                return value: 30
warning: transaction executed locally, but may not be confirmed by the network yet         ]
yekai@叶开:~/cppwork/student$ cleos push action student getname '[1002]' -p yekai@active
executed transaction: 19d8c7dc18dc559143d51757d88dd08ecd9cd76be0b6ada76169707a59657268  104 bytes  132 us
#       student <= student::getname             {"sid":1002}
=>                                return value: "fuhongxue"
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```





### 2.3 获取账户信息

```go
package main

import (
	"context"
	"encoding/json"
	"fmt"

	eos "github.com/eoscanada/eos-go"
)

func main() {
	// 1. 创建API，相当于连接到节点
	api := eos.New("http://127.0.0.1:8888")
	ctx := context.Background()

	// 2. 获取链信息
	infoResp, _:= api.GetInfo(ctx)

	fmt.Println("Chain Info", toJson(infoResp))
	// 3. 获取账户信息
	accountResp, _ := api.GetAccount(ctx, "eosio")
	fmt.Println("Account Info", toJson(accountResp))
}

//显示返回的结果
func toJson(v interface{}) string {
	out, _:= json.MarshalIndent(v, "", "  ")

	return string(out)
}
```







### 2.4 调用action



```go
package main

import (
	"context"
	"fmt"
	"log"

	eos "github.com/yekai1003/eos-go"
)

type AddData struct {
	Sid   uint64 `json:"sid"`
	Sname string `json:"sname"`
	Sage  uint8  `json:"sage"`
}

func main() {
	// 1. 连接到节点
	api := eos.New("http://127.0.0.1:8888")
	//ctx := context.Background()

	// 构建Action数据
	data := AddData{10, "messi", 33}
	actData := eos.NewActionData(data)

	// 构建调用权限级别
	level := eos.PermissionLevel{
		Actor:      eos.AN("yekai"),
		Permission: eos.PN("active"),
	}
	// 2. 创建action
	act := eos.Action{
		Account:       eos.AN("student"),
		Name:          eos.ActN("add"),
		Authorization: []eos.PermissionLevel{level},
		ActionData:    actData,
	}

	//3. 私钥导入
	keyBag := &eos.KeyBag{}
	keyBag.ImportPrivateKey(context.Background(), "5HwzChDSF6VSWCwX7rDokMfDNNuMn4g1GRsEdPihtojQ4iiMdED")

	api.SetSigner(keyBag)

	//4. 填写交易附选项
	txOpts := &eos.TxOptions{}
	if err := txOpts.FillFromChain(context.Background(), api); err != nil {
		panic(fmt.Errorf("filling tx opts: %w", err))
	}

	//5. 创建交易

	response, err := api.SignPushActionsWithOpts(context.Background(), []*eos.Action{&act}, txOpts)
	if err != nil {
		log.Panic("failed tp SignPushActionsWithOpts ", err)
	}
	fmt.Printf("-------------%+v\n", response)
	return
}

```



### 2.5 获取table数据

在获取api后，通过api可以很便捷的获取table数据

```go
package main

import (
	"context"
	"fmt"
	"log"

	eos "github.com/yekai1003/eos-go"
)

type AddData struct {
	Sid   uint64 `json:"sid"`
	Sname string `json:"sname"`
	Sage  uint8  `json:"sage"`
}

func main() {
	// 1. 连接到节点
	api := eos.New("http://127.0.0.1:8888")
	//ctx := context.Background()

	params := eos.GetTableRowsRequest{}
	params.Code = "student"
    params.Scope = "yekai"
	params.Table = "persons"
	params.JSON = true
	params.LowerBound = "1"
	params.UpperBound = "20"
	
    //2. 获取表数据
	resprows, err := api.GetTableRows(context.Background(), params)
	if err != nil {
		log.Panic("failed to GetTableRows ", err)
	}
	fmt.Printf("getrows:%+s\n", resprows.Rows)
	return
}

```





## 3. 智能合约开发

### 3.1 用户合约

用户合约功能

- 注册
- 登录

准备一个userauth用户

```sh
cleos wallet create_key
Created new private key with a public key of: "EOS6e3kECQtQNW7BC6Wwnw7eoq1ef3J5VwrqLXZwfFuHG6524Nc9u"
cleos create account eosio userauth EOS6e3kECQtQNW7BC6Wwnw7eoq1ef3J5VwrqLXZwfFuHG6524Nc9u
cleos set contract userauth ../userauth/
```

创建一个管理

```sh
cleos wallet create_key
Created new private key with a public key of: "EOS6D6pYjCcPggsYj1gnSjfSEBS798p2ZuLh922T6iBY6iG1TWfaq"
cleos create account eosio admin EOS6D6pYjCcPggsYj1gnSjfSEBS798p2ZuLh922T6iBY6iG1TWfaq
```

测试合约

```sh
cleos push action userauth userreg '["admin","zhangsan","123456"]' -p admin
cleos get table userauth admin users
cleos push action userauth login '["admin","zhangsan","123456"]' -p admin
```





### 3.2 积分合约

```sh
cleos wallet create_key

Created new private key with a public key of: "EOS5NFZNSpYHZNoQMpdT7aEe99xUL81J8oF6KXQ9AsEbDys1szCem"

cleos create account eosio yktoken EOS5NFZNSpYHZNoQMpdT7aEe99xUL81J8oF6KXQ9AsEbDys1szCem

 cleos set contract yktoken ../yktoken
```

测试合约动作

```sh
cleos push action yktoken ykcreate '["admin","ykc"]' -p admin
cleos get table yktoken admin supplys
cleos push action yktoken ykissue '["admin","ykc",10000]' -p admin
cleos get table yktoken ykc balances
cleos push action yktoken yktransfer '["admin","ykc","ykc","yekai",5000]' -p admin
cleos get table yktoken ykc balances
cleos push action yktoken ykbalanceof '["admin","ykc","yekai"]' -p admin
cleos push action yktoken yksupply '["admin","ykc"]' -p admin
```





### 3.3 任务合约



创建yktask账户

```sh
cleos wallet create_key
Created new private key with a public key of: "EOS7ESWpFUuz9g8qN6DedvUx53JLw6h9UzoiVhWJkvU5MUe5e7dkJ"

cleos create account eosio yktask EOS7ESWpFUuz9g8qN6DedvUx53JLw6h9UzoiVhWJkvU5MUe5e7dkJ
```



测试合约

```sh
 eosio-cpp -abigen -o yktask.wasm yktask.cpp
 cleos set contract yktask ../yktask
 
cleos push action yktask issuetask '["admin","yekai","write code", 200]' -p admin
cleos push action yktask issuetask '["admin","yekai","洗澡", 400]' -p admin
cleos get table yktask admin tasks
cleos push action yktask taketask '["admin",1,"alice"]' -p admin
cleos push action yktask committask '["admin",1,"alice"]' -p admin
cleos push action yktask confirmtask '["admin",1,"yekai", 3, "well done"]' -p admin
cleos push action yktask querytask '["admin",1]' -p admin
```







## 4. 后端应用开发

