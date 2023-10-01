package memory

import (
	"sync"
	"wc1/measure"
	measureStorage "wc1/measure/storage/memory"
	"wc1/product"
	productStorage "wc1/product/storage/memory"
	sharedStorage "wc1/shared/storage"
)

type Composite struct {
	Product product.Storage
	Measure measure.Storage
}

var composite *Composite = nil
var once sync.Once = sync.Once{}

func newComposite() *Composite {

	return &Composite{
		Product: productStorage.NewProductStorage(),
		Measure: measureStorage.NewMeasureStorage(),
	}
}

// -----------------------------------------------------------------------

func Instance() sharedStorage.CompositeStorage {
	once.Do(func() {
		composite = newComposite()
	})

	return composite
}

func (this *Composite) ProductStorage() product.Storage {
	return this.Product
}
func (this *Composite) MeasureStorage() measure.Storage {
	return this.Measure
}
