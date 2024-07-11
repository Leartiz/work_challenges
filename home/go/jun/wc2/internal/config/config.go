package config

import (
	"wc2/pkg/utils"

	"github.com/spf13/viper"
)

const (
	ConfigFileName = "config"
	ConfigFileExt  = "yaml"
)

func Init() (*Config, error) {

	viper.SetConfigType(ConfigFileExt)
	viper.SetConfigName(ConfigFileName)

	// ***

	configPaths := []string{
		".", "..", "../internal/config"}
	for _, cf := range configPaths {
		viper.AddConfigPath(cf)
	}

	if err := viper.ReadInConfig(); err != nil {
		return nil, utils.NewFuncError(Init, err)
	}

	// ***

	c := MakeConfigFromViper()
	if err := c.MergeWithEnv(); err != nil {
		return nil, utils.NewFuncError(Init, err)
	}

	return &c, nil
}
