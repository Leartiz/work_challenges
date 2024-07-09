package internal

import (
	"github.com/jackc/pgx/v4"
)

type ScannableResult interface {
	Scan(dest ...interface{}) error
}

func SerializableTxOptions() pgx.TxOptions {
	return pgx.TxOptions{
		IsoLevel:       pgx.Serializable,
		AccessMode:     pgx.ReadWrite,
		DeferrableMode: pgx.NotDeferrable,
	}
}
