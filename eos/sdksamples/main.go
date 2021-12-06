package main

import (
	"context"
	"fmt"
	"log"

	eos "github.com/yekai1003/eos-go"
)

type AddData struct {
	Sid   uint64 `json:"sid"`
	Sname string `json:"sname"`
	Sage  uint8  `json:"sage"`
}

func main() {
	// 1. 连接到节点
	api := eos.New("http://101.43.41.44:8888")
	//ctx := context.Background()

	// 构建Action数据
	data := AddData{14, "zhaokk4", 35}
	actData := eos.NewActionData(data)

	// 构建调用权限级别
	level := eos.PermissionLevel{
		Actor:      eos.AN("yekai"),
		Permission: eos.PN("active"),
	}
	// 2. 创建action
	act := eos.Action{
		Account:       eos.AN("student"),
		Name:          eos.ActN("add"),
		Authorization: []eos.PermissionLevel{level},
		ActionData:    actData,
	}

	//3. 私钥导入
	keyBag := &eos.KeyBag{}
	keyBag.ImportPrivateKey(context.Background(), "5HsGoQTADsykXysTEwUq8RrurYtrqpgLnWunoCQDHoWWsBf1DX5")

	api.SetSigner(keyBag)

	//4. 填写交易附选项
	txOpts := &eos.TxOptions{}
	if err := txOpts.FillFromChain(context.Background(), api); err != nil {
		panic(fmt.Errorf("filling tx opts: %w", err))
	}

	//5. 创建交易
	//tx := eos.NewTransaction([]*eos.Action{&act}, txOpts)

	response, err := api.SignPushActionsWithOpts(context.Background(), []*eos.Action{&act}, txOpts)
	if err != nil {
		log.Panic("failed tp SignPushActionsWithOpts ", err)
	}
	fmt.Printf("-------------%+v\n", response)
	return
}
