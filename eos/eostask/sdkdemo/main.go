package main

import (
	"bytes"
	"context"
	"encoding/json"
	"fmt"
	"io"
	"log"
	"net/http"
	"net/http/httputil"

	eos "github.com/yekai1003/eos-go"
)

type AddData struct {
	Sid   uint64 `json:"sid"`
	Sname string `json:"sname"`
	Sage  uint8  `json:"sage"`
}

func main1() {
	// 1. 连接到节点
	api := eos.New("http://127.0.0.1:8888")
	ctx := context.Background()

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
	if err != nil {
		log.Panic("failed to ListKeys ", err)
	}

	api.SetSigner(keyBag)

	//4. 填写交易附选项
	txOpts := &eos.TxOptions{}
	if err := txOpts.FillFromChain(context.Background(), api); err != nil {
		panic(fmt.Errorf("filling tx opts: %w", err))
	}

	//5. 创建交易
	tx := eos.NewTransaction([]*eos.Action{&act}, txOpts)

	response, err := api.SignPushActionsWithOpts(context.Background(), []*eos.Action{&act}, txOpts)
	if err != nil {
		log.Panic("failed tp SignPushActionsWithOpts ", err)
	}
	fmt.Printf("-------------%+v\n", response)
	return
}

type GetData struct {
	Sid uint64 `json:"sid"`
}

func main2() {
	api := eos.New("http://127.0.0.1:8888")
	//ctx := context.Background()

	data := GetData{14}
	actData := eos.NewActionData(data)
	//actData.HexData = []byte(jsondata)
	level := eos.PermissionLevel{
		Actor:      eos.AN("yekai"),
		Permission: eos.PN("active"),
	}
	act := eos.Action{
		Account:       eos.AN("student"),
		Name:          eos.ActN("get"),
		Authorization: []eos.PermissionLevel{level},
		ActionData:    actData,
	}
	keyBag := &eos.KeyBag{}
	keyBag.ImportPrivateKey(context.Background(), "5J6rPCaPrtViyqKvWKAAgcRE4msK4TptM83tzcDQ4NuzTpQhWtm")

	api.SetSigner(keyBag)

	txOpts := &eos.TxOptions{}
	if err := txOpts.FillFromChain(context.Background(), api); err != nil {
		panic(fmt.Errorf("filling tx opts: %w", err))
	}

	response, err := api.SignPushActionsWithOpts(context.Background(), []*eos.Action{&act}, txOpts)
	if err != nil {
		log.Panic("failed tp SignPushActionsWithOpts ", err)
	}
	fmt.Printf("-------------%+v\n", response)

	// -------- 查询table数据

	// params := eos.GetTableByScopeRequest{}
	// params.Code = "student"
	// params.Table = "persons"
	// params.LowerBound = ""
	// params.UpperBound = ""
	// params.Limit = 20
	// resprows, err := api.GetTableByScope(context.Background(), params)
	// if err != nil {
	// 	log.Panic("failed to GetTableByScope ", err)
	// }

	// fmt.Printf("%+v\n", resprows)
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

	//api.GetABI()

	return

}

func main() {
	api := eos.New("http://127.0.0.1:8888")
	//ctx := context.Background()

	data := GetData{1}
	api.Debug = true
	actData := eos.NewActionData(data)
	//actData.HexData = []byte(jsondata)
	level := eos.PermissionLevel{
		Actor:      eos.AN("yekai"),
		Permission: eos.PN("active"),
	}
	act := eos.Action{
		Account:       eos.AN("student"),
		Name:          eos.ActN("getname"),
		Authorization: []eos.PermissionLevel{level},
		ActionData:    actData,
	}
	keyBag := &eos.KeyBag{}
	keyBag.ImportPrivateKey(context.Background(), "5J6rPCaPrtViyqKvWKAAgcRE4msK4TptM83tzcDQ4NuzTpQhWtm")

	api.SetSigner(keyBag)

	txOpts := &eos.TxOptions{}
	if err := txOpts.FillFromChain(context.Background(), api); err != nil {
		panic(fmt.Errorf("filling tx opts: %w", err))
	}

	response, err := api.SignPushActionsWithOpts(context.Background(), []*eos.Action{&act}, txOpts)
	if err != nil {
		log.Panic("failed tp SignPushActionsWithOpts ", err)
	}
	fmt.Printf("-------------%+v\n", response)

	// // 查询交易
	// txresp, err := api.GetTransaction(context.Background(), "a0daac215683ba92203e98bdcc60b4e01a8f0f18eb5e50e89a79253037b00704")
	// if err != nil {
	// 	log.Panic("failed to GetTransaction ", err)
	// }
	// fmt.Printf("%+v\n", txresp)
	return

}

func toJson(v interface{}) string {
	out, _ := json.MarshalIndent(v, "", "  ")
	//clii.NoError(err, "unable to marshal json")

	return string(out)
}

func enc(v interface{}) (io.Reader, error) {
	if v == nil {
		return nil, nil
	}

	buffer := &bytes.Buffer{}
	encoder := json.NewEncoder(buffer)
	encoder.SetEscapeHTML(false)

	err := encoder.Encode(v)
	if err != nil {
		return nil, err
	}

	return buffer, nil
}

func Call(api *eos.API, ctx context.Context, baseAPI string, endpoint string, body interface{}) error {
	jsonBody, err := enc(body)
	if err != nil {
		return err
	}

	targetURL := fmt.Sprintf("%s/v1/%s/%s", "http://192.168.137.129:8888", baseAPI, endpoint)
	req, err := http.NewRequest("POST", targetURL, jsonBody)
	if err != nil {
		return fmt.Errorf("NewRequest: %w", err)
	}

	for k, v := range api.Header {
		if req.Header == nil {
			req.Header = http.Header{}
		}
		req.Header[k] = append(req.Header[k], v...)
	}
	if true {
		// Useful when debugging API calls
		requestDump, err := httputil.DumpRequest(req, true)
		if err != nil {
			fmt.Println(err)
		}
		fmt.Println("-------------------------------")
		fmt.Println(string(requestDump))
		fmt.Println("")
	}

	resp, err := api.HttpClient.Do(req.WithContext(ctx))
	if err != nil {
		return fmt.Errorf("%s: %w", req.URL.String(), err)
	}
	defer resp.Body.Close()

	var cnt bytes.Buffer
	_, err = io.Copy(&cnt, resp.Body)
	if err != nil {
		return fmt.Errorf("Copy: %w", err)
	}

	// if resp.StatusCode == 404 {
	// 	var apiErr APIError
	// 	if err := json.Unmarshal(cnt.Bytes(), &apiErr); err != nil {
	// 		return ErrNotFound
	// 	}
	// 	return apiErr
	// }

	// if resp.StatusCode > 299 {
	// 	var apiErr APIError
	// 	if err := json.Unmarshal(cnt.Bytes(), &apiErr); err != nil {
	// 		return fmt.Errorf("%s: status code=%d, body=%s", req.URL.String(), resp.StatusCode, cnt.String())
	// 	}

	// 	// Handle cases where some API calls (/v1/chain/get_account for example) returns a 500
	// 	// error when retrieving data that does not exist.
	// 	if apiErr.IsUnknownKeyError() {
	// 		return ErrNotFound
	// 	}

	// 	return apiErr
	// }

	if true {
		fmt.Println("RESPONSE:")
		responseDump, err := httputil.DumpResponse(resp, true)
		if err != nil {
			fmt.Println(err)
		}
		fmt.Println("-------------------------------")
		fmt.Println(cnt.String())
		fmt.Println("-------------------------------")
		fmt.Printf("%q\n", responseDump)
		fmt.Println("")
	}

	// if err := json.Unmarshal(cnt.Bytes(), &out); err != nil {
	// 	return fmt.Errorf("Unmarshal: %w", err)
	// }

	return nil
}
