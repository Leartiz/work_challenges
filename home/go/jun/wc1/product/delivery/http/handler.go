package http

import (
	"math"
	"net/http"
	"strconv"
	root "wc1/product"
	"wc1/product/dto"
	shared "wc1/shared/delivery/http"

	"github.com/gin-gonic/gin"
)

type Handler struct {
	usecase root.UseCase
}

func NewHandler(uc root.UseCase) *Handler {
	return &Handler{
		usecase: uc,
	}
}

// handlers
// -----------------------------------------------------------------------

func (h *Handler) Get(ctx *gin.Context) {
	some, err := h.usecase.GetProducts(ctx)
	if err != nil {
		// TODO: possibly a different error code?
		jsonErr := shared.Error{
			Text: err.Error(),
		}
		ctx.JSON(http.StatusInternalServerError, jsonErr)
		return
	}

	ctx.JSON(http.StatusOK, some)
}

func (h *Handler) GetConcrete(ctx *gin.Context) {
	str := ctx.Param("id")
	if len(str) == 0 {
		ctx.Redirect(http.StatusFound, "/product")
		return
	}

	productId, err := strconv.ParseUint(str, 10, 64)
	if err != nil {
		ctx.AbortWithStatus(http.StatusBadRequest)
		return
	}

	// ***

	product, err := h.usecase.GetConcreteProduct(ctx, productId)
	if err != nil {
		jsonErr := shared.Error{
			Text: err.Error(),
		}
		ctx.JSON(http.StatusInternalServerError, jsonErr)
		return
	}

	ctx.JSON(http.StatusOK, product)
}

func (h *Handler) Create(ctx *gin.Context) {
	reqDto := new(dto.CreateProductReq)
	if err := ctx.BindJSON(reqDto); err != nil {
		ctx.AbortWithStatus(http.StatusBadRequest)
		return
	}

	measureId := reqDto.MeasureId
	if measureId != math.Trunc(measureId) {
		ctx.AbortWithStatus(http.StatusBadRequest)
		return
	}

	// ***

	resDto, err := h.usecase.CreateProduct(ctx, reqDto)
	if err != nil {
		jsonErr := shared.Error{
			Text: err.Error(),
		}
		ctx.JSON(http.StatusInternalServerError, jsonErr)
		return
	}

	ctx.JSON(http.StatusOK, resDto)
}

func (h *Handler) PutConcrete(ctx *gin.Context) {
	str := ctx.Param("id")
	productId, err := strconv.ParseUint(str, 10, 64)
	if err != nil {
		ctx.AbortWithStatus(http.StatusBadRequest)
		return
	}

	reqDto := new(dto.PutConcreteProductReq)
	if err := ctx.BindJSON(reqDto); err != nil {
		ctx.AbortWithStatus(http.StatusBadRequest)
		return
	}

	if reqDto.MeasureId != nil {
		measureId := *reqDto.MeasureId
		if measureId != math.Trunc(measureId) {
			ctx.AbortWithStatus(http.StatusBadRequest)
			return
		}
	}

	// ***

	err = h.usecase.PutConcreteProduct(ctx, productId, reqDto)
	if err != nil {
		jsonErr := shared.Error{
			Text: err.Error(),
		}
		ctx.JSON(http.StatusInternalServerError, jsonErr)
		return
	}

	ctx.Status(http.StatusOK)
}

func (h *Handler) Delete(ctx *gin.Context) {
	str := ctx.Param("id")
	productId, err := strconv.ParseUint(str, 10, 64)
	if err != nil {
		ctx.AbortWithStatus(http.StatusBadRequest)
		return
	}

	// ***

	err = h.usecase.DeleteConcreteProduct(ctx, productId)
	if err != nil {
		jsonErr := shared.Error{
			Text: err.Error(),
		}
		ctx.JSON(http.StatusInternalServerError, jsonErr)
		return
	}

	ctx.Status(http.StatusOK)
}
