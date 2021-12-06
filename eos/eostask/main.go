package main

import (
	"eostask/routes"

	"github.com/gin-gonic/gin"
	"github.com/go-session/gin-session"
)

func Ping(c *gin.Context) {
	c.JSON(200, gin.H{
		"message": "pong",
	})
}

func main() {

	//创建gin对象
	r := gin.Default()

	r.Use(ginsession.New()) //使用session中间件

	//静态文件处理
	r.StaticFile("/", "./dist/index.html")
	r.StaticFile("/index", "./dist/index.html")
	r.Static("/static", "./dist/static")

	//设置路由规则 ： 请求方法，请求url，相应方法
	r.GET("/ping", Ping)
	//注册的路由设置
	r.POST("/register", routes.Register)
	//登陆的路由设置
	r.POST("/login", routes.Login)
	//任务发布路由设置
	r.POST("/issue", routes.Issue)
	//任务列表获取
	r.GET("/tasklist", routes.Tasklist)
	//任务更新接口
	r.POST("/update", routes.Update)

	r.Run(":9090") // listen and serve on 0.0.0.0:8080 (for windows "localhost:8080")
}
