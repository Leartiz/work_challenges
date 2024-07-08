package database

import (
	"context"
	"wc2/internal/application/domain"
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
	Name       *string
	Surname    *string
	Patronymic *string
	Address    *string
}

// -----------------------------------------------------------------------

type User interface {
	GetUserData(ctx context.Context, p Passport) (*domain.UserData, error) // info
	GetUserDataList(ctx context.Context, ff UserDataGettingFilter) ([]*domain.UserData, error)

	CreateUser(ctx context.Context, cred Credentials) (uint64, error)
	HasUserByCredentials(ctx context.Context, cred Credentials) (bool, error)

	UpdateRefreshTokenHash(ctx context.Context, userId uint64, val string) error
	UpdateUserData(ctx context.Context, userId uint64, p UserOptionalData) error
	DeleteUser(ctx context.Context, userId uint64) error
}
