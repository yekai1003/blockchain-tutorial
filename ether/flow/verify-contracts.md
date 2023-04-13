
```sh
mkdir disperseflow
cd disperseflow/
npx hardhat init
rm contracts/Lock.sol

```

创建contracts/DisperseFlow.sol文件
添加合约代码

修改scripts/deploy.js文件
```js
// We require the Hardhat Runtime Environment explicitly here. This is optional
// but useful for running the script in a standalone fashion through `node <script>`.
//
// You can also run a script with `npx hardhat run <script>`. If you do that, Hardhat
// will compile your contracts, add the Hardhat Runtime Environment's members to the
// global scope, and execute the script.
const hre = require("hardhat");

async function main() {

  const Flow = await hre.ethers.getContractFactory("DisperseFlow");
  const flow = await Flow.deploy();

  await flow.deployed();

  console.log(
    `Flow with deployed to ${flow.address}`
  );
}

// We recommend this pattern to be able to use async/await everywhere
// and properly handle errors.
main().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
```

修改hardhat.config.js文件
```js
require("@nomicfoundation/hardhat-toolbox");
require("dotenv").config();

/** @type import('hardhat/config').HardhatUserConfig */
module.exports = {
  solidity: "0.8.18",
  networks: {
    mumbai: {
      url: 'https://matic-mumbai.chainstacklabs.com',
      accounts: [process.env.PRIVATE_KEY]
    },
  },
  etherscan: {
    apiKey: process.env.POLYGONSCAN_API_KEY
 }
};

```
编译合约

```sh
npm install dotenv
npm install @superfluid-finance/ethereum-contracts
npx hardhat compile

```

部署合约，得到地址：0xcA152245d39097b0Fb1291466504F2115c99A0F1
```sh
npx hardhat run scripts/deploy.js --network mumbai
```

开源合约：
```sh
npx hardhat verify --network mumbai 0xcA152245d39097b0Fb1291466504F2115c99A0F1
```
