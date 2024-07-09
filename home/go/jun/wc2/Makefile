init_migrate:
	migrate create -ext sql \
		-dir ./internal/adapters/out/database/sql/postgre/migrations \
		-seq -digits 6 init

up_migrate_ll:
	migrate -source file://./internal/adapters/out/database/sql/postgre/migrations \
		-database postgres://postgres:admin@localhost:5432/time_tracker?sslmode=disable up 

down_migrate_ll:
	migrate -source file://./internal/adapters/out/database/sql/postgre/migrations \
		-database postgres://postgres:admin@localhost:5432/time_tracker?sslmode=disable down