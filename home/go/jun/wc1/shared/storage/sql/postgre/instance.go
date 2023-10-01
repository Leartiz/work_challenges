package postgre

import (
	"context"
	"fmt"
	"log"
	"sync"
	measureStoragePostgre "wc1/measure/storage/sql/postgre"
	productStoragePostgre "wc1/product/storage/sql/postgre"
	sharedStorage "wc1/shared/storage"

	"github.com/jackc/pgx/v4/pgxpool"
	"github.com/spf13/viper"
)

var initialized = false
var once sync.Once = sync.Once{}

var composite *sharedStorage.Whole = nil
var bigPool *pgxpool.Pool = nil

func newComposite() *sharedStorage.Whole {

	// TODO: update context.
	bigPool, err := pgxpool.Connect(
		context.Background(),
		connectionString(),
	)

	if err != nil {
		log.Fatalf("Unable to connection to database: %v\n", err)
	}

	return &sharedStorage.Whole{
		Product: productStoragePostgre.NewProductStorage(bigPool),
		Measure: measureStoragePostgre.NewMeasureStorage(bigPool),
	}
}

func connectionString() string {
	return fmt.Sprintf(
		"user=%v password=%v dbname=%v sslmode=%v",
		viper.GetString("storage.postgre.user"),
		viper.GetString("storage.postgre.pass"),
		viper.GetString("storage.postgre.dbname"),
		viper.GetString("storage.postgre.sslmode"),
	)
}

// -----------------------------------------------------------------------

func Instance() sharedStorage.Composite {
	once.Do(func() {
		composite = newComposite()
		initialized = true
	})

	return composite
}

func Clear() {
	if initialized {
		bigPool.Close()
	}
}
