package measure

import (
	"context"
	"wc1/measure/dto"
)

type UseCase interface {
	GetMeasures(ctx context.Context) ([]*dto.Measure, error)
	GetConcreteMeasure(ctx context.Context, id uint64) (*dto.Measure, error)
	CreateMeasure(ctx context.Context, reqDto *dto.CreateMeasureReq) (*dto.CreateMeasureRes, error)
	PutConcreteMeasure(ctx context.Context, id uint64, reqDto *dto.PutMeasureReq) error
	DeleteConcreteMeasure(ctx context.Context, id uint64) error
}
