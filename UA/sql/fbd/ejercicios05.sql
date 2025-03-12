USE tiendaonline;

-- DIFICULTAD A
-- T05.011- Código y nombre de los artículos que no tienen marca.
SELECT a.cod, a.nombre FROM articulo a WHERE a.marca IS NULL;
-- T05.012- Código, nombre y marca de todos los artículos, tengan o no marca.
SELECT a.cod, a.nombre, a.marca FROM articulo a;
-- T05.001- Número de pedido e identificador, apellidos y nombre del usuario que realiza el pedido (usando join).
SELECT p.numPedido, u.email, u.nombre, u.apellidos FROM pedido p JOIN usuario u ON (u.email = p.usuario);
-- T05.005- Apellidos y nombre de los usuarios y, si tienen, pedido que han realizado.
SELECT u.apellidos, u.nombre FROM usuario u LEFT JOIN pedido p ON (p.usuario = u.email);
-- T05.006- Código y nombre de los artículos, si además es una cámara, mostrar también la resolución y el sensor.
SELECT a.cod, a.nombre, c.resolucion, c.sensor FROM articulo a LEFT JOIN camara c ON (a.cod = c.cod);
-- T05.007- Código, nombre y pvp de los artículos, si además se trata de un objetivo mostrar todos sus datos.
SELECT a.cod artcod, a.nombre, a.pvp, o.* FROM articulo a LEFT JOIN objetivo o ON (o.cod = a.cod);
-- T05.008- Muestra las cestas del año 2010 junto con el nombre del artículo al que referencia y su precio de venta al público.
SELECT c.*, a.nombre, a.pvp FROM cesta c JOIN articulo a ON (c.articulo = a.cod) WHERE YEAR(c.fecha) = 2010;
-- T05.010- Disponibilidad en el stock de cada cámara, junto con el código y la resolución de todas las cámaras.
SELECT s.disponible, c.cod, c.resolucion FROM stock s RIGHT JOIN camara c ON (s.articulo = c.cod);
-- T05.015- Código y nombre de los artículos, y código de pack en el caso de que pertenezca a alguno.
SELECT a.cod, a.nombre, p.pack packCod FROM articulo a LEFT JOIN ptienea p ON (p.articulo = a.cod);

-- DIFICULTAD B
-- T05.016- Usuarios y pedidos que han realizado.
SELECT u.*, p.* FROM usuario u, pedido p WHERE p.usuario = u.email;
-- T05.002- Número de pedido e identificador, apellidos y nombre del usuario que realiza el pedido, y nombre de la localidad del usuario (usando join).
SELECT p.numPedido, u.email, u.nombre, u.apellidos, l.pueblo FROM pedido p 
													JOIN usuario u ON (u.email = p.usuario)
													JOIN localidad l ON (l.provincia = u.provincia AND l.codm = u.pueblo);
-- T05.003- Número de pedido e identificador, apellidos y nombre del usuario que realiza el pedido, nombre de la localidad y nombre de la provincia del usuario (usando join).
SELECT p.numPedido, u.email, u.nombre, u.apellidos, l.pueblo, p2.nombre FROM pedido p 
													JOIN usuario u ON (u.email = p.usuario)
													JOIN localidad l ON (l.provincia = u.provincia AND l.codm = u.pueblo)
													JOIN provincia p2 ON (p2.codp = l.provincia );
-- T05.004- Nombre de provincia y nombre de localidad ordenados por provincia y localidad (usando join) de las provincias de Aragón y de localidades cuyo nombre comience por "B".
SELECT p.nombre, l.pueblo FROM provincia p JOIN localidad l ON (l.provincia = p.codp) WHERE p.nombre IN ('huesca', 'zaragoza', 'teruel')
										AND l.pueblo LIKE 'B%' ORDER BY p.nombre, l.pueblo;
-- T05.009- Muestra toda la información de los artículos. Si alguno aparece en una cesta del año 2010 muestra esta información.
SELECT a.*, c.* FROM articulo a LEFT JOIN cesta c ON (c.articulo = a.cod AND YEAR(c.fecha) = 2010);
-- T05.013- Código, nombre, marca y empresa responsable de la misma de todos los artículos. Si algún artículo no tiene marca debe aparecer en el listado con esta información vacía.
SELECT cod, nombre, a.marca, empresa FROM articulo a LEFT JOIN marca m ON (a.marca = m.marca);
-- T05.014- Información de todos los usuarios de la comunidad valenciana cuyo nombre empiece por 'P' incluyendo la dirección de envío en caso de que la tenga.
SELECT u.*, d.* FROM usuario u JOIN provincia p ON (u.provincia = codp)
				LEFT JOIN direnvio d ON (d.email=u.email)
				WHERE (p.nombre LIKE '%Alicante%' 
    				OR p.nombre LIKE '%Valencia%' 
    				OR p.nombre LIKE '%Castell%') 
				AND u.nombre LIKE 'P%';

-- DIFICULTAD C
-- T05.017- Información de aquellos usuarios de la comunidad valenciana (códigos 03, 12 y 46) cuyo nombre empiece por 'P' que tienen dirección de envío pero mostrando, a la derecha, todas las direcciones de envío de la base de datos.




