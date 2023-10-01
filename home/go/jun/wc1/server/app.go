package server

import (
	"log"
	"net/http"
	"time"
	"wc1/measure"
	measureHttp "wc1/measure/delivery/http"
	measureUc "wc1/measure/usecase"
	"wc1/product"
	productHttp "wc1/product/delivery/http"
	productUc "wc1/product/usecase"
	sharedStorage "wc1/shared/storage"
	sharedStorageConcrete "wc1/shared/storage/memory"

	"github.com/gin-gonic/gin"
)

type App struct {
	httpSvr *http.Server

	productUseCase product.UseCase
	measureUseCase measure.UseCase
}

func NewApp() *App {
	compositeStorage := sharedStorageConcrete.Instance()
	sharedStorage.GlobalStorage = compositeStorage

	productStorage := compositeStorage.ProductStorage()
	measureStorage := compositeStorage.MeasureStorage()

	// ***

	return &App{
		productUseCase: productUc.NewProduct(productStorage),
		measureUseCase: measureUc.NewMeasure(measureStorage),
	}
}

func (a *App) Run(port string) {
	router := gin.Default()
	router.Use(gin.Recovery(), gin.Logger())

	productHttp.RegisterHandler(router, a.productUseCase)
	measureHttp.RegisterHandler(router, a.measureUseCase)

	a.httpSvr = &http.Server{
		Addr:           ":" + port,
		Handler:        router,
		ReadTimeout:    5 * time.Second,
		WriteTimeout:   5 * time.Second,
		MaxHeaderBytes: 1 << 20,
	}

	if err := a.httpSvr.ListenAndServe(); err != nil {
		log.Fatalf("Failed to listen and serve: %+v", err)
	}
}
