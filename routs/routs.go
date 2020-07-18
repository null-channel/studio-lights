
package routs

import (
	"net/http"
	"github.com/gin-gonic/gin"
	"github.com/null-channel/studio-lights/structs"
	"strconv"
)

var Lights []*structs.Light

func init() {
	Lights = []*structs.Light {
		&structs.Light {
			Number: 0,
			Red: 255,
			Blue: 50,
			Green: 255,
		},
		&structs.Light {
			Number: 1,
			Red:255,
			Blue: 255,
			Green: 0,
		},
		&structs.Light {
			Number: 2,
			Red:0,
			Blue: 205,
			Green: 0,
		},
		&structs.Light {
			Number: 3,
			Red:0,
			Blue: 100,
			Green: 10,
		},
	}
}

func GetLights(c *gin.Context) {
	c.JSON(http.StatusOK, Lights)
}

func PostLights(c *gin.Context) {
	r, g, b, number := 0,0,0,0
	if n, err := strconv.Atoi(c.Param("number")); err == nil {
		number = n
	}

	if n, err := strconv.Atoi(c.DefaultQuery("red", "0")); err == nil {
		r = n
	}
	if n, err := strconv.Atoi(c.DefaultQuery("blue","0")); err == nil {
		b = n
	}
	if n, err := strconv.Atoi(c.DefaultQuery("green", "0")); err == nil {
		g = n
	}

	for _, v := range Lights {
		if v.Number == number {
			v.Red = r
			v.Blue = b
			v.Green = g
		}
	}
	c.JSON(200, gin.H{
		"status": "posted",
		"colors": Lights,
	})
}
