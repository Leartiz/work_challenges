package product

import "fmt"

func ErrProductWithIdNotFound(id uint64) error {
	return fmt.Errorf("product with id %v not found", id)
}

func ErrParamProductIsNull() error {
	return fmt.Errorf("param product is null")
}

func ErrParamIncompleteProductIsNull() error {
	return fmt.Errorf("param incomplete product is null")
}

func ErrProductNameIsSmall() error {
	return fmt.Errorf("product name is small")
}

func ErrProductQuantityIsNegative() error {
	return fmt.Errorf("product quantity is negative")
}

func ErrProductUnitCoastIsNegative() error {
	return fmt.Errorf("product unit coast is negative")
}
