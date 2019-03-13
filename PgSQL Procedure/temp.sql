SELECT provider_id, firstname, lastname, patronymic, date_trunc('day', supply_date) AS date, sum(price * quantity) AS total
FROM supply LEFT JOIN provider ON (supply.provider_id = provider.id) 
GROUP BY (provider_id, firstname, lastname, patronymic, date_trunc('day', supply_date))
ORDER BY (provider_id, date_trunc('day', supply_date));

SELECT buyer_id, firstname, lastname, patronymic, date_trunc('day', sale_date) AS date, sum(price * quantity) AS total
FROM sale LEFT JOIN buyer ON (sale.buyer_id = buyer.id) 
GROUP BY (buyer_id, firstname, lastname, patronymic, date_trunc('day', sale_date))
ORDER BY (buyer_id, date_trunc('day', sale_date));

SELECT date, sum(total) AS total FROM sale_data GROUP BY date ORDER BY date;

SELECT date, sum(total) AS total FROM supply_data GROUP BY date ORDER BY date;

SELECT product_id, name, date_trunc('day', supply_date) AS date, sum(quantity) AS quantity
FROM supply LEFT JOIN product ON (supply.product_id = product.id)
GROUP BY (product_id, name, date_trunc('day', supply_date))
ORDER BY (product_id, date_trunc('day', supply_date));

SELECT product_id, name, date_trunc('day', sale_date) AS date, sum(quantity) AS quantity
FROM sale LEFT JOIN product ON (sale.product_id = product.id)
GROUP BY (product_id, name, date_trunc('day', sale_date))
ORDER BY (product_id, date_trunc('day', sale_date));