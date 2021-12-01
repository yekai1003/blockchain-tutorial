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
	api := eos.New("http://192.168.137.129:8888")
	ctx := context.Background()

	infoResp, err := api.GetInfo(ctx)
	//clii.NoError(err, "unable to get chain info")
	if err != nil {
		log.Panic("Failed to GetInfo", err)
	}

	fmt.Println("Chain Info", toJson(infoResp))

	accountResp, _ := api.GetAccount(ctx, "yekai")
	fmt.Println("Account Info", toJson(accountResp))
	fmt.Println("\n\n\n\n\n\n")

	//jsondata := `"sid":11,"sname":"zhaoliu","sage":33}`
	//jsondata := `[13,"zhaokk",33]`
	data := AddData{14, "zhaokk4", 35}
	actData := eos.NewActionData(data)
	//actData.HexData = []byte(jsondata)
	level := eos.PermissionLevel{
		Actor:      eos.AN("yekai"),
		Permission: eos.PN("active"),
	}
	act := eos.Action{
		Account:       eos.AN("student"),
		Name:          eos.ActN("add"),
		Authorization: []eos.PermissionLevel{level},
		ActionData:    actData,
	}
	keyBag := &eos.KeyBag{}
	keyBag.ImportPrivateKey(context.Background(), "5KMLqUbbD5ehkbvBgZetU2wixenrzmEBhYKVWevsM7Ee7gRNzud")
	if err != nil {
		log.Panic("failed to ListKeys ", err)
	}
	// out, err := api.NetConnect(context.Background(), "http://192.168.137.138:8888")
	// if err != nil {
	// 	log.Panic("failed to Netconnect ", err)
	// }
	//fmt.Printf("%+v\n", out)
	//signer := eos.NewWalletSigner(api, "default")
	api.SetSigner(keyBag)
	// err = api.WalletImportKey(context.Background(), "default", "5KMLqUbbD5ehkbvBgZetU2wixenrzmEBhYKVWevsM7Ee7gRNzud")
	// if err != nil {
	// 	log.Panic("failed to ImportPrivateKey ", err)
	// }
	txOpts := &eos.TxOptions{}
	if err := txOpts.FillFromChain(context.Background(), api); err != nil {
		panic(fmt.Errorf("filling tx opts: %w", err))
	}

	tx := eos.NewTransaction([]*eos.Action{&act}, txOpts)

	response, err := api.SignPushActionsWithOpts(context.Background(), []*eos.Action{&act}, txOpts)
	if err != nil {
		log.Panic("failed tp SignPushActionsWithOpts ", err)
	}
	fmt.Printf("-------------%+v\n", response)
	return

	signedTx, packedTx, err := api.SignTransaction(context.Background(), tx, txOpts.ChainID, eos.CompressionNone)
	if err != nil {
		panic(fmt.Errorf("sign transaction: %w", err))
	}
	content, err := json.MarshalIndent(signedTx, "", "  ")
	if err != nil {
		panic(fmt.Errorf("json marshalling transaction: %w", err))
	}

	fmt.Println(string(content))
	fmt.Println()
	// resp, err := api.SignPushActions(context.Background(), &act)
	// if err != nil {
	// 	log.Panic("faield to signpushaction --- ", err)
	// }
	// fmt.Printf("%+v\n", packedTx)
	// response, err := api.SendTransaction(context.Background(), packedTx)
	// //response, err := api.PushTransaction(context.Background(), packedTx)
	// if err != nil {
	// 	fmt.Printf("%+v\n", response)
	// 	panic(fmt.Errorf("push transaction: %w", err))
	// }
	//var out eos.PushTransactionFullResp
	err = Call(api, context.Background(), "chain", "push_action", packedTx)
	if err != nil {
		log.Panic("failed to Call ", err)
	}
	//fmt.Printf("Transaction [%s] submitted to the network succesfully.\n", hex.EncodeToString(response.Processed.ID))
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
