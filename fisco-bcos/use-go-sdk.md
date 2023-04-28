# use fisco-bcos go-sdk

特别注意：go语言的版本至少是1.17。

## fisco-bcos 2.0

下载库

```sh
git clone -b master-FISCO-BCOS-v2 https://github.com/FISCO-BCOS/go-sdk.git
cd cmd/abigen/
go build
```

如果缺少库，可以按提示安装依赖库。

```sh
go mod download github.com/FISCO-BCOS/crypto
go get github.com/FISCO-BCOS/go-sdk/core/types
go get github.com/FISCO-BCOS/go-sdk/cmd/abigen
```

编译得到的abigen可以留作以后使用。

下载solc编译器，在go-sdk工程的tools目录有下载工具。

```sh
bash go-sdk/tools/download_solc.sh -v 0.6.10
mv solc-0.6.10 ~/bin
```

创建sdkdemo工程

```sh
mkdir sdkdemo
cd sdkdemo
```

配置config.toml文件

```toml
[Network]
#type rpc or channel
Type="channel"
CAFile="ca.crt"
Cert="sdk.crt"
Key="sdk.key"
[[Network.Connection]]
NodeURL="127.0.0.1:20200"
GroupID=1
# [[Network.Connection]]
# NodeURL="127.0.0.1:20200"
# GroupID=2

[Account]
# only support PEM format for now
KeyFile="accounts/sender.pem"

[Chain]
ChainID=1
SMCrypto=false
```

需要将节点启动目录sdk内的证书文件ca.crt、sdk.crt、sdk.key拷贝到工程目录，sender.pem是私钥文件，可以使用github.com/FISCO-BCOS/console里的get_account.sh工具来生成。

sender.pem文件内容如下。

```pem
-----BEGIN PRIVATE KEY-----
MIGEAgEAMBAGByqGSM49AgEGBSuBBAAKBG0wawIBAQQggLsYjDW2lwBA/ZsSfKGI
v7CXqpE+D7UjEmqq+3dBnluhRANCAATGB/al5rRz38fcRzyUxjFIVOuQuNg+hyaG
UiG+JbXLgBPq0j7TV3hBavEyfYFAf7vivUP3XP7+z+UVqANyqVsS
-----END PRIVATE KEY-----
```

准备智能合约，保存到bcos/HelloWorld.sol文件。

```solidity
// SPDX-License-Identifier: Apache-2.0
pragma solidity >=0.6.10 <0.8.20;

contract HelloWorld {
    string value;
    event setValue(string v, address indexed from, address indexed to, int256 value);
    int public version;

    constructor(string memory initValue) public {
        value = initValue;
        version = 0;
    }

    function get() public view returns (string memory) {
        return value;
    }

    function set(string calldata v) public returns (string memory) {
        string memory old = value;
        value = v;
        version = version + 1;
        emit setValue(v, tx.origin, msg.sender, version);
        return old;
    }
}

```

使用之前下载的solc编译器来编译合约代码，得到abi和bin两个文件。

```sh
solc-0.6.10 --abi --bin HelloWorld.sol -o ./
```

使用abigen编译abi和bin代码来得到go代码。

```sh
abigen -abi HelloWorld.abi -bin HelloWorld.bin -type hello -pkg bcos -out hello.go
```

在sdkdemo创建main.go文件

```go
package main

import (
	"fmt"
	"log"

	"sdkdemo/bcos"

	"github.com/FISCO-BCOS/go-sdk/client"
	"github.com/FISCO-BCOS/go-sdk/conf"
)

func main() {
	//1. 解析配置文件
	configs, err := conf.ParseConfigFile("config.toml")
	if err != nil {
		log.Fatalf("ParseConfigFile failed, err: %v", err)
	}

	//2. 连接节点
	client, err := client.Dial(&configs[0])
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("sender:", client.GetCallOpts().From.Hex())

	fmt.Println("-------test-----deploy-------")
	addr, _, instance, err := bcos.DeployHello(client.GetTransactOpts(), client)
	fmt.Println("addr:", addr.Hex())
	fmt.Println("-------test-----read-function-------")
	msg, err := instance.GetMsg(client.GetCallOpts())
	fmt.Println("msg:", msg)
	fmt.Println("-------test-----write-function-------")
	tx, receipt, err := instance.SetMsg(client.GetTransactOpts(), "hello,fisco")
	fmt.Println("tx.hash:", tx.Hash().Hex())
	fmt.Println("blockNumber:", receipt.BlockNumber)
	fmt.Println("-------test-----read-function--again-------")
	msg, err = instance.GetMsg(client.GetCallOpts())
	fmt.Println("msg:", msg)
	if err != nil {
		log.Panic("failed to test", err)
	}
	fmt.Println("test done")

}
```

创建go.mod

```sh
go mod init sdkdemo
```

修改go.mod文件，指向本地go-sdk工程，在go.mod添加代码。

```sh
replace github.com/FISCO-BCOS/go-sdk v1.0.0 => ../go-sdk
```

如果有必要，也可以将go.mod引用的go-ethereum版本修改为v1.10.21

```sh
go mod tidy
go build
```

执行

```sh
./sdkdemo
sender: 0x5946A2eC703E74Ce91Ac0703396BE65DAEB5eA99
-------test-----deploy-------
addr: 0x0071aD8aCFBe9a1e31AbAB6f2c891960a00cD3Bd
-------test-----read-function-------
msg: hello, yekai!
-------test-----write-function-------
tx.hash: 0xf8225df3927667e4064746fb6c20cb19d0b1868f36dea83c2936bac51015d9cf
blockNumber: 0xc6
-------test-----read-function--again-------
msg: hello,fisco
test done
```

## fisco-bcos 3.0

下载库

```sh
git clone https://github.com/FISCO-BCOS/go-sdk.git
cd cmd/abigen/
go build
```

如果缺少库，可以按提示安装依赖库。

```sh
go mod download github.com/FISCO-BCOS/crypto
go get github.com/FISCO-BCOS/go-sdk/core/types
go get github.com/FISCO-BCOS/go-sdk/cmd/abigen
```

编译得到的abigen可以留作以后使用。

下载solc编译器，在go-sdk工程的tools目录有下载工具。

```sh
bash go-sdk/tools/download_solc.sh -v 0.8.11
mv solc-0.8.11 ~/bin
# 下载fisco-bcos-csdk
sudo go-sdk/tools/download_csdk_lib.sh
```

创建sdkdemo工程

```sh
mkdir sdkdemo
cd sdkdemo
```

***需要将节点启动目录sdk内的证书文件ca.crt、sdk.crt、sdk.key拷贝到工程目录。***

准备智能合约，保存到bcos/HelloWorld.sol文件。

```solidity
// SPDX-License-Identifier: Apache-2.0
pragma solidity >=0.6.10 <0.8.20;

contract HelloWorld {
    string value;
    event setValue(string v, address indexed from, address indexed to, int256 value);
    int public version;

    constructor(string memory initValue) public {
        value = initValue;
        version = 0;
    }

    function get() public view returns (string memory) {
        return value;
    }

    function set(string calldata v) public returns (string memory) {
        string memory old = value;
        value = v;
        version = version + 1;
        emit setValue(v, tx.origin, msg.sender, version);
        return old;
    }
}

```

使用之前下载的solc编译器来编译合约代码，得到abi和bin两个文件。

```sh
solc-0.8.11 --abi --bin HelloWorld.sol -o ./
```

使用abigen编译abi和bin代码来得到go代码。

```sh
abigen -abi HelloWorld.abi -bin HelloWorld.bin -type HelloWorld -pkg bcos -out hello.go
```

在sdkdemo创建main.go文件

```go
package main

import (
    "context"
    "encoding/hex"
    "fmt"
    "log"

    "github.com/FISCO-BCOS/go-sdk/client"
    "github.com/FISCO-BCOS/go-sdk/core/types"
    "sdkdemo/bcos"
)

func main() {
     privateKey, _ := hex.DecodeString("145e247e170ba3afd6ae97e88f00dbc976c2345d511b0f6713355d19d8b80b58")
    config := &client.Config{IsSMCrypto: false, GroupID: "group0",
        PrivateKey: privateKey, Host: "127.0.0.1", Port: 20200, TLSCaFile: "./ca.crt", TLSKeyFile: "./sdk.key", TLSCertFile: "./sdk.crt"}
    client, err := client.DialContext(context.Background(), config)
    if err != nil {
        log.Fatal(err)
    }
    input := "HelloWorld deployment 1.0"
    fmt.Println("=================DeployHelloWorld===============")
    address, receipt, instance, err := bcos.DeployHelloWorld(client.GetTransactOpts(), client, input)
    if err != nil {
        log.Fatal(err)
    }
    fmt.Println("contract address: ", address.Hex()) // the address should be saved, will use in next example
    fmt.Println("transaction hash: ", receipt.TransactionHash)

    fmt.Println("================================")
    helloSession := &bcos.HelloWorldSession{Contract: instance, CallOpts: *client.GetCallOpts(), TransactOpts: *client.GetTransactOpts()}

    version, err := helloSession.Version()
    if err != nil {
        log.Fatal(err)
    }

    fmt.Println("version :", version) // "HelloWorld deployment 1.0"

    ret, err := helloSession.Get()
    if err != nil {
        fmt.Printf("hello.Get() failed: %v", err)
        return
    }
    done := make(chan bool)
    _, err = helloSession.WatchAllSetValue(nil, func(ret int, logs []types.Log) {
        fmt.Printf("WatchAllSetValue receive statud: %d, logs: %v\n", ret, logs)
        setValue, err := helloSession.ParseSetValue(logs[0])
        if err != nil {
            fmt.Printf("hello.WatchAllSetValue() failed: %v", err)
            panic("WatchAllSetValue hello.WatchAllSetValue() failed")
        }
        fmt.Printf("receive setValue: %+v\n", *setValue)
        done <- true
    })
    if err != nil {
        fmt.Printf("hello.WatchAllSetValue() failed: %v", err)
        return
    }
    fmt.Printf("Get: %s\n", ret)
    fmt.Println("================================")

    oldValue, _, receipt, err := helloSession.Set("hello fisco")
    fmt.Println("old value is: ", oldValue)
    if err != nil {
        log.Fatal(err)
    }

    fmt.Printf("transaction hash of receipt: %s\n", receipt.GetTransactionHash())

    ret, err = helloSession.Get()
    if err != nil {
        fmt.Printf("hello.Get() failed: %v", err)
        return
    }
    fmt.Printf("Get: %s\n", ret)
    <-done
}

```

创建go.mod

```sh
go mod init sdkdemo
```

修改go.mod文件，指向本地go-sdk工程，在go.mod添加代码。***这是因为go-sdk目前没有发布新的tag，所以暂时需要使用本地工程来适配***。

```sh
replace github.com/FISCO-BCOS/go-sdk v1.0.0 => ../go-sdk
```

编译sdkdemo工程。

```sh
go mod tidy
go build
```

执行

```sh
Not found available log config(./clog.ini or ./conf/clog.ini), use the default configuration items
=================DeployHelloWorld===============
contract address:  0xd24180cc0feF2f3E545de4F9AAFc09345cD08903
transaction hash:  0xa8150b95ac87dee35a868c115ee543f0abb1263828ebf58b4667e809ddf1f6f5
================================
version : 0
Get: HelloWorld deployment 1.0
================================
old value is:  HelloWorld deployment 1.0
transaction hash of receipt: 0xaf71361b66078fc40639dd30cd78a92bc10c45df014c68e818a5c890b13914fc
Get: hello fisco
WatchAllSetValue receive statud: 0, logs: [{0xd24180cc0feF2f3E545de4F9AAFc09345cD08903 [0xc3bf5911f8e0476e774566ef3fa1259f04156ba5c61ea5ff35c0201390381f96 0x000000000000000000000000fbb18d54e9ee57529cda8c7c52242efe879f064f 0x000000000000000000000000fbb18d54e9ee57529cda8c7c52242efe879f064f] [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 64 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 11 104 101 108 108 111 32 102 105 115 99 111 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] 5 0xaf71361b66078fc40639dd30cd78a92bc10c45df014c68e818a5c890b13914fc 0 0}]
receive setValue: {V:hello fisco From:0xFbb18d54e9Ee57529cda8c7c52242EFE879f064F To:0xFbb18d54e9Ee57529cda8c7c52242EFE879f064F Value:+1 Raw:{Address:0x0000000000000000000000000000000000000000 Topics:[] Data:[] BlockNumber:0 TxHash:0x0000000000000000000000000000000000000000000000000000000000000000 TxIndex:0 Index:0}}
```
