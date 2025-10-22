USE tiendaonline;

-- T02B.001- Código, nombre y pvp de los artículos de menos de 100€; la salida ha de ser código, nombre, "tiene el precio de", pvp.
SELECT cod, nombre, 'tiene el precio de', pvp FROM articulo WHERE pvp < 100;

-- T02B.002- DNI,email,nombre y apellidos de los usuarios de la provincia de Asturias (código 33).
SELECT dni, email, nombre, apellidos FROM usuario WHERE provincia = '33';
-- T02B.003- Toda la información (código y nombre) de las provincias de las que se tienen usuarios.
SELECT provincia.* FROM usuario, provincia WHERE usuario.provincia = provincia.codp;
-- T02B.004- Toda la información (código y nombre) de las provincias de las que se tienen usuarios, eliminando duplicados y ordenando por nombre.
SELECT DISTINCT provincia.* FROM usuario, provincia WHERE usuario.provincia = provincia.codp 
													ORDER BY provincia.nombre;
-- T02B.005- Email de los usuarios de la provincia de Murcia que no tienen teléfono, acompañado en la salida por un mensaje que diga "No tiene teléfono".
SELECT u.email, 'No tiene telefono' FROM usuario u, provincia pv WHERE u.provincia = pv.nombre = 'Murcia' AND u.telefono IS NULL;
-- T02B.006- Artículos que no tienen marca.
SELECT * FROM articulo WHERE marca IS NULL;
-- T02B.007- Código y nombre de los articulos con un precio entre 400 y 500 euros.
SELECT cod, nombre FROM articulo WHERE pvp BETWEEN 400 AND 500;
-- T02B.008- Código y nombre de los articulos con precio 415, 129, 1259 o 3995.
SELECT cod, nombre FROM articulo WHERE pvp IN (415, 129, 1259, 3995); -- Listas con el operador IN
-- T02B.009- Código, nombre, marca, pvp e importe de los artículos solicitados en el pedido número 1.
SELECT a.cod, a.nombre, a.marca, a.pvp, l.importe FROM articulo a, linped l WHERE l.numPedido = 1 
																			AND a.cod = l.articulo;
-- T02B.012- Código, sensor y pantalla de las cámaras, si es que "pantalla" tiene valor, ordenado por código descendentemente;
SELECT cod, sensor, pantalla FROM camara c WHERE c.pantalla IS NOT NULL ORDER BY c.cod DESC;
-- T02B.020- Código y nombre de las provincias que no son Huelva, Sevilla, Asturias ni Barcelona.
SELECT codp, nombre FROM provincia WHERE nombre NOT IN ('Huevla', 'Sevilla', 'Asturias', 'BARCELONA');

-- T02B.010- Código, nombre, marca, pvp e importe de los artículos solicitados en el pedido número 1 que sean televisores.
SELECT  FROM linped l, articulo a, pedido p WHERE 













