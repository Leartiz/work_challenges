package internal

import (
	"context"
	"fmt"
	"log"
	"os"
	"testing"
	"wc2/internal/application/ports/out/database"
	"wc2/pkg/postgreUtils"

	"github.com/doug-martin/goqu/v9"
	"github.com/jackc/pgx/v4/pgxpool"
)

func Test_goqu_buildQuery(t *testing.T) {
	queryText, _, _ := goqu.From("test").Where(goqu.Ex{
		"d": []string{"a", "b", "c"},
	}).ToSQL()

	fmt.Println(queryText)
}

func Test_goqu_buildSelectDataset(t *testing.T) {
	queryText, _, _ := goqu.From(tableUserEntry).InnerJoin(
		goqu.T(tableUserData),
		goqu.On(goqu.Ex{
			tableUserEntry + ".id": goqu.I(tableUserData + ".id")})).
		Where(
			goqu.Ex{"d": []string{"a", "b", "c"}},
			goqu.Ex{"c": []string{"a", "b", "c"}}).ToSQL()

	fmt.Println(queryText)
}

func Test_goqu_buildUpdateDataset(t *testing.T) {
	var p = database.UserOptionalData{
		Name:    new(string),
		Surname: new(string),
	}
	*p.Name = "123"
	*p.Surname = "4"

	queryText, _, err := goqu.Update(tableUserData).
		Set(p).Where(goqu.Ex{"id": 1}).ToSQL()
	if err != nil {
		t.Error(err)
		return
	}

	fmt.Println(queryText)
}

// -----------------------------------------------------------------------

func TestMain(m *testing.M) {
	setup()
	rc := m.Run()
	teardown()

	os.Exit(rc)
}

func setup() {
	params := postgreUtils.ConnectionParamsWithDb{
		Username:     "postgres",
		Password:     "admin",
		Host:         "127.0.0.1",
		Port:         5432,
		DatabaseName: "time_tracker"}

	// ***

	pool, err = pgxpool.Connect(ctx,
		params.CreateConnectionString())
	if err != nil {
		log.Fatal(err)
	}

	// ***

	userDatabase = NewUserDatabase(pool)
}

func teardown() {
	userDatabase = nil
	pool.Close()
}

var (
	err error
	ctx context.Context = context.Background()

	pool         *pgxpool.Pool
	userDatabase *UserDatabase
)

func Test_GetUserDataList(t *testing.T) {

	filter := database.UserDataGettingFilter{
		PassportSeries: new(uint32),
		PassportNumber: new(uint32)}
	*filter.PassportSeries = 1
	*filter.PassportNumber = 3

	udList, err := userDatabase.GetUserDataList(ctx, filter)
	if err != nil {
		t.Error(err)
		return
	}

	for i := 0; i < len(udList); i++ {
		log.Println(udList[i])
	}
}

func Test_userDataGettingFilterToSelectDataset(t *testing.T) {
	selectDataset := goqu.From(tableUserEntry).InnerJoin(
		goqu.T(tableUserData),
		goqu.On(goqu.Ex{tableUserEntry + ".id": goqu.I(tableUserData + ".id")}))
	var filter = database.UserDataGettingFilter{
		PassportSeries: new(uint32),
		PassportNumber: new(uint32)}
	*filter.PassportSeries = 2
	*filter.PassportNumber = 5
	//...

	selectDataset = userDataGettingFilterToSelectDataset(
		filter, selectDataset)

	fmt.Println(selectDataset.ToSQL())
}
