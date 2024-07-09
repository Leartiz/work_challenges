package internal

import (
	"errors"
)

var (
	ErrInsertFailed = errors.New("insert failed")
	ErrUpdateFailed = errors.New("update failed")
	ErrDeleteFailed = errors.New("delete failed")
)
