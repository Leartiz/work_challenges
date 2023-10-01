package usecase

import (
	"context"
	"wc1/domain"
	"wc1/product"
	"wc1/product/dto"
)

type Product struct {
	storage product.Storage
}

func NewProduct(storage product.Storage) *Product {
	return &Product{
		storage: storage,
	}
}

// -----------------------------------------------------------------------

func (p *Product) GetProducts(ctx context.Context) ([]*dto.Product, error) {
	some, err := p.storage.GetProducts(ctx)
	if err != nil {
		return nil, err
	}

	return dto.ProductsDomainToDto(some), nil
}

func (p *Product) GetConcreteProduct(ctx context.Context, id uint64) (*dto.Product, error) {
	concrete, err := p.storage.GetConcreteProduct(ctx, id)
	if err != nil {
		return nil, err
	}

	return dto.ProductDomainToDto(concrete), nil
}

func (p *Product) CreateProduct(ctx context.Context, reqDto *dto.CreateProductReq) (*dto.CreateProductRes, error) {
	if len(reqDto.Name) < 2 {
		return nil, product.ErrProductNameIsSmall()
	}
	if reqDto.Quantity < 0 {
		return nil, product.ErrProductQuantityIsNegative()
	}
	if reqDto.UnitCoast < 0 {
		return nil, product.ErrProductUnitCoastIsNegative()
	}

	// ***

	// id will be ignored.
	in := &domain.Product{
		Name:      reqDto.Name,
		Quantity:  reqDto.Quantity,
		UnitCoast: reqDto.UnitCoast,
		MeasureId: uint64(reqDto.MeasureId),
	}

	productId, err := p.storage.CreateProduct(ctx, in)
	if err != nil {
		return nil, err
	}

	out := &dto.CreateProductRes{
		Id: float64(productId),
	}

	return out, nil
}

func (p *Product) PutConcreteProduct(ctx context.Context, id uint64, reqDto *dto.PutConcreteProductReq) error {
	if reqDto.Name != nil && len(*reqDto.Name) < 2 {
		return product.ErrProductNameIsSmall()
	}
	if reqDto.Quantity != nil && *reqDto.Quantity < 0 {
		return product.ErrProductQuantityIsNegative()
	}
	if reqDto.UnitCoast != nil && *reqDto.UnitCoast < 0 {
		return product.ErrProductUnitCoastIsNegative()
	}

	// ***

	in := &domain.IncompleteProduct{
		Name:      reqDto.Name,
		Quantity:  reqDto.Quantity,
		UnitCoast: reqDto.UnitCoast,
	}

	if reqDto.MeasureId != nil {
		in.MeasureId = new(uint64)
		*in.MeasureId = uint64(*reqDto.MeasureId)
	}

	return p.storage.PutConcreteProduct(ctx, id, in)
}

func (p *Product) DeleteConcreteProduct(ctx context.Context, id uint64) error {
	return p.storage.DeleteConcreteProduct(ctx, id)
}
