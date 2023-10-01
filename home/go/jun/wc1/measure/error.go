package measure

import "fmt"

func ErrMeasureWithIdNotFound(id uint64) error {
	return fmt.Errorf("measure with id %v not found", id)
}

func ErrParamMeasureIsNull() error {
	return fmt.Errorf("param measure is null")
}

func ErrParamIncompleteMeasureIsNull() error {
	return fmt.Errorf("param incomplete measure is null")
}

func ErrMeasureNameIsEmpty() error {
	return fmt.Errorf("measure name is empty")
}
