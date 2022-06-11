package logger

import (
	"log"
	"os"

	"github.com/gin-gonic/gin"

	"path"
	"time"

	rotatelogs "github.com/lestrrat-go/file-rotatelogs"
	"github.com/rifflock/lfshook"
	"github.com/shirou/gopsutil/process"
	"github.com/sirupsen/logrus"
)

var (
	WarnLogger *logrus.Logger
	InfoLogger *logrus.Logger
)

var (
	//日志地址
	logFilePath = "./logs/"
)

func init() {
	processName := getPname()
	WarnLogger = initLog(logFilePath, processName+".warn")
	InfoLogger = initLog(logFilePath, processName+".log")
	//InfoLogger.Logln(logrus.InfoLevel, "begin write")
	WarnLogger.Logln(logrus.WarnLevel, "do sth warn", "not ok?")
	//WarnLogger.Panicln("init over")

}

func initLog(filePath, fileName string) *logrus.Logger {

	// 日志文件
	fileName = path.Join(filePath, fileName)
	// 写入文件

	src, err := os.OpenFile(fileName, os.O_APPEND|os.O_WRONLY, os.ModeAppend)
	if err != nil {
		//log.Panic("failed to openfile", err)
		log.Println("failed to open file ", err)
	}
	// 实例化

	logger := logrus.New()

	//设置日志级别
	logger.SetLevel(logrus.DebugLevel)
	//设置输出
	logger.Out = src
	// 设置 rotatelogs
	logWriter, err := rotatelogs.New(
		// 分割后的文件名称
		fileName+".%Y%m%d",

		// 生成软链，指向最新日志文件
		rotatelogs.WithLinkName(fileName),

		// 设置最大保存时间(7天)
		rotatelogs.WithMaxAge(7*24*time.Hour),

		// 设置日志切割时间间隔(1天)
		rotatelogs.WithRotationTime(24*time.Hour),
	)

	writeMap := lfshook.WriterMap{
		logrus.InfoLevel:  logWriter,
		logrus.TraceLevel: logWriter,
		logrus.DebugLevel: logWriter,
		logrus.WarnLevel:  logWriter,
		logrus.ErrorLevel: logWriter,
		logrus.PanicLevel: logWriter,
	}

	logger.AddHook(lfshook.NewHook(writeMap, &logrus.JSONFormatter{
		TimestampFormat: "2006-01-02 15:04:05",
	}))

	return logger
}

func LoggerMiddleware() gin.HandlerFunc {

	return func(c *gin.Context) {
		//开始时间
		startTime := time.Now()
		//处理请求
		c.Next()
		//结束时间
		endTime := time.Now()
		// 执行时间
		latencyTime := endTime.Sub(startTime)
		//请求方式
		reqMethod := c.Request.Method
		//请求路由
		reqUrl := c.Request.RequestURI
		//状态码
		statusCode := c.Writer.Status()
		//请求ip
		clientIP := c.ClientIP()

		// 日志格式
		InfoLogger.WithFields(logrus.Fields{
			"status_code":  statusCode,
			"latency_time": latencyTime,
			"client_ip":    clientIP,
			"req_method":   reqMethod,
			"req_uri":      reqUrl,
		}).Info()

	}
}

func getPname() string {
	//os.Getpid()
	proc, err := process.NewProcess(int32(os.Getpid()))
	if err != nil {
		WarnLogger.Panic("failed to Newprocess ", err)
	}
	name, err := proc.Name()
	if err != nil {
		WarnLogger.Panic("failed to get Name ", err)
	}
	return name
}
