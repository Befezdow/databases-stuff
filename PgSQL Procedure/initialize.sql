DROP TABLE IF EXISTS product CASCADE;
DROP TABLE IF EXISTS provider CASCADE;
DROP TABLE IF EXISTS buyer CASCADE;
DROP TABLE IF EXISTS sale CASCADE;
DROP TABLE IF EXISTS supply CASCADE;

CREATE TABLE product (
    id SERIAL NOT NULL PRIMARY KEY,
    name VARCHAR(64) NOT NULL UNIQUE,
    weight FLOAT NOT NULL CHECK(weight >= 0),
    manufacturer VARCHAR(64) NOT NULL DEFAULT 'China',
    comment VARCHAR(256)
);

CREATE TABLE provider (
    id SERIAL NOT NULL PRIMARY KEY,
    firstname VARCHAR(64) NOT NULL,
    lastname VARCHAR(64) NOT NULL,
    patronymic VARCHAR(64),
    phone_number VARCHAR(64) NOT NULL
);

CREATE TABLE buyer (
    id SERIAL NOT NULL PRIMARY KEY,
    firstname VARCHAR(64) NOT NULL,
    lastname VARCHAR(64) NOT NULL,
    patronymic VARCHAR(64),
    phone_number VARCHAR(64) NOT NULL
);

CREATE TABLE supply (
    id SERIAL NOT NULL PRIMARY KEY,
    product_id INT NOT NULL REFERENCES product(id),
    provider_id INT NOT NULL REFERENCES provider(id),
    price INT NOT NULL CHECK(price >= 0),
    quantity INT NOT NULL CHECK(quantity > 0),
    supply_date DATE NOT NULL
);

CREATE TABLE sale (
    id SERIAL NOT NULL PRIMARY KEY,
    product_id INT NOT NULL REFERENCES product(id),
    buyer_id INT NOT NULL REFERENCES buyer(id),
    price INT NOT NULL CHECK(price >= 0),
    quantity INT NOT NULL CHECK(quantity > 0),
    sale_date DATE NOT NULL
);

INSERT INTO product(name, weight, manufacturer, comment) VALUES
('Плойка Doom-3000', 0.3, 'Toshiba', 'Жарит как рыцарь ада'),
('Фен Ветра пустыни', 0.7, 'Bosch', 'Взял в руки и ...');

INSERT INTO provider(firstname, lastname, patronymic, phone_number) VALUES
('Иван', 'Иванов', 'Иванович', '+78005553535'),
('Борис', 'Борисов', 'Борисович', '+79067893212');

INSERT INTO buyer(firstname, lastname, patronymic, phone_number) VALUES
('Петр', 'Петров', 'Петрович', '+78953457634'),
('Павел', 'Павлов', 'Павлович', '+76542357854');

INSERT INTO supply(product_id, provider_id, price, quantity, supply_date) VALUES
(1, 1, 5700, 70, '2017-09-28 14:24:30'),
(2, 2, 7200, 150, '2017-09-13 18:12:50'),
(1, 2, 8970, 20, '2017-07-13 18:12:50'),
(1, 1, 4869, 500, '2017-08-13 18:12:50');

INSERT INTO sale(product_id, buyer_id, price, quantity, sale_date) VALUES
(1, 1, 9500, 1, '2017-09-29 12:33:10'),
(2, 1, 15300, 12, '2017-09-20 11:38:00');
