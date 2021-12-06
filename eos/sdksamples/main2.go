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
	api := eos.New("http://127.0.0.1:8888")
	//ctx := context.Background()

	params := eos.GetTableRowsRequest{}
	params.Code = "student"
	params.Table = "persons"
	params.Scope = "yekai"
	params.JSON = true
	params.LowerBound = "1"
	params.UpperBound = "20"

	resprows, err := api.GetTableRows(context.Background(), params)
	if err != nil {
		log.Panic("failed to GetTableRows ", err)
	}
	fmt.Printf("getrows:%+s\n", resprows.Rows)
	return
}
