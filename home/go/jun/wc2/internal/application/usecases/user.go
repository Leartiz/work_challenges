package usecases

import (
	"context"
	"wc2/internal/application/domain/table"
	"wc2/internal/application/ports/in/usecases"
	"wc2/internal/application/ports/out/database"
)

type UserUsecase struct {
	db database.Database
}

func NewUserUsecase(db database.Database) (*UserUsecase, error) {
	return &UserUsecase{
		db: db,
	}, nil
}

// -----------------------------------------------------------------------

func (u *UserUsecase) GetInfo(ctx context.Context, passport usecases.Passport) (*table.UserData, error) {

}

func (u *UserUsecase) GetUserDataList(ctx context.Context, filter usecases.UserDataGettingFilter) ([]*table.UserData, error) {

}

func (u *UserUsecase) GetAccount(ctx context.Context, userId uint64) (*table.UserData, error) {

}

func (u *UserUsecase) UpdateAccount(ctx context.Context, userId uint64, input usecases.UserOptionalData) error {

}

func (u *UserUsecase) UpdateAccountPassword(ctx context.Context, userId uint64, input usecases.DataForChangePassword) error {

}

func (u *UserUsecase) DeleteAccount(ctx context.Context, userId uint64) error {

}
