package storage

import (
	"wc1/measure"
	"wc1/product"
)

type Composite interface {
	ProductStorage() product.Storage
	MeasureStorage() measure.Storage
}

// -----------------------------------------------------------------------

type Whole struct {
	Product product.Storage
	Measure measure.Storage
}

func (this *Whole) ProductStorage() product.Storage {
	return this.Product
}
func (this *Whole) MeasureStorage() measure.Storage {
	return this.Measure
}

var Global Composite
