package config

import (
	"fmt"
	"os"
	"strconv"
	"time"
	"wc2/pkg/utils"

	"github.com/spf13/viper"
)

type LogConfig struct {
	Name   string
	Level  uint32
	Format string

	EnableConsole  bool
	EnableFile     bool
	FileName       string
	DirName        string
	EnableRotation bool
	FileCount      uint32
	FileSizeKb     uint32
}

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

// -----------------------------------------------------------------------

type Config struct {
	StartTimeout time.Duration
	StopTimeout  time.Duration

	LogConfig                 LogConfig
	HttpInAdapter             HttpInAdapter
	PostgreDatabaseOutAdapter PostgreDatabaseOutAdapter
}

func MakeConfigFromViper() Config {
	return Config{
		StartTimeout: viper.GetDuration("start_timeout"),
		StopTimeout:  viper.GetDuration("stop_timeout"),

		LogConfig: LogConfig{
			Name:   viper.GetString("log.name"),
			Level:  viper.GetUint32("log.level"),
			Format: viper.GetString("log.format"),

			EnableConsole:  viper.GetBool("log.console.enable"),
			EnableFile:     viper.GetBool("log.file.enable"),
			FileName:       viper.GetString("log.file.name"),
			DirName:        viper.GetString("log.file.dir.name"),
			EnableRotation: viper.GetBool("log.file.rotation.enable"),
			FileCount:      viper.GetUint32("log.file.rotation.count"),
			FileSizeKb:     viper.GetUint32("log.file.rotation.size_kb"),
		},

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

func (c *Config) MergeWithEnv() error {
	sourceFunc := c.MergeWithEnv

	if v := os.Getenv(envar("LOG_FORMAT")); v != "" {
		c.LogConfig.Format = v
	}

	// ***

	if v := os.Getenv(envar("HOST")); v != "" {
		c.HttpInAdapter.Host = v
	}
	if v := os.Getenv(envar("PORT")); v != "" {
		portAsU64, err := strconv.ParseUint(v, 10, 16)
		if err != nil {
			return utils.NewFuncError(sourceFunc, err)
		}
		c.HttpInAdapter.Port = uint16(portAsU64)
	}

	// ***

	if v := os.Getenv(envar("POSTGRES_HOST")); v != "" {
		c.PostgreDatabaseOutAdapter.Host = v
	}
	if v := os.Getenv(envar("POSTGRES_PORT")); v != "" {
		portAsU64, err := strconv.ParseUint(v, 10, 16)
		if err != nil {
			return utils.NewFuncError(sourceFunc, err)
		}
		c.PostgreDatabaseOutAdapter.Port = uint16(portAsU64)
	}
	if v := os.Getenv(envar("POSTGRES_USER")); v != "" {
		c.PostgreDatabaseOutAdapter.User = v
	}
	if v := os.Getenv(envar("POSTGRES_PASSWORD")); v != "" {
		c.PostgreDatabaseOutAdapter.Password = v
	}
	if v := os.Getenv(envar("POSTGRES_DB_NAME")); v != "" {
		c.PostgreDatabaseOutAdapter.Database = v
	}

	return nil
}
