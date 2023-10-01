package main

import (
	"log"
	"wc1/config"
	"wc1/server"

	"github.com/spf13/viper"
)

func main() {
	err := config.Initialize()
	if err != nil {
		log.Fatalf("initialize config failed")
	}

	// ***

	app := server.NewApp()
	defer app.ClearEnv()

	// ***

	app.Run(
		viper.GetString(
			"server.http.port"))
}
