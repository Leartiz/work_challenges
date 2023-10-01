package http

import (
	"wc1/product"

	"github.com/gin-gonic/gin"
)

func RegisterHandler(router *gin.Engine, uc product.UseCase) {
	handler := NewHandler(uc)
	groupRouter := router.Group("/product")
	{
		groupRouter.GET("", handler.Get)
		groupRouter.GET("/:id", handler.GetConcrete)

		groupRouter.POST("", handler.Create)
		groupRouter.PUT("/:id", handler.PutConcrete)
		groupRouter.DELETE("/:id", handler.Delete)
	}
}
