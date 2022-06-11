package main

import (
	"logger/logger"
	"logger/routes"

	"logger/configs"

	"github.com/gin-gonic/gin"
)

func main() {
	//禁用控制台颜色
	//gin.DisableConsoleColor()
	configs.Show()
	// Logging to a file.
	// 如果需要同时将日志写入文件和控制台，请使用以下代码。
	r := gin.Default()
	r.Use(logger.LoggerMiddleware())
	r.GET("/ping", routes.Ping)
	r.GET("/login", routes.Login)

	r.Run()
}
