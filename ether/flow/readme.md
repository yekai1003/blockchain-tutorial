# 操作说明

## 1. 领取水龙头
可以在[https://mumbaifaucet.com/](https://mumbaifaucet.com/)领取水龙头，目前每天可领取0.5

## 2. 兑换spuertoken

流支付使用的是supertoken，可以与erc20等比例兑换。
在[https://app.superfluid.finance/wrap?upgrade=](https://app.superfluid.finance/wrap?upgrade=)进行兑换matic即可

## 3. 部署合约
部署到mumbai网络
合约源码
```solidity
// SPDX-License-Identifier: GPL-3.0
pragma solidity^0.8.14;

import {
    ISuperfluid, 
    ISuperToken, 
    ISuperApp
} from "@superfluid-finance/ethereum-contracts/contracts/interfaces/superfluid/ISuperfluid.sol";

import { SuperTokenV1Library } from "@superfluid-finance/ethereum-contracts/contracts/apps/SuperTokenV1Library.sol";

error Unauthorized();

contract DisperseFlow {

    address owner; 
    using SuperTokenV1Library for ISuperToken;
    //ISuperToken public token;
    // github->address
    mapping(string=>address) nick2addrs;
    
    constructor() {
        owner = msg.sender;
    }

    /// @notice Transfer ownership.
    /// @param _newOwner New owner account.
    function changeOwner(address _newOwner) external {
        if (msg.sender != owner) revert Unauthorized();

        owner = _newOwner;
    }
    modifier onlyOwner() {
        require(msg.sender == owner, "only owner can do");
        _;
    }

    /// @notice address's owner register his github account.
    /// @param _account owner's github account.
    function register(string memory _account) external {
        require(bytes(_account).length > 0, "account is null");
        require(nick2addrs[_account] == address(0), "account already exists");
        nick2addrs[_account] = msg.sender;
    }

    /// @notice batch airdrop by address.
    /// @param _token address for SuperToken.
    /// @param _recipients address list.
    /// @param _flowRates rate list.
    function disperseToken(ISuperToken _token, address[] memory _recipients, int96[] memory _flowRates) external onlyOwner {
        for (uint256 i = 0; i < _recipients.length; i++) {
            _token.createFlow(_recipients[i], _flowRates[i]);
        }
            
    }

    /// @notice batch airdrop by account.
    /// @param _token address for SuperToken.
    /// @param _recipients account list.
    /// @param _flowRates rate list.
    function disperseTokenByAccount(ISuperToken _token, string[] memory _recipients, int96[] memory _flowRates) external onlyOwner {
        for (uint256 i = 0; i < _recipients.length; i++) {
            address recipient = nick2addrs[_recipients[i]];
            if(address(0) != recipient) {
                _token.createFlow(recipient, _flowRates[i]);
            }
        }
            
    }

    /// @notice batch update flow by address.
    /// @param _token address for SuperToken.
    /// @param _recipients account list.
    /// @param _flowRates rate list.
    function batchUpdateFlow(ISuperToken _token, address[] memory _recipients, int96[] memory _flowRates) external onlyOwner {
        for (uint256 i = 0; i < _recipients.length; i++) {
            _token.updateFlow(_recipients[i], _flowRates[i]);
        }  
    }

    /// @notice batch update flow by account.
    /// @param _token address for SuperToken.
    /// @param _recipients account list.
    /// @param _flowRates rate list.
    function batchUpdateFlowbyAccount(ISuperToken _token, string[] memory _recipients, int96[] memory _flowRates) external onlyOwner {
        for (uint256 i = 0; i < _recipients.length; i++) {
            address recipient = nick2addrs[_recipients[i]];
            if(address(0) != recipient) {
                _token.updateFlow(recipient, _flowRates[i]);
            }
        }
            
    }

    /// @notice Update flow from contract to specified address.
    /// @param _token address for SuperToken.
    /// @param _receiver Receiver of stream.
    /// @param _flowRate Flow rate per second to stream.
    function updateFlow(
        ISuperToken _token, 
        address _receiver,
        int96 _flowRate
    ) external onlyOwner {

        _token.updateFlow(_receiver, _flowRate);
    }

    /// @notice Update flow from contract to specified address.
    /// @param _token address for SuperToken.
    /// @param _account Receiver of stream.
    /// @param _flowRate Flow rate per second to stream.
    function updateFlowByAccount(
        /// @param _token address for SuperToken.
        ISuperToken _token, 
        string memory _account,
        int96 _flowRate
    ) external onlyOwner {
        require(nick2addrs[_account] != address(0), "account does's exists");
        _token.updateFlow(nick2addrs[_account], _flowRate);
    }

    /// @notice Withdraw funds from the contract.
    /// @param _token address for SuperToken.
    function withdrawFunds(ISuperToken _token) external  {
        uint256 amount = _token.balanceOf(address(this));
        _token.transfer(owner, amount);
    }
}
```

## 4. 充supertoken到合约

目前的代码需要提前将supertoken放到合约内，然后进行流支付，后续有必要可以使用appve模式，那样可以让合约拥有转移某账户supertoken的能力也可以。
当前状态下，需要将第2步兑换的token转账到第3步部署的合约地址中，可以在remix使用ierc20接口打开0x96B82B65ACF7072eFEb00502F45757F254c2a0D4，进行transfer操作。

## 5. 开始批量流转账

可以找若干账户执行合约的register来注册，我测试了yekai1003，yekai233两个账户。
之后执行disperseTokenByAccount方法，来设置流支付，输入参数依次为：supertoken地址、github账号列表、速率列表（单位为：数量/秒）。

```solidity
disperseTokenByAccount(0x96B82B65ACF7072eFEb00502F45757F254c2a0D4, ["yekai1003","yekai233"], [100,200])
```
