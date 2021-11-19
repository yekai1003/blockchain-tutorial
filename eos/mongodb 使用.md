# mongodb 使用





























































### 安装



下载地址：https://www.mongodb.com/try/download/community

可以在这里看到对应的下载信息

![image-20211119140457635](./pics/download.png)





### 启动

```sh
mongod --dbpath=./data
```

也可以配置一个配置文件 mongo.cfg

```sh
#数据库数据存放目录
dbpath=mongodb-home/data/db

#数据库日志存放目录
logpath=mongodb-home/data/logs/mongo.log

#以追加的方式记录日志
logappend = true

#开启用户认证
auth=false

#后台运行
fork=true

#mongodb所绑定的ip地址
bind_ip=0.0.0.0

#端口号 默认为27017
port=27017 

#启用日志文件，默认启用

```

基于配置文件启动mongod

```sh
mongod -f mongo.cfg
```





### mongodb配置验证用户



添加用户



```sh
use admin
db.createUser(
 {
  user: "root",
  pwd: "kong1234",
  roles: [ { role: "root", db: "admin" } ]
 }
)
```

之后可以验证用户是否创建成功

```sh
db.auth("root","密码")
```

客户端登陆

```sh
mongo --port 27017 -u "root" -p "密码" --authenticationDatabase "admin"
```

创建其他用户

```sh
use test
db.createUser(
 {
  user: "tester",
  pwd: "test123",
  roles: [ { role: "readWrite", db: "test" },
       { role: "read", db: "reporting" } ]
 }
)
```



使用其他身份用户登陆

```sh
mongo --port 27017 -u "tester" -p "test123" --authenticationDatabase "test"
```

参考文档：https://www.cnblogs.com/codexueyuan/p/8592319.html