package measure

import (
	"context"
	"wc1/domain"
)

type Storage interface {
	GetMeasures(ctx context.Context) ([]*domain.Measure, error)
	GetConcreteMeasure(ctx context.Context, id uint64) (*domain.Measure, error)
	CreateMeasure(ctx context.Context, measure *domain.Measure) (uint64, error)
	PutConcreteMeasure(ctx context.Context, id uint64, incomplete *domain.IncompleteMeasure) error
	DeleteConcreteMeasure(ctx context.Context, id uint64) error

	//HasMeasure(ctx context.Context, id uint64) (bool, error)
}
