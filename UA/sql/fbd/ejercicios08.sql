-- DIFICULTAD A
-- T08.001- Obtener el importe total por línea para el pedido 1, en la salida aparecerá las columnas linea, articulo y el campo calculado total.
SELECT l.linea, l.articulo, (l.importe*l.cantidad) total FROM linped l WHERE l.numPedido = 1;
-- T08.002- Obtener la cantidad de provincias distintas de las que tenemos conocimiento de algún usuario.
SELECT COUNT(DISTINCT u.provincia) provincias FROM usuario u;
-- T08.003- Cantidad de usuarios de nuestra BD.
SELECT COUNT(*) usuarios FROM usuario u;
-- T08.004- Número de articulos con precio de venta al público mayor de 200 euros.
SELECT COUNT(*) FROM articulo WHERE pvp>200;
--T08.005- Total en euros de la cesta del usuario "bmm@agwab.com".
SELECT SUM(a.pvp) FROM cesta c, articulo a WHERE c.usuario='bmm@agwab.com' and a.cod=c.articulo;
-- T08.006- Tamaño máximo de pantalla para las televisiones.
SELECT MAX(pantalla) maxPantalla FROM tv;
-- T08.007- Media de precios de venta al público distintos de los articulos, redondeada a dos decimales.
SELECT ROUND(AVG(DISTINCT pvp), 2) MediaVenta FROM articulo;
-- T08.010- Máximo, mínimo y media de importe de los artículos.
SELECT MAX(pvp) maxPvp, MIN(pvp) minPvp, AVG(pvp) avgPvp FROM articulo;
-- T08.012- Cantidad de artículos que están descatalogados.
SELECT COUNT(*) ArtDescatalogados FROM stock WHERE entrega='Descatalogado';
-- T08.013- Precio máximo del artículo en stock que será entregado próximamente.
SELECT MAX(pvp) FROM articulo, stock WHERE cod=articulo AND entrega='Próximamente';
-- T08.015- Importe máximo, mínimo y medio de las líneas de pedido que incluyen el artículo “Bravia KDL-32EX402” 
SELECT MAX(pvp) máximo, MIN(pvp) mínimo, AVG(pvp) medio FROM articulo a, linped l WHERE a.cod=l.articulo AND a.nombre='Bravia KDL-32EX402';
-- T08.016- Cantidad total que se ha pedido de los artículos cuyo nombre empieza por "UE22".
SELECT SUM(cantidad) total FROM articulo a, linped l WHERE a.cod=l.articulo AND a.nombre LIKE'UE22%';
-- T08.017- Importe medio de los artículos incluidos en la línea de pedido número 4, redondeado a 3 decimales.
SELECT ROUND(AVG(importe), 3) PrecioMedio FROM linped WHERE linea=4;
-- T08.019- Diferencia entre el importe máximo y el importe mínimo del pedido número 30.
SELECT (MAX(importe)-MIN(importe)) Diferencia FROM linped WHERE numPedido=30;
-- T08.021- Fecha de nacimiento del usuario más viejo.
SELECT MIN(nacido) FROM usuario;
-- T08.022- Obtener en una única consulta, cuántas filas tiene la tabla artículo, cuántas de ellas tienen valor en la columna marca y cuántas marcas distintas hay almacenadas en la tabla.
SELECT COUNT(*) filas, COUNT(marca) conmarca, COUNT(DISTINCT marca) marcas FROM articulo;


-- DIFICULTAD B
-- T08.008- Nombre y precio de los articulos con el mínimo stock disponible.
SELECT a.nombre, a.pvp FROM articulo a, stock s WHERE a.cod=s.articulo AND s.disponible = (SELECT min(disponible) FROM stock);
-- T08.009- Número de pedido, fecha y nombre y apellidos del usuario de las lineas de pedido cuyo total en euros es el más alto.
SELECT p.numPedido, fecha, nombre, apellidos FROM pedido p, linped l, usuario u WHERE p.usuario=u.email AND p.numPedido=l.numPedido AND (l.cantidad*l.importe)=(SELECT (MAX(l.cantidad*l.importe)) FROM linped);
-- T08.011- Código, nombre, pvp y fecha de incorporación del artículo a la cesta más reciente.
SELECT a.cod, a.nombre, a.pvp, c.fecha FROM articulo a, cesta c WHERE a.cod=c.articulo AND c.fecha= (SELECT MAX(fecha) FROM cesta);
-- T08.014- Nombre, código y disponible en stock para todos los artículos cuyo código acabe en 3, siendo ese disponible el mínimo de toda la tabla.
SELECT nombre, cod, disponible MinDisponible FROM stock, articulo WHERE articulo=cod AND cod LIKE '%3' AND disponible=(SELECT MIN(disponible) FROM stock);
-- T08.018- Número de pedido, nombre, teléfono y email de usuario del pedido (o los pedidos) que contiene líneas de pedido cuyo importe unitario por artículo sea igual al importe más alto de entre todas las segundas líneas de todos los pedidos.
SELECT l.numPedido, nombre, telefono, email FROM usuario u, pedido p, linped l WHERE l.numPedido=p.numPedido AND p.usuario=u.email AND importe=(select MAX(importe) from linped where linea=2);
-- T08.020- Código, nombre, y PVP del artículo que más hay en stock.
SELECT cod, nombre, pvp FROM articulo, stock WHERE cod=articulo AND disponible= (SELECT MAX(disponible) FROM stock);
-- T08.023- Código, nombre y marca del artículo más caro.
SELECT cod, nombre, marca FROM articulo WHERE pvp = (SELECT MAX(pvp) FROM articulo);
-- T08.024- Código, nombre y pvp de la cámara más cara de entre las de tipo réflex.
SELECT a.cod, nombre, pvp FROM articulo a, camara c WHERE a.cod=c.cod AND c.tipo LIKE '%reflex%'
    AND pvp = (SELECT MAX(pvp) FROM articulo a, camara c WHERE  a.cod=c.cod AND c.tipo LIKE '%reflex%');
-- T08.025- Código, nombre y disponibilidad de los artículos con menor disponibilidad de entre los que pueden estar disponibles en 24 horas.
SELECT cod, nombre, disponible FROM articulo, stock WHERE cod=articulo AND entrega='24 horas'
    AND disponible = (SELECT MIN(disponible) FROM stock WHERE entrega='24 horas');
-- T08.026- Número de pedido y artículo con la línea de pedido de menor importe.
SELECT numPedido, articulo FROM linped WHERE importe = (SELECT MIN(importe) FROM linped); 
-- T08.027- Líneas de pedido y número de pedido al que correspondan dichas líneas, y que incluyan más cantidad de artículos que las demás.
SELECT linea, numPedido FROM linped WHERE cantidad = (SELECT MAX(cantidad) FROM linped);
-- T08.028- Líneas de pedido y nombre de los artículos que aparecen en esas líneas, si el importe de esas líneas no es el menor de todas las líneas conocidas.
SELECT DISTINCT linea, nombre FROM articulo a, linped l WHERE a.cod=l.articulo AND l.importe > (SELECT MIN(importe) FROM linped);
-- T08.029- Nombre, precio y marca de los artículos con mayor disponibilidad de stock.
SELECT nombre, pvp, marca FROM articulo a, stock s WHERE a.cod=s.articulo AND s.disponible = (SELECT MAX(disponible) FROM stock);
-- T08.030- Nombre, precio y marca de los artículos que no tengan la mayor disponibilidad de stock.
SELECT nombre, pvp, marca FROM articulo a, stock s WHERE a.cod=s.articulo AND s.disponible <> (SELECT MAX(disponible) FROM stock);