package zkits

import (
	"fmt"
	"io"
	"os"
	"wc2/pkg/logger"
	"wc2/pkg/utils"

	zz "github.com/edoger/zkits-logger"
)

type ZkitsLogger struct {
	zzLogger zz.Logger
}

func New(p *logger.Params) (*ZkitsLogger, error) {
	wrs := []io.Writer{}
	if p.EnableConsole {
		wrs = append(wrs, os.Stdout)
	}

	if p.EnableFile {
		pathToLogs := p.DirName + "/" + p.FileName
		fmt.Printf("path to logs: %v\n", pathToLogs)

		if !p.EnableRotate {
			p.FileCount = 1
			p.FileSizeKb = 0
		}

		w, err := zz.NewFileWriter(pathToLogs, p.FileSizeKb*1024, p.FileCount)
		if err != nil {
			return nil, utils.NewFuncError(New, err)
		}

		wrs = append(wrs, w)
	}

	zzLogger := zz.New(p.Name)
	zzLogger.SetLevel(zz.Level(p.Level))
	if p.Format == logger.FormatJson {
		zzLogger.SetFormatter(zz.DefaultJSONFormatter())
	} else {
		zzLogger.SetFormatter(zz.DefaultTextFormatter())
	}
	zzLogger.SetOutput(io.MultiWriter(wrs...))
	zzLogger.EnableCaller(2) // down the stack!

	return &ZkitsLogger{zzLogger: zzLogger}, nil
}

// Logger
// -----------------------------------------------------------------------

func (z *ZkitsLogger) Trace(format string, args ...any) {
	z.zzLogger.Tracef(format, args...)
}

func (z *ZkitsLogger) Debug(format string, args ...any) {
	z.zzLogger.Debugf(format, args...)
}

func (z *ZkitsLogger) Warn(format string, args ...any) {
	z.zzLogger.Warnf(format, args...)
}

func (z *ZkitsLogger) Info(format string, args ...any) {
	z.zzLogger.Infof(format, args...)
}

func (z *ZkitsLogger) Error(format string, args ...any) {
	z.zzLogger.Errorf(format, args...)
}

func (z *ZkitsLogger) Fatal(format string, args ...any) {
	z.zzLogger.Fatalf(format, args...)
}
