package usecases

import (
	"context"
)

type Tokens struct {
	Access  string
	Refresh string
}

type AuthUsecase interface {
	SignUp(ctx context.Context, passportNumber string) (Tokens, error)
	SignIn(ctx context.Context, passportNumber, passwordHash string) (Tokens, error)
	RefreshTokens(ctx context.Context, userId uint64, refreshToken string) (Tokens, error)
}
