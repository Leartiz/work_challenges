package dto

import (
	"log"
	"wc1/domain"
)

// dto`s
// -----------------------------------------------------------------------

/*

The default concrete Go types are:
- bool for JSON booleans;
- float64 for JSON numbers;
- string for JSON strings;
- nil for JSON null.

*/

type Product struct {
	Id        float64 `json:"id"` // ---> uint64
	Name      string  `json:"name"`
	Quantity  float64 `json:"quantity"`
	UnitCoast float64 `json:"unit_coast"`
	MeasureId float64 `json:"measure_id"` // ---> uint64
}

// TODO: how to avoid conversion?
// TODO: can remove these structures... see domain.
type CreateProductReq struct {
	Name      string  `json:"name"`
	Quantity  float64 `json:"quantity"`
	UnitCoast float64 `json:"unit_coast"`
	MeasureId float64 `json:"measure_id"` // ---> uint64
}

type CreateProductRes struct {
	Id float64 `json:"id"` // ---> uint64 // TODO
}

type PutConcreteProductReq struct {
	Name      *string  `json:"name,omitempty"`
	Quantity  *float64 `json:"quantity,omitempty"`
	UnitCoast *float64 `json:"unit_coast,omitempty"`
	MeasureId *float64 `json:"measure_id,omitempty"` // ---> uint64
}

// converter
// -----------------------------------------------------------------------

func ProductDomainToDto(product *domain.Product) *Product {
	// TODO: remove check?
	if product == nil {
		log.Fatalf("domain product nil")
	}

	return &Product{
		Id:        float64(product.Id),
		Name:      product.Name,
		Quantity:  product.Quantity,
		UnitCoast: product.UnitCoast,
		MeasureId: float64(product.MeasureId),
	}
}

func ProductsDomainToDto(some []*domain.Product) []*Product {
	results := []*Product{}
	for _, val := range some {
		results = append(
			results, ProductDomainToDto(val))
	}
	return results
}
