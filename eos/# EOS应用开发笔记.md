# EOS应用开发笔记

## 1. 节点准备





## 2. SDK使用



### 2.1 测试合约准备

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



### 2.2 获取账户信息

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







### 2.3 调用action



```go
func main() {
	// 1. 连接到节点
	api := eos.New("http://127.0.0.1:8888")
	ctx := context.Background()

	// 构建Action数据
	data := AddData{14, "zhaokk4", 35}
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
	keyBag.ImportPrivateKey(context.Background(), "5KMLqUbbD5ehkbvBgZetU2wixenrzmEBhYKVWevsM7Ee7gRNzud")
	if err != nil {
		log.Panic("failed to ListKeys ", err)
	}

	api.SetSigner(keyBag)

	//4. 填写交易附选项
	txOpts := &eos.TxOptions{}
	if err := txOpts.FillFromChain(context.Background(), api); err != nil {
		panic(fmt.Errorf("filling tx opts: %w", err))
	}

	//5. 创建交易
	tx := eos.NewTransaction([]*eos.Action{&act}, txOpts)

	response, err := api.SignPushActionsWithOpts(context.Background(), []*eos.Action{&act}, txOpts)
	if err != nil {
		log.Panic("failed tp SignPushActionsWithOpts ", err)
	}
	fmt.Printf("-------------%+v\n", response)
	return
}
```



### 2.4 获取table数据

在获取api后，通过api可以很便捷的获取table数据

```go
params := eos.GetTableRowsRequest{}
	params.Code = "student"
	params.Table = "persons"
	params.Scope = "yekai"
	params.JSON = true
	params.LowerBound = "1"
	params.UpperBound = "20"

	resprows, err := api.GetTableRows(context.Background(), params)
	if err != nil {
		log.Panic("failed to GetTableRows ", err)
	}
	fmt.Printf("getrows:%+s\n", resprows.Rows)
```



### 2.5 return-value合约处理







## 3. 智能合约开发

## 4. 后端应用开发

