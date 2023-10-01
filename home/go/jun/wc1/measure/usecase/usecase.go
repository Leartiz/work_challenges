package usecase

import (
	"context"
	"wc1/domain"
	"wc1/measure"
	"wc1/measure/dto"
)

type Measure struct {
	storage measure.Storage
}

func NewMeasure(storage measure.Storage) *Measure {
	return &Measure{
		storage: storage,
	}
}

// -----------------------------------------------------------------------

func (m *Measure) GetMeasures(ctx context.Context) ([]*dto.Measure, error) {
	some, err := m.storage.GetMeasures(ctx)
	if err != nil {
		return nil, err
	}

	return dto.MeasuresDomainToDto(some), nil
}

func (m *Measure) GetConcreteMeasure(ctx context.Context, id uint64) (*dto.Measure, error) {
	concrete, err := m.storage.GetConcreteMeasure(ctx, id)
	if err != nil {
		return nil, err
	}

	return dto.MeasureDomainToDto(concrete), nil
}

func (m *Measure) CreateMeasure(ctx context.Context, dtoReq *dto.CreateMeasureReq) (*dto.CreateMeasureRes, error) {
	if len(dtoReq.Name) == 0 {
		return nil, measure.ErrMeasureNameIsEmpty()
	}

	// ***

	in := &domain.Measure{
		Name: dtoReq.Name,
	}

	measureId, err := m.storage.CreateMeasure(ctx, in)
	if err != nil {
		return nil, err
	}

	out := &dto.CreateMeasureRes{
		Id: float64(measureId),
	}

	return out, nil
}

func (m *Measure) PutConcreteMeasure(ctx context.Context, id uint64, dtoReq *dto.PutMeasureReq) error {
	if len(*dtoReq.Name) == 0 {
		return measure.ErrMeasureNameIsEmpty()
	}

	// ***

	in := &domain.IncompleteMeasure{
		Name: dtoReq.Name,
	}

	return m.storage.PutConcreteMeasure(ctx, id, in)
}

func (m *Measure) DeleteConcreteMeasure(ctx context.Context, id uint64) error {
	return m.storage.DeleteConcreteMeasure(ctx, id)
}
