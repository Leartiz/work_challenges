package postgre

import (
	"context"
	"fmt"
	"wc2/pkg/utils"

	"github.com/jackc/pgx/v4/pgxpool"
)

type ConnectionParamsWithDb struct {
	Username     string
	Password     string
	Host         string
	Port         uint16
	DatabaseName string
}

func (params *ConnectionParamsWithDb) CreateConnectionString() string {
	return fmt.Sprintf(
		"user=%v password=%v "+
			"host=%v port=%v database=%v",
		params.Username, params.Password,
		params.Host, params.Port,
		params.DatabaseName,
	)
}

// -----------------------------------------------------------------------

type Postgre struct {
	*UserDatabase
	pool *pgxpool.Pool
}

func New(startCtx context.Context, params ConnectionParamsWithDb) (*Postgre, error) {
	pool, err := pgxpool.Connect(startCtx, params.CreateConnectionString())
	if err != nil {
		return nil, utils.NewFuncError(New, err)
	}

	return &Postgre{
		UserDatabase: newUser(pool),
	}, nil
}

func (p *Postgre) Stop() error {
	p.pool.Close()
	return nil
}
