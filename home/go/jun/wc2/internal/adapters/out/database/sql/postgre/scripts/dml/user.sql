SELECT * FROM user_entry;
SELECT * FROM user_data;

INSERT INTO user_entry 
(passport_series, passport_number, password_hash)
VALUES (1, 2, '123');

INSERT INTO user_data
(id, name, surname, patronymic, address)
VALUES (4, '1', '1', '1', '1');

SELECT user_data.* FROM user_entry
INNER JOIN user_data ON user_data.id = user_entry.id
WHERE passport_series = 1 AND passport_number = 2;

SELECT 
    case when COUNT(*) > 0 THEN true
    else false end as has
FROM user_entry
WHERE passport_series = 1 AND 
    passport_number = 2 AND
    password_hash = '123';

UPDATE user_entry
SET refresh_token_hash = '123_123_123'
WHERE id = 1;

UPDATE user_entry
SET password_hash = '123'
WHERE id = 1;

DELETE FROM user_entry
WHERE id = 1;

SELECT * FROM user_entry
INNER JOIN user_data ON user_entry.id = user_data.id
WHERE passport_series = 1;

SELECT * FROM "user_entry" INNER JOIN "user_data" ON 
    ("user_entry"."id" = "user_data"."id");