package internal

import (
	"context"
	"time"
	"wc2/internal/application/domain/table"

	"github.com/jackc/pgx/v4/pgxpool"
)

type TaskDatabase struct {
	pool *pgxpool.Pool
}

func NewTaskDatabase(pool *pgxpool.Pool) *TaskDatabase {
	return &TaskDatabase{
		pool: pool,
	}
}

// public
// -----------------------------------------------------------------------

func (t *TaskDatabase) GetTasks(ctx context.Context, userId uint64, startTime, stopTime time.Time) ([]*table.Task, error) {
	return nil, nil
}

func (t *TaskDatabase) CreateTask(ctx context.Context, userId uint64, name string) (uint64, error) {
	return 0, nil
}

func (t *TaskDatabase) StartTask(ctx context.Context, taskId uint64) error {
	return nil
}

func (t *TaskDatabase) StopTask(ctx context.Context, taskId uint64) error {
	return nil
}
