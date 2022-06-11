package main

import (
	"fmt"
	"log"

	"github.com/ethereum/go-ethereum/accounts/keystore"
)

func main() {
	ks := keystore.NewPlaintextKeyStore("data")
	acct, err := ks.NewAccount("123")
	if err != nil {
		log.Panic("failed to NewAccount ", err)
	}

	fmt.Println("new account sucess:", acct.URL.String(), acct.Address.String(), acct.Address.Hex())
}
