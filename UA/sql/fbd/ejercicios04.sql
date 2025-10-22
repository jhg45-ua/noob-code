USE tiendaonline;

-- DIFICULTAD A
-- T04.001- Toda la información de los pedidos anteriores a octubre de 2010.
SELECT * FROM pedido p WHERE p.fecha < '2010-10-01';
-- T04.002- Toda la información de los pedidos posteriores a agosto de 2010.
SELECT * FROM pedido p WHERE p.fecha > '2010-08-01';
-- T04.003- Toda la información de los pedidos realizados entre agosto y octubre de 2010.
SELECT * FROM pedido p WHERE p.fecha BETWEEN '2010-08-01' AND '2010-10-01';
-- T04.004- Toda la información de los pedidos realizados el 3 de marzo o el 27 de octubre de 2010.
SELECT * FROM pedido p WHERE p.fecha = '2010-03-03' OR p.fecha = '2010-10-27';
-- T04.005- ¿En qué día y hora vivimos?
SELECT NOW();
-- T04.006- Códigos de articulos solicitados en 2010, eliminando duplicados y ordenado ascendentemente.
SELECT DISTINCT l.articulo FROM linped l, pedido p WHERE l.numPedido  = p.numPedido 
													AND YEAR(p.fecha) = 2010 ORDER BY l.articulo;
-- T04.007- Códigos de articulos solicitados en pedidos de marzo de 2010, eliminando duplicados y ordenado ascendentemente.
SELECT DISTINCT l.articulo FROM linped l, pedido p WHERE l.numPedido = p.numPedido AND p.fecha BETWEEN '2010-03-01' AND '2010-03-31'
										ORDER BY l.articulo;
-- T04.008- Toda la información de USUARIOs nacido en marzo de cualquier año.
SELECT * FROM usuario u WHERE MONTH(u.nacido) = 03;