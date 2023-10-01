package memory

import (
	"context"
	"log"
	"sort"
	"sync"
	"wc1/domain"
	root "wc1/product"
	sharedStorage "wc1/shared/storage"
)

// TODO: to shared repo.
type ProductStorage struct {
	lastInsertedId uint64
	products       map[uint64]*domain.Product
	rwMutex        sync.RWMutex
}

func NewProductStorage() *ProductStorage {
	return &ProductStorage{
		lastInsertedId: 0, // insert from 1...
		products:       make(map[uint64]*domain.Product),
		rwMutex:        sync.RWMutex{},
	}
}

// public
// -----------------------------------------------------------------------

func (ps *ProductStorage) GetProducts(ctx context.Context) ([]*domain.Product, error) {
	ps.rwMutex.RLock()
	defer ps.rwMutex.RUnlock()

	result := make([]*domain.Product, 0, len(ps.products))
	for id, val := range ps.products {

		// TODO: remove a check that the product in the card is not null?
		if val == nil {
			log.Fatalf("product with id %v in map is null", id)
		}

		result = append(result, val)
	}

	sort.Slice(result, func(i, j int) bool {
		return result[i].Id < result[j].Id
	})

	return result, nil
}

func (ps *ProductStorage) GetConcreteProduct(ctx context.Context, id uint64) (*domain.Product, error) {
	ps.rwMutex.RLock()
	defer ps.rwMutex.RUnlock()

	if val, ok := ps.products[id]; ok {
		if val == nil {
			log.Fatalf("product with id %v in map is null", id)
		}

		return val, nil
	}

	return nil, root.ErrProductWithIdNotFound(id)
}

func (ps *ProductStorage) CreateProduct(ctx context.Context, product *domain.Product) (uint64, error) {
	ps.rwMutex.Lock()
	defer ps.rwMutex.Unlock()

	if product == nil {
		return 0, root.ErrParamProductIsNull()
	}

	// TODO: create a special method to check.
	measureStorage := sharedStorage.Global.MeasureStorage()
	_, err := measureStorage.GetConcreteMeasure(ctx, product.MeasureId)
	if err != nil {
		return 0, err
	}

	ps.lastInsertedId += 1
	product.Id = ps.lastInsertedId
	ps.products[ps.lastInsertedId] = product

	return ps.lastInsertedId, nil
}

func (ps *ProductStorage) PutConcreteProduct(ctx context.Context, id uint64, incomplete *domain.IncompleteProduct) error {
	ps.rwMutex.Lock()
	defer ps.rwMutex.Unlock()

	if incomplete == nil {
		return root.ErrParamIncompleteProductIsNull()
	}

	if incomplete.MeasureId != nil {
		measureStorage := sharedStorage.Global.MeasureStorage()
		_, err := measureStorage.GetConcreteMeasure(ctx, *incomplete.MeasureId)
		if err != nil {
			return err
		}
	}

	if val, ok := ps.products[id]; ok {
		if val == nil {
			log.Fatalf("product with id %v in map is null", id)
		}

		domain.UpdateProduct(val, incomplete)
		ps.products[id] = val
		return nil
	}

	return root.ErrProductWithIdNotFound(id)
}

func (ps *ProductStorage) DeleteConcreteProduct(ctx context.Context, id uint64) error {
	ps.rwMutex.Lock()
	defer ps.rwMutex.Unlock()

	if _, ok := ps.products[id]; ok {
		delete(ps.products, id)
		return nil
	}

	return root.ErrProductWithIdNotFound(id)
}
