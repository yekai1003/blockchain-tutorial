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

> 治理

区块生产者提出对宪法的修改，并获得15/21的批准。  

在连续30天内，区块生产者对新宪法的批准率为15/21。  

所有用户都必须表示接受新章程，以此作为未来交易处理的条件。  

块生产者采用对源代码的更改来反映构造的更改，并使用新构造的哈希值将其提交给区块链。  

在连续30天内，区块生产者对新法规的批准率为15/21。  

对代码的修改将在7天后生效，在源代码批准后给予所有非生产的完整节点1周的升级时间。  

所有没有升级到新代码的节点都会自动关闭。 

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200407115828682.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3djYzE5ODQwODI3,size_16,color_FFFFFF,t_70)

如果客户不需要处理所有的交易，那么与其他区块链集成就容易得多。 毕竟，一个交易所只关心交易的进进出出，仅此而已。 如果交易所链能够利用轻量级默克尔存款证明，而不是完全信任自己的区块生产者，那将是理想的。 至少，在与另一个区块链同步时，链上的块生产者希望保持尽可能小的开销。  



LCV的目标是生成相对轻量级的存在证明，跟踪相对轻量级数据集的任何人都可以验证该证明。 在本例中，目标是证明特定的事务包含在特定的块中，并且该块包含在特定的区块链的验证历史中。  

 

比特币支持交易验证，假设所有节点都能访问完整的区块报头历史，相当于每年4MB的区块报头。 以每秒10个事务的速度，有效的证明大约需要512字节。 这对于10分钟的区块间隔的区块链来说工作得很好，但是对于0.5秒的区块间隔的区块链来说不再是“轻的”。 



如果客户端不需要处理全部交易的话，和其他区块链的结合将变得非常容易。毕竟类似交易所这样的客户端，它只关心资产的转入和转出。理想情况下，交易所的链可以用转账交易的轻量默克尔证明（来完成交易所业务），而不是完全信任某个区块生产者。每条链的区块生产者都希望和其他链同步的开销尽可能地小。

轻量客户端验证（LCV）的目标是生成相对轻量的存在证明，这些证明可以被任何关心一个轻量的数据集的客户端用来验证。在上述例子中，LCV 的目的就是为了用来证明某笔交易已经被包含进某一特定区块，而这一区块已经被某条特定的链所收录。

比特币支持交易验证的功能，这一功能基于一个假设，那就是所有的节点都可以访问到全部的区块头历史数据（区块头数据每年增加 4MB）。在每秒 10 笔交易的吞吐下，一个验证用到的存储空间约为 512 个字节。对于 10 分钟一个区块的比特币来说，这是可行的。但对于拥有 0.5 秒的出块速度的 EOS.IO 软件来说，这个机制显然不够轻量。

任何有不可逆区块头数据的用户在交易被区块记录后，都可以使用 EOS.IO 提供的轻量证明。轻量证明的哈希连接（hash-linked）结构表明，最多只要 1024 个字节，即可验证任何一笔交易的存在与否。

考虑到区块链中的区块的 id 和区块头都是可信的且不可逆的，因此证明某个区块被包含在某个区块链中也是可行的。这类证明最多只需 ceil(log2(N)) 次摘要计算即可完成，其中 N 为区块链中的区块个数。就 SHA256 这种摘要算法来说，你只需要 864 个字节就可以在一个有着 1 亿个区块的链上验证某个区块的存在。

使用合适的哈希连接（hash-linking）机制生产区块以启用上述证明，几乎不会带来什么额外开销，所以这种方式十分可行。

若要在其他链上验证证明，时间、空间和带宽上都有很多优化空间。追踪全部的区块头（每年 420MB 递增）可以将证明维持在比较小的空间占用。仅追踪最近的区块头会在最小长期存储和证明大小之间实现平衡。另外也可以采用惰性求值的方式，记录过去的证明的中间哈希值。新证明只需要包含已知的稀疏树的连接。具体选取何种方式，取决于默克尔证明引用的带有交易的外部区块的比例。

当互联和耦合程度达到一定的复杂度之后，将两条链的数据合并将更简单高效，如此一来也就不再需要默克尔证明了。因为性能的原因，跨链证明的频度当然是越小越好。


权限示例

| 允许              | 账户/公钥   | 重量 | 临界点 |
| :---------------- | :---------- | :--- | :----- |
| 发布              | 鲍勃@active | 2    | 2      |
| 斯泰西@active     | 2           |      |        |
| EOS7Hnv4iBfcw2... | 1           |      |        |
| EOS3Wo1p9er7fh... | 1           |      |        |

![image-20211125103017307](C:\Users\95762\AppData\Roaming\Typora\typora-user-images\image-20211125103017307.png)



- RAM - This resource is the amount of RAM available to an account. RAM stores smart contracts loaded on the blockchain. Smart contacts use RAM via the multi-index table to store smart contract state. Spend tokens to purchase more RAM, RAM can be sold.
- CPU - This resource is the amount of CPU which can be used by an account in each 24 hour period. Transactions consume CPU. Stake tokens for more CPU. Unstaking returns CPU.
- NET - This resource is the amount of data which can be written to blockchain blocks by an account in each 24 hour period. The blockchain blocks store transactions and transaction parameters, the history of blockchain . Stake tokens for more NET. Unstaking returns NET.

