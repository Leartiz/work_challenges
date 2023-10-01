package domain

type Measure struct {
	Id   uint64
	Name string
}

type IncompleteMeasure struct {
	Id   *uint64
	Name *string
}
