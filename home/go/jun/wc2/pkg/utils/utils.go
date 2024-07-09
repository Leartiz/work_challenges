package utils

import (
	"fmt"
	"reflect"
	"runtime"
	"strings"
)

func IsFunction(i interface{}) bool {
	funType := reflect.TypeOf(i)
	funTypeName := funType.String()
	return strings.Contains(funTypeName, "func")
}

func GetFunctionName(i interface{}) string {
	if !IsFunction(i) {
		return ""
	}

	fullFunctionName := runtime.FuncForPC(
		reflect.ValueOf(
			i).Pointer()).Name()

	parts := strings.Split(fullFunctionName, "/")
	if len(parts) == 0 { // impossible?
		return ""
	}

	shortFunctionName := parts[len(parts)-1]
	return shortFunctionName
}

// creating a stack with errors!
func NewFuncError(i interface{}, err error) error {
	return fmt.Errorf(GetFunctionName(i)+"\n with an error/in: %w", err)
}

func RemoveAdjacentSpacesFromString(text string) string {
	fields := strings.Fields(text)
	return strings.Join(fields, " ")
}

func RemoveAdjacentWs(text string) string {
	return RemoveAdjacentSpacesFromString(text)
}

type FuncReturningError = func() error

func RunFuncsRetErr(ff ...FuncReturningError) error {
	for _, f := range ff {
		if err := f(); err != nil {
			return err
		}
	}

	return nil
}
