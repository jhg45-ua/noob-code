USE tiendaonline;

-- DIFICULTAD 1
-- T03.001- Código de los artículos que pertenecen a algún pack.
SELECT articulo FROM ptienea;


-- DIFICULTAD A
-- T03.002- Número de pack, nombre y precio del mismo.
SELECT p.cod, a.nombre, a.pvp FROM articulo a, pack p WHERE a.cod = p.cod;
-- T03.003- Código, nombre y marca de los artículos que pertenecen a algún pack.
SELECT a.cod, a.nombre, a.marca FROM articulo a, ptienea p WHERE a.cod = p.articulo;
-- T03.004- Código de la provincia Alicante.
SELECT p.codp FROM provincia p WHERE p.nombre LIKE 'Alicante%';
-- T03.005- Obtener el código, nombre y pvp de los articulos cuya marca comience por S.
SELECT a.cod, a.nombre, a.pvp FROM articulo a WHERE a.marca LIKE 'S%';
-- T03.006- Información sobre los usuarios cuyo email es de la eps.
SELECT * FROM usuario u WHERE u.email LIKE '%eps%';
-- T03.009- Email de los usuarios cuyo código postal no sea 02012, 02018 o 02032.
SELECT u.email FROM usuario u WHERE u.codpos NOT IN ('02012', '02018', '02032');
-- T03.021- Nombre de los artículos cuyo nombre contenga la palabra EOS.
SELECT a.nombre FROM articulo a WHERE a.nombre LIKE '%EOS%';
-- T03.022- Tipo y focal de los objetivos que se monten en una cámara Canon sea cual sea el modelo.
SELECT o.tipo, o.focal FROM objetivo o WHERE o.montura LIKE 'Canon%';
-- T03.023- Nombre de los artículos cuyo precio sea mayor de 100 pero menor o igual que 200.
SELECT a.nombre FROM articulo a WHERE a.pvp > 100 AND a.pvp >= 200;
-- T03.024- Nombre de los artículos cuyo precio sea mayor o igual que 100 pero menor o igual que 300.
SELECT a.nombre FROM articulo a WHERE a.pvp BETWEEN 100 AND 300;
-- T03.025- Nombre de las cámaras cuya marca no comience por la letra S.
SELECT a.nombre FROM camara c, articulo a WHERE c.cod = a.cod and a.marca NOT LIKE 'S%';
-- T03.027- Código de los televisores que tengan un panel LCD o LED.
SELECT t.cod FROM tv t WHERE t.panel LIKE '%LCD%' OR t.panel LIKE '%LED%';


-- DIFICULTAD B
-- T03.007- Código, nombre y resolución de los televisores cuya pantalla no esté entre 22 y 42.
SELECT a.cod, a.nombre, t.resolucion FROM articulo a, tv t WHERE a.cod = t.cod AND t.pantalla BETWEEN 22 AND 42;
-- T03.008- Código y nombre de los televisores cuyo panel sea tipo LED y su precio no supere los 1000 euros.
SELECT a.cod, a.nombre FROM tv t, articulo a WHERE t.cod = a.cod AND t.panel LIKE '%LED%' AND a.pvp <= 1000;
-- T03.010- Código y nombre de los packs de los que se conoce qué articulos los componen, eliminando duplicados.
SELECT DISTINCT a.cod, a.nombre FROM ptienea p , articulo a WHERE p.pack = a.cod; 
-- T03.011- ¿Hay algún artículo en cesta que esté descatalogado?

-- T03.012- Código, nombre y pvp de las cámaras de tipo compacta.
SELECT a.cod, a.nombre, a.pvp FROM camara c, articulo a WHERE c.cod = a.cod AND c.tipo LIKE '%compacta%';
-- T03.013- Código, nombre y diferencia entre pvp e importe de los articulos que hayan sido solicitados en algún pedido a un importe distinto de su precio de venta al público.

-- T03.014- Número de pedido,fecha y nombre y apellidos del usuario que solicita el pedido, para aquellos pedidos solicitados por algún usuario de apellido MARTINEZ.
SELECT p.numPedido, p.fecha, u.nombre, u.apellidos FROM pedido p, usuario u  WHERE u.email = p.usuario AND u.apellidos LIKE '%MARTINEZ%';
-- T03.019- Marcas de las que no existe ningún televisor en nuestra base de datos.
SELECT m.marca FROM marca m WHERE m.marca NOT IN (SELECT a.marca FROM articulo a, tv t WHERE a.cod = t.cod);
-- T03.026- Dirección de correo de los usuarios cuyo dni termine en B, L o P.
SELECT u.email FROM usuario u WHERE u.dni LIKE '%B' OR u.dni LIKE '%L' OR u.dni LIKE '%P';
-- T03.035- Nombre de los artículos que hayan sido seleccionados en alguna cesta con fecha entre 01.11.2010 y 31.12.2010.
SELECT a.nombre FROM articulo a, cesta c WHERE a.cod = c.articulo AND c.fecha BETWEEN '2010-11-01' AND '2010-12-31';
-- T03.037- Número identificador de los pedidos en los que se han incluido artículos a un importe menor que su pvp, eliminando duplicados.
SELECT DISTINCT l.numPedido FROM articulo a, linped l WHERE a.cod = l.articulo AND l.importe < a.pvp;

-- DIFICULTAD C
-- T03.016- Nombre, marca y resolucion de las cámaras que nunca se han solicitado.
SELECT a.nombre, a.marca, c.resolucion FROM camara c, articulo a WHERE c.cod = a.cod AND c.cod NOT IN (SELECT l.articulo FROM linped l);
-- T03.017- Código, nombre, tipo y marca de las cámaras de marca Nikon, LG o Sigma.
SELECT a.cod, a.nombre, c.tipo, a.marca FROM articulo a, camara c WHERE a.cod = c.cod AND a.marca IN ('Nikon', 'LG', 'Sigma');
-- T03.029- Nombre de los televisores que tengan una pantalla mayor que el televisor de código A0686.
SELECT a.nombre FROM articulo a, tv t WHERE a.cod = t.cod AND t.pantalla > (SELECT t2.pantalla FROM tv t2 WHERE t2.cod = 'A0686');
-- T03.036- Nombre de los artículos que hayan sido seleccionados en alguna cesta por usuarios de las provincias de Valencia o Alicante.
SELECT DISTINCT a.nombre FROM articulo a, cesta c, usuario u, provincia p WHERE a.cod = c.articulo AND c.usuario = u.email 
														 AND u.provincia IN (SELECT p2.codp FROM provincia p2 WHERE p2.nombre LIKE 'Alicante%' OR p2.nombre LIKE 'Valencia%');
-- T03.038- Número de pack, nombre y precio del mismo, y código, nombre y marca de los artículos que pertenezcan a ellos.
SELECT a.cod, a.nombre, a.pvp, a2.cod, a2.nombre, a2.marca FROM articulo a, articulo a2, ptienea p WHERE p.pack = a.cod AND p.articulo = a2.cod;











