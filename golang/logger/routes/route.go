package routes

import (
	"logger/logger"
	"net/http"

	"github.com/gin-gonic/gin"
)

func Ping(c *gin.Context) {
	logger.WarnLogger.Warn("user ping request...")
	c.String(200, "pong")
}

func Login(c *gin.Context) {
	logger.InfoLogger.Info("user request login...")
	//logger.WarnLogger.WithField
	c.JSON(http.StatusOK, "login ok")
}
