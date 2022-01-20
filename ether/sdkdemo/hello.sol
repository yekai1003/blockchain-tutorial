pragma solidity^0.8.7;

contract hello {
    string public Msg;
    constructor() public {
        Msg = "hello world";
    }

    function setMsg(string memory _msg) public {
        Msg = _msg;
    }
}