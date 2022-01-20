## 1. 准备工作

安装参考文档：https://hyperledger-fabric.readthedocs.io/en/release-2.3/test_network.html

创建Linux账户：

```sh
groupadd fabric
useradd fabric -m -s /bin/bash -d /home/fabric -g fabric
```

python默认使用2.7版本，如果升级，可能会存在问题。

使用daocloud一键安装命令来安装docker。

```sh
curl -sSL https://get.daocloud.io/docker | sh

```

启动docker
- centOS

```sh
sudo systemctl start docker
```
- ubuntu

```sh
sudo service docker start
```




安装完docker后，需要把新建用户加入docker组

```sh
sudo groupadd docker
sudo gpasswd -a $USER docker
newgrp docker

sudo usermod -a -G docker fabric
```

安装compose

```sh
sudo curl -L "https://github.com/docker/compose/releases/download/1.24.1/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
sudo chmod +x /usr/local/bin/docker-compose
```

服务器需要关闭防火墙，或者开启443端口

防火墙操作相关命令：

```sh
systemctl status firewalld #查看防火墙状态
systemctl start firewalld.service #启动firewall
systemctl stop firewalld.service #停止firewall
systemctl disable firewalld.service #禁止firewall开机启动
systemctl enable firewalld.service # 开机启动
```



## 2. 安装fabric





安装命令：

```sh
curl -sSL https://bit.ly/2ysbOFE | bash -s
```



https://raw.githubusercontent.com/hyperledger/fabric/master/scripts/bootstrap.sh

如果都开启，仍然无法执行安装命令，那么可以考虑将命令脚本先下载到本地。

将如下代码保存为 bootstrap.sh文件。

 ```sh
 #!/bin/bash
 #
 # Copyright IBM Corp. All Rights Reserved.
 #
 # SPDX-License-Identifier: Apache-2.0
 #
 
 # if version not passed in, default to latest released version
 VERSION=2.3.3
 # if ca version not passed in, default to latest released version
 CA_VERSION=1.5.2
 ARCH=$(echo "$(uname -s|tr '[:upper:]' '[:lower:]'|sed 's/mingw64_nt.*/windows/')-$(uname -m | sed 's/x86_64/amd64/g')")
 MARCH=$(uname -m)
 
 printHelp() {
     echo "Usage: bootstrap.sh [version [ca_version]] [options]"
     echo
     echo "options:"
     echo "-h : this help"
     echo "-d : bypass docker image download"
     echo "-s : bypass fabric-samples repo clone"
     echo "-b : bypass download of platform-specific binaries"
     echo
     echo "e.g. bootstrap.sh 2.3.3 1.5.2 -s"
     echo "will download docker images and binaries for Fabric v2.3.3 and Fabric CA v1.5.2"
 }
 
 # dockerPull() pulls docker images from fabric and chaincode repositories
 # note, if a docker image doesn't exist for a requested release, it will simply
 # be skipped, since this script doesn't terminate upon errors.
 
 dockerPull() {
     #three_digit_image_tag is passed in, e.g. "1.4.7"
     three_digit_image_tag=$1
     shift
     #two_digit_image_tag is derived, e.g. "1.4", especially useful as a local tag for two digit references to most recent baseos, ccenv, javaenv, nodeenv patch releases
     two_digit_image_tag=$(echo "$three_digit_image_tag" | cut -d'.' -f1,2)
     while [[ $# -gt 0 ]]
     do
         image_name="$1"
         echo "====> hyperledger/fabric-$image_name:$three_digit_image_tag"
         docker pull "hyperledger/fabric-$image_name:$three_digit_image_tag"
         docker tag "hyperledger/fabric-$image_name:$three_digit_image_tag" "hyperledger/fabric-$image_name"
         docker tag "hyperledger/fabric-$image_name:$three_digit_image_tag" "hyperledger/fabric-$image_name:$two_digit_image_tag"
         shift
     done
 }
 
 cloneSamplesRepo() {
     # clone (if needed) hyperledger/fabric-samples and checkout corresponding
     # version to the binaries and docker images to be downloaded
     if [ -d test-network ]; then
         # if we are in the fabric-samples repo, checkout corresponding version
         echo "==> Already in fabric-samples repo"
     elif [ -d fabric-samples ]; then
         # if fabric-samples repo already cloned and in current directory,
         # cd fabric-samples
         echo "===> Changing directory to fabric-samples"
         cd fabric-samples
     else
         echo "===> Cloning hyperledger/fabric-samples repo"
         git clone -b main https://github.com/hyperledger/fabric-samples.git && cd fabric-samples
     fi
 
     if GIT_DIR=.git git rev-parse v${VERSION} >/dev/null 2>&1; then
         echo "===> Checking out v${VERSION} of hyperledger/fabric-samples"
         git checkout -q v${VERSION}
     else
         echo "fabric-samples v${VERSION} does not exist, defaulting to main. fabric-samples main branch is intended to work with recent versions of fabric."
         git checkout -q main
     fi
 }
 
 # This will download the .tar.gz
 download() {
     local BINARY_FILE=$1
     local URL=$2
     echo "===> Downloading: " "${URL}"
     curl -L --retry 5 --retry-delay 3 "${URL}" | tar xz || rc=$?
     if [ -n "$rc" ]; then
         echo "==> There was an error downloading the binary file."
         return 22
     else
         echo "==> Done."
     fi
 }
 
 pullBinaries() {
     echo "===> Downloading version ${FABRIC_TAG} platform specific fabric binaries"
     download "${BINARY_FILE}" "https://github.com/hyperledger/fabric/releases/download/v${VERSION}/${BINARY_FILE}"
     if [ $? -eq 22 ]; then
         echo
         echo "------> ${FABRIC_TAG} platform specific fabric binary is not available to download <----"
         echo
         exit
     fi
 
     echo "===> Downloading version ${CA_TAG} platform specific fabric-ca-client binary"
     download "${CA_BINARY_FILE}" "https://github.com/hyperledger/fabric-ca/releases/download/v${CA_VERSION}/${CA_BINARY_FILE}"
     if [ $? -eq 22 ]; then
         echo
         echo "------> ${CA_TAG} fabric-ca-client binary is not available to download  (Available from 1.1.0-rc1) <----"
         echo
         exit
     fi
 }
 
 pullDockerImages() {
     command -v docker >& /dev/null
     NODOCKER=$?
     if [ "${NODOCKER}" == 0 ]; then
         FABRIC_IMAGES=(peer orderer ccenv tools)
         case "$VERSION" in
         2.*)
             FABRIC_IMAGES+=(baseos)
             shift
             ;;
         esac
         echo "FABRIC_IMAGES:" "${FABRIC_IMAGES[@]}"
         echo "===> Pulling fabric Images"
         dockerPull "${FABRIC_TAG}" "${FABRIC_IMAGES[@]}"
         echo "===> Pulling fabric ca Image"
         CA_IMAGE=(ca)
         dockerPull "${CA_TAG}" "${CA_IMAGE[@]}"
         echo "===> List out hyperledger docker images"
         docker images | grep hyperledger
     else
         echo "========================================================="
         echo "Docker not installed, bypassing download of Fabric images"
         echo "========================================================="
     fi
 }
 
 DOCKER=true
 SAMPLES=true
 BINARIES=true
 
 # Parse commandline args pull out
 # version and/or ca-version strings first
 if [ -n "$1" ] && [ "${1:0:1}" != "-" ]; then
     VERSION=$1;shift
     if [ -n "$1" ]  && [ "${1:0:1}" != "-" ]; then
         CA_VERSION=$1;shift
         if [ -n  "$1" ] && [ "${1:0:1}" != "-" ]; then
             THIRDPARTY_IMAGE_VERSION=$1;shift
         fi
     fi
 fi
 
 # prior to 1.2.0 architecture was determined by uname -m
 if [[ $VERSION =~ ^1\.[0-1]\.* ]]; then
     export FABRIC_TAG=${MARCH}-${VERSION}
     export CA_TAG=${MARCH}-${CA_VERSION}
     export THIRDPARTY_TAG=${MARCH}-${THIRDPARTY_IMAGE_VERSION}
 else
     # starting with 1.2.0, multi-arch images will be default
     : "${CA_TAG:="$CA_VERSION"}"
     : "${FABRIC_TAG:="$VERSION"}"
     : "${THIRDPARTY_TAG:="$THIRDPARTY_IMAGE_VERSION"}"
 fi
 
 BINARY_FILE=hyperledger-fabric-${ARCH}-${VERSION}.tar.gz
 CA_BINARY_FILE=hyperledger-fabric-ca-${ARCH}-${CA_VERSION}.tar.gz
 
 # then parse opts
 while getopts "h?dsb" opt; do
     case "$opt" in
         h|\?)
             printHelp
             exit 0
             ;;
         d)  DOCKER=false
             ;;
         s)  SAMPLES=false
             ;;
         b)  BINARIES=false
             ;;
     esac
 done
 
 if [ "$SAMPLES" == "true" ]; then
     echo
     echo "Clone hyperledger/fabric-samples repo"
     echo
     cloneSamplesRepo
 fi
 if [ "$BINARIES" == "true" ]; then
     echo
     echo "Pull Hyperledger Fabric binaries"
     echo
     pullBinaries
 fi
 if [ "$DOCKER" == "true" ]; then
     echo
     echo "Pull Hyperledger Fabric docker images"
     echo
     pullDockerImages
 fi
 ```

这个文件里主要三个功能：

- 安装二进制文件
  - fabric
  - fabric-ca
- 下载samples工程
- 拉取docker镜像



理论上来说，都可以分步操作，先clone样例库：
```sh
git clone https://github.com/hyperledger/fabric-samples.git
```



手动下载二进制文件：

```sh
wget https://github.com/hyperledger/fabric/releases/download/v2.3.3/hyperledger-fabric-linux-amd64-2.3.3.tar.gz
```

```sh
wget https://github.com/hyperledger/fabric-ca/releases/download/v1.5.2/hyperledger-fabric-ca-linux-amd64-1.5.2.tar.gz
```

将上述文件解压后，拷贝到fabric-samples/bin目录下。

docker镜像下载需要参考脚本内的执行逻辑。

```sh
./bootstrap.sh -sb
```



## 3. 启动fabric测试网络



启动命令：

```sh
./network.sh up
```

创建channel

```sh
 ./network.sh createChannel
```

使用测试的链码安装链码

```sh
./network.sh deployCC -ccn basic -ccp ../asset-transfer-basic/chaincode-go -ccl go
```



```sh
export PATH=${PWD}/../bin:$PATH
export FABRIC_CFG_PATH=$PWD/../config/

```

组织1的环境变量配置

```sh
# Environment variables for Org1

export CORE_PEER_TLS_ENABLED=true
export CORE_PEER_LOCALMSPID="Org1MSP"
export CORE_PEER_TLS_ROOTCERT_FILE=${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt
export CORE_PEER_MSPCONFIGPATH=${PWD}/organizations/peerOrganizations/org1.example.com/users/Admin@org1.example.com/msp
export CORE_PEER_ADDRESS=localhost:7051
```





授权

```sh
peer chaincode invoke -o localhost:7050 --ordererTLSHostnameOverride orderer.example.com --tls --cafile ${PWD}/organizations/ordererOrganizations/example.com/orderers/orderer.example.com/msp/tlscacerts/tlsca.example.com-cert.pem -C mychannel -n basic --peerAddresses localhost:7051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org1.example.com/peers/peer0.org1.example.com/tls/ca.crt --peerAddresses localhost:9051 --tlsRootCertFiles ${PWD}/organizations/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt -c '{"function":"InitLedger","Args":[]}'
```



查询

```sh
 peer chaincode query -C mychannel -n basic -c '{"Args":["GetAllAssets"]}'

```



组织2的环境变量配置

```sh
# Environment variables for Org2

export CORE_PEER_TLS_ENABLED=true
export CORE_PEER_LOCALMSPID="Org2MSP"
export CORE_PEER_TLS_ROOTCERT_FILE=${PWD}/organizations/peerOrganizations/org2.example.com/peers/peer0.org2.example.com/tls/ca.crt
export CORE_PEER_MSPCONFIGPATH=${PWD}/organizations/peerOrganizations/org2.example.com/users/Admin@org2.example.com/msp
export CORE_PEER_ADDRESS=localhost:9051
```

