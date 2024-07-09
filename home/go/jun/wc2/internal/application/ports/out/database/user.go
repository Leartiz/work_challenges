package database

import (
	"context"
	"wc2/internal/application/domain/table"
)

// -----------------------------------------------------------------------

type UserDataGettingFilter struct {
	PassportSeries *uint32
	PassportNumber *uint32
	UserOptionalData
	Limit  *uint64
	Offset *uint64
}

type Passport struct {
	PassportSeries uint32
	PassportNumber uint32
}

type Credentials struct {
	Passport
	PasswordHash string
}

type UserOptionalData struct {
	Name       *string `db:"name" goqu:"omitnil"`
	Surname    *string `db:"surname" goqu:"omitnil"`
	Patronymic *string `db:"patronymic" goqu:"omitnil"`
	Address    *string `db:"address" goqu:"omitnil"`
}

// -----------------------------------------------------------------------

type User interface {
	GetUserData(ctx context.Context, p Passport) (*table.UserData, error)
	GetUserDataList(ctx context.Context, filter UserDataGettingFilter) ([]*table.UserData, error)

	CreateUser(ctx context.Context, cred Credentials) (uint64, error)
	HasUserByCredentials(ctx context.Context, cred Credentials) (bool, error)

	UpdateRefreshTokenHash(ctx context.Context, userId uint64, val string) error
	UpdatePasswordHash(ctx context.Context, userId uint64, passwordHash string) error
	UpdateUserData(ctx context.Context, userId uint64, p UserOptionalData) error

	DeleteUser(ctx context.Context, userId uint64) error
}
