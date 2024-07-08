SELECT table_name
FROM information_schema.tables
WHERE table_schema = 'public'
AND table_type = 'BASE TABLE';

-- ----------------------------------------------

CREATE TABLE user_entry (
    id bigserial PRIMARY KEY,
    passport_series int not null,
    passport_number int not null,
    password_hash varchar(255) not null,
    refresh_token_hash varchar(255) not null default '',

    CONSTRAINT passport_comb UNIQUE
        (passport_series, passport_number)
);

CREATE TABLE user_data (
    id int8 not null,
    name varchar(255) not null default '',
    surname varchar(255) not null default '',
    patronymic varchar(255) not null default '',
    address varchar(255) not null default '',

    FOREIGN KEY (id) REFERENCES user_entry (id) 
        on delete cascade
);