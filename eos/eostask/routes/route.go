package routes

import (
	"eostask/eosgo"
	_ "eostask/eosgo"
	"fmt"
	"log"
	"net/http"
	"strconv"

	"github.com/gin-gonic/gin"
	_ "github.com/go-session/gin-session"
)

// 通用化响应消息格式
type RespMsg struct {
	Code string      `json:"code"`
	Msg  string      `json:"msg"`
	Data interface{} `json:"data"`
}

//code提前编码
const (
	RESPCODE_OK       = "0"
	RESPCODE_LOGINERR = "1"
	RESPCODE_PARAMERR = "2"
	RESPCODE_BLKERR   = "3"
	RESPCODE_UNKNOWN  = "4"
)

var respMapMsg = map[string]string{
	RESPCODE_OK:       "正常",
	RESPCODE_LOGINERR: "登陆失败",
	RESPCODE_PARAMERR: "参数错误",
	RESPCODE_BLKERR:   "区块链访问错误",
	RESPCODE_UNKNOWN:  "系统正在升级",
}

//统一的响应消息
func CoderspMsg(resp *RespMsg, c *gin.Context) {
	resp.Msg = respMapMsg[resp.Code]
	c.JSON(http.StatusOK, resp)
}

//需要一个请求消息内容的结构体
type UserInfo struct {
	UserName string `json:"username"`
	Passwd   string `json:"password"` // 严格遵循接口
}

func Register(c *gin.Context) {
	//1. 组织响应消息
	resp := RespMsg{
		Code: "0",
	}

	defer CoderspMsg(&resp, c) //当Register退出时，CoderspMsg执行，使用resp信息
	//2. 解析请求消息
	var ui UserInfo
	err := c.ShouldBind(&ui)
	if err != nil {

		resp.Code = RESPCODE_PARAMERR
		log.Panic("failed to ShouldBind", err)
	}
	fmt.Printf("Register:%+v\n", ui)
	//3. 调用区块链合约
	// err = bcos.Register(ui.UserName, ui.Passwd)
	// if err != nil {
	// 	resp.Code = RESPCODE_BLKERR
	// 	log.Panic("failed to bcos.Register", err)
	// }
}

//curl  -H "Content-type: application/json" -X POST -d '{"username":"yekai","password":"123"}' "http://localhost:9090/login"

func Login(c *gin.Context) {
	//1. 组织响应消息
	resp := RespMsg{
		Code: "0",
	}

	defer CoderspMsg(&resp, c) //当Login退出时，CoderspMsg执行，使用resp信息
	//2. 解析请求消息
	var ui UserInfo
	err := c.ShouldBind(&ui)
	if err != nil {

		resp.Code = RESPCODE_PARAMERR
		log.Panic("failed to ShouldBind", err)
	}
	fmt.Printf("Login:%+v\n", ui)

	//3. 调用区块链合约
	eosgo.Login(ui.UserName, ui.Passwd)
	// ok, err := bcos.Login(ui.UserName, ui.Passwd)
	// if err != nil {
	// 	resp.Code = RESPCODE_BLKERR
	// 	log.Panic("failed to bcos.Login", err)
	// }
	// if !ok {
	// 	resp.Code = RESPCODE_LOGINERR
	// 	fmt.Println("User or password err")
	// }

	// //4. session记录
	// store := ginsession.FromContext(c)
	// store.Set("username", ui.UserName)
	// store.Set("password", ui.Passwd)
	// err = store.Save()
	// if err != nil {
	// 	//c.AbortWithError(500, err)
	// 	resp.Code = RESPCODE_UNKNOWN
	// 	fmt.Println("session err", err)
	// 	return
	// }
}

type TaskInfo struct {
}

func Issue(c *gin.Context) {
	//1. 组织响应消息
	resp := RespMsg{
		Code: "0",
	}

	defer CoderspMsg(&resp, c)
	//2. 解析请求消息
	var taskinfo TaskInfo
	err := c.ShouldBind(&taskinfo)
	if err != nil {

		resp.Code = RESPCODE_PARAMERR
		log.Panic("failed to ShouldBind", err)
	}
	fmt.Printf("Issue:%+v\n", taskinfo)
	//3. 从session获取用户和密码信息
	// store := ginsession.FromContext(c)
	// username, ok1 := store.Get("username")
	// password, ok2 := store.Get("password")
	// if !ok1 || !ok2 {
	// 	resp.Code = RESPCODE_UNKNOWN
	// 	fmt.Println("Failed to get session")
	// 	return
	// }
	// //4. 调用智能合约
	// err = bcos.Issue(username.(string), password.(string), taskinfo.Desc, taskinfo.Bonus)
	// if err != nil {
	// 	resp.Code = RESPCODE_BLKERR
	// 	log.Panic("failed to bcos.Issue", err)
	// }

}

//  /tasklist?page=1
func Tasklist(c *gin.Context) {
	//1. 组织响应消息(data字段使用)
	resp := RespMsg{
		Code: "0",
	}

	defer CoderspMsg(&resp, c)

	//2. 获取前端请求页(任务列表可以有很多，前端请求分页显示，一行显示10条，显示第几页)
	page := c.Query("page")
	ipage, _ := strconv.Atoi(page)
	fmt.Println("Tasklist:page = ", ipage)

	//3. 获取任务列表信息
	// tasks, err := bcos.Tasklist()
	// if err != nil {
	// 	resp.Code = RESPCODE_BLKERR
	// 	log.Panic("failed to Tasklist", err)
	// }

	// //4. 响应消息填写
	// //需要根据page计算要返回的列表是什么
	// ibegin := (ipage - 1) * 10
	// iend := ipage * 10
	// if iend > len(tasks) {
	// 	iend = len(tasks)
	// }
	// //data:{total:8, data:[]list}
	// data := struct {
	// 	Total int         `json:"total"`
	// 	Data  interface{} `json:"data"`
	// }{
	// 	Total: len(tasks),
	// 	Data:  tasks[ibegin:iend],
	// }

	// resp.Data = data

}

//任务更新接口
func Update(c *gin.Context) {
	//1. 组织响应消息
	resp := RespMsg{
		Code: "0",
	}

	defer CoderspMsg(&resp, c)
	//2. 解析请求消息
	var taskinfo TaskInfo
	err := c.ShouldBind(&taskinfo)
	if err != nil {

		resp.Code = RESPCODE_PARAMERR
		log.Panic("failed to ShouldBind", err)
	}
	fmt.Printf("Update:%+v\n", taskinfo)
	//3. 从session获取用户和密码信息
	// store := ginsession.FromContext(c)
	// username, ok1 := store.Get("username")
	// password, ok2 := store.Get("password")
	// if !ok1 || !ok2 {
	// 	resp.Code = RESPCODE_UNKNOWN
	// 	fmt.Println("Failed to get session")
	// 	return
	// }
	//4. 调用智能合约
	// taskID, _ := strconv.Atoi(taskinfo.TaskID)

	// err = bcos.Update(username.(string), password.(string), taskinfo.Comment, int64(taskID), taskinfo.Status)
	// if err != nil {
	// 	resp.Code = RESPCODE_BLKERR
	// 	log.Panic("failed to bcos.Update", err)
	// }

}
