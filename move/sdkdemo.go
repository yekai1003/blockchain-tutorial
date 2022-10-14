package main

import (
	"context"
	"encoding/hex"
	"fmt"
	"log"

	"github.com/coming-chat/go-aptos/aptosaccount"
	"github.com/coming-chat/go-aptos/aptosclient"
	txBuilder "github.com/coming-chat/go-aptos/transaction_builder"
)

func main() {
	// Import account with private key
	privateKey, _ := hex.DecodeString("f25e7e3383424c49c09923e820942997a2aa33572b311afb1d212e8659bf5426")
	account := aptosaccount.NewAccount(privateKey)

	// Get private key, public key, address
	fmt.Printf("privateKey = %x\n", account.PrivateKey[:32])
	fmt.Printf(" publicKey = %x\n", account.PublicKey)
	fmt.Printf("   address = %x\n", account.AuthKey)

	fromAddress := "0x" + hex.EncodeToString(account.AuthKey[:])

	toAddress := "0xcdbe33da8d218e97a9bec6443ba4a1b1858494f29142976d357f4770c384e015"
	amount := uint64(100)

	// Initialize the client
	restUrl := "http://localhost:8080"
	client, err := aptosclient.Dial(context.Background(), restUrl)
	if err != nil {
		log.Panic("failed to Dial", err)

	}
	// Get Sender's account data and ledger info
	data, err := client.GetAccount(fromAddress)
	info, err := client.LedgerInfo()

	// Get gas price
	gasPrice, err := client.EstimateGasPrice()

	// Build paylod
	moduleName, err := txBuilder.NewModuleIdFromString("0x1::account")
	toAddr, err := txBuilder.NewAccountAddressFromHex(toAddress)
	toAmountBytes := txBuilder.BCSSerializeBasicValue(amount)

	payload := txBuilder.TransactionPayloadEntryFunction{
		ModuleName:   *moduleName,
		FunctionName: "transfer",
		TyArgs:       []txBuilder.TypeTag{},
		Args: [][]byte{
			toAddr[:], toAmountBytes,
		},
	}

	// Build transaction
	txn := &txBuilder.RawTransaction{
		Sender:                  account.AuthKey,
		SequenceNumber:          data.SequenceNumber,
		Payload:                 payload,
		MaxGasAmount:            2000,
		GasUnitPrice:            gasPrice,
		ExpirationTimestampSecs: info.LedgerTimestamp + 600,
		ChainId:                 uint8(info.ChainId),
	}

	// Sign raw transaction with account, and encode into data using BCS
	signedTxn, err := txBuilder.GenerateBCSTransaction(account, txn)
	fmt.Printf("stx:%v\n", signedTxn)
	// Submit transaction with BCS format.
	newTxn, err := client.SubmitSignedBCSTransaction(signedTxn)
	if err != nil {
		log.Panic("failed to SubmitSignedBCSTransaction", err)
	}
	fmt.Printf("tx hash = %v\n", newTxn)
}
