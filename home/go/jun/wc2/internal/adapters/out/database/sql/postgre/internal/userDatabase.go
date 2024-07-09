package internal

import (
	"context"
	"errors"
	"fmt"
	"wc2/internal/application/domain/table"
	"wc2/internal/application/ports/out/database"
	"wc2/pkg/utils"

	"github.com/doug-martin/goqu/v9"
	"github.com/jackc/pgx/v4"
	"github.com/jackc/pgx/v4/pgxpool"
)

type UserDatabase struct {
	pool *pgxpool.Pool
}

func NewUserDatabase(pool *pgxpool.Pool) *UserDatabase {
	return &UserDatabase{
		pool: pool,
	}
}

// templates
// -----------------------------------------------------------------------

const (
	tableUserData  = "user_data"
	tableUserEntry = "user_entry"
)

var (
	templateInsertUserEntry = utils.RemoveAdjacentWs(`
		INSERT INTO user_entry 
			(passport_series, passport_number, password_hash)
		VALUES ($1, $2, $3) 
			RETURNING id`)

	templateInsertUserDataWithId = utils.RemoveAdjacentWs(`
		INSERT INTO user_data
			(id, name, surname, patronymic, address)
		VALUES ($1, $2, $3, $4, $5)`)

	templateGetUserData = utils.RemoveAdjacentWs(`
		SELECT user_data.* FROM user_entry
			INNER JOIN user_data ON user_data.id = user_entry.id
		WHERE passport_series = $1 AND passport_number = $2`)

	templateHasUserByCred = utils.RemoveAdjacentWs(`
		SELECT 
    		case when COUNT(*) > 0 THEN true
    		else false end as has
		FROM user_entry
			WHERE passport_series = $1 AND 
    			passport_number = $2 AND
    			password_hash = $3`)

	templateUpdateUserRefreshTokenHash = utils.RemoveAdjacentWs(`
		UPDATE user_entry SET refresh_token_hash = $1
			WHERE id = $2`)

	templateUpdatePasswordHash = utils.RemoveAdjacentWs(`
		UPDATE user_entry SET password_hash = $1
			WHERE id = $2`)

	templateDeleteUserEntry = utils.RemoveAdjacentWs(`
		DELETE FROM user_entry WHERE id = $1`)
)

// public
// -----------------------------------------------------------------------

func (u *UserDatabase) CreateUser(ctx context.Context, cred database.Credentials) (uint64, error) {
	sourceFunc := u.CreateUser
	tx, err := u.pool.BeginTx(ctx, SerializableTxOptions())
	if err != nil {
		return 0, utils.NewFuncError(sourceFunc, err)
	}
	row := tx.QueryRow(ctx, templateInsertUserEntry+`;`,
		cred.PassportSeries, cred.PassportNumber,
		cred.PasswordHash)

	var insertedId uint64
	err = utils.RunFuncsRetErr(
		func() error { return row.Scan(&insertedId) },
		func() error {
			cmdTag, err := tx.Exec(ctx, templateInsertUserDataWithId+`;`,
				insertedId, "", "", "", "")
			if err != nil {
				return err
			}
			if !cmdTag.Insert() {
				return ErrInsertFailed
			}

			return nil
		})

	if err != nil {
		err := errors.Join(err, tx.Rollback(ctx))
		return 0, utils.NewFuncError(sourceFunc, err)
	}

	// ***

	if err = tx.Commit(ctx); err != nil {
		return 0, utils.NewFuncError(sourceFunc, err)
	}
	return insertedId, nil
}

func (u *UserDatabase) GetUserData(ctx context.Context, p database.Passport) (*table.UserData, error) {
	sourceFunc := u.GetUserData
	row := u.pool.QueryRow(ctx, templateGetUserData+`;`,
		p.PassportSeries, p.PassportNumber)

	var ud table.UserData
	err := row.Scan(&ud.Id, &ud.Name,
		&ud.Surname, &ud.Patronymic, &ud.Address)
	if err != nil {
		return nil, utils.NewFuncError(sourceFunc, err)
	}
	return &ud, nil
}

func (u *UserDatabase) GetUserDataList(ctx context.Context, filter database.UserDataGettingFilter) (
	[]*table.UserData, error) {
	sourceFunc := u.GetUserDataList

	selectDataset := goqu.From(tableUserEntry).InnerJoin(
		goqu.T(tableUserData),
		goqu.On(goqu.Ex{tableUserEntry + ".id": goqu.I(tableUserData + ".id")}))
	selectDataset = userDataGettingFilterToSelectDataset(filter, selectDataset)

	// ***

	var (
		err       error
		queryText string
		rows      pgx.Rows
	)

	err = utils.RunFuncsRetErr(
		func() error {
			queryText, _, err = selectDataset.ToSQL()
			fmt.Println(queryText)
			return err
		},
		func() error {
			rows, err = u.pool.Query(ctx, queryText)
			return err
		})
	if err != nil {
		return nil, utils.NewFuncError(sourceFunc, err)
	}

	// ***

	udList := []*table.UserData{}
	for rows.Next() {
		ud, err := scanUserDataFromTwoTableWithAllCols(rows)
		if err != nil {
			return nil, utils.NewFuncError(sourceFunc, err)
		}

		udList = append(udList, ud)
	}

	return udList, nil
}

func (u *UserDatabase) HasUserByCredentials(ctx context.Context, cred database.Credentials) (bool, error) {
	sourceFunc := u.HasUserByCredentials
	row := u.pool.QueryRow(ctx, templateHasUserByCred+`;`,
		cred.PassportSeries, cred.PassportNumber,
		cred.PasswordHash)

	var has bool
	if err := row.Scan(&has); err != nil {
		return false, utils.NewFuncError(sourceFunc, err)
	}
	return has, nil
}

// -----------------------------------------------------------------------

func (u *UserDatabase) UpdateRefreshTokenHash(ctx context.Context, userId uint64, val string) error {
	sourceFunc := u.UpdateRefreshTokenHash
	cmdTag, err := u.pool.Exec(ctx, templateUpdateUserRefreshTokenHash+`;`,
		val, userId)
	if err != nil {
		return utils.NewFuncError(sourceFunc, err)
	}
	if !cmdTag.Update() {
		return ErrUpdateFailed
	}
	return nil
}

func (u *UserDatabase) UpdatePasswordHash(ctx context.Context, userId uint64, passwordHash string) error {
	sourceFunc := u.UpdatePasswordHash
	cmdTag, err := u.pool.Exec(ctx, templateUpdatePasswordHash+`;`,
		passwordHash, userId)
	if err != nil {
		return utils.NewFuncError(sourceFunc, err)
	}
	if !cmdTag.Update() {
		return ErrUpdateFailed
	}
	return nil
}

func (u *UserDatabase) UpdateUserData(ctx context.Context,
	userId uint64, p database.UserOptionalData) error {

	sourceFunc := u.UpdateUserData
	queryText, _, err := goqu.Update(tableUserData).
		Set(p).Where(goqu.Ex{"id": userId}).ToSQL()
	if err != nil {
		return utils.NewFuncError(sourceFunc, err)
	}

	cmdTag, err := u.pool.Exec(ctx, queryText)
	if err != nil {
		return utils.NewFuncError(sourceFunc, err)
	}
	if !cmdTag.Update() {
		return ErrUpdateFailed
	}

	return nil
}

// -----------------------------------------------------------------------

func (u *UserDatabase) DeleteUser(ctx context.Context, userId uint64) error {
	sourceFunc := u.DeleteUser
	cmdTag, err := u.pool.Exec(ctx, templateDeleteUserEntry+`;`, userId)
	if err != nil {
		return utils.NewFuncError(sourceFunc, err)
	}
	if !cmdTag.Delete() {
		return ErrUpdateFailed
	}
	return nil
}

// private
// -----------------------------------------------------------------------

func userDataGettingFilterToSelectDataset(
	filter database.UserDataGettingFilter,
	selectDataset *goqu.SelectDataset) *goqu.SelectDataset {

	exprs := []goqu.Expression{}
	if filter.PassportSeries != nil {
		exprs = append(exprs, goqu.Ex{"passport_series": *filter.PassportSeries})
	}
	if filter.PassportNumber != nil {
		exprs = append(exprs, goqu.Ex{"passport_number": *filter.PassportNumber})
	}

	// ***

	if filter.Name != nil {
		exprs = append(exprs, goqu.Ex{"name": *filter.Name})
	}
	if filter.Surname != nil {
		exprs = append(exprs, goqu.Ex{"surname": *filter.Surname})
	}
	if filter.Patronymic != nil {
		exprs = append(exprs, goqu.Ex{"patronymic": *filter.Patronymic})
	}
	if filter.Address != nil {
		exprs = append(exprs, goqu.Ex{"address": *filter.Address})
	}

	// ***

	if filter.Limit != nil {
		selectDataset = selectDataset.Limit(uint(*filter.Limit))
	}
	if filter.Offset != nil {
		selectDataset = selectDataset.Offset(uint(*filter.Offset))
	}

	return selectDataset.Where(exprs...)
}

func scanUserDataFromTwoTableWithAllCols(ss ScannableResult) (*table.UserData, error) {
	sourceFunc := scanUserDataFromTwoTableWithAllCols
	ud := table.UserData{}
	err := ss.Scan(nil, nil, nil, nil, nil, // not good!
		&ud.Id, &ud.Name, &ud.Surname, &ud.Patronymic,
		&ud.Address)
	if err != nil {
		return nil, utils.NewFuncError(sourceFunc, err)
	}

	return &ud, err
}
