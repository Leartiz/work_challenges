package usecases

import (
	"context"
	"wc2/internal/application/domain/table"
	"wc2/internal/application/ports/out/database"
)

type Passport = database.Passport
type UserDataGettingFilter = database.UserDataGettingFilter
type UserOptionalData = database.UserOptionalData

type DataForChangePassword struct {
	CurrentPasswordHash string
	NewPasswordHash     string
}

// -----------------------------------------------------------------------

type UserUsecase interface {
	GetInfo(ctx context.Context, passport Passport) (*table.UserData, error)
	GetUserDataList(ctx context.Context, filter UserDataGettingFilter) ([]*table.UserData, error)

	// only with token...

	GetAccount(ctx context.Context, userId uint64) (*table.UserData, error)
	UpdateAccount(ctx context.Context, userId uint64, input UserOptionalData) error
	UpdateAccountPassword(ctx context.Context, userId uint64, input DataForChangePassword) error
	DeleteAccount(ctx context.Context, userId uint64) error
}
