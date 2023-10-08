package postgre

import (
	"context"
	"fmt"
	"wc1/domain"
	"wc1/measure"
	"wc1/product"

	sharedStorage "wc1/shared/storage"

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
	conn, err := ps.pool.Acquire(ctx)
	if err != nil {
		return nil, sharedStorage.ErrFailedToAccess()
	}
	defer conn.Release()

	// ***

	textQuery := `select * from "product";`
	rows, err := conn.Query(ctx, textQuery)
	if err != nil {
		return nil, sharedStorage.ErrFailedToExecuteQuery()
	}
	defer rows.Close()

	// ***

	products := []*domain.Product{}
	for rows.Next() {
		var element domain.Product
		err = rows.Scan(
			&element.Id, &element.Name,
			&element.Quantity, &element.UnitCoast,
			&element.MeasureId,
		)

		if err != nil {
			return nil, sharedStorage.ErrFailedToScanResult()
		}

		products = append(products, &element)
	}
	return products, nil
}

func (ps *ProductStorage) GetConcreteProduct(ctx context.Context, id uint64) (*domain.Product, error) {
	conn, err := ps.pool.Acquire(ctx)
	if err != nil {
		return nil, sharedStorage.ErrFailedToAccess()
	}
	defer conn.Release()

	// ***

	textQuery := fmt.Sprintf(`select * from "product" where "id" = %v;`, id)
	rows, err := conn.Query(ctx, textQuery)
	if err != nil {
		return nil, sharedStorage.ErrFailedToExecuteQuery()
	}

	if !rows.Next() {
		return nil, measure.ErrMeasureWithIdNotFound(id)
	}

	// ***

	var element domain.Product
	err = rows.Scan(
		&element.Id, &element.Name,
		&element.Quantity, &element.UnitCoast,
		&element.MeasureId,
	)
	if err != nil {
		return nil, sharedStorage.ErrFailedToScanResult()
	}

	return &element, nil
}

// TODO: add check product is nil.
func (ps *ProductStorage) CreateProduct(ctx context.Context, product *domain.Product) (uint64, error) {
	conn, err := ps.pool.Acquire(ctx)
	if err != nil {
		return 0, sharedStorage.ErrFailedToAccess()
	}
	defer conn.Release()

	// ***

	measureStorage := sharedStorage.Global.MeasureStorage()
	_, err = measureStorage.GetConcreteMeasure(ctx, product.MeasureId)
	if err != nil {
		return 0, err
	}

	// ***

	textQuery := fmt.Sprintf(
		`INSERT INTO product ("name", quantity, unit_coast, measure_id) 
		VALUES ('%v', %v, %v, %v);`,
		product.Name, product.Quantity, product.UnitCoast,
		product.MeasureId,
	)
	_, err = conn.Exec(ctx, textQuery)
	if err != nil {
		return 0, sharedStorage.ErrFailedToExecuteQuery()
	}

	// ***

	textQuery = `select currval(pg_get_serial_sequence('product','id')) as last_inserted_id;`
	rows, err := conn.Query(ctx, textQuery)
	if err != nil {
		return 0, sharedStorage.ErrFailedToExecuteQuery()
	}
	defer rows.Close()

	// ***

	if !rows.Next() {
		return 0, sharedStorage.ErrFailedToSelectLastInsertedId()
	}

	var lastInsertedId uint64
	rows.Scan(&lastInsertedId)
	return lastInsertedId, nil
}

func (ps *ProductStorage) PutConcreteProduct(ctx context.Context, id uint64, incomplete *domain.IncompleteProduct) error {
	conn, err := ps.pool.Acquire(ctx)
	if err != nil {
		return sharedStorage.ErrFailedToAccess()
	}
	defer conn.Release()

	// ***

	if incomplete == nil {
		return product.ErrParamIncompleteProductIsNull()
	}

	// ***

	if incomplete.MeasureId != nil {
		measureStorage := sharedStorage.Global.MeasureStorage()
		_, err := measureStorage.GetConcreteMeasure(ctx, *incomplete.MeasureId)
		if err != nil {
			return err
		}
	}

	// ***

	concreteProduct, err := ps.GetConcreteProduct(ctx, id)
	if err != nil {
		return err
	}
	domain.UpdateProduct(concreteProduct, incomplete)

	// ***

	textQuery := fmt.Sprintf(
		`update product set "name"='%v', quantity=%v, unit_coast=%v, measure_id=%v
		where "id" = %v;`,
		concreteProduct.Name,
		concreteProduct.Quantity,
		concreteProduct.UnitCoast,
		concreteProduct.MeasureId,
		id,
	)
	_, err = conn.Exec(ctx, textQuery)
	if err != nil {
		return sharedStorage.ErrFailedToExecuteQuery()
	}

	return nil
}

func (ps *ProductStorage) DeleteConcreteProduct(ctx context.Context, id uint64) error {
	conn, err := ps.pool.Acquire(ctx)
	if err != nil {
		return sharedStorage.ErrFailedToAccess()
	}
	defer conn.Release()

	// ***

	textQuery := fmt.Sprintf(`delete from product where id = %v;`, id)
	_, err = conn.Exec(ctx, textQuery)
	if err != nil {
		return sharedStorage.ErrFailedToExecuteQuery()
	}

	return nil
}

func (self *ProductStorage) HasProductWhichUseMeasure(ctx context.Context, measureId uint64) (bool, error) {
	conn, err := self.pool.Acquire(ctx)
	if err != nil {
		return false, sharedStorage.ErrFailedToAccess()
	}
	defer conn.Release()

	// ***

	textQuery := fmt.Sprintf(
		`select * from "product" where measure_id = %v;`,
		measureId,
	)
	rows, err := conn.Query(ctx, textQuery)
	if err != nil {
		return false, sharedStorage.ErrFailedToExecuteQuery()
	}
	defer rows.Close()

	// ***

	return rows.Next(), nil
}
