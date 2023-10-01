package storage

import (
	"wc1/measure"
	"wc1/product"
)

type CompositeStorage interface {
	ProductStorage() product.Storage
	MeasureStorage() measure.Storage
}

var GlobalStorage CompositeStorage
