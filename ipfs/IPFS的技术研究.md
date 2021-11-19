# IPFS的技术研究



## 1. 如何安装ipfs

ipfs可以安装桌面版，客户端版

下面介绍安装client版本

```sh
wget https://github.com/ipfs/go-ipfs/releases/download/v0.10.0/go-ipfs_v0.10.0_linux-amd64.tar.gz
```

解压缩文件

```sh
tar zxvf go-ipfs_v0.10.0_linux-amd64.tar.gz
```

进入到go-ipfs目录

```sh
cd go-ipfs
```

运行install.sh脚本

```sh
sudo ./install.sh
```

检查版本

```sh
ipfs --version
```



## 2. 搭建私有网络

准备2台主机：

- 192.168.137.138
- 192.168.137.140 

分别在两台主机安装ipfs，步骤略去。

在138主机创建一个ipfsdemo目录，执行初始化

```sh
ipfs init
```

在140主机上同样的操作，执行初始化

```sh
ipfs init
```

生成swarm网络密钥生成工具，只能生成1次，并将其拷贝到另一主机相同位置

```sh
go get -u github.com/Kubuxu/go-ipfs-swarm-key-gen/ipfs-swarm-key-gen
export PATH=$PATH:$GOPATH/bin
ipfs-swarm-key-gen > ~/.ipfs/swarm.key
```

删除网络连接信息

```sh
$ ipfs bootstrap rm --all
removed /dnsaddr/bootstrap.libp2p.io/p2p/QmNnooDu7bfjPFoTZYxMNLWUQJyrVwtbZg5gBMjTezGAJN
removed /dnsaddr/bootstrap.libp2p.io/p2p/QmQCU2EcMqAqQPR2i9bChDtGNJchTbq5TbXJJ16u19uLTa
removed /dnsaddr/bootstrap.libp2p.io/p2p/QmbLHAnMoJPWSCR5Zhtx6BHJX9KiKNN6tpvbUcqanj75Nb
removed /dnsaddr/bootstrap.libp2p.io/p2p/QmcZf59bWwK5XFi76CZX8cbJ4BhTzzA3gU1ZjYZcYW3dwt
removed /ip4/104.131.131.82/tcp/4001/p2p/QmaCpDMGvV2BGHeYERUEnRQAwe3N8SzbUtfsmvsqQLuvuJ
removed /ip4/104.131.131.82/udp/4001/quic/p2p/QmaCpDMGvV2BGHeYERUEnRQAwe3N8SzbUtfsmvsqQLuvuJ
```

在138启动主节点

```sh
ipfs daemon
```

查看主机的id

```sh
ipfs id
```

将查看到的地址在140主机上添加，并启动140主机

```sh
ipfs bootstrap add /ip4/192.168.137.138/tcp/4001/ipfs/12D3KooWAPguS87nFLDH4g638zvAgPB3Bwv85SVuZESG7jncfdua
ipfs daemon
```



## 3. 添加文件

可以在任一主机上操作

```sh
echo "helloworld" >>hello.txt
ipfs add hello.txt

```

查看文件内容

```sh
ipfs cat QmUU2HcUBVSXkfWPUc3WUSeCMrWWeEJTuAgR9uyWBhh9Nf
```

添加文件目录





```sh
peer lifecycle chaincode approveformyorg -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --channelID ykchannel --name tokens --version 1 --package-id $PKG_TOKEN --sequence 1 --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem

peer lifecycle chaincode commit -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --channelID ykchannel --name tokens --version 1 --sequence 1 --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem --peerAddresses localhost:7051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt --peerAddresses localhost:9051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt

peer lifecycle chaincode querycommitted --channelID ykchannel --name tokens --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem --output json


peer chaincode invoke -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem -C ykchannel -n userauth --peerAddresses localhost:7051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt --peerAddresses localhost:9051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt -c '{"function":"Register","Args":["jbf","jbf","{\"username\":\"zhangsan\",\"org\":\"jbfp\",\"dept\":\"product\"}"]}'
```



```sh
peer lifecycle chaincode package tokens.tar.gz --path ./tokens --lang golang --label tokens_1.0

# both
peer lifecycle chaincode install myuser.tar.gz
```

