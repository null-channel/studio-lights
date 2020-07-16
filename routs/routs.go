
package routs

import (
	"net/http"
	"github.com/gin-gonic/gin"
	"github.com/null-channel/studio-lights/structs"
	"strconv"
)

var Lights structs.Lights

func init() {
	Lights = structs.Lights {
		Status: structs.Status {
			On: true,
		},
		Red: 255,
		Blue: 50,
		Green: 255,
	}
}

func GetLights(c *gin.Context) {
	c.JSON(http.StatusOK, Lights)
}

func PostLights(c *gin.Context) {
	r, g, b := 0,0,0
	is_on := false
	if n, err := strconv.Atoi(c.DefaultQuery("red", "0")); err == nil {
		r = n
	}
	if n, err := strconv.Atoi(c.DefaultQuery("blue","0")); err == nil {
		b = n
	}
	if n, err := strconv.Atoi(c.DefaultQuery("green", "0")); err == nil {
		g = n
	}
	if b, err := strconv.ParseBool(c.DefaultQuery("status_on", "false")); err == nil {
		is_on = b
	}

	Lights = structs.Lights{
		Status: structs.Status{
			On: is_on,
		},
		Red: r,
		Blue: b,
		Green: g,
	}
	c.JSON(200, gin.H{
		"status": "posted",
		"colors": Lights,
	})
}
