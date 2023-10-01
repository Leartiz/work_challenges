package dto

import (
	"log"
	"wc1/domain"
)

// dto`s
// -----------------------------------------------------------------------

type Measure struct {
	Id   float64 `json:"id"` // ---> uint64
	Name string  `json:"name"`
}

type CreateMeasureReq struct {
	Name string `json:"name"`
}

type CreateMeasureRes struct {
	Id float64 `json:"id"` // ---> uint64
}

type PutMeasureReq struct {
	Name *string `json:"name"`
}

// converter
// -----------------------------------------------------------------------

func MeasureDomainToDto(measure *domain.Measure) *Measure {
	if measure == nil {
		log.Fatalf("domain measure nil")
	}

	return &Measure{
		Id:   float64(measure.Id),
		Name: measure.Name,
	}
}

func MeasuresDomainToDto(some []*domain.Measure) []*Measure {
	results := []*Measure{}
	for _, val := range some {
		results = append(results, MeasureDomainToDto(val))
	}
	return results
}
