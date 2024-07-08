package database

import (
	"context"
	"time"
)

type Task interface {
	GetTasks(ctx context.Context, userId uint64, startTime, stopTime time.Time)
	CreateTask(ctx context.Context, userId uint64, name string) (uint64, error)
	StartTask(ctx context.Context, taskId uint64) error
	StopTask(ctx context.Context, taskId uint64) error
}
