# fisco-bcos教程

## 1. 一键部署

参考教程：https://fisco-bcos-documentation.readthedocs.io/zh_CN/latest/docs/enterprise_tools/tutorial_one_click.html



下载

```sh
cd ~/ 
git clone https://github.com/FISCO-BCOS/generator.git

# 若因为网络问题导致长时间无法下载，请尝试以下命令：
git clone https://gitee.com/FISCO-BCOS/generator.git
```

安装文件

```
cd ~/generator && bash ./scripts/install.sh
```

下载

```sh
./generator --download_fisco ./meta
```

检查目录

```sh
cd ~/generator
ls ./tmp_one_click
```

修改配置后生成节点

```sh
bash ./one_click_generator.sh -b ./tmp_one_click
```

启动节点

```sh
bash ./tmp_one_click/agencyA/node/start_all.sh
bash ./tmp_one_click/agencyB/node/start_all.sh
```





## 安装浏览器

https://webasedoc.readthedocs.io/zh_CN/latest/docs/WeBASE-Install/developer.html