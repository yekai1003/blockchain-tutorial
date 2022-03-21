import sys
sys.path.append("../../python-sdk")
from client.bcosclient import BcosClient
# import os
# from client.stattool import StatTool
# from client.datatype_parser import DatatypeParser
# from client.common.compiler import Compiler
# from client_config import client_config
# from client.bcoserror import BcosException, BcosError
# import traceback
# import json


client = BcosClient()
# ['blockLimit', 'call', 'channel_getBlockLimit', 'channel_handler', 'channel_sendRawTransactionGetReceipt', 'common_request', 'default_from_account_signer', 'deploy', 'deployFromFile', 'finish', 'fiscoChainId', 'getBlockByHash', 'getBlockByNumber', 'getBlockHashByNumber', 'getBlockLimit', 'getBlockNumber', 'getCode', 'getConsensusStatus', 'getGroupList', 'getGroupPeers', 'getNodeIDList', 'getNodeVersion', 'getObserverList', 'getPbftView', 'getPeers', 'getPendingTransactions', 'getPendingTxSize', 'getSealerList', 'getSyncStatus', 'getSystemConfigByKey', 'getTotalTransactionCount', 'getTransactionByBlockHashAndIndex', 'getTransactionByBlockNumberAndIndex', 'getTransactionByHash', 'getTransactionReceipt', 'getinfo', 'groupid', 'init', 'is_error_response', 'lastblocklimittime', 'lastblocknum', 'load_default_account', 'logger', 'max_chain_id', 'max_group_id', 'protocol_list', 'request_counter', 'rpc', 'rpc_sendRawTransactionGetReceipt', 'sendRawTransaction', 'sendRawTransactionGetReceipt', 'sysconfig_keys']
abi = [{"inputs":[],"stateMutability":"nonpayable","type":"constructor"},{"anonymous":False,"inputs":[{"indexed":False,"internalType":"string","name":"newname","type":"string"}],"name":"onset","type":"event"},{"inputs":[],"name":"get","outputs":[{"internalType":"string","name":"","type":"string"}],"stateMutability":"view","type":"function"},{"inputs":[{"internalType":"string","name":"n","type":"string"}],"name":"set","outputs":[],"stateMutability":"nonpayable","type":"function"}]

data = client.call("0x792a54133323321bd7ef73374e48b18529e264e3",abi,"get")
print(data)
data = client.sendRawTransactionGetReceipt("0x792a54133323321bd7ef73374e48b18529e264e3",abi,"set",["aa"])
print(data)
data = client.call("0x792a54133323321bd7ef73374e48b18529e264e3",abi,"get")
print(data)

client.finish()