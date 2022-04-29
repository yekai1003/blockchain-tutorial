package main

import (
	"fmt"
	"log"

	"github.com/FISCO-BCOS/go-sdk/abi/bind"
	"github.com/FISCO-BCOS/go-sdk/client"
	"github.com/FISCO-BCOS/go-sdk/conf"
	"github.com/ethereum/go-ethereum/common"
	"github.com/ethereum/go-ethereum/crypto"
)

func pem2Auth(path string) (*bind.TransactOpts, string, error) {
	privBytes, privType, err := conf.LoadECPrivateKeyFromPEM(path)
	if err != nil {
		log.Panic("failed to Load private key")
	}
	privateKey, err := crypto.ToECDSA(privBytes)
	if err != nil {
		log.Panic("failed to ToECDSA", err)
	}

	//fmt.Printf("%s:%+v\n", privType, auth.From.String())
	return bind.NewKeyedTransactor(privateKey), privType, nil
}

func main() {
	// auth, ptype, _ := pem2Auth("yekai.pem")
	// fmt.Printf("%s:%+v\n", ptype, auth.From.String())
	// fmt.Println("---------------------------------------------")
	// auth, ptype, _ = pem2Auth("gm.pem")
	// fmt.Printf("%s:%+v\n", ptype, auth.From.String())

	multConfigs, err := conf.ParseConfigFile("fisco.toml")
	if err != nil {
		log.Fatalf("ParseConfigFile failed, err: %+v", err)

	}
	//2. 连接节点
	client, err := client.Dial(&multConfigs[0])
	if err != nil {
		log.Fatal(err)
	}
	// 3.
	instance, err := NewHello(common.HexToAddress("0x0b22fba4531b64e7d187e0e4fff4f6df645a326e"), client)
	if err != nil {
		log.Fatal("failed to NewHello ", err)
	}
	//4. auth
	auth, _, err := pem2Auth("gm.pem")
	tx, receipt, err := instance.Set(auth, "zhang3san")
	fmt.Println(tx.Hash().String(), receipt.BlockNumber)

	opts := bind.CallOpts{
		From: auth.From,
	}

	name, _ := instance.Get(&opts)
	fmt.Println(name)
}
