package product

import (
	"context"
	"wc1/product/dto"
)

type UseCase interface {
	GetProducts(ctx context.Context) ([]*dto.Product, error)
	GetConcreteProduct(ctx context.Context, id uint64) (*dto.Product, error)
	CreateProduct(ctx context.Context, reqDto *dto.CreateProductReq) (*dto.CreateProductRes, error)
	PutConcreteProduct(ctx context.Context, id uint64, reqDto *dto.PutConcreteProductReq) error
	DeleteConcreteProduct(ctx context.Context, id uint64) error
}
