# 搭建Fabric浏览器



创建浏览器工程

```sh
mkdir blockchain-explorer
cd blockchain-explorer
```



拉取相关配置文件

```sh

wget https://raw.githubusercontent.com/hyperledger/blockchain-explorer/main/examples/net1/config.json
 wget https://raw.githubusercontent.com/hyperledger/blockchain-explorer/main/examples/net1/connection-profile/test-network.json -P connection-profile
 wget https://raw.githubusercontent.com/hyperledger/blockchain-explorer/main/docker-compose.yaml
```

拷贝Fabric网络启动时创建的organizations目录到本地

```sh
cp -r ~/fabric-samples/test-network/organizations/ .
```

设置环境变量

```sh
export EXPLORER_CONFIG_FILE_PATH=./config.json
export EXPLORER_PROFILE_DIR_PATH=./connection-profile
export FABRIC_CRYPTO_PATH=./organizations
```

**可能存在问题**：如果channel不是默认的mychannel，需要修改`connection-profile/test-network.json`文件的channel名称。

启动浏览器

```sh
docker-compose up -d
```

