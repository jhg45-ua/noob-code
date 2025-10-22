-- DIFICULTAD C
-- T09B.002- ¿Cuáles son las marcas (en la tabla ARTICULO) que tienen menos de 150 artículos?
SELECT marca, COUNT(*) AS cantidad FROM articulo GROUP BY marca HAVING COUNT(*)<150;
-- T09B.003- ¿Cuáles son las marcas (en la tabla ARTICULO) que tienen menos de 150 artículos (eliminar las marcas que sean null)?
SELECT marca, COUNT(*) AS cantidad FROM articulo WHERE marca IS NOT NULL GROUP BY marca HAVING COUNT(*)<150;
-- T09B.005- Dni, nombre, apellidos y email de los usuarios que han realizado más de un pedido.
SELECT u.dni, u.nombre, u.apellidos, u.email FROM usuario u, pedido p WHERE u.email=p.usuario GROUP BY u.dni, u.nombre, u.apellidos, u.email HAVING COUNT(*)>1;
-- T09B.006- Pedidos (número de pedido y usuario) de importe mayor a 4000 euros.
SELECT p.numPedido, p.usuario FROM linped l, pedido p WHERE l.numPedido=p.numPedido GROUP BY p.numPedido, p.usuario HAVING SUM(l.cantidad*l.importe)>4000;
-- T09B.007- Pedidos (número de pedido y usuario) con más de 10 unidades solicitadas entre todos sus artículos pedidos, mostrando esta cantidad.
SELECT p.numPedido, p.usuario, SUM(l.cantidad) FROM pedido p, linped l WHERE p.numPedido=l.numPedido 
GROUP BY p.numPedido, p.usuario HAVING SUM(l.cantidad)>10;
-- T09B.008- Pedidos (número de pedido y usuario) que contengan más de cuatro artículos distintos.
SELECT p.numPedido, p.usuario, COUNT(DISTINCT l.articulo) FROM pedido p, linped l WHERE p.numPedido=l.numPedido 
    GROUP BY p.numPedido, p.usuario HAVING COUNT(DISTINCT l.articulo)>4;
-- T09B.009- ¿Hay dos provincias que se llamen igual (con nombre repetido)?
SELECT nombre, COUNT(*) FROM provincia GROUP BY nombre HAVING COUNT(*)>1;
-- T09B.010- ¿Hay algún pueblo con nombre repetido?
SELECT pueblo, COUNT(*) FROM localidad GROUP BY pueblo HAVING COUNT(*)>1;
-- T09B.011- Obtener el código y nombre de las provincias que tengan más de 100 pueblos.
SELECT p.nombre, p.codp FROM provincia p, localidad l WHERE p.codp=l.provincia GROUP BY p.nombre, p.codp HAVING COUNT(*)>100;
-- T09B.013- Clientes que hayan adquirido (pedido) más de 2 tv
SELECT p.usuario, SUM(l.cantidad) FROM pedido p, linped l, tv WHERE p.numPedido=l.numPedido AND l.articulo=tv.cod
    GROUP BY p.usuario HAVING SUM(l.cantidad)>2;
-- T09B.015- Código y nombre de las provincias que tienen más de 50 usuarios (provincia del usuario, no de la dirección de envío).