-- DIFICULTAD A
-- T09.004- Número de cámaras que tienen sensor CMOS
SELECT COUNT(*) FROM camara WHERE sensor LIKE '%CMOS%';
-- T09.016- Cantidad de artículos con stock 0
SELECT COUNT(*) FROM stock WHERE disponible=0;

-- DIFICULTAD B
-- T09.001- ¿Cuántos artículos de cada marca hay?
SELECT marca, COUNT(*) FROM articulo GROUP BY marca;
-- T09.012- Ha habido un error en Tiendaonline y se han colado varios artículos sin stock, con cero unidades disponibles, en la cesta. Averigua el código de esos artículos y las veces que aparece cada uno en cesta.
SELECT c.articulo, COUNT(*) AS Error FROM cesta c, stock s WHERE c.articulo=s.articulo AND s.disponible=0 GROUP BY c.articulo;
-- T09.017- Cantidad de artículos que no son ni memoria, ni tv, ni objetivo, ni cámara ni pack.
SELECT COUNT(*) FROM articulo WHERE cod NOT IN (SELECT cod FROM camara
                                            UNION SELECT cod FROM tv
                                            UNION SELECT cod FROM objetivo
                                            UNION SELECT cod FROM camara
                                            UNION SELECT cod FROM pack);
-- T09.021- Cantidad de líneas por cada pedido.
SELECT numPedido AS Pedido, COUNT(*) AS Lineas FROM linped GROUP BY numPedido;
-- T09.022- Cantidad de líneas por cada pedido, eliminando aquellas filas con cantidades de artículo pedidas menores a 3.
SELECT numPedido AS Pedido, COUNT(*) AS Lineas FROM linped WHERE cantidad >= 3 GROUP BY numPedido;
-- T09.023- Para los pedidos anteriores a septiembre de 2010, cantidad de líneas por cada pedido.
SELECT l.numPedido AS Pedido, COUNT(*) AS Lineas FROM linped l, pedido p WHERE l.numPedido=p.numPedido AND p.fecha < '2010-09-01' GROUP BY l.numPedido;
-- T09.024- Por cada artículo pedido, cantidad total de unidades pedidas.
SELECT articulo, SUM(cantidad) AS 'cantidad total' FROM linped GROUP BY articulo;
-- T09.025- Por cada artículo pedido, cantidad total de unidades pedidas y promedio de importe unitario.
SELECT articulo, SUM(cantidad) AS 'cantidad total', AVG(importe) AS promedio FROM linped GROUP BY articulo;
-- T09.026- Para las cámaras pedidas, código de artículo, cantidad total de unidades pedidas y promedio de importe unitario.
SELECT articulo, SUM(cantidad) AS 'cantidad total', AVG(importe) AS promedio FROM linped WHERE articulo IN (SELECT cod FROM camara) GROUP BY articulo; 
-- T09.027- Para las cámaras pedidas, código, nombre, marca del artículo, y cantidad total de unidades pedidas y promedio de importe unitario.
SELECT l.articulo, a.nombre, a.marca, SUM(cantidad) AS 'cantidad total', AVG(importe) AS promedio FROM linped l, articulo a WHERE l.articulo=a.cod AND l.articulo IN (SELECT cod FROM camara) GROUP BY l.articulo, a.nombre, a.marca;
-- T09.028- Para todo usuario cuyo primer apellido sea Martínez, comprobar si hay algún otro usuario con los mismos apellidos y nombre.
SELECT apellidos, nombre, COUNT(*) FROM usuario WHERE apellidos LIKE 'Martínez%' GROUP BY apellidos, nombre;
-- T09.029- Por cada mes y año, cantidad de pedidos realizados.
SELECT MONTH(fecha) AS mes, YEAR(fecha) AS año, COUNT(*) AS Pedidos FROM pedido GROUP BY MONTH(fecha), YEAR(fecha);
-- T09.030- Para los artículos 'A0233' y 'A1085', código de artículo y cantidad de pedidos distintos en los que ha sido solicitado.
SELECT articulo, COUNT(DISTINCT numPedido) FROM linped WHERE articulo IN ('A0233', 'A1085') GROUP BY articulo;
-- T09.031- ¿Cuántas veces se ha pedido cada artículo? Deben mostrarse todos los artículos, incluso los que no se han pedido nunca. La salida contendrá el código y nombre del artículo, junto con las veces que ha sido incluido en un pedido (solo si ha sido incluido, no se trata de la "cantidad").
SELECT cod, nombre, COUNT(numPedido) AS veces FROM articulo a LEFT JOIN linped l ON (a.cod=l.articulo) GROUP BY cod, nombre;
-- T09.032- Por cada usuario, email y total de precio de venta al público acumulado en sus cestas actuales.
SELECT usuario, SUM(pvp) FROM cesta c, articulo a WHERE c.articulo=a.cod GROUP BY usuario;
-- T09.033- Por cada usuario, email y total de precio de venta al público acumulado en sus cestas actuales, eliminando previamente los artículos sin PVP, y ordenando de mayor a menor por ese total.
SELECT usuario, SUM(pvp) AS total FROM cesta c, articulo a WHERE c.articulo=a.cod AND pvp IS NOT NULL GROUP BY usuario ORDER BY total;