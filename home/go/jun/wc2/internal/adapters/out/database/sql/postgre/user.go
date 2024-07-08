package postgre

import (
	"context"
	"wc2/internal/application/domain"
	"wc2/internal/application/ports/out/database"
	"wc2/pkg/utils"

	"github.com/jackc/pgx/v4/pgxpool"
)

type User struct {
	pool *pgxpool.Pool
}

func newUser(pool *pgxpool.Pool) *User {
	return &User{
		pool: pool,
	}
}

// templates
// -----------------------------------------------------------------------

var (
	templateCreateUser = utils.RemoveAdjacentWs(`
		
	`)
)

// public
// -----------------------------------------------------------------------

func (u *User) GetUserPersonal(ctx context.Context, p database.Passport) (*domain.UserData, error) {

}

func (u *User) CreateUser(ctx context.Context, cred database.Credentials) (uint64, error) {

}

func (u *User) HasUserByCredentials(ctx context.Context, cred database.Credentials) (bool, error) {

}

func (u *User) UpdateRefreshTokenHash(ctx context.Context, userId uint64, val string) error {

}

func (u *User) UpdateUserPersonal(ctx context.Context, userId uint64, p database.UserOptionalData) error {

}

func (u *User) DeleteUser(ctx context.Context, userId uint64) error {

}
