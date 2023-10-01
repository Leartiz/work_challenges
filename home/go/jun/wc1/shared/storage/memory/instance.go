package memory

import (
	"sync"
	measureStorageMemory "wc1/measure/storage/memory"
	productStorageMemory "wc1/product/storage/memory"
	sharedStorage "wc1/shared/storage"
)

var once sync.Once = sync.Once{}
var composite *sharedStorage.Whole = nil

func newComposite() *sharedStorage.Whole {
	return &sharedStorage.Whole{
		Product: productStorageMemory.NewProductStorage(),
		Measure: measureStorageMemory.NewMeasureStorage(),
	}
}

// -----------------------------------------------------------------------

func Instance() sharedStorage.Composite {
	once.Do(func() {
		composite = newComposite()
	})

	return composite
}
