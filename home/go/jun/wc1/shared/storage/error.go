package storage

import "fmt"

func ErrFailedToAccess() error {
	return fmt.Errorf("failed to access storage")
}

func ErrFailedToExecuteQuery() error {
	return fmt.Errorf("failed to execute storage query")
}

func ErrFailedToScanResult() error {
	return fmt.Errorf("failed to scan storage result")
}

func ErrFailedToSelectLastInsertedId() error {
	return fmt.Errorf("failed to select last inserted id")
}
