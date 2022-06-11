/*
	Company: jbf
	Author : ye.gao
	Date   : 2022-01-14
	File   : config.go
*/
package configs

import (
	"log"

	"github.com/BurntSushi/toml"
)

type SvrConfig struct {
	Version    string       `toml:"version"`
	BlockChain string       `toml:"blockchain"`
	SvrPort    string       `toml:"svrport"`
	LogPath    string       `toml:"logpath"`
	Fabric     FabricConfig `toml:"fabric"`
	Fisco      FiscoInfo    `toml:"fisco"`
}

type FabricConfig struct {
	UserCode       string     `toml:"usercode"`
	EvidenceCode   string     `toml:"evidencecode"`
	Channel        string     `toml"channel"`
	OrgName        string     `toml"orgname"`
	AdminName      string     `toml"adminname"`
	ConnectionFile string     `toml"connectionfile"`
	Wallet         WalletInfo `toml:"wallet"`
}

type WalletInfo struct {
	WalletDir string `toml:"walletdir"`
	UserKey   string `toml:"userkey"`
}

type FiscoInfo struct {
	ConfigFile string `toml:"configfile"`
}

var FpspConfig SvrConfig

func init() {
	_, err := toml.DecodeFile("config.toml", &FpspConfig)
	if err != nil {
		log.Panic("failed to DecodeFile ", err)
	}
	log.Printf("config init ok\n")
}

func Show() {
	log.Printf("config: %+v\n", FpspConfig)
}
