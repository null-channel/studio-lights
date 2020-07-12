
package routs

import (
	"net/http"
	"github.com/gin-gonic/gin"
	"github.com/null-channel/studio-lights/structs"
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
