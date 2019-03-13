--  as admin
--  create database steward with owner befezdow;

-- as user
create table rooms(
  id serial primary key,
  name varchar(8) not null unique,
  description varchar(256)
);

create table managers(
  id serial primary key,
  firstname varchar(32) not null,
  lastname varchar(32) not null,
  patronymic varchar(32) not null,
  description varchar(256),
  phone_number varchar(32)
);

create table objects(
  id serial primary key,
  weight float not null,
  fragile boolean,
  manager integer references managers(id) on delete cascade not null,
  room integer references rooms(id) on delete cascade not null
);

create table furniture(
  material varchar(64),
  collapsible boolean not null
) inherits (objects);

create table equipment(
  manufacturer varchar(32)
) inherits (objects);

create table chairs(
  chair_type varchar(32),
  max_weight float
) inherits (furniture);

create table tables(
  height float,
  table_type varchar(32)
) inherits (furniture);

create table monitors(
  resolution varchar(16) not null,
  matrix_type varchar(16)
) inherits (equipment);

create table mice(
  buttons_count integer,
  wireless boolean
) inherits (equipment);

alter table chairs add foreign key (manager) references managers(id) on delete cascade;
alter table chairs add foreign key (room) references rooms(id) on delete cascade;

alter table tables add foreign key (manager) references managers(id) on delete cascade;
alter table tables add foreign key (room) references rooms(id) on delete cascade;

alter table monitors add foreign key (manager) references managers(id) on delete cascade;
alter table monitors add foreign key (room) references rooms(id) on delete cascade;

alter table mice add foreign key (manager) references managers(id) on delete cascade;
alter table mice add foreign key (room) references rooms(id) on delete cascade;