package api

import (
	"wc2/internal/application/ports/in/usecases"

	"github.com/gin-gonic/gin"
)

type Handler struct {
	router gin.IRouter

	authUsecase usecases.AuthUsecase
	userUsecase usecases.UserUsecase
}

func New(engine gin.IRouter) (*Handler, error) {
	var h = &Handler{
		router: engine,
	}

	// ***

	h.registerAuth()
	h.registerUser()
	h.registerTask()

	return h, nil
}
