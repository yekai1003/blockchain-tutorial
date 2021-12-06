package eosgo

import (
	"context"
	"fmt"

	eos "github.com/yekai1003/eos-go"
)

var api *eos.API
var adminpermisson eos.PermissionLevel
var txOpts *eos.TxOptions

func init() {
	api = eos.New("http://127.0.0.1:8888")
	adminpermisson = eos.PermissionLevel{
		Actor:      eos.AN("admin"),
		Permission: eos.PN("active"),
	}

	keyBag := &eos.KeyBag{}
	keyBag.ImportPrivateKey(context.Background(), "5HsSt8BTrUkGPBmB7tMbBFvdA3TczUbaZMtH7buceV5H29FXMqc")

	api.SetSigner(keyBag)

	txOpts = &eos.TxOptions{}
	if err := txOpts.FillFromChain(context.Background(), api); err != nil {
		panic(fmt.Errorf("filling tx opts: %w", err))
	}

}

type LoginReq struct {
	Adminname string `json:"admin"`
	Username  string `json:"sname"`
	Password  string `json:"password"`
}

func Login(username, password string) (bool, error) {

	// 构建Action数据
	data := LoginReq{"admin", username, password}
	actData := eos.NewActionData(data)
	api.Debug = true

	// 2. 创建action
	act := &eos.Action{
		Account:       eos.AN("userauth"),
		Name:          eos.ActN("login"),
		Authorization: []eos.PermissionLevel{adminpermisson},
		ActionData:    actData,
	}

	//func (api *API) SignPushActionsWithOpts(ctx context.Context, actions []*Action, opts *TxOptions) (out *PushTransactionFullResp, err error)
	response, err := api.SignPushActionsWithOpts(context.Background(), []*eos.Action{act}, txOpts)
	if err != nil {
		fmt.Printf("failed to SignPushActionsWithOpts %v\n", err)
		return false, err
	}

	fmt.Printf("retval : %v\n", response.Processed.ActionTraces)

	return false, nil
}

func ParseRetval() {

}
