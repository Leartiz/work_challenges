package handler

import (
	"github.com/gin-gonic/gin"
)

type Handler struct {
	router gin.IRouter
}

func New(engine gin.IRouter) (*Handler, error) {
	var h Handler

	h.registerUser()
	h.registerTask()

	return &h, nil
}
