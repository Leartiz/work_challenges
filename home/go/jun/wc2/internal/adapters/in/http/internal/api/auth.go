package api

import (
	"github.com/gin-gonic/gin"
)

func (h *Handler) registerAuth() {
	h.router.POST("/api/sign-up", h.signUp)
	h.router.POST("/api/sign-in", h.signIn)
	h.router.POST("/api/refresh", h.refresh)
}

// -----------------------------------------------------------------------

func (h *Handler) signUp(ctx *gin.Context) {

}

func (h *Handler) signIn(ctx *gin.Context) {

}

func (h *Handler) refresh(ctx *gin.Context) {

}
