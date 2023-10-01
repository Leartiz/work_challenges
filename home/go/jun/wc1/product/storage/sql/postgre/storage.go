package postgre

import (
	"context"
	"wc1/domain"

	"github.com/jackc/pgx/v4/pgxpool"
)

type ProductStorage struct {
	pool *pgxpool.Pool
}

func NewProductStorage(pool *pgxpool.Pool) *ProductStorage {
	return &ProductStorage{
		pool: pool,
	}
}

// public
// -----------------------------------------------------------------------

func (ps *ProductStorage) GetProducts(ctx context.Context) ([]*domain.Product, error) {
	return nil, nil
}

func (ps *ProductStorage) GetConcreteProduct(ctx context.Context, id uint64) (*domain.Product, error) {
	return nil, nil
}

func (ps *ProductStorage) CreateProduct(ctx context.Context, product *domain.Product) (uint64, error) {
	return 0, nil
}

func (ps *ProductStorage) PutConcreteProduct(ctx context.Context, id uint64, incomplete *domain.IncompleteProduct) error {
	return nil
}

func (ps *ProductStorage) DeleteConcreteProduct(ctx context.Context, id uint64) error {
	return nil
}
