package main

import (
    "fmt"
    "net/http"
    "github.com/gin-gonic/gin"
    "github.com/null-channel/studio-lights/routs"
)

type server struct {
	Engine *gin.Engine
}

func (s *server) start() {
	s.Engine = gin.Default()
	s.Engine.GET("/test", func(c *gin.Context) {
		c.String(http.StatusOK, "accepted")
	})
	s.Engine.GET("/lights", routs.GetLights)
	s.Engine.POST("/test", testPost)
	fmt.Printf("boom")
	s.Engine.Run(":8080")
}

func main() {
	server := &server{}
	server.start()
}

func testPost(c *gin.Context) {
	c.String(http.StatusOK, "posted")
}
