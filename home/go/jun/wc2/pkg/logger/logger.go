package logger

const (
	FormatText = "text"
	FormatJson = "json"
)

type Params struct {
	Name   string
	Level  uint32
	Format string

	EnableConsole bool

	EnableFile bool
	DirName    string
	FileName   string

	EnableRotate bool
	FileCount    uint32
	FileSizeKb   uint32 // bytes?
}

type Logger interface {
	Trace(format string, args ...any)
	Debug(format string, args ...any)

	Warn(format string, args ...any)
	Info(format string, args ...any)

	Error(format string, args ...any)
	Fatal(format string, args ...any)
}

// !
// -----------------------------------------------------------------------

var globalInstance Logger

func SetGlobalInstance(l Logger) error {
	globalInstance = l
	return nil
}

// To Global Instance
// -----------------------------------------------------------------------

func Trace(format string, args ...any) {
	globalInstance.Trace(format, args...)
}

func Debug(format string, args ...any) {
	globalInstance.Debug(format, args...)
}

func Warn(format string, args ...any) {
	globalInstance.Warn(format, args...)
}

func Info(format string, args ...any) {
	globalInstance.Info(format, args...)
}

func Error(format string, args ...any) {
	globalInstance.Error(format, args...)
}

func Fatal(format string, args ...any) {
	globalInstance.Fatal(format, args...)
}
