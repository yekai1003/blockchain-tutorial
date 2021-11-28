# MongoDB操作笔记



## 1. CURD操作



### 1.1 新增文档

```js
db.emp.insert({"empno":1001,"empname":"李寻欢","age":50,"sex":"man","isdy":false,"body":[183,80]})
db.emp.insert({"empno":1002,"empname":"叶开","age":25,"sex":"man","isdy":false,"body":[178,65]})
db.emp.insert({"empno":1003,"empname":"白飞飞","age":24,"sex":"woman","isdy":false,"body":[168,50]})
db.emp.insert({"empno":1005,"empname":"沈浪","age":25,"sex":"man","isdy":false,"body":[180,80], dept:{"deptno":40, "deptname":"大虾部"} })
```






### 1.2 查看文档

数据准备：

```sh
db.city.insert({name:"Bernardo Silva",age:27,cm:173,kg:64,apps:11,mins:940,data:[4,1],rating:7.45})
db.city.insert({name:"Ilkay Gündogan",age:31,cm:180,kg:80,apps:8,mins:684,data:[2],rating:7.41})
db.city.insert({name:"João Cancelo",age:27,cm:182,kg:74,apps:12,mins:1068,data:[0,3],rating:7.40})
db.city.insert({name:"Rodri",age:25,cm:191,kg:82,apps:10,mins:900,data:[2],rating:7.40})
db.city.insert({name:"Jack Grealish",age:26,cm:175,kg:68,apps:9,mins:743,data:[1,2],rating:7.32})
db.city.insert({name:"Gabriel Jesus",age:24,cm:175,kg:73,apps:9,mins:769,data:[2,5],rating:7.26})
db.city.insert({name:"Ferran Torres",age:21,cm:184,kg:77,apps:4,mins:305,data:[2,1],rating:7.23})
db.city.insert({name:"Zack Steffen",age:26,cm:191,kg:86,apps:1,mins:90,data:[],rating:7.16})
db.city.insert({name:"Phil Foden",age:21,cm:171,kg:70,apps:7,mins:613,data:[3,1],rating:7.09})
db.city.insert({name:"John Stones",age:27,cm:188,kg:70,apps:3,mins:301,data:[0],rating:7.03})
db.city.insert({name:"Rúben Dias",age:24,cm:186,kg:76,apps:10,mins:918,data:[0,1],rating:6.95})
db.city.insert({name:"Kevin De Bruyne",age:30,cm:181,kg:68,apps:5,mins:453,data:[2,0],rating:6.93})
db.city.insert({name:"Kyle Walker",age:31,cm:180,kg:80,apps:10,mins:856,data:[],rating:6.80})
db.city.insert({name:"Riyad Mahrez",age:30,cm:179,kg:67,apps:2,mins:293,data:[2,1],rating:6.69})
db.city.insert({name:"Nathan Aké",age:26,cm:180,kg:75,apps:3,mins:284,data:[],rating:6.66})
db.city.insert({name:"Ederson",age:28,cm:186,kg:86,apps:11,mins:990,data:[],rating:6.66})
db.city.insert({name:"Aymeric Laporte",age:27,cm:191,kg:86,apps:9,mins:735,data:[1],rating:6.65})
db.city.insert({name:"Benjamin Mendy",age:27,cm:185,kg:85,apps:1,mins:79,data:[2],rating:6.60})
db.city.insert({name:"Raheem Sterling",age:26,cm:170,kg:69,apps:4,mins:466,data:[2],rating:6.60})
db.city.insert({name:"Cole Palmer",age:20,cm:190,kg:60,apps:1,mins:109,data:[],rating:6.54})
db.city.insert({name:"Oleksandr Zinchenko",age:24,cm:175,kg:64,apps:1,mins:56,data:[0],rating:6.37})
db.city.insert({name:"Fernandinho",age:36,cm:179,kg:67,apps:2,mins:186,data:[],rating:6.30})
db.city.insert({name:"James McAtee",age:19,cm:174,kg:62,apps:1,mins:3,data:[0],rating:6.17})
```

尝试题目（一）：

```sh
1. 查看曼城队内球员总数
> db.city.find().count()
23
2. 查看曼城队内全部球员信息
db.city.find()
3. 查看曼城队内球员名字为Fernandinho的球员信息
db.city.find({name:"Fernandinho"})
db.city.find({name:"John Stones"}, {name:1,age:1, cm:1, apps:1, _id:0})

4. 查看曼城队内身高为185，体重为85的球员信息 select * from city where cm=185 and kg = 85;
db.city.find({cm:185,kg:85})
5. 查看曼城队内进球数为2的球员信息
db.city.find({"data.0":2})
```

尝试题目（二）：

```sh
1. 查看曼城队内年龄为28或30的球员信息 
db.city.find({$or:[{age:28},{age:30}]})
db.city.find({age:{$in:[28,30]}})
db.city.find({age:{$nin:[28,30]}})
2. 查看曼城队内年龄大于28的球员信息 
db.city.find({age:{$gt:28}})
3. 查看曼城队内出场时间在300~800之间的球员信息
db.city.find({$and:[{mins:{$gt:300}}, {mins:{$lt:800}}]})

```

### 1.3 删除文档

```sh
# 只删除一条
db.city.remove({age:26}, {justOne:true})
# 全部删除
db.city.remove({age:30})
```







### 1.4 修改文档

```sh
1. 修改年龄26的人变为年龄27 $set
db.city.update({age:26}, {$set:{age:27}}, {upsert:false, multi:true})
2. 将年龄为27的球员出场次数增加2，出场时间加90 $inc
db.city.update({age:27}, {$inc:{apps:2,mins:90}}, {upsert:false, multi:true})

db.city.update({age:40}, {$set:{pos:"GK", name:"yekai"}}, {upsert:true, multi:true})
```



### 1.5 索引



```sh
# 按名字创建升序索引
db.city.createIndex({name:1}, {unique:true, name:"city_name"})
# 按年龄创建降序索引
db.city.createIndex({age:-1})
# 删除索引
db.city.dropIndex({age:-1})

```



### 1.6 聚合函数


练习题目
```sh
1. 查看不同年龄的球员个数
db.city.aggregate({ $group: { _id:"$age", count:{$sum:1}  }  })
2. 查看不同年龄的出场次数
db.city.aggregate({ $group: { _id:"$age", count:{$sum:"$mins"}  }  })

3. 查看不同年龄、身高的出场时间
db.city.aggregate({ $group: { _id:{"age":"$age","xcm":"$cm"}, count:{$sum:"$mins"}  }  })
4. 将球员按年龄排序
db.city.find().sort({age:-1})

```



### 1.7 高级查询

forEach+ js

```js
db.city.find().forEach(
 	function(item) { 
		if(item.age > 34) { print(item) }
	} 
)

```

where操作符

```sh
db.city.find( { $where: "this.age > 30" } );

```

正则表达式

```sh
db.city.find({name: {$regex: /^B.*/}});

```



## 2. 身份认证

添加用户

```sh
use admin
db.createUser(
 {
  user: "admin",
  pwd: "admin123",
  roles: [ { role: "root", db: "admin" } ]
 }
)
```

之后可以验证用户是否创建成功

```sh
db.auth("admin","admin123")
```

客户端登陆

```sh
mongo --port 27017 -u "root" -p "admin123" --authenticationDatabase "admin"
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



## 3. 副本集实验

### 3.1 副本集启动

切换至root用户，创建3个目录

```sh
mkdir -p /data/node1
mkdir -p /data/node2
mkdir -p /data/arbiter
```



启动三个节点

```sh
nohup mongod --replSet application --dbpath /data/node1/ --port 9927 --oplogSize 1024 &
nohup mongod --replSet application --dbpath /data/node2/ --port 9928 --oplogSize 1024 &
nohup mongod --replSet application --dbpath /data/arbiter/ --port 9929 --oplogSize 1024 &
```

参数介绍：

- --replSet 用来指定副本集的名称
- --datapath 指定数据目录
- --port 指定数据库侦听端口
- --oplogsize 指定日志大小，单位为M

接下来，登陆9927的mongo

```sh
mongo localhost:9927
```

配置副本集数据

```sh
>config = {_id: "application", members: []}
```

配置3个节点信息

```sh
>config.members.push({_id: 0, host: "localhost:9927"})
>config.members.push({_id: 1, host: "localhost:9928"})
>config.members.push({_id: 2, host: "localhost:9929", arbiterOnly: true})
```

接下来初始化

```sh
>  rs.initiate(config)
{ "ok" : 1 }

```

可以分别登陆第2个节点

```sh
mongo localhost:9928
```

也可以登陆仲裁节点

```sh
mongo localhost:9929
```

可以在3个终端内查看节点变化情况，过一会其中一个变为primary，也就是主节点。

可以使用rs.isMaster()查看情况

```sh
application:PRIMARY> rs.isMaster()
{
	"topologyVersion" : {
		"processId" : ObjectId("619afadd4560ab25189efcf7"),
		"counter" : NumberLong(6)
	},
	"hosts" : [
		"localhost:9927",
		"localhost:9928"
	],
	"arbiters" : [
		"localhost:9929"
	],
	"setName" : "application",
	"setVersion" : 1,
	"ismaster" : true,
	"secondary" : false,
	"primary" : "localhost:9927",
	"me" : "localhost:9927",
	"electionId" : ObjectId("7fffffff0000000000000001"),
	"lastWrite" : {
		"opTime" : {
			"ts" : Timestamp(1637547519, 1),
			"t" : NumberLong(1)
		},
		"lastWriteDate" : ISODate("2021-11-22T02:18:39Z"),
		"majorityOpTime" : {
			"ts" : Timestamp(1637547519, 1),
			"t" : NumberLong(1)
		},
		"majorityWriteDate" : ISODate("2021-11-22T02:18:39Z")
	},
	"maxBsonObjectSize" : 16777216,
	"maxMessageSizeBytes" : 48000000,
	"maxWriteBatchSize" : 100000,
	"localTime" : ISODate("2021-11-22T02:18:45.333Z"),
	"logicalSessionTimeoutMinutes" : 30,
	"connectionId" : 1,
	"minWireVersion" : 0,
	"maxWireVersion" : 13,
	"readOnly" : false,
	"ok" : 1,
	"$clusterTime" : {
		"clusterTime" : Timestamp(1637547519, 1),
		"signature" : {
			"hash" : BinData(0,"AAAAAAAAAAAAAAAAAAAAAAAAAAA="),
			"keyId" : NumberLong(0)
		}
	},
	"operationTime" : Timestamp(1637547519, 1)
}

```

也可以使用rs.status()和rs.conf()查看信息



### 3.2 测试数据同步



在主节点操作

```sh
application:PRIMARY> db.users.insert({name:"yekai",age:40})
WriteResult({ "nInserted" : 1 })
application:PRIMARY> db.users.find()
{ "_id" : ObjectId("619b001b18f4a0cf160edc1f"), "name" : "yekai", "age" : 40 }

```

在从节点查看数据

```sh
application:SECONDARY> db.users.find()
Error: error: {
	"topologyVersion" : {
		"processId" : ObjectId("619afb1f931f799e7b7398d7"),
		"counter" : NumberLong(4)
	},
	"ok" : 0,
	"errmsg" : "not master and slaveOk=false",
	"code" : 13435,
	"codeName" : "NotPrimaryNoSecondaryOk",
	"$clusterTime" : {
		"clusterTime" : Timestamp(1637548100, 1),
		"signature" : {
			"hash" : BinData(0,"AAAAAAAAAAAAAAAAAAAAAAAAAAA="),
			"keyId" : NumberLong(0)
		}
	},
	"operationTime" : Timestamp(1637548100, 1)
}

```

从节点需要意识到自己的从属地位之后才能查看数据。

```sh
application:SECONDARY> rs.secondaryOk()

```

从节点查看数据

```sh
application:SECONDARY> show tables
users
application:SECONDARY> show collections
users
application:SECONDARY> db.users.find()
{ "_id" : ObjectId("619b001b18f4a0cf160edc1f"), "name" : "yekai", "age" : 40 }

```

可以再次从主节点插入数据

```sh
application:PRIMARY> db.users.insert({name:"fuhongxue",age:41})
WriteResult({ "nInserted" : 1 })
```

之后再在从节点查看

```sh
application:SECONDARY> db.users.find()
{ "_id" : ObjectId("619b001b18f4a0cf160edc1f"), "name" : "yekai", "age" : 40 }
{ "_id" : ObjectId("619b017818f4a0cf160edc20"), "name" : "fuhongxue", "age" : 41 }
```

尝试在从节点插入数据，提示报错，从节点无权限写数据

```sh
application:SECONDARY> db.users.insert({name:"luxiaojia",age:33})
WriteCommandError({
	"topologyVersion" : {
		"processId" : ObjectId("619afb1f931f799e7b7398d7"),
		"counter" : NumberLong(4)
	},
	"ok" : 0,
	"errmsg" : "not master",
	"code" : 10107,
	"codeName" : "NotWritablePrimary",
	"$clusterTime" : {
		"clusterTime" : Timestamp(1637548500, 1),
		"signature" : {
			"hash" : BinData(0,"AAAAAAAAAAAAAAAAAAAAAAAAAAA="),
			"keyId" : NumberLong(0)
		}
	},
	"operationTime" : Timestamp(1637548500, 1)
})

```

杀掉主节点，之后检测节点的关系变化

```sh
[root@jbf138 fabric]# ps aux |grep mongod
root       2662  1.5  3.7 1908576 144884 pts/1  Sl   18:05   0:28 mongod --replSet application --dbpath /data/node1/ --port 9927 --oplogSize 1024
root       2722  1.5  3.7 1910548 143080 pts/1  Sl   18:06   0:28 mongod --replSet application --dbpath /data/node2/ --port 9928 --oplogSize 1024
root       2780  1.2  2.9 1765260 114608 pts/1  Sl   18:06   0:23 mongod --replSet application --dbpath /data/arbiter/ --port 9929 --oplogSize 1024
#杀掉主节点pid
kill -9 2662
```

此时，会发现原来的从节点主动变为主节点，再次提交数据，可以成功

```sh
application:SECONDARY> 
application:PRIMARY> db.users.insert({name:"luxiaojia",age:33})
WriteResult({ "nInserted" : 1 })
```

再次启动原9927端口的mongod

```sh
nohup mongod --replSet application --dbpath /data/node1/ --port 9927 --oplogSize 1024 &
```

再次登陆后，该节点已经成为了从节点。
