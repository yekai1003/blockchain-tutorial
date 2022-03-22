import sys
#sys.path.append("./")
import bcos

if len(sys.argv) < 4:
    print("params too less")
    print("python3 bcos.py register yekai 123")
    print("python3 bcos.py login yekai 123")

if sys.argv[1] == "login":
    bcos.login(sys.argv[2],sys.argv[3])
if sys.argv[1] == "register":
    bcos.register(sys.argv[2],sys.argv[3])