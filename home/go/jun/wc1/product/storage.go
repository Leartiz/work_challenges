package product

import (
	"context"
	"wc1/domain"
)

type Storage interface {
	GetProducts(ctx context.Context) ([]*domain.Product, error)
	GetConcreteProduct(ctx context.Context, id uint64) (*domain.Product, error)
	CreateProduct(ctx context.Context, product *domain.Product) (uint64, error)
	PutConcreteProduct(ctx context.Context, id uint64, incomplete *domain.IncompleteProduct) error
	DeleteConcreteProduct(ctx context.Context, id uint64) error
}
