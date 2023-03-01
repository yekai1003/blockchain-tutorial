# 链码开发笔记



## 1. basic链码

### 1.1 链码分析

链码启动：

- 需要主函数
- 需要新建链码
- 需要start启动链码

vendor 配置第三方包，要运行在docker，有时候可能无法联网

chaincode链码本身



```go
type SmartContract struct {
	contractapi.Contract
}
```



存放数据：ctx，交易上下文接口，每个合约的方法内都必须有该信息

```
err = ctx.GetStub().PutState(asset.ID, assetJSON)
```

关于state的操作

```go
PutState
DelState
GetState
```



### 1.2 部署basic链码



停止网络

```sh
./network.sh down
```

启动网络

```sh
./network.sh up createChannel -c ykchannel
# 查看网络启动情况
peer channel list
2021-12-17 18:38:44.721 PST [channelCmd] InitCmdFactory -> INFO 001 Endorser and orderer connections initialized
Channels peers has joined: 
ykchannel

```

启动2个组织，每个组织1个节点

链码如果没有vendor，需要手动创建

```sh
GO111MODULE=on go mod vendor
```

在test-network目录下

```sh
export PATH=${PWD}/../bin:$PATH
export FABRIC_CFG_PATH=$PWD/../config/
```

打包链码

```sh
peer lifecycle chaincode package basic.tar.gz --path ../asset-transfer-basic/chaincode-go/ --lang golang --label basic_1.0
```

设置环境变量

org1

```sh
export CORE_PEER_TLS_ENABLED=true
export CORE_PEER_LOCALMSPID="Org1MSP"
export CORE_PEER_TLS_ROOTCERT_FILE=${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt
export CORE_PEER_MSPCONFIGPATH=${PWD}/organizations/peerOrganizations/org1.example.com/users/Admin@org1.example.com/msp
export CORE_PEER_ADDRESS=localhost:7051
```

org2

```sh
export CORE_PEER_TLS_ENABLED=true
export CORE_PEER_LOCALMSPID="Org2MSP"
export CORE_PEER_TLS_ROOTCERT_FILE=${PWD}/organizations/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt
export CORE_PEER_MSPCONFIGPATH=${PWD}/organizations/peerOrganizations/org2.example.com/users/Admin@org2.example.com/msp
export CORE_PEER_ADDRESS=localhost:9051
```

安装链码(org1 & org2)

```sh
peer lifecycle chaincode install basic.tar.gz
```

查看链码安装状态

```sh
peer lifecycle chaincode queryinstalled
Installed chaincodes on peer:
Package ID: basic_1.0:573e60ee92b3a414761e53bdd783cdf21490110b8dfca6d51de2b52c4d8c8996, Label: basic_1.0

```

设置链码包环境变量(org1 & org2)

```sh
export CC_PACKAGE_ID=basic_1.0:573e60ee92b3a414761e53bdd783cdf21490110b8dfca6d51de2b52c4d8c8996
```



approve(org1 & org2)

```sh
peer lifecycle chaincode approveformyorg -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --channelID ykchannel --name basic --version 1.0 --package-id $CC_PACKAGE_ID --sequence 1 --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem
```

检查是否可以commit

```sh
peer lifecycle chaincode checkcommitreadiness --channelID ykchannel --name basic --version 1.0 --sequence 1 --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem --output json
```



commit（org1 或 org2）

```sh
peer lifecycle chaincode commit -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --channelID ykchannel --name basic --version 1.0 --sequence 1 --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem --peerAddresses localhost:7051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt --peerAddresses localhost:9051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt
```

检查是否提交

```sh
peer lifecycle chaincode querycommitted --channelID ykchannel --name basic --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem
```

执行

初始化

```sh
peer chaincode invoke -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem -C ykchannel -n basic --peerAddresses localhost:7051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt --peerAddresses localhost:9051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt -c '{"function":"InitLedger","Args":[]}'


```

查询全部资产

```sh
peer chaincode query -C ykchannel -n basic -c '{"Args":["GetAllAssets"]}'
```

添加资产

```sh
peer chaincode invoke -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem -C ykchannel -n basic --peerAddresses localhost:7051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt --peerAddresses localhost:9051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt -c '{"function":"CreateAsset","Args":["asset7","white","20","yekai","900"]}'
```

## 2. token-erc-20链码

### 2.1 链码分析



需要main函数引导，创建链码，并start

两个key：

- allowance
- totalsupply

ERC-20必须接口

- TotalSupply 总发行量（通常使用mint来解决发行问题）
- BalanceOf 账户余额查询
- Allowance 授权额度查询
- Approve 授权
- Transfer 转账
- TransferFrom 授权转账
- Transfer 转账事件
- Approval 授权事件



合约定义

```
type SmartContract struct {
	contractapi.Contract
}
```



函数实现：

- mint 空投，发行
  - amount代表金额
  - ctx上下文



API：

- GetClientIdentity 获得客户端身份
  - GetMSPID 获取MSPID
  - GetID 获取身份ID
- SetEvent  设置事件
- CreateCompositeKey 创建组合key



### 2.2 erc20部署

打包链码

```sh
peer lifecycle chaincode package erc20.tar.gz --path ../token-erc-20/chaincode-go/ --lang golang --label erc20_1.0
```

安装链码(org1 + org2)

```sh
peer lifecycle chaincode install erc20.tar.gz
```

查询链码安装情况

```sh
$ peer lifecycle chaincode queryinstalled
Installed chaincodes on peer:
Package ID: basic_1.0:573e60ee92b3a414761e53bdd783cdf21490110b8dfca6d51de2b52c4d8c8996, Label: basic_1.0
Package ID: erc20_1.0:496f8dc15ef437c33a0608ec21ba56748a954dd3f71e44725c6a46440574afd7, Label: erc20_1.0

```

设置环境变量（org1 + org2）

```sh
export ERC20_ID=erc20_1.0:496f8dc15ef437c33a0608ec21ba56748a954dd3f71e44725c6a46440574afd7
```

approve(org1 + org2)

```sh
peer lifecycle chaincode approveformyorg -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --channelID ykchannel --name erc20 --version 1.0 --package-id $ERC20_ID --sequence 1 --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem
```

检查是否可以commit

```sh
peer lifecycle chaincode checkcommitreadiness --channelID ykchannel --name erc20 --version 1.0 --sequence 1 --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem --output json
```



commit（org1 或 org2）

```sh
peer lifecycle chaincode commit -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --channelID ykchannel --name erc20 --version 1.0 --sequence 1 --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem --peerAddresses localhost:7051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt --peerAddresses localhost:9051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt
```

### 2.3 测试token-erc-20

由于版本更新，链码中增加了Initialize函数，因此需要先调用，否则可能会报错。
函数原型为：
```go
func (s *SmartContract) Initialize(ctx contractapi.TransactionContextInterface, name string, symbol string, decimals string)
```
需要传递名称、符号以及精度3个参数，精度代表小数点的位数，应填写1个数字。


```sh
peer chaincode invoke -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem -C ykchannel -n erc20 --peerAddresses localhost:7051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt --peerAddresses localhost:9051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt -c '{"function":"Initialize","Args":["YKToken","YKT","6"]}'
```

mint测试(org1可以执行)

```sh
peer chaincode invoke -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem -C ykchannel -n erc20 --peerAddresses localhost:7051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt --peerAddresses localhost:9051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt -c '{"function":"Mint","Args":["900"]}'


```

ClientAccountBalance测试

```sh
peer chaincode query -C ykchannel -n erc20 -c '{"Args":["ClientAccountBalance"]}'

```

ClientAccountID测试

```sh
peer chaincode query -C ykchannel -n erc20 -c '{"Args":["ClientAccountID"]}'

eDUwOTo6Q049QWRtaW5Ab3JnMS5leGFtcGxlLmNvbSxPVT1hZG1pbixMPVNhbiBGcmFuY2lzY28sU1Q9Q2FsaWZvcm5pYSxDPVVTOjpDTj1jYS5vcmcxLmV4YW1wbGUuY29tLE89b3JnMS5leGFtcGxlLmNvbSxMPVNhbiBGcmFuY2lzY28sU1Q9Q2FsaWZvcm5pYSxDPVVT

eDUwOTo6Q049QWRtaW5Ab3JnMi5leGFtcGxlLmNvbSxPVT1hZG1pbixMPVNhbiBGcmFuY2lzY28sU1Q9Q2FsaWZvcm5pYSxDPVVTOjpDTj1jYS5vcmcyLmV4YW1wbGUuY29tLE89b3JnMi5leGFtcGxlLmNvbSxMPVNhbiBGcmFuY2lzY28sU1Q9Q2FsaWZvcm5pYSxDPVVT
```

BalanceOf测试

```sh
peer chaincode query -C ykchannel -n erc20 -c '{"Args":["BalanceOf","eDUwOTo6Q049QWRtaW5Ab3JnMS5leGFtcGxlLmNvbSxPVT1hZG1pbixMPVNhbiBGcmFuY2lzY28sU1Q9Q2FsaWZvcm5pYSxDPVVTOjpDTj1jYS5vcmcxLmV4YW1wbGUuY29tLE89b3JnMS5leGFtcGxlLmNvbSxMPVNhbiBGcmFuY2lzY28sU1Q9Q2FsaWZvcm5pYSxDPVVT"]}'

peer chaincode query -C ykchannel -n erc20 -c '{"Args":["BalanceOf","eDUwOTo6Q049QWRtaW5Ab3JnMi5leGFtcGxlLmNvbSxPVT1hZG1pbixMPVNhbiBGcmFuY2lzY28sU1Q9Q2FsaWZvcm5pYSxDPVVTOjpDTj1jYS5vcmcyLmV4YW1wbGUuY29tLE89b3JnMi5leGFtcGxlLmNvbSxMPVNhbiBGcmFuY2lzY28sU1Q9Q2FsaWZvcm5pYSxDPVVT"]}'

peer chaincode query -C ykchannel -n erc20 -c '{"Args":["TotalSupply"]}'
```

测试Transfer

```sh
peer chaincode invoke -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem -C ykchannel -n erc20 --peerAddresses localhost:7051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt --peerAddresses localhost:9051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt -c '{"function":"Transfer","Args":["yekai","666"]}'


peer chaincode query -C ykchannel -n erc20 -c '{"Args":["BalanceOf","yekai"]}'
```



## 3. 部署结婚证书链码

链码

```go
package main

import (
	"bytes"
	"encoding/json"
	"fmt"
	"log"

	"github.com/xlcetc/cryptogm/sm/sm3"

	"github.com/hyperledger/fabric-contract-api-go/contractapi"
)

type MarriageContract struct {
	contractapi.Contract
}

type RegPerson struct {
	MarriageID string `json:"marriage_id"`
	PersonName string `json:"person_name"`
}

type MarrigeInfo struct {
	MarriageID string `json:"marriage_id"`
	Name1      string `json:"name1"`
	Name2      string `json:"name2"`
	TimeStamp  int64  `json:"timestamp"`
	Desc       string `json:"desc"`
}

type ResponseMsg struct {
	Code    string
	CodeMsg string
	Data    interface{}
}

func (s *MarriageContract) Register(ctx contractapi.TransactionContextInterface, cid, name string) error {

	//1. 权限判断
	clientMSPID, err := ctx.GetClientIdentity().GetMSPID()
	if err != nil {
		return fmt.Errorf("failed to get MSPID: %v", err)
	}
	if clientMSPID != "Org1MSP" {
		return fmt.Errorf("client is not authorized to mint new tokens")
	}
	//2. 判断cid是否已经注册了
	regdata, err := ctx.GetStub().GetState(cid)
	if err != nil {
		return err
	}
	if regdata != nil {
		return fmt.Errorf("person's cid already exists")
	}
	//3. 添加注册数据到链码
	rp := RegPerson{"", name}
	jsondata, err := json.Marshal(rp)
	if err != nil {
		return err
	}
	err = ctx.GetStub().PutState(cid, jsondata)

	return err
}

func (s *MarriageContract) Create(ctx contractapi.TransactionContextInterface, cid1, cid2 string) error {

	//1. 权限判断
	clientMSPID, err := ctx.GetClientIdentity().GetMSPID()
	if err != nil {
		return fmt.Errorf("failed to get MSPID: %v", err)
	}
	if clientMSPID != "Org1MSP" {
		return fmt.Errorf("client is not authorized to mint new tokens")
	}
	//2. 检查cid1是否注册，是否已婚
	data1, err := ctx.GetStub().GetState(cid1)
	if err != nil {
		return err
	}
	if data1 == nil {
		return fmt.Errorf("user does not register")
	}

	var rp1 RegPerson

	err = json.Unmarshal(data1, &rp1)
	if err != nil {
		return err
	}

	if rp1.MarriageID != "" {
		return fmt.Errorf("user already married")
	}

	//3. 检查cid2是否注册，是否已婚
	data2, err := ctx.GetStub().GetState(cid2)
	if err != nil {
		return err
	}
	if data1 == nil {
		return fmt.Errorf("user does not register")
	}

	var rp2 RegPerson

	err = json.Unmarshal(data2, &rp2)
	if err != nil {
		return err
	}

	if rp2.MarriageID != "" {
		return fmt.Errorf("user already married")
	}

	//4. 生成结婚证书id
	marriageID := makeMarriageID(cid1, cid2)

	//5. 结婚证书信息存储
	var mi MarrigeInfo
	mi.MarriageID = marriageID
	mi.Name1 = rp1.PersonName
	mi.Name2 = rp2.PersonName
	tm, _ := ctx.GetStub().GetTxTimestamp()
	mi.TimeStamp = tm.GetSeconds()
	mi.Desc = "love for ever"

	jsonMI, err := json.Marshal(mi)
	if err != nil {
		return err
	}
	err = ctx.GetStub().PutState(mi.MarriageID, jsonMI)
	if err != nil {
		return err
	}

	//6. 建立cid1与marriageid的关系
	rp1.MarriageID = marriageID
	data1, err = json.Marshal(rp1)
	if err != nil {
		return err
	}
	err = ctx.GetStub().PutState(cid1, data1)
	if err != nil {
		return err
	}

	//7. 建立cid2与marriageid的关系
	rp2.MarriageID = marriageID
	data2, err = json.Marshal(rp2)
	if err != nil {
		return err
	}
	err = ctx.GetStub().PutState(cid2, data2)
	if err != nil {
		return err
	}

	return nil
}

func makeMarriageID(cid1, cid2 string) string {
	data := bytes.Join([][]byte{[]byte(cid1),
		[]byte(cid2),
	}, []byte{})

	return fmt.Sprintf("%x", sm3.SumSM3(data))
}

func (s *MarriageContract) Query(ctx contractapi.TransactionContextInterface, cid string) (*MarrigeInfo, error) {
	//1. 通过cid获取人注册信息
	regJson, err := ctx.GetStub().GetState(cid)
	if err != nil {
		return nil, err
	}
	if regJson == nil {
		return nil, fmt.Errorf("user does not register")
	}
	// 解析json
	var rp RegPerson
	err = json.Unmarshal(regJson, &rp)
	if err != nil {
		return nil, err
	}
	if rp.MarriageID == "" {
		return nil, fmt.Errorf("user does not married")
	}
	//2. 通过结婚证书id获取结婚证书内容
	miData, err := ctx.GetStub().GetState(rp.MarriageID)
	if err != nil {
		return nil, err
	}
	var mi MarrigeInfo
	err = json.Unmarshal(miData, &mi)
	if err != nil {
		return nil, err
	}
	return &mi, nil
}

func (s *MarriageContract) Query3(ctx contractapi.TransactionContextInterface, cid string) *ResponseMsg {
	//1. 通过cid获取人注册信息
	var resp ResponseMsg
	resp.Code = "0"
	resp.CodeMsg = "ok"
	regJson, err := ctx.GetStub().GetState(cid)
	if err != nil {
		resp.CodeMsg = err.Error()
		return &resp
	}
	if regJson == nil {
		resp.CodeMsg = fmt.Errorf("user does not register").Error()
		return &resp
	}
	// 解析json
	var rp RegPerson
	err = json.Unmarshal(regJson, &rp)
	if err != nil {
		resp.CodeMsg = err.Error()
		return &resp
	}
	resp.Data = rp

	return &resp
}

func main() {
	tokenChaincode, err := contractapi.NewChaincode(&MarriageContract{})
	if err != nil {
		log.Panicf("Error creating MarriageContract chaincode: %v", err)
	}

	if err := tokenChaincode.Start(); err != nil {
		log.Panicf("Error starting MarriageContract chaincode: %v", err)
	}
}

```





打包代码

```sh
peer lifecycle chaincode package marriage.tar.gz --path ./marriage --lang golang --label marriage_1.0
```

安装链码

```sh
peer lifecycle chaincode install marriage.tar.gz
```

设置环境变量

```sh
peer lifecycle chaincode queryinstalled
Installed chaincodes on peer:
Package ID: basic_1.0:573e60ee92b3a414761e53bdd783cdf21490110b8dfca6d51de2b52c4d8c8996, Label: basic_1.0
Package ID: erc20_1.0:496f8dc15ef437c33a0608ec21ba56748a954dd3f71e44725c6a46440574afd7, Label: erc20_1.0
Package ID: marriage_1.0:80791cc856d922d52e73bb22b50cca6ec2b1044c3d037458a37f21dc7fa33ef2, Label: marriage_1.0


export PKG_MARRIAGE=marriage_1.0:80791cc856d922d52e73bb22b50cca6ec2b1044c3d037458a37f21dc7fa33ef2
```



授权

```sh
peer lifecycle chaincode approveformyorg -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --channelID ykchannel --name marriage --version 1.0 --package-id $PKG_MARRIAGE --sequence 1 --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem
```

提交

```sh
peer lifecycle chaincode commit -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --channelID ykchannel --name marriage --version 1.0 --sequence 1 --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem --peerAddresses localhost:7051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt --peerAddresses localhost:9051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt
```

测试运行

```sh
peer chaincode invoke -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem -C ykchannel -n marriage --peerAddresses localhost:7051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt --peerAddresses localhost:9051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt -c '{"function":"Register","Args":["1001","alice"]}'

peer chaincode invoke -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem -C ykchannel -n marriage --peerAddresses localhost:7051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt --peerAddresses localhost:9051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt -c '{"function":"Register","Args":["1002","bob"]}'

peer chaincode invoke -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem -C ykchannel -n marriage --peerAddresses localhost:7051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt --peerAddresses localhost:9051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt -c '{"function":"Create","Args":["1002","1001"]}'


peer chaincode invoke -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem -C ykchannel -n marriage --peerAddresses localhost:7051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt --peerAddresses localhost:9051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt -c '{"function":"Query","Args":["1002"]}'

peer chaincode query -C ykchannel -n marriage -c '{"Args":["Query","1001"]}'
```



## 4. 关于链码的猜想

### 4.1 是否隔离



测试代码

```go
package main

import (
	"encoding/json"
	"fmt"
	"log"

	"github.com/hyperledger/fabric-contract-api-go/contractapi"
)

type MarriageContract struct {
	contractapi.Contract
}

type RegPerson struct {
	MarriageID string `json:"marriage_id"`
	PersonName string `json:"person_name"`
}

func (s *MarriageContract) Query(ctx contractapi.TransactionContextInterface, cid string) (*RegPerson, error) {
	//1. 通过cid获取人注册信息
	regJson, err := ctx.GetStub().GetState(cid)
	if err != nil {
		return nil, err
	}
	if regJson == nil {
		return nil, fmt.Errorf("user does not register")
	}
	// 解析json
	var rp RegPerson
	err = json.Unmarshal(regJson, &rp)
	if err != nil {
		return nil, err
	}

	return &rp, nil
}

func main() {
	tokenChaincode, err := contractapi.NewChaincode(&MarriageContract{})
	if err != nil {
		log.Panicf("Error creating MarriageContract chaincode: %v", err)
	}

	if err := tokenChaincode.Start(); err != nil {
		log.Panicf("Error starting MarriageContract chaincode: %v", err)
	}
}

```

部署代码

```sh
peer lifecycle chaincode package demo.tar.gz --path ../demo --lang golang --label demo_1.0

export DEMO_PKG=demo_1.0:cbf1ef3b3b98bf5bcb0efa2f62657dd7e0e4811e67351b2839a551f1e237601c


peer lifecycle chaincode approveformyorg -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --channelID ykchannel --name demo --version 1.0 --package-id $DEMO_PKG --sequence 1 --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem


peer lifecycle chaincode commit -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --channelID ykchannel --name demo --version 1.0 --sequence 1 --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem --peerAddresses localhost:7051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt --peerAddresses localhost:9051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt

peer chaincode query -C ykchannel -n demo -c '{"Args":["Query","1001"]}'
```



### 4.2 clientID和什么有关

### 4.3 返回值有几个，类型有什么要求？

1. 返回值只能<=2个
2. 类型可以是原生类型，也可以是自定义结构，可以使用interface{}类型



测试步骤

```sh
peer lifecycle chaincode package demoret.tar.gz --path ../demoret --lang golang --label demoret_1.0

peer lifecycle chaincode install demoret.tar.gz

export DEMORET_PKG=demoret_1.0:a5ba1c2b90bfa79bbcde425a2d44e71917fb45d250949314cb8698b4c9fde679

peer lifecycle chaincode approveformyorg -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --channelID ykchannel --name demoret --version 1.0 --package-id $DEMORET_PKG --sequence 1 --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem


peer lifecycle chaincode commit -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --channelID ykchannel --name demoret --version 1.0 --sequence 1 --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem --peerAddresses localhost:7051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt --peerAddresses localhost:9051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt


peer chaincode query -C ykchannel -n demoret -c '{"Args":["Query","1001"]}'
peer chaincode query -C ykchannel -n demoret -c '{"Args":["Query3","1001"]}'
```



### 4.4 chaincode升级

重新打包链码，注意tag

```sh
peer lifecycle chaincode package marriage.2.0.tar.gz --path ../marriage --lang golang --label marriage_2.0

export PKG_MARRIAGE=marriage_2.0:0658f518504e4f61e6f3fbb592c994597b0e17a407633e52ace7f98788b1835c


peer lifecycle chaincode approveformyorg -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --channelID ykchannel --name marriage --version 2.0 --package-id $PKG_MARRIAGE --sequence 2 --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem

peer lifecycle chaincode commit -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --channelID ykchannel --name marriage --version 2.0 --sequence 2 --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem --peerAddresses localhost:7051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt --peerAddresses localhost:9051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt

peer lifecycle chaincode querycommitted --channelID ykchannel --name marriage --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem

peer chaincode query -C ykchannel -n marriage -c '{"Args":["Query","1001"]}'
```

