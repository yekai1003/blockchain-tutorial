# python-sdk使用



## 1. 控制台使用

下载python-sdk工程

```sh
git clone https://github.com/FISCO-BCOS/python-sdk
```

安装依赖

```sh
cd python-sdk 
pip install -r requirements.txt
```



创建账户

```sh
python-sdk$ python3 console.py newaccount yekai yekai123

INFO >> user input : ['newaccount', 'yekai', 'yekai123']

starting : yekai yekai123  , if save:False
new address :    0x56730bD892FDcBbf13c2d8AB8Fd716D1D9231923
new privkey :    0xe2c36a79077866ac8b514d313baf4e84668775fbc340a914ce0ddf702e6ff35a
new pubkey :     0x7b188f09a34189b3f3352a8b56c54a6c91577d9967c8cedb6bd47936e4adaa4f3e829b9fa5dc275f5773bff0905fc08b75a3f7a1bc5eee39d2fba1cf8e4f9baa
encrypt use time : 0.825 s
save to file : [bin/accounts/yekai.keystore]
>>-------------------------------------------------------
INFO >> read [bin/accounts/yekai.keystore] again after new account,address & keys in file:
decrypt use time : 0.809 s
address:         0x56730bD892FDcBbf13c2d8AB8Fd716D1D9231923
privkey:         0xe2c36a79077866ac8b514d313baf4e84668775fbc340a914ce0ddf702e6ff35a
pubkey :         0x7b188f09a34189b3f3352a8b56c54a6c91577d9967c8cedb6bd47936e4adaa4f3e829b9fa5dc275f5773bff0905fc08b75a3f7a1bc5eee39d2fba1cf8e4f9baa

account store in file: [bin/accounts/yekai.keystore]

**** please remember your password !!! *****


wget https://openGauss.obs.cn-south1.myhuaweicloud.com/2.0.0/arm/openGauss-2.0.0-openEuler-64bit-all.tar.gz
```

