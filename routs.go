
package main

import (
	"fmt"
	"github.com/gin-gonic/gin"
	"github.com/null-channel/studio-lights/structs"
)

func (s *Server) getLights(c *gin.Context) {
	c.JSON(http.StatusOK, s.RGB)
}
