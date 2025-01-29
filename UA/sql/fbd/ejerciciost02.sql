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
