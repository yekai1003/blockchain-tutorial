package main

import (
	"context"
	"encoding/json"
	"fmt"
	"log"

	eos "github.com/eoscanada/eos-go"
)

func main() {
	api := eos.New("http://192.168.137.138:8888")
	ctx := context.Background()

	infoResp, err := api.GetInfo(ctx)
	//clii.NoError(err, "unable to get chain info")
	if err != nil {
		log.Panic("Failed to GetInfo", err)
	}

	fmt.Println("Chain Info", toJson(infoResp))

	accountResp, _ := api.GetAccount(ctx, "yekai")
	fmt.Println("Account Info", toJson(accountResp))
	jsondata := `{"sid":3,"sname":"zhaoliu","sage":33}`
	actData := eos.NewActionData(jsondata)
	level := eos.PermissionLevel{
		Actor:      "yekai",
		Permission: "active",
	}
	act := eos.Action{
		Account:       "student",
		Name:          "add",
		Authorization: []eos.PermissionLevel{level},
		ActionData:    actData,
	}

	out, err := api.NetConnect(context.Background(), "http://192.168.137.138:8888")
	if err != nil {
		log.Panic("failed to Netconnect", err)
	}
	fmt.Printf("%+v\n", out)
	signer := eos.NewWalletSigner(api, "default")
	api.SetSigner(signer)
	err = api.WalletImportKey(context.Background(), "default", "5KMLqUbbD5ehkbvBgZetU2wixenrzmEBhYKVWevsM7Ee7gRNzud")
	if err != nil {
		log.Panic("failed to ImportPrivateKey ", err)
	}

	resp, err := api.SignPushActions(context.Background(), &act)
	if err != nil {
		log.Panic("faield to signpushaction", err)
	}
	fmt.Printf("%+v\n", resp)
}

func toJson(v interface{}) string {
	out, _ := json.MarshalIndent(v, "", "  ")
	//clii.NoError(err, "unable to marshal json")

	return string(out)
}
