CREATE TABLE product (
    id INT NOT NULL PRIMARY KEY,
    name VARCHAR(64) NOT NULL UNIQUE,
    weight FLOAT NOT NULL CHECK(weight >= 0),
    manufacturer VARCHAR(64) NOT NULL DEFAULT 'China',
    comment VARCHAR(256)
);

CREATE TABLE provider (
    id INT NOT NULL PRIMARY KEY,
    firstname VARCHAR(64) NOT NULL,
    lastname VARCHAR(64) NOT NULL,
    patronymic VARCHAR(64),
    phone_number VARCHAR(64) NOT NULL
);

CREATE TABLE buyer (
    id INT NOT NULL PRIMARY KEY,
    firstname VARCHAR(64) NOT NULL,
    lastname VARCHAR(64) NOT NULL,
    patronymic VARCHAR(64),
    phone_number VARCHAR(64) NOT NULL
);

CREATE TABLE supply (
    id INT NOT NULL PRIMARY KEY,
    product_id INT NOT NULL REFERENCES product(id),
    provider_id INT NOT NULL REFERENCES provider(id),
    price INT NOT NULL CHECK(price >= 0),
    quantity INT NOT NULL CHECK(quantity > 0),
    supply_date DATE NOT NULL
);

CREATE TABLE sale (
    id INT NOT NULL PRIMARY KEY,
    product_id INT NOT NULL REFERENCES product(id),
    buyer_id INT NOT NULL REFERENCES buyer(id),
    price INT NOT NULL CHECK(price >= 0),
    quantity INT NOT NULL CHECK(quantity > 0),
    sale_date DATE NOT NULL
);

INSERT INTO product(id, name, weight, manufacturer, comment) VALUES
(1, 'Плойка Doom-3000', 0.3, 'Toshiba', 'Жарит как рыцарь ада'),
(2, 'Фен Ветра пустыни', 0.7, 'Bosch', 'Взял в руки и ...');

INSERT INTO provider(id, firstname, lastname, patronymic, phone_number) VALUES
(1, 'Иван', 'Иванов', 'Иванович', '+78005553535'),
(2, 'Борис', 'Борисов', 'Борисович', '+79067893212');

INSERT INTO buyer(id, firstname, lastname, patronymic, phone_number) VALUES
(1, 'Петр', 'Петров', 'Петрович', '+78953457634'),
(2, 'Павел', 'Павлов', 'Павлович', '+76542357854');

INSERT INTO supply(id, product_id, provider_id, price, quantity, supply_date) VALUES
(1, 1, 1, 5700, 70, '2017-09-28 14:24:30'),
(2, 2, 2, 7200, 150, '2017-09-13 18:12:50'),
(3, 1, 2, 8970, 20, '2017-07-13 18:12:50'),
(4, 1, 1, 4869, 500, '2017-08-13 18:12:50');

INSERT INTO sale(id, product_id, buyer_id, price, quantity, sale_date) VALUES
(1, 1, 1, 9500, 1, '2017-09-29 12:33:10'),
(2, 2, 1, 15300, 12, '2017-09-20 11:38:00');