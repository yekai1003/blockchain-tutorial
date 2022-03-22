import sys
sys.path.append("../../python-sdk")
from client.bcosclient import BcosClient

taskabi=[{"inputs":[{"internalType":"address","name":"owner","type":"address"}],"stateMutability":"nonpayable","type":"constructor"},{"inputs":[{"internalType":"string","name":"_owner","type":"string"}],"name":"balanceOf","outputs":[{"internalType":"uint256","name":"balance","type":"uint256"}],"stateMutability":"view","type":"function"},{"inputs":[{"internalType":"string","name":"worker","type":"string"},{"internalType":"string","name":"passwd","type":"string"},{"internalType":"uint256","name":"taskID","type":"uint256"}],"name":"commit","outputs":[],"stateMutability":"nonpayable","type":"function"},{"inputs":[{"internalType":"string","name":"issuer","type":"string"},{"internalType":"string","name":"passwd","type":"string"},{"internalType":"uint256","name":"taskID","type":"uint256"},{"internalType":"string","name":"comment","type":"string"},{"internalType":"uint8","name":"status","type":"uint8"}],"name":"confirm","outputs":[],"stateMutability":"nonpayable","type":"function"},{"inputs":[{"internalType":"string","name":"issuer","type":"string"},{"internalType":"string","name":"passwd","type":"string"},{"internalType":"string","name":"desc","type":"string"},{"internalType":"uint256","name":"bonus","type":"uint256"}],"name":"issue","outputs":[],"stateMutability":"nonpayable","type":"function"},{"inputs":[{"internalType":"string","name":"username","type":"string"},{"internalType":"string","name":"passwd","type":"string"}],"name":"login","outputs":[{"internalType":"bool","name":"","type":"bool"}],"stateMutability":"view","type":"function"},{"inputs":[{"internalType":"string","name":"_to","type":"string"},{"internalType":"uint256","name":"_value","type":"uint256"}],"name":"mint","outputs":[],"stateMutability":"nonpayable","type":"function"},{"inputs":[],"name":"qryAllBonus","outputs":[{"internalType":"uint256[]","name":"","type":"uint256[]"}],"stateMutability":"view","type":"function"},{"inputs":[],"name":"qryAllComments","outputs":[{"internalType":"string[]","name":"","type":"string[]"}],"stateMutability":"view","type":"function"},{"inputs":[],"name":"qryAllDesc","outputs":[{"internalType":"string[]","name":"","type":"string[]"}],"stateMutability":"view","type":"function"},{"inputs":[],"name":"qryAllIssuers","outputs":[{"internalType":"string[]","name":"","type":"string[]"}],"stateMutability":"view","type":"function"},{"inputs":[],"name":"qryAllStatus","outputs":[{"internalType":"uint8[]","name":"","type":"uint8[]"}],"stateMutability":"view","type":"function"},{"inputs":[],"name":"qryAllWorkers","outputs":[{"internalType":"string[]","name":"","type":"string[]"}],"stateMutability":"view","type":"function"},{"inputs":[{"internalType":"uint256","name":"taskID","type":"uint256"}],"name":"qryOneTask","outputs":[{"internalType":"string","name":"","type":"string"},{"internalType":"string","name":"","type":"string"},{"internalType":"uint256","name":"","type":"uint256"},{"internalType":"string","name":"","type":"string"},{"internalType":"uint8","name":"","type":"uint8"}],"stateMutability":"view","type":"function"},{"inputs":[{"internalType":"string","name":"username","type":"string"},{"internalType":"string","name":"passwd","type":"string"}],"name":"register","outputs":[],"stateMutability":"nonpayable","type":"function"},{"inputs":[{"internalType":"string","name":"worker","type":"string"},{"internalType":"string","name":"passwd","type":"string"},{"internalType":"uint256","name":"taskID","type":"uint256"}],"name":"take","outputs":[],"stateMutability":"nonpayable","type":"function"},{"inputs":[],"name":"totalSupply","outputs":[{"internalType":"uint256","name":"","type":"uint256"}],"stateMutability":"view","type":"function"},{"inputs":[{"internalType":"string","name":"_from","type":"string"},{"internalType":"string","name":"_to","type":"string"},{"internalType":"uint256","name":"_value","type":"uint256"}],"name":"transfer","outputs":[{"internalType":"bool","name":"success","type":"bool"}],"stateMutability":"nonpayable","type":"function"}]

taskcontract="0xf52d572eaee9e1f7a91001bdec22a4ea305d9478"

client = BcosClient()

def register(name, password):
    data = client.sendRawTransactionGetReceipt(taskcontract, taskabi, "register", [name, password])
    print(data)

def login(name, password):
    data = client.call(taskcontract, taskabi, "login", [name, password])
    print(data)
