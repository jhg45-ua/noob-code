-- DIFICULTAD A
-- T08.001- Obtener el importe total por línea para el pedido 1, en la salida aparecerá las columnas linea, articulo y el campo calculado total.
SELECT l.linea, l.articulo, (l.importe*l.cantidad) total FROM linped l WHERE l.numPedido = 1;
-- T08.002- Obtener la cantidad de provincias distintas de las que tenemos conocimiento de algún usuario.
SELECT COUNT(DISTINCT u.provincia) provincias FROM usuario u;
-- T08.003- Cantidad de usuarios de nuestra BD.
SELECT COUNT(*) usuarios FROM usuario u;