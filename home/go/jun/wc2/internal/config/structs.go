package config

import (
	"fmt"
	"time"

	"github.com/spf13/viper"
)

type Config struct {
	StartTimeout time.Duration
	StopTimeout  time.Duration

	HttpInAdapter             HttpInAdapter
	PostgreDatabaseOutAdapter PostgreDatabaseOutAdapter
}

func MakeConfigFromViper() Config {
	return Config{
		StartTimeout: viper.GetDuration("start_timeout"),
		StopTimeout:  viper.GetDuration("stop_timeout"),

		HttpInAdapter: HttpInAdapter{
			Host:         viper.GetString("adapters.in.http.host"),
			Port:         viper.GetUint16("adapters.in.http.port"),
			ReadTimeout:  viper.GetDuration("adapters.in.http.read_timeout"),
			WriteTimeout: viper.GetDuration("adapters.in.http.write_timeout"),
		},

		PostgreDatabaseOutAdapter: PostgreDatabaseOutAdapter{
			Host:     viper.GetString("adapters.out.database.sql.postgre.host"),
			Port:     viper.GetUint16("adapters.out.database.sql.postgre.port"),
			User:     viper.GetString("adapters.out.database.sql.postgre.user"),
			Password: viper.GetString("adapters.out.database.sql.postgre.password"),
			Database: viper.GetString("adapters.out.database.sql.postgre.database"),
		},
	}
}

const (
	EnvPrefix = "TIME_TRACKER"
)

func envar(name string) string {
	return fmt.Sprintf("%v_%v", EnvPrefix, name)
}

func (c *Config) MergeWithEnv() {

}

// ------------------------------------------------------------------------------

type HttpInAdapter struct {
	Host         string
	Port         uint16
	ReadTimeout  time.Duration
	WriteTimeout time.Duration
}

type PostgreDatabaseOutAdapter struct {
	Host     string
	Port     uint16
	User     string
	Password string
	Database string
}
