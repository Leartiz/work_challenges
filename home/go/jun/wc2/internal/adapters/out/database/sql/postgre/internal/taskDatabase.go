package internal

import (
	"context"
	"time"

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

func (t *TaskDatabase) GetTasks(ctx context.Context, userId uint64, startTime, stopTime time.Time) {

}

func (t *TaskDatabase) CreateTask(ctx context.Context, userId uint64, name string) (uint64, error) {

}

func (t *TaskDatabase) StartTask(ctx context.Context, taskId uint64) error {

}

func (t *TaskDatabase) StopTask(ctx context.Context, taskId uint64) error {

}
