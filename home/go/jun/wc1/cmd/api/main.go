package main

import (
	"wc1/server"
)

func main() {
	app := server.NewApp()
	app.Run("8080")
}
