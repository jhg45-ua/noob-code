USE tiendaonline;

-- DIFICULTAD A
-- T04B.001- Pedidos realizados el 13.9.2010 (este formato, obligatorio en la comparación).
SELECT * FROM pedido p WHERE p.fecha = STR_TO_DATE('13.9.2010', '%d.%c.%Y');
-- T04B.002- 31 de febrero de 2011 en formato dd/mm/aaaa
SELECT DATE_FORMAT('2011-02-31', '%d/%m/%Y') fechaFormateada;
-- T04B.003- 21 de febrero de 2011 en ese mismo formato (el mes aparecerá en inglés)
SELECT DATE_FORMAT('2011-02-31', '%d de %M de %Y') fechaFormat;
-- T04B.004- Numero y fecha de los pedidos realizados el 13.9.2010 (este formato, obligatorio tanto en la comparación como en la salida).
SELECT p.numPedido, DATE_FORMAT(p.fecha, '%d.%c.%Y') fecha FROM pedido p WHERE p.fecha = STR_TO_DATE('13.9.2010', '%d.%c.%Y');
-- T04B.005- Numero, fecha (en formato dd.mm.aa), y usuario de los pedidos ordenado descendentemente por fecha y ascendentemente por usuario.
SELECT p.numPedido, DATE_FORMAT(p.fecha, '%d.%c.%Y') fecha, p.usuario FROM pedido p ORDER BY p.fecha DESC, p.usuario;
-- T04B.006- Información sobre los usuarios menores de 25 años.
SELECT * FROM usuario u WHERE YEAR(NOW() - YEAR(u.nacido) < 25);
-- T04B.007- Toda la información de los pedidos realizados el 3 de marzo o el 27 de octubre de 2010, y que han sido realizados por usuarios del dominio "cazurren"
SELECT * FROM pedido p WHERE p.usuario LIKE '%cazurren%' AND p.fecha = '2010-03-03' OR p.fecha = '2010-10-27';

-- DIFICULTAD B
-- T04B.008- Email y cantidad de días que han pasado desde los pedidos realizados por cada usuario hasta la fecha de cada artículo que ahora mismo hay en su cesta. Eliminad duplicados.
SELECT DISTINCT c.usuario, DATEDIFF(c.fecha, p.fecha) dias FROM cesta c, pedido p, linped l WHERE c.usuario = p.usuario 
															AND l.numPedido = p.numPedido AND l.articulo = c.articulo;
-- T04B.009- Códigos de articulos solicitados en pedidos de septiembre de 2010, y semana del año (la semana comienza en lunes) y año del pedido, ordenado por semana.
