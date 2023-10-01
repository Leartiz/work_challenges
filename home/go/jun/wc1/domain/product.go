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

// extra
// -----------------------------------------------------------------------

func UpdateProduct(current *Product, incomplete *IncompleteProduct) {
	if incomplete.Name != nil {
		current.Name = *incomplete.Name
	}
	if incomplete.Quantity != nil {
		current.Quantity = *incomplete.Quantity
	}
	if incomplete.UnitCoast != nil {
		current.UnitCoast = *incomplete.UnitCoast
	}
	if incomplete.MeasureId != nil {
		current.MeasureId = *incomplete.MeasureId
	}
}
