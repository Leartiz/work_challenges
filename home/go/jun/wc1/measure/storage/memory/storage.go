package memory

import (
	"context"
	"sort"
	"sync"
	"wc1/domain"
	root "wc1/measure"
)

type MeasureStorage struct {
	lastInsertedId uint64
	measures       map[uint64]*domain.Measure
	rwMutex        sync.RWMutex
}

func NewMeasureStorage() *MeasureStorage {
	return &MeasureStorage{
		lastInsertedId: 0,
		measures:       make(map[uint64]*domain.Measure),
		rwMutex:        sync.RWMutex{},
	}
}

// public
// -----------------------------------------------------------------------

func (ms *MeasureStorage) GetMeasures(ctx context.Context) ([]*domain.Measure, error) {
	ms.rwMutex.RLock()
	defer ms.rwMutex.RUnlock()

	result := make([]*domain.Measure, 0, len(ms.measures))
	for _, val := range ms.measures {
		result = append(result, val)
	}

	sort.Slice(result, func(i, j int) bool {
		return result[i].Id < result[j].Id
	})

	return result, nil
}

func (ms *MeasureStorage) GetConcreteMeasure(ctx context.Context, id uint64) (*domain.Measure, error) {
	ms.rwMutex.RLock()
	defer ms.rwMutex.RUnlock()

	if val, ok := ms.measures[id]; ok {
		return val, nil
	}

	return nil, root.ErrMeasureWithIdNotFound(id)
}

func (ms *MeasureStorage) CreateMeasure(ctx context.Context, measure *domain.Measure) (uint64, error) {
	ms.rwMutex.Lock()
	defer ms.rwMutex.Unlock()

	if measure == nil {
		return 0, root.ErrParamMeasureIsNull()
	}

	ms.lastInsertedId += 1
	measure.Id = ms.lastInsertedId
	ms.measures[ms.lastInsertedId] = measure

	return ms.lastInsertedId, nil
}

func (ms *MeasureStorage) PutConcreteMeasure(ctx context.Context, id uint64, incomplete *domain.IncompleteMeasure) error {
	ms.rwMutex.Lock()
	defer ms.rwMutex.Unlock()

	if incomplete == nil {
		return root.ErrParamIncompleteMeasureIsNull()
	}

	if val, ok := ms.measures[id]; ok {
		domain.UpdateMeasure(val, incomplete)
		ms.measures[id] = val
		return nil
	}

	return root.ErrMeasureWithIdNotFound(id)
}

func (ms *MeasureStorage) DeleteConcreteMeasure(ctx context.Context, id uint64) error {
	ms.rwMutex.Lock()
	defer ms.rwMutex.Unlock()

	// TODO: find out where the measurement is used!

	if _, ok := ms.measures[id]; ok {
		delete(ms.measures, id)
		return nil
	}

	return root.ErrMeasureWithIdNotFound(id)
}
