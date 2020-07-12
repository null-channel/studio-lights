
package routs

import (
	"net/http"
	"github.com/gin-gonic/gin"
	"github.com/null-channel/studio-lights/structs"
	"strconv"
)

var RGB structs.RGB

func init() {
	RGB = structs.RGB {
		Red: 255,
		Blue: 255,
		Green: 255,
	}
}

func GetLights(c *gin.Context) {
	c.JSON(http.StatusOK, RGB)
}

func PostLights(c *gin.Context) {
	r, g, b := 0,0,0
	if n, err := strconv.Atoi(c.DefaultQuery("red", "0")); err == nil {
		r = n
	}
	if n, err := strconv.Atoi(c.DefaultQuery("blue","0")); err == nil {
		b = n
	}
	if n, err := strconv.Atoi(c.DefaultQuery("green", "0")); err == nil {
		g = n
	}
	RGB = structs.RGB{
		Red: r,
		Blue: b,
		Green: g,
	}
	c.JSON(200, gin.H{
		"status": "posted",
		"colors": RGB,
	})
}
