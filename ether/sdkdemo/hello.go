// Code generated - DO NOT EDIT.
// This file is a generated binding and any manual changes will be lost.

package main

import (
	"errors"
	"math/big"
	"strings"

	ethereum "github.com/ethereum/go-ethereum"
	"github.com/ethereum/go-ethereum/accounts/abi"
	"github.com/ethereum/go-ethereum/accounts/abi/bind"
	"github.com/ethereum/go-ethereum/common"
	"github.com/ethereum/go-ethereum/core/types"
	"github.com/ethereum/go-ethereum/event"
)

// Reference imports to suppress errors if they are not otherwise used.
var (
	_ = errors.New
	_ = big.NewInt
	_ = strings.NewReader
	_ = ethereum.NotFound
	_ = bind.Bind
	_ = common.Big1
	_ = types.BloomLookup
	_ = event.NewSubscription
)

// HelloMetaData contains all meta data concerning the Hello contract.
var HelloMetaData = &bind.MetaData{
	ABI: "[{\"inputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"constructor\"},{\"inputs\":[],\"name\":\"Msg\",\"outputs\":[{\"internalType\":\"string\",\"name\":\"\",\"type\":\"string\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"string\",\"name\":\"_msg\",\"type\":\"string\"}],\"name\":\"setMsg\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"}]",
	Sigs: map[string]string{
		"7ac7ef85": "Msg()",
		"c4784fd4": "setMsg(string)",
	},
	Bin: "0x608060405234801561001057600080fd5b5060408051808201909152600b8082526a1a195b1b1bc81ddbdc9b1960aa1b602090920191825261004391600091610049565b5061011d565b828054610055906100e2565b90600052602060002090601f01602090048101928261007757600085556100bd565b82601f1061009057805160ff19168380011785556100bd565b828001600101855582156100bd579182015b828111156100bd5782518255916020019190600101906100a2565b506100c99291506100cd565b5090565b5b808211156100c957600081556001016100ce565b600181811c908216806100f657607f821691505b6020821081141561011757634e487b7160e01b600052602260045260246000fd5b50919050565b6103398061012c6000396000f3fe608060405234801561001057600080fd5b50600436106100365760003560e01c80637ac7ef851461003b578063c4784fd414610059575b600080fd5b61004361006e565b604051610050919061025d565b60405180910390f35b61006c6100673660046101ac565b6100fc565b005b6000805461007b906102b2565b80601f01602080910402602001604051908101604052809291908181526020018280546100a7906102b2565b80156100f45780601f106100c9576101008083540402835291602001916100f4565b820191906000526020600020905b8154815290600101906020018083116100d757829003601f168201915b505050505081565b805161010f906000906020840190610113565b5050565b82805461011f906102b2565b90600052602060002090601f0160209004810192826101415760008555610187565b82601f1061015a57805160ff1916838001178555610187565b82800160010185558215610187579182015b8281111561018757825182559160200191906001019061016c565b50610193929150610197565b5090565b5b808211156101935760008155600101610198565b6000602082840312156101be57600080fd5b813567ffffffffffffffff808211156101d657600080fd5b818401915084601f8301126101ea57600080fd5b8135818111156101fc576101fc6102ed565b604051601f8201601f19908116603f01168101908382118183101715610224576102246102ed565b8160405282815287602084870101111561023d57600080fd5b826020860160208301376000928101602001929092525095945050505050565b600060208083528351808285015260005b8181101561028a5785810183015185820160400152820161026e565b8181111561029c576000604083870101525b50601f01601f1916929092016040019392505050565b600181811c908216806102c657607f821691505b602082108114156102e757634e487b7160e01b600052602260045260246000fd5b50919050565b634e487b7160e01b600052604160045260246000fdfea2646970667358221220897378035164f39363ec8b80f9812e9b137cd2871b62aaac271f8057319474f364736f6c63430008070033",
}

// HelloABI is the input ABI used to generate the binding from.
// Deprecated: Use HelloMetaData.ABI instead.
var HelloABI = HelloMetaData.ABI

// Deprecated: Use HelloMetaData.Sigs instead.
// HelloFuncSigs maps the 4-byte function signature to its string representation.
var HelloFuncSigs = HelloMetaData.Sigs

// HelloBin is the compiled bytecode used for deploying new contracts.
// Deprecated: Use HelloMetaData.Bin instead.
var HelloBin = HelloMetaData.Bin

// DeployHello deploys a new Ethereum contract, binding an instance of Hello to it.
func DeployHello(auth *bind.TransactOpts, backend bind.ContractBackend) (common.Address, *types.Transaction, *Hello, error) {
	parsed, err := HelloMetaData.GetAbi()
	if err != nil {
		return common.Address{}, nil, nil, err
	}
	if parsed == nil {
		return common.Address{}, nil, nil, errors.New("GetABI returned nil")
	}

	address, tx, contract, err := bind.DeployContract(auth, *parsed, common.FromHex(HelloBin), backend)
	if err != nil {
		return common.Address{}, nil, nil, err
	}
	return address, tx, &Hello{HelloCaller: HelloCaller{contract: contract}, HelloTransactor: HelloTransactor{contract: contract}, HelloFilterer: HelloFilterer{contract: contract}}, nil
}

// Hello is an auto generated Go binding around an Ethereum contract.
type Hello struct {
	HelloCaller     // Read-only binding to the contract
	HelloTransactor // Write-only binding to the contract
	HelloFilterer   // Log filterer for contract events
}

// HelloCaller is an auto generated read-only Go binding around an Ethereum contract.
type HelloCaller struct {
	contract *bind.BoundContract // Generic contract wrapper for the low level calls
}

// HelloTransactor is an auto generated write-only Go binding around an Ethereum contract.
type HelloTransactor struct {
	contract *bind.BoundContract // Generic contract wrapper for the low level calls
}

// HelloFilterer is an auto generated log filtering Go binding around an Ethereum contract events.
type HelloFilterer struct {
	contract *bind.BoundContract // Generic contract wrapper for the low level calls
}

// HelloSession is an auto generated Go binding around an Ethereum contract,
// with pre-set call and transact options.
type HelloSession struct {
	Contract     *Hello            // Generic contract binding to set the session for
	CallOpts     bind.CallOpts     // Call options to use throughout this session
	TransactOpts bind.TransactOpts // Transaction auth options to use throughout this session
}

// HelloCallerSession is an auto generated read-only Go binding around an Ethereum contract,
// with pre-set call options.
type HelloCallerSession struct {
	Contract *HelloCaller  // Generic contract caller binding to set the session for
	CallOpts bind.CallOpts // Call options to use throughout this session
}

// HelloTransactorSession is an auto generated write-only Go binding around an Ethereum contract,
// with pre-set transact options.
type HelloTransactorSession struct {
	Contract     *HelloTransactor  // Generic contract transactor binding to set the session for
	TransactOpts bind.TransactOpts // Transaction auth options to use throughout this session
}

// HelloRaw is an auto generated low-level Go binding around an Ethereum contract.
type HelloRaw struct {
	Contract *Hello // Generic contract binding to access the raw methods on
}

// HelloCallerRaw is an auto generated low-level read-only Go binding around an Ethereum contract.
type HelloCallerRaw struct {
	Contract *HelloCaller // Generic read-only contract binding to access the raw methods on
}

// HelloTransactorRaw is an auto generated low-level write-only Go binding around an Ethereum contract.
type HelloTransactorRaw struct {
	Contract *HelloTransactor // Generic write-only contract binding to access the raw methods on
}

// NewHello creates a new instance of Hello, bound to a specific deployed contract.
func NewHello(address common.Address, backend bind.ContractBackend) (*Hello, error) {
	contract, err := bindHello(address, backend, backend, backend)
	if err != nil {
		return nil, err
	}
	return &Hello{HelloCaller: HelloCaller{contract: contract}, HelloTransactor: HelloTransactor{contract: contract}, HelloFilterer: HelloFilterer{contract: contract}}, nil
}

// NewHelloCaller creates a new read-only instance of Hello, bound to a specific deployed contract.
func NewHelloCaller(address common.Address, caller bind.ContractCaller) (*HelloCaller, error) {
	contract, err := bindHello(address, caller, nil, nil)
	if err != nil {
		return nil, err
	}
	return &HelloCaller{contract: contract}, nil
}

// NewHelloTransactor creates a new write-only instance of Hello, bound to a specific deployed contract.
func NewHelloTransactor(address common.Address, transactor bind.ContractTransactor) (*HelloTransactor, error) {
	contract, err := bindHello(address, nil, transactor, nil)
	if err != nil {
		return nil, err
	}
	return &HelloTransactor{contract: contract}, nil
}

// NewHelloFilterer creates a new log filterer instance of Hello, bound to a specific deployed contract.
func NewHelloFilterer(address common.Address, filterer bind.ContractFilterer) (*HelloFilterer, error) {
	contract, err := bindHello(address, nil, nil, filterer)
	if err != nil {
		return nil, err
	}
	return &HelloFilterer{contract: contract}, nil
}

// bindHello binds a generic wrapper to an already deployed contract.
func bindHello(address common.Address, caller bind.ContractCaller, transactor bind.ContractTransactor, filterer bind.ContractFilterer) (*bind.BoundContract, error) {
	parsed, err := abi.JSON(strings.NewReader(HelloABI))
	if err != nil {
		return nil, err
	}
	return bind.NewBoundContract(address, parsed, caller, transactor, filterer), nil
}

// Call invokes the (constant) contract method with params as input values and
// sets the output to result. The result type might be a single field for simple
// returns, a slice of interfaces for anonymous returns and a struct for named
// returns.
func (_Hello *HelloRaw) Call(opts *bind.CallOpts, result *[]interface{}, method string, params ...interface{}) error {
	return _Hello.Contract.HelloCaller.contract.Call(opts, result, method, params...)
}

// Transfer initiates a plain transaction to move funds to the contract, calling
// its default method if one is available.
func (_Hello *HelloRaw) Transfer(opts *bind.TransactOpts) (*types.Transaction, error) {
	return _Hello.Contract.HelloTransactor.contract.Transfer(opts)
}

// Transact invokes the (paid) contract method with params as input values.
func (_Hello *HelloRaw) Transact(opts *bind.TransactOpts, method string, params ...interface{}) (*types.Transaction, error) {
	return _Hello.Contract.HelloTransactor.contract.Transact(opts, method, params...)
}

// Call invokes the (constant) contract method with params as input values and
// sets the output to result. The result type might be a single field for simple
// returns, a slice of interfaces for anonymous returns and a struct for named
// returns.
func (_Hello *HelloCallerRaw) Call(opts *bind.CallOpts, result *[]interface{}, method string, params ...interface{}) error {
	return _Hello.Contract.contract.Call(opts, result, method, params...)
}

// Transfer initiates a plain transaction to move funds to the contract, calling
// its default method if one is available.
func (_Hello *HelloTransactorRaw) Transfer(opts *bind.TransactOpts) (*types.Transaction, error) {
	return _Hello.Contract.contract.Transfer(opts)
}

// Transact invokes the (paid) contract method with params as input values.
func (_Hello *HelloTransactorRaw) Transact(opts *bind.TransactOpts, method string, params ...interface{}) (*types.Transaction, error) {
	return _Hello.Contract.contract.Transact(opts, method, params...)
}

// Msg is a free data retrieval call binding the contract method 0x7ac7ef85.
//
// Solidity: function Msg() view returns(string)
func (_Hello *HelloCaller) Msg(opts *bind.CallOpts) (string, error) {
	var out []interface{}
	err := _Hello.contract.Call(opts, &out, "Msg")

	if err != nil {
		return *new(string), err
	}

	out0 := *abi.ConvertType(out[0], new(string)).(*string)

	return out0, err

}

// Msg is a free data retrieval call binding the contract method 0x7ac7ef85.
//
// Solidity: function Msg() view returns(string)
func (_Hello *HelloSession) Msg() (string, error) {
	return _Hello.Contract.Msg(&_Hello.CallOpts)
}

// Msg is a free data retrieval call binding the contract method 0x7ac7ef85.
//
// Solidity: function Msg() view returns(string)
func (_Hello *HelloCallerSession) Msg() (string, error) {
	return _Hello.Contract.Msg(&_Hello.CallOpts)
}

// SetMsg is a paid mutator transaction binding the contract method 0xc4784fd4.
//
// Solidity: function setMsg(string _msg) returns()
func (_Hello *HelloTransactor) SetMsg(opts *bind.TransactOpts, _msg string) (*types.Transaction, error) {
	return _Hello.contract.Transact(opts, "setMsg", _msg)
}

// SetMsg is a paid mutator transaction binding the contract method 0xc4784fd4.
//
// Solidity: function setMsg(string _msg) returns()
func (_Hello *HelloSession) SetMsg(_msg string) (*types.Transaction, error) {
	return _Hello.Contract.SetMsg(&_Hello.TransactOpts, _msg)
}

// SetMsg is a paid mutator transaction binding the contract method 0xc4784fd4.
//
// Solidity: function setMsg(string _msg) returns()
func (_Hello *HelloTransactorSession) SetMsg(_msg string) (*types.Transaction, error) {
	return _Hello.Contract.SetMsg(&_Hello.TransactOpts, _msg)
}
