package domain

type Measure struct {
	Id   uint64
	Name string
}

type IncompleteMeasure struct {
	Id   *uint64
	Name *string
}

// extra
// -----------------------------------------------------------------------

func UpdateMeasure(current *Measure, incomplete *IncompleteMeasure) {
	if incomplete.Name != nil {
		current.Name = *incomplete.Name
	}
}
