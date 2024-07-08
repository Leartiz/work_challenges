package postgre

import (
	"context"
	"wc2/internal/application/domain/table"
	"wc2/internal/application/ports/out/database"
	"wc2/pkg/utils"

	"github.com/jackc/pgx/v4/pgxpool"
)

type UserDatabase struct {
	pool *pgxpool.Pool
}

func newUser(pool *pgxpool.Pool) *UserDatabase {
	return &UserDatabase{
		pool: pool,
	}
}

// templates
// -----------------------------------------------------------------------

var (
	templateCreateUser = utils.RemoveAdjacentWs(`
		INSERT INTO user_entry 
			(passport_series, passport_number, password_hash)
		VALUES ($1, $2, $3)`)
)

// public
// -----------------------------------------------------------------------

func (u *UserDatabase) CreateUser(ctx context.Context, cred database.Credentials) (uint64, error) {

}

func (u *UserDatabase) GetUserData(ctx context.Context, p database.Passport) (*table.UserData, error) {

}

func (u *UserDatabase) GetUserDataList(ctx context.Context, filter database.UserDataGettingFilter) ([]*table.UserData, error) {

}

func (u *UserDatabase) HasUserByCredentials(ctx context.Context, cred database.Credentials) (bool, error) {

}

func (u *UserDatabase) UpdateRefreshTokenHash(ctx context.Context, userId uint64, val string) error {

}
func (u *UserDatabase) UpdatePasswordHash(ctx context.Context, userId uint64, passwordHash string) error {

}
func (u *UserDatabase) UpdateUserData(ctx context.Context, userId uint64, p database.UserOptionalData) error {

}

func (u *UserDatabase) DeleteUser(ctx context.Context, userId uint64) error {

}
