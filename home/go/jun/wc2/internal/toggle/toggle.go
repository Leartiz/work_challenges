package toggle

import (
	"context"
	"os"
	"os/signal"
	"syscall"
	inHttp "wc2/internal/adapters/in/http"
	"wc2/internal/config"
	"wc2/pkg/logger"
	"wc2/pkg/logger/zkits"
	"wc2/pkg/utils"
)

func Do() error {
	c, err := config.Init()
	if err != nil {
		return utils.NewFuncError(Do, err)
	}

	if err := initLog(c); err != nil {
		return utils.NewFuncError(Do, err)
	}

	// ***

	startCtx, cancel := context.WithTimeout(
		context.Background(), c.StartTimeout)
	defer cancel()

	// infra

	// usecase

	// interfaces

	httpInAd, err := inHttp.New(startCtx, c.HttpInAdapter.Host, c.HttpInAdapter.Port,
		c.HttpInAdapter.ReadTimeout, c.HttpInAdapter.WriteTimeout)
	if err != nil {
		return utils.NewFuncError(Do, err)
	}

	go func() {
		if err := httpInAd.Start(); err != nil {
			logger.Error("%v", err)
		}
	}()

	<-shutdown()

	return nil
}

func shutdown() <-chan os.Signal {
	exitCh := make(chan os.Signal, 1)
	signal.Notify(exitCh,
		syscall.SIGABRT,
		syscall.SIGQUIT,
		syscall.SIGTERM,
		syscall.SIGINT)
	return exitCh
}

func initLog(c *config.Config) error {
	params := &logger.Params{
		Name:   c.LogConfig.Name,
		Level:  c.LogConfig.Level,
		Format: c.LogConfig.Format,

		EnableConsole: c.LogConfig.EnableConsole,

		EnableFile: c.LogConfig.EnableFile,
		DirName:    c.LogConfig.DirName,
		FileName:   c.LogConfig.FileName,

		EnableRotate: c.LogConfig.EnableRotation,
		FileCount:    c.LogConfig.FileCount,
		FileSizeKb:   c.LogConfig.FileSizeKb,
	}

	l, err := zkits.New(params)
	if err != nil {
		return utils.NewFuncError(initLog, err)
	}

	logger.SetGlobalInstance(l)

	logger.Trace("trace")
	logger.Debug("debug")
	logger.Info("info")
	logger.Warn("warn")
	logger.Error("error")

	return nil
}
