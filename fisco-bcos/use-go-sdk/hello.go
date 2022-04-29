// Code generated - DO NOT EDIT.
// This file is a generated binding and any manual changes will be lost.

package main

import (
	"math/big"
	"strings"

	"github.com/FISCO-BCOS/go-sdk/abi"
	"github.com/FISCO-BCOS/go-sdk/abi/bind"
	"github.com/FISCO-BCOS/go-sdk/core/types"
	"github.com/FISCO-BCOS/go-sdk/event"
	ethereum "github.com/ethereum/go-ethereum"
	"github.com/ethereum/go-ethereum/common"
)

// Reference imports to suppress errors if they are not otherwise used.
var (
	_ = big.NewInt
	_ = strings.NewReader
	_ = ethereum.NotFound
	_ = abi.U256
	_ = bind.Bind
	_ = common.Big1
	_ = types.BloomLookup
	_ = event.NewSubscription
)

// HelloABI is the input ABI used to generate the binding from.
const HelloABI = "[{\"inputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"constructor\"},{\"anonymous\":false,\"inputs\":[{\"indexed\":false,\"internalType\":\"string\",\"name\":\"newname\",\"type\":\"string\"}],\"name\":\"onset\",\"type\":\"event\"},{\"inputs\":[],\"name\":\"get\",\"outputs\":[{\"internalType\":\"string\",\"name\":\"\",\"type\":\"string\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[],\"name\":\"getHash\",\"outputs\":[{\"internalType\":\"bytes32\",\"name\":\"\",\"type\":\"bytes32\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[],\"name\":\"getHash2\",\"outputs\":[{\"internalType\":\"bytes32\",\"name\":\"\",\"type\":\"bytes32\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"uint256\",\"name\":\"\",\"type\":\"uint256\"}],\"name\":\"names\",\"outputs\":[{\"internalType\":\"string\",\"name\":\"\",\"type\":\"string\"}],\"stateMutability\":\"view\",\"type\":\"function\"},{\"inputs\":[{\"internalType\":\"string\",\"name\":\"n\",\"type\":\"string\"}],\"name\":\"set\",\"outputs\":[],\"stateMutability\":\"nonpayable\",\"type\":\"function\"}]"

// Hello is an auto generated Go binding around a Solidity contract.
type Hello struct {
	HelloCaller     // Read-only binding to the contract
	HelloTransactor // Write-only binding to the contract
	HelloFilterer   // Log filterer for contract events
}

// HelloCaller is an auto generated read-only Go binding around a Solidity contract.
type HelloCaller struct {
	contract *bind.BoundContract // Generic contract wrapper for the low level calls
}

// HelloTransactor is an auto generated write-only Go binding around a Solidity contract.
type HelloTransactor struct {
	contract *bind.BoundContract // Generic contract wrapper for the low level calls
}

// HelloFilterer is an auto generated log filtering Go binding around a Solidity contract events.
type HelloFilterer struct {
	contract *bind.BoundContract // Generic contract wrapper for the low level calls
}

// HelloSession is an auto generated Go binding around a Solidity contract,
// with pre-set call and transact options.
type HelloSession struct {
	Contract     *Hello            // Generic contract binding to set the session for
	CallOpts     bind.CallOpts     // Call options to use throughout this session
	TransactOpts bind.TransactOpts // Transaction auth options to use throughout this session
}

// HelloCallerSession is an auto generated read-only Go binding around a Solidity contract,
// with pre-set call options.
type HelloCallerSession struct {
	Contract *HelloCaller  // Generic contract caller binding to set the session for
	CallOpts bind.CallOpts // Call options to use throughout this session
}

// HelloTransactorSession is an auto generated write-only Go binding around a Solidity contract,
// with pre-set transact options.
type HelloTransactorSession struct {
	Contract     *HelloTransactor  // Generic contract transactor binding to set the session for
	TransactOpts bind.TransactOpts // Transaction auth options to use throughout this session
}

// HelloRaw is an auto generated low-level Go binding around a Solidity contract.
type HelloRaw struct {
	Contract *Hello // Generic contract binding to access the raw methods on
}

// HelloCallerRaw is an auto generated low-level read-only Go binding around a Solidity contract.
type HelloCallerRaw struct {
	Contract *HelloCaller // Generic read-only contract binding to access the raw methods on
}

// HelloTransactorRaw is an auto generated low-level write-only Go binding around a Solidity contract.
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
func (_Hello *HelloRaw) Call(opts *bind.CallOpts, result interface{}, method string, params ...interface{}) error {
	return _Hello.Contract.HelloCaller.contract.Call(opts, result, method, params...)
}

// Transfer initiates a plain transaction to move funds to the contract, calling
// its default method if one is available.
func (_Hello *HelloRaw) Transfer(opts *bind.TransactOpts) (*types.Transaction, *types.Receipt, error) {
	return _Hello.Contract.HelloTransactor.contract.Transfer(opts)
}

// Transact invokes the (paid) contract method with params as input values.
func (_Hello *HelloRaw) Transact(opts *bind.TransactOpts, method string, params ...interface{}) (*types.Transaction, *types.Receipt, error) {
	return _Hello.Contract.HelloTransactor.contract.Transact(opts, method, params...)
}

// Call invokes the (constant) contract method with params as input values and
// sets the output to result. The result type might be a single field for simple
// returns, a slice of interfaces for anonymous returns and a struct for named
// returns.
func (_Hello *HelloCallerRaw) Call(opts *bind.CallOpts, result interface{}, method string, params ...interface{}) error {
	return _Hello.Contract.contract.Call(opts, result, method, params...)
}

// Transfer initiates a plain transaction to move funds to the contract, calling
// its default method if one is available.
func (_Hello *HelloTransactorRaw) Transfer(opts *bind.TransactOpts) (*types.Transaction, *types.Receipt, error) {
	return _Hello.Contract.contract.Transfer(opts)
}

// Transact invokes the (paid) contract method with params as input values.
func (_Hello *HelloTransactorRaw) Transact(opts *bind.TransactOpts, method string, params ...interface{}) (*types.Transaction, *types.Receipt, error) {
	return _Hello.Contract.contract.Transact(opts, method, params...)
}

// Get is a free data retrieval call binding the contract method 0x6d4ce63c.
//
// Solidity: function get() constant returns(string)
func (_Hello *HelloCaller) Get(opts *bind.CallOpts) (string, error) {
	var (
		ret0 = new(string)
	)
	out := ret0
	err := _Hello.contract.Call(opts, out, "get")
	return *ret0, err
}

// Get is a free data retrieval call binding the contract method 0x6d4ce63c.
//
// Solidity: function get() constant returns(string)
func (_Hello *HelloSession) Get() (string, error) {
	return _Hello.Contract.Get(&_Hello.CallOpts)
}

// Get is a free data retrieval call binding the contract method 0x6d4ce63c.
//
// Solidity: function get() constant returns(string)
func (_Hello *HelloCallerSession) Get() (string, error) {
	return _Hello.Contract.Get(&_Hello.CallOpts)
}

// GetHash is a free data retrieval call binding the contract method 0xd13319c4.
//
// Solidity: function getHash() constant returns(bytes32)
func (_Hello *HelloCaller) GetHash(opts *bind.CallOpts) ([32]byte, error) {
	var (
		ret0 = new([32]byte)
	)
	out := ret0
	err := _Hello.contract.Call(opts, out, "getHash")
	return *ret0, err
}

// GetHash is a free data retrieval call binding the contract method 0xd13319c4.
//
// Solidity: function getHash() constant returns(bytes32)
func (_Hello *HelloSession) GetHash() ([32]byte, error) {
	return _Hello.Contract.GetHash(&_Hello.CallOpts)
}

// GetHash is a free data retrieval call binding the contract method 0xd13319c4.
//
// Solidity: function getHash() constant returns(bytes32)
func (_Hello *HelloCallerSession) GetHash() ([32]byte, error) {
	return _Hello.Contract.GetHash(&_Hello.CallOpts)
}

// GetHash2 is a free data retrieval call binding the contract method 0x33c0f099.
//
// Solidity: function getHash2() constant returns(bytes32)
func (_Hello *HelloCaller) GetHash2(opts *bind.CallOpts) ([32]byte, error) {
	var (
		ret0 = new([32]byte)
	)
	out := ret0
	err := _Hello.contract.Call(opts, out, "getHash2")
	return *ret0, err
}

// GetHash2 is a free data retrieval call binding the contract method 0x33c0f099.
//
// Solidity: function getHash2() constant returns(bytes32)
func (_Hello *HelloSession) GetHash2() ([32]byte, error) {
	return _Hello.Contract.GetHash2(&_Hello.CallOpts)
}

// GetHash2 is a free data retrieval call binding the contract method 0x33c0f099.
//
// Solidity: function getHash2() constant returns(bytes32)
func (_Hello *HelloCallerSession) GetHash2() ([32]byte, error) {
	return _Hello.Contract.GetHash2(&_Hello.CallOpts)
}

// Names is a free data retrieval call binding the contract method 0x4622ab03.
//
// Solidity: function names(uint256 ) constant returns(string)
func (_Hello *HelloCaller) Names(opts *bind.CallOpts, arg0 *big.Int) (string, error) {
	var (
		ret0 = new(string)
	)
	out := ret0
	err := _Hello.contract.Call(opts, out, "names", arg0)
	return *ret0, err
}

// Names is a free data retrieval call binding the contract method 0x4622ab03.
//
// Solidity: function names(uint256 ) constant returns(string)
func (_Hello *HelloSession) Names(arg0 *big.Int) (string, error) {
	return _Hello.Contract.Names(&_Hello.CallOpts, arg0)
}

// Names is a free data retrieval call binding the contract method 0x4622ab03.
//
// Solidity: function names(uint256 ) constant returns(string)
func (_Hello *HelloCallerSession) Names(arg0 *big.Int) (string, error) {
	return _Hello.Contract.Names(&_Hello.CallOpts, arg0)
}

// Set is a paid mutator transaction binding the contract method 0x4ed3885e.
//
// Solidity: function set(string n) returns()
func (_Hello *HelloTransactor) Set(opts *bind.TransactOpts, n string) (*types.Transaction, *types.Receipt, error) {
	return _Hello.contract.Transact(opts, "set", n)
}

func (_Hello *HelloTransactor) AsyncSet(handler func(*types.Receipt, error), opts *bind.TransactOpts, n string) (*types.Transaction, error) {
	return _Hello.contract.AsyncTransact(opts, handler, "set", n)
}

// Set is a paid mutator transaction binding the contract method 0x4ed3885e.
//
// Solidity: function set(string n) returns()
func (_Hello *HelloSession) Set(n string) (*types.Transaction, *types.Receipt, error) {
	return _Hello.Contract.Set(&_Hello.TransactOpts, n)
}

func (_Hello *HelloSession) AsyncSet(handler func(*types.Receipt, error), n string) (*types.Transaction, error) {
	return _Hello.Contract.AsyncSet(handler, &_Hello.TransactOpts, n)
}

// Set is a paid mutator transaction binding the contract method 0x4ed3885e.
//
// Solidity: function set(string n) returns()
func (_Hello *HelloTransactorSession) Set(n string) (*types.Transaction, *types.Receipt, error) {
	return _Hello.Contract.Set(&_Hello.TransactOpts, n)
}

func (_Hello *HelloTransactorSession) AsyncSet(handler func(*types.Receipt, error), n string) (*types.Transaction, error) {
	return _Hello.Contract.AsyncSet(handler, &_Hello.TransactOpts, n)
}

// HelloOnsetIterator is returned from FilterOnset and is used to iterate over the raw logs and unpacked data for Onset events raised by the Hello contract.
type HelloOnsetIterator struct {
	Event *HelloOnset // Event containing the contract specifics and raw log

	contract *bind.BoundContract // Generic contract to use for unpacking event data
	event    string              // Event name to use for unpacking event data

	logs chan types.Log        // Log channel receiving the found contract events
	sub  ethereum.Subscription // Subscription for errors, completion and termination
	done bool                  // Whether the subscription completed delivering logs
	fail error                 // Occurred error to stop iteration
}

// Next advances the iterator to the subsequent event, returning whether there
// are any more events found. In case of a retrieval or parsing error, false is
// returned and Error() can be queried for the exact failure.
func (it *HelloOnsetIterator) Next() bool {
	// If the iterator failed, stop iterating
	if it.fail != nil {
		return false
	}
	// If the iterator completed, deliver directly whatever's available
	if it.done {
		select {
		case log := <-it.logs:
			it.Event = new(HelloOnset)
			if err := it.contract.UnpackLog(it.Event, it.event, log); err != nil {
				it.fail = err
				return false
			}
			it.Event.Raw = log
			return true

		default:
			return false
		}
	}
	// Iterator still in progress, wait for either a data or an error event
	select {
	case log := <-it.logs:
		it.Event = new(HelloOnset)
		if err := it.contract.UnpackLog(it.Event, it.event, log); err != nil {
			it.fail = err
			return false
		}
		it.Event.Raw = log
		return true

	case err := <-it.sub.Err():
		it.done = true
		it.fail = err
		return it.Next()
	}
}

// Error returns any retrieval or parsing error occurred during filtering.
func (it *HelloOnsetIterator) Error() error {
	return it.fail
}

// Close terminates the iteration process, releasing any pending underlying
// resources.
func (it *HelloOnsetIterator) Close() error {
	it.sub.Unsubscribe()
	return nil
}

// HelloOnset represents a Onset event raised by the Hello contract.
type HelloOnset struct {
	Newname string
	Raw     types.Log // Blockchain specific contextual infos
}

// FilterOnset is a free log retrieval operation binding the contract event 0xafb180742c1292ea5d67c4f6d51283ecb11e49f8389f4539bef82135d689e118.
//
// Solidity: event onset(string newname)
func (_Hello *HelloFilterer) FilterOnset(opts *bind.FilterOpts) (*HelloOnsetIterator, error) {

	logs, sub, err := _Hello.contract.FilterLogs(opts, "onset")
	if err != nil {
		return nil, err
	}
	return &HelloOnsetIterator{contract: _Hello.contract, event: "onset", logs: logs, sub: sub}, nil
}

// WatchOnset is a free log subscription operation binding the contract event 0xafb180742c1292ea5d67c4f6d51283ecb11e49f8389f4539bef82135d689e118.
//
// Solidity: event onset(string newname)
func (_Hello *HelloFilterer) WatchOnset(opts *bind.WatchOpts, sink chan<- *HelloOnset) (event.Subscription, error) {

	logs, sub, err := _Hello.contract.WatchLogs(opts, "onset")
	if err != nil {
		return nil, err
	}
	return event.NewSubscription(func(quit <-chan struct{}) error {
		defer sub.Unsubscribe()
		for {
			select {
			case log := <-logs:
				// New log arrived, parse the event and forward to the user
				event := new(HelloOnset)
				if err := _Hello.contract.UnpackLog(event, "onset", log); err != nil {
					return err
				}
				event.Raw = log

				select {
				case sink <- event:
				case err := <-sub.Err():
					return err
				case <-quit:
					return nil
				}
			case err := <-sub.Err():
				return err
			case <-quit:
				return nil
			}
		}
	}), nil
}

// ParseOnset is a log parse operation binding the contract event 0xafb180742c1292ea5d67c4f6d51283ecb11e49f8389f4539bef82135d689e118.
//
// Solidity: event onset(string newname)
func (_Hello *HelloFilterer) ParseOnset(log types.Log) (*HelloOnset, error) {
	event := new(HelloOnset)
	if err := _Hello.contract.UnpackLog(event, "onset", log); err != nil {
		return nil, err
	}
	return event, nil
}
