package postgre

import (
	"context"
	"fmt"
	"wc1/domain"
	"wc1/measure"
	sharedStorage "wc1/shared/storage"

	"github.com/jackc/pgx/v4/pgxpool"
)

// Package pgxpool is a concurrency-safe connection pool for pgx.

type MeasureStorage struct {
	pool *pgxpool.Pool
}

func NewMeasureStorage(pool *pgxpool.Pool) *MeasureStorage {
	return &MeasureStorage{
		pool: pool,
	}
}

// public
// -----------------------------------------------------------------------

func (ms *MeasureStorage) GetMeasures(ctx context.Context) ([]*domain.Measure, error) {
	conn, err := ms.pool.Acquire(ctx)
	if err != nil {
		return nil, sharedStorage.ErrFailedToAccess()
	}
	defer conn.Release()

	// ***

	textQuery := `select "id", "name" from "measure";`
	rows, err := conn.Query(ctx, textQuery)
	if err != nil {
		return nil, sharedStorage.ErrFailedToExecuteQuery()
	}
	defer rows.Close()

	// ***

	measures := []*domain.Measure{}
	for rows.Next() {
		var measure domain.Measure
		err = rows.Scan(&measure.Id, &measure.Name)
		if err != nil {
			return nil, sharedStorage.ErrFailedToScanResult()
		}

		measures = append(measures, &measure)
	}

	return measures, nil
}

func (ms *MeasureStorage) GetConcreteMeasure(ctx context.Context, id uint64) (*domain.Measure, error) {
	conn, err := ms.pool.Acquire(ctx)
	if err != nil {
		return nil, sharedStorage.ErrFailedToAccess()
	}
	defer conn.Release()

	// ***

	textQuery := fmt.Sprintf(`select "id", "name" from "measure" where "id" = %v;`, id)
	rows, err := conn.Query(ctx, textQuery)
	if err != nil {
		return nil, sharedStorage.ErrFailedToExecuteQuery()
	}

	if !rows.Next() {
		return nil, measure.ErrMeasureWithIdNotFound(id)
	}

	// ***

	var measure domain.Measure
	err = rows.Scan(&measure.Id, &measure.Name)
	if err != nil {
		return nil, sharedStorage.ErrFailedToScanResult()
	}

	return &measure, nil
}

func (ms *MeasureStorage) CreateMeasure(ctx context.Context, measure *domain.Measure) (uint64, error) {
	conn, err := ms.pool.Acquire(ctx)
	if err != nil {
		return 0, sharedStorage.ErrFailedToAccess()
	}
	defer conn.Release()

	// ***

	// TODO: wrap in transaction.
	textQuery := fmt.Sprintf(`insert into "measure" values ('%v');`, measure.Name)
	_, err = conn.Exec(ctx, textQuery)
	if err != nil {
		return 0, sharedStorage.ErrFailedToExecuteQuery()
	}

	// ***

	textQuery = `select currval(pg_get_serial_sequence('measure','id')) as last_inserted_id;`
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

func (ms *MeasureStorage) PutConcreteMeasure(ctx context.Context, id uint64, incomplete *domain.IncompleteMeasure) error {
	conn, err := ms.pool.Acquire(ctx)
	if err != nil {
		return sharedStorage.ErrFailedToAccess()
	}
	defer conn.Release()

	// ***

	// TODO: can make a flexible update request!
	concreteMeasure, err := ms.GetConcreteMeasure(ctx, id)
	if err != nil {
		return err
	}
	domain.UpdateMeasure(
		concreteMeasure, incomplete)

	// ***

	textQuery := fmt.Sprintf(
		`update measure set "name" = '%v' where "id" = %v;`,
		concreteMeasure.Name,
		id,
	)
	_, err = conn.Exec(ctx, textQuery)
	if err != nil {
		return sharedStorage.ErrFailedToExecuteQuery()
	}

	return nil
}

func (ms *MeasureStorage) DeleteConcreteMeasure(ctx context.Context, id uint64) error {
	conn, err := ms.pool.Acquire(ctx)
	if err != nil {
		return sharedStorage.ErrFailedToAccess()
	}
	defer conn.Release()

	// ***

	// TODO: find out where the measurement is used!

	textQuery := fmt.Sprintf(`delete from measure where id = %v;`, id)
	_, err = conn.Exec(ctx, textQuery)
	if err != nil {
		return sharedStorage.ErrFailedToExecuteQuery()
	}

	return nil
}
