package usecases

import (
	"context"
)

type TaskUsecase interface {
	GetInfo(ctx context.Context)
	GetUsers(ctx context.Context)
}
