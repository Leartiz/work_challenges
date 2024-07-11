package main

import (
	"fmt"
	"wc2/internal/toggle"
	"wc2/pkg/utils"
)

func main() {
	if err := toggle.Do(); err != nil {
		fmt.Printf("%v", utils.NewFuncError(main, err))
	}
}
