package postgre

import (
	"context"
	"wc2/internal/adapters/out/database/sql/postgre/internal"
	"wc2/pkg/postgreUtils"
	"wc2/pkg/utils"

	"github.com/jackc/pgx/v4/pgxpool"
)

type Postgre struct {
	*internal.UserDatabase
	pool *pgxpool.Pool
}

func New(startCtx context.Context,
	params postgreUtils.ConnectionParamsWithDb) (*Postgre, error) {

	pool, err := pgxpool.Connect(startCtx, params.CreateConnectionString())
	if err != nil {
		return nil, utils.NewFuncError(New, err)
	}

	return &Postgre{
		UserDatabase: internal.NewUserDatabase(pool),
	}, nil
}

func (p *Postgre) Stop() error {
	p.pool.Close()
	return nil
}
