package handler

import "github.com/gin-gonic/gin"

func (h *Handler) registerTask() {
	g := h.router.Group("/api/task")
	{
		g.GET("", func(ctx *gin.Context) {})
		g.POST("", func(ctx *gin.Context) {})
		g.POST("/{id}/start", func(ctx *gin.Context) {})
		g.POST("/{id}/stop", func(ctx *gin.Context) {})
	}
}
