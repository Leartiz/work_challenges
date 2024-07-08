package table

type UserEntry struct {
	Id             uint64
	PassportSeries uint32
	PassportNumber uint32

	PasswordHash     string
	RefreshTokenHash string
}

type UserData struct {
	Id         uint64
	Name       string
	Surname    string
	Patronymic string
	Address    string
}
