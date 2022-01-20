package main

import (
	"context"
	"fmt"
	"log"
	"strings"

	"github.com/ethereum/go-ethereum/accounts/abi/bind"
	"github.com/ethereum/go-ethereum/accounts/keystore"
	"github.com/ethereum/go-ethereum/common"
	"github.com/ethereum/go-ethereum/ethclient"
)

const keyin = `{"address":"ee8b190a41b8554823633de2cec202b80f85ddb3","crypto":{"cipher":"aes-128-ctr","ciphertext":"5e839df8d6de73702335a185c99e2637b0d772ed71eaaf0fc72fd24e388c5081","cipherparams":{"iv":"ebee7b3f9c15d9df095cc0f69d0d1f01"},"kdf":"scrypt","kdfparams":{"dklen":32,"n":262144,"p":1,"r":8,"salt":"4252c9c3a06cb794f4ea32354e6d6910b11863910a617ffd27b99d110e489e04"},"mac":"af02c2d3d528163728d8dd11a96dfb6c083bbdf0582d5ff84f12d64c3b119ce5"},"id":"aae034c2-bca8-4a53-9e97-0ee6e0a8988a","version":3}`

func main() {
	ks := keystore.NewPlaintextKeyStore("data")
	acct, err := ks.NewAccount("123")
	if err != nil {
		log.Panic("failed to NewAccount ", err)
	}

	fmt.Println("new account sucess:", acct.URL.String(), acct.Address.String(), acct.Address.Hex())
}

func main3() {
	cli, err := ethclient.Dial("http://192.168.137.131:8545")
	if err != nil {
		log.Fatal("failed to Dial ", err)
	}
	chainID, err := cli.ChainID(context.Background())
	if err != nil {
		log.Panic("failed to get ChainID ", err)
	}
	fmt.Println("get chainid:", chainID.Int64())
	keyreader := strings.NewReader(keyin)
	auth, err := bind.NewTransactorWithChainID(keyreader, "123", chainID)
	if err != nil {
		log.Fatal("failed to NewTransactorWithChainID ", err)
	}
	addr, tx, instance, err := DeployHello(auth, cli)
	if err != nil {
		log.Panic("failed to DeployHello", err)
	}
	fmt.Println("addr:", addr.Hex())
	fmt.Println("tx:", tx.Hash())
	opts := bind.CallOpts{}
	opts.From = common.HexToAddress("0xaC15F8BEa93576d8A3a56B3332B61d12f2aE4C5b")
	getMsg, err := instance.Msg(&opts)
	if err != nil {
		log.Panic("failed to Msg call", err)
	}
	fmt.Println("msg:", getMsg)
}

func main4() {
	cli, err := ethclient.Dial("http://192.168.137.131:8545")
	if err != nil {
		log.Fatal("failed to Dial ", err)
	}
	chainID, err := cli.ChainID(context.Background())
	if err != nil {
		log.Panic("failed to get ChainID ", err)
	}
	fmt.Println("get chainid:", chainID.Int64())
	// keyreader := strings.NewReader(keyin)
	// auth, err := bind.NewTransactorWithChainID(keyreader, "123", chainID)
	// if err != nil {
	// 	log.Fatal("failed to NewTransactorWithChainID ", err)
	// }
	instance, err := NewHello(common.HexToAddress("0xB3638DbC080991E579bDB46B4f6b4a4595d94012"), cli)
	if err != nil {
		log.Panic("failed to NewHello", err)
	}

	opts := bind.CallOpts{}
	opts.From = common.HexToAddress("0xaC15F8BEa93576d8A3a56B3332B61d12f2aE4C5b")
	getMsg, err := instance.Msg(&opts)
	if err != nil {
		log.Panic("failed to Msg call", err)
	}
	fmt.Println("msg:", getMsg)
}

func main1() {
	cli, err := ethclient.Dial("http://192.168.137.131:8545")
	if err != nil {
		log.Fatal("failed to Dial ", err)
	}
	chainID, err := cli.ChainID(context.Background())
	if err != nil {
		log.Panic("failed to get ChainID ", err)
	}
	fmt.Println("get chainid:", chainID.Int64())
	keyreader := strings.NewReader(keyin)
	auth, err := bind.NewTransactorWithChainID(keyreader, "123", chainID)
	if err != nil {
		log.Fatal("failed to NewTransactorWithChainID ", err)
	}
	instance, err := NewHello(common.HexToAddress("0xB3638DbC080991E579bDB46B4f6b4a4595d94012"), cli)
	if err != nil {
		log.Panic("failed to NewHello", err)
	}

	tx, err := instance.SetMsg(auth, "yekai")
	if err != nil {
		log.Panic("failed to Msg call", err)
	}
	fmt.Println("tx:", tx.Hash())
}
