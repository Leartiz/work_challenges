CREATE TABLE task (
    id bigserial PRIMARY KEY,
    user_id int8 not null,
    name varchar(255) not null,
    time_of_creation timestamp not null,
    start_time timestamp null,
    stop_time timestamp null,

    FOREIGN KEY (user_id) REFERENCES user_entry (id) 
        on delete cascade
);