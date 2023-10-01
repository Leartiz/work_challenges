package http

import (
	"net/http"
	"strconv"
	root "wc1/measure"
	measureDto "wc1/measure/dto"
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
	some, err := h.usecase.GetMeasures(ctx)
	if err != nil {
		jsonErr := shared.Error{
			Text: err.Error(),
		}
		ctx.JSON(http.StatusInternalServerError, jsonErr)
		return
	}

	ctx.JSON(http.StatusOK, some)
	ctx.Status(http.StatusOK)
}

func (h *Handler) GetConcrete(ctx *gin.Context) {
	str := ctx.Param("id")
	if len(str) == 0 {
		ctx.Redirect(http.StatusFound, "/measure")
		return
	}

	measureId, err := strconv.ParseUint(str, 10, 64)
	if err != nil {
		ctx.AbortWithStatus(http.StatusBadRequest)
		return
	}

	// ***

	measure, err := h.usecase.GetConcreteMeasure(ctx, measureId)
	if err != nil {
		jsonErr := shared.Error{
			Text: err.Error(),
		}
		ctx.JSON(http.StatusInternalServerError, jsonErr)
		return
	}

	ctx.JSON(http.StatusOK, measure)
	ctx.Status(http.StatusOK)
}

func (h *Handler) Create(ctx *gin.Context) {
	reqDto := new(measureDto.CreateMeasureReq)
	if err := ctx.BindJSON(reqDto); err != nil {
		ctx.AbortWithStatus(http.StatusBadRequest)
		return
	}

	// ***

	resDto, err := h.usecase.CreateMeasure(ctx, reqDto)
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
	measureId, err := strconv.ParseUint(str, 10, 64)
	if err != nil {
		ctx.AbortWithStatus(http.StatusBadRequest)
		return
	}

	reqDto := new(measureDto.PutMeasureReq)
	if err := ctx.BindJSON(reqDto); err != nil {
		ctx.AbortWithStatus(http.StatusBadRequest)
		return
	}

	// ***

	err = h.usecase.PutConcreteMeasure(ctx, measureId, reqDto)
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
	measureId, err := strconv.ParseUint(str, 10, 64)
	if err != nil {
		ctx.AbortWithStatus(http.StatusBadRequest)
		return
	}

	// ***

	err = h.usecase.DeleteConcreteMeasure(ctx, measureId)
	if err != nil {
		jsonErr := shared.Error{
			Text: err.Error(),
		}
		ctx.JSON(http.StatusInternalServerError, jsonErr)
		return
	}

	ctx.Status(http.StatusOK)
}
