package config

import "github.com/spf13/viper"

func Initialize() error {
	// TODO: something wrong with the path.
	viper.AddConfigPath("../../config")
	viper.SetConfigName("config")
	return viper.ReadInConfig()
}
