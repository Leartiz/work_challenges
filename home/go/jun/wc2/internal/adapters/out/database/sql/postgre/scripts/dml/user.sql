SELECT * FROM user_entry;
SELECT * FROM user_data;

INSERT INTO user_entry 
(passport_series, passport_number, password_hash)
VALUES (1, 2, '123');

INSERT INTO user_data
(id, name, surname, patronymic, address)
VALUES (2, '1', '1', '1', '1');