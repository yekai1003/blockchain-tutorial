
需要先检查linux系统的g++版本，centos7的默认版本是4.8，不够用。

```sh
sudo yum install centos-release-scl
sudo yum install devtoolset-8-gcc*
```

接下来使修改生效。
```sh
scl enable devtoolset-8 bash
```

安装准备环境，其实官方给的教程里也提供了devtoolset-7的安装。

```sh
sudo yum install -y epel-release centos-release-scl
sudo yum install -y openssl-devel openssl cmake3 git flex patch bison gmp-static devtoolset-7
```
克隆工程。

```sh
git clone https://github.com/FISCO-BCOS/FISCO-BCOS.git

# 若因为网络问题导致长时间无法执行上面的命令，请尝试下面的命令：
git clone https://gitee.com/FISCO-BCOS/FISCO-BCOS.git
```
编译源代码。

```sh
$ cd FISCO-BCOS
$ git checkout master-2.0
$ mkdir -p build && cd build
$ source /opt/rh/devtoolset-7/enable  # CentOS请执行此命令，其他系统不需要
# CentOS请使用cmake3
$ cmake ..
# 高性能机器可添加-j4使用4核加速编译
# macOS 编译出现 "ld: warning: direct access" 提示时，可以忽略
$ make
```

时间会比较长，视机器性能决定。