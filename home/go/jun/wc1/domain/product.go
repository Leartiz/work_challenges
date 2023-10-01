package domain

type Product struct {
	Id        uint64
	Name      string
	Quantity  float64
	UnitCoast float64 // TODO: accuracy problems?
	MeasureId uint64
}

type IncompleteProduct struct {
	Id        *uint64
	Name      *string
	Quantity  *float64
	UnitCoast *float64
	MeasureId *uint64
}
