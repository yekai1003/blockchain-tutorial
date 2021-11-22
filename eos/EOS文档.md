开发参考手册：

https://developers.eos.io/manuals/eos/latest/nodeos/index



nodeos节点启动

```sh
nodeos -e -p eosio --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin
```

查看区块信息

```sh
cleos get info
```

测试API

```sh
curl http://localhost:8888/v1/chain/get_account
```



创建钱包

```sh
$ cleos wallet create -n mywallet --to-console
"/usr/opt/eosio/2.0.13/bin/keosd" launched
Creating wallet: mywallet
Save password to use in the future to unlock this wallet.
Without password imported keys will not be retrievable.
"PW5JbbBLugsRvxvRZaTRRb9PguWbaQ3hJKzrhUFmR7xKHYj45SZ6N"

```



