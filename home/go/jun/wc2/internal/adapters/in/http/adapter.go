package http

import (
	"context"
	"fmt"
	"net/http"
	"time"
	handler "wc2/internal/adapters/in/http/internal/api"
	"wc2/pkg/utils"

	"github.com/gin-gonic/gin"
)

type Adapter struct {
	svr *http.Server
}

func New(startCtx context.Context,
	host string, port uint16,
	readTimeout, writeTimeout time.Duration) (*Adapter, error) {

	engine := gin.Default()
	engine.GET("/ping", func(ctx *gin.Context) {
		ctx.String(http.StatusOK, "pong")
	})

	if _, err := handler.New(engine); err != nil {
		return nil, utils.NewFuncError(New, err)
	}

	// ***

	svr := &http.Server{
		Addr:           fmt.Sprintf("%v:%v", host, port),
		ReadTimeout:    readTimeout,
		WriteTimeout:   writeTimeout,
		MaxHeaderBytes: 1 << 20,
		Handler:        engine,
	}

	return &Adapter{
		svr: svr,
	}, nil
}

func (a *Adapter) Start() error {
	if err := a.svr.ListenAndServe(); err != nil {
		return utils.NewFuncError(a.Start, err)
	}
	return nil
}

func (a *Adapter) Stop(stopCtx context.Context) error {
	if err := a.svr.Shutdown(stopCtx); err != nil {
		return utils.NewFuncError(a.Start, err)
	}
	return nil
}
