package main

import (
    "fmt"
    "net/http"
    "github.com/gin-gonic/gin"
    "github.com/null-channel/studio-lights/structs"
)

type server struct {
	Engine *gin.Engine
	RGB structs.RGB
}

func (s *server) start() {
	s.Engine = gin.Default()
	s.Engine.GET("/test", func(c *gin.Context) {
		c.String(http.StatusOK, "accepted")
	})
	s.Engine.GET("/lights", s.getLights)
	s.Engine.POST("/test", testPost)
	fmt.Printf("boom")
	s.Engine.Run(":8080")
	s.RGB = structs.RGB{
		Red: 255,
		Blue: 255,
		Green: 255,
	}
}

func main() {
	server := &server{}
	server.start()
}

func testPost(c *gin.Context) {
	c.String(http.StatusOK, "posted")
}
