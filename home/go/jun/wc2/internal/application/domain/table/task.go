package table

import (
	"time"
)

type Task struct {
	Id     uint64
	UserId uint64
	Name   string

	TimeOfCreation time.Time
	StartTime      time.Time
	StopTime       time.Time
}
