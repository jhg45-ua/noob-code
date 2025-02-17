USE tiendaonline;

-- T02.001- Obtén toda la información de los usuarios
SELECT * FROM usuario;
-- T02.011- Marcas
SELECT * FROM marca;

-- T02.002- Lista los email y nombre y apellidos de los usuarios
SELECT email, nombre, apellidos FROM usuario;
-- T02.003- Lista los email y nombre y apellidos de los usuarios ordenados por email
SELECT email, nombre, apellidos FROM usuario ORDER BY email;
-- T02.004- Lista los email y nombre y apellidos de los usuarios ordenados por apellidos y nombre
SELECT email, nombre, apellidos FROM usuario ORDER BY apellidos, nombre;
-- T02.005- Lista los email y nombre y apellidos de los usuarios ordenados ascendentemente por apellidos y descendentemente por nombre
SELECT email, nombre, apellidos FROM usuario ORDER BY apellidos, nombre DESC;
-- T02.006- Lista los email y nombre y apellidos de los usuarios en orden descendente de apellidos y nombre
SELECT email, nombre, apellidos FROM usuario ORDER BY apellidos DESC, nombre DESC;
-- T02.016- Código e importe de los artículos solicitados en el pedido número 1.
SELECT articulo, importe FROM linped WHERE numpedido=1;
-- T02.023- Panel de los televisores de 21 pulgadas o menos de pantalla, eliminando duplicados.
SELECT DISTINCT panel FROM tv where pantalla < 21;
-- T02.024- Código, nombre, marca y pvp de los artículos que tienen ese precio entre 350 y 450.
SELECT cod, nombre, marca, pvp FROM articulo WHERE pvp >= 350 AND pvp <= 450;

-- T02.025- Código, nombre y precio de venta al público de los artículos que no tienen marca.
SELECT cod, nombre, pvp FROM articulo WHERE marca IS NULL;
-- T02.026- Código, nombre y precio de venta al público de los artículos que no tienen precio de venta al público y son de marca Sigma.
SELECT cod, nombre, pvp FROM articulo WHERE pvp IS NULL AND marca = 'Sigma';
-- T02.027- Email, nombre, apellidos y teléfono de los usuarios que se llaman Santiago, Wenceslao o Sergio.
SELECT email, nombre, apellidos, telefono FROM usuario WHERE nombre = 'Santiago' OR nombre = 'Wenceslao' OR nombre = 'Sergio';
-- T02.028- Email, nombre, apellidos y teléfono de los usuarios que se llaman Santiago, Wenceslao o Sergio y que sí tienen teléfono.
SELECT email, nombre, apellidos, telefono FROM usuario WHERE nombre = 'Santiago' OR nombre = 'Wenceslao' OR nombre = 'Sergio' AND telefono IS NOT NULL;