```sh
[fabric@jbf138 cppwork]$ cleos wallet create_key
Created new private key with a public key of: "EOS6Re5RaJNYLAsipzLaMWvveERJoMN6tK6FHgMHCnUJfeCcZL1pt"
[fabric@jbf138 cppwork]$ 
[fabric@jbf138 cppwork]$ 
[fabric@jbf138 cppwork]$ cleos wallet keys
[
  "EOS6CJ3ypWHFgopH7SEq4deSBeDjNkpMaMZRMFyRsGa3DbXdWgRb4",
  "EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV",
  "EOS6Re5RaJNYLAsipzLaMWvveERJoMN6tK6FHgMHCnUJfeCcZL1pt",
  "EOS6dkikqxS2E8EBocRJYCTWPv6JUGd1C8QgfNhjzmZX2oJnFxhJE"
]
[fabric@jbf138 cppwork]$ cleos create account eosio jing EOS6Re5RaJNYLAsipzLaMWvveERJoMN6tK6FHgMHCnUJfeCcZL1pt
executed transaction: fb400a0c48dc04c43fecebd7e174f7293154f1038b234937b12b55ea7c020104  200 bytes  345 us
#         eosio <= eosio::newaccount            {"creator":"eosio","name":"jing","owner":{"threshold":1,"keys":[{"key":"EOS6Re5RaJNYLAsipzLaMWvveERJ...
warning: transaction executed locally, but may not be confirmed by the network yet         ] 


[fabric@jbf138 cppwork]$ cleos create account eosio alice EOS6YMHw5pVB6eC6SScWToLd1Yy35m8tySqNyreV8AKCNw5QX1SFC
executed transaction: a0f022879adc0984cf3b3614c57a61b0c419341ef00b3038d5513a491c6cb394  200 bytes  238 us
#         eosio <= eosio::newaccount            {"creator":"eosio","name":"alice","owner":{"threshold":1,"keys":[{"key":"EOS6YMHw5pVB6eC6SScWToLd1Yy...
warning: transaction executed locally, but may not be confirmed by the network yet         
```



```sh
cleos set contract jing ./jing -p jing@active


cleos push action jing create '["yekai","alice"]' -p yekai@active

# 合约调用
$ cleos push action jing create '["yekai","alice"]' -p yekai@active
executed transaction: 994333a732544843f8bc88d4b2238622520192223fb6a01d062f568bced65790  112 bytes  430 us
#          jing <= jing::create                 {"host":"yekai","challenger":"alice"}
>> on create yekai,alice
warning: transaction executed locally, but may not be confirmed by the network yet         ] 

```

