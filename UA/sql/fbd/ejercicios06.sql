-- DIFICULTAD A
-- T06.001- Crea una tabla de nombre "xx" con 2 columnas, col1 de tipo integer, y col2 de tipo char(3), con col1 como clave primaria.
CREATE TABLE xx
(
	col1 integer,
	col2 char(3),
	PRIMARY KEY (col1)
);
-- T06.002- Consulta la tabla.
SELECT * FROM xx;
-- T06.003- Inserta en la tabla la fila (1,’AA’).
INSERT INTO xx VALUES (1, 'AA');
-- T06.004- inserta en la tabla la fila ('BB',2).
INSERT INTO xx VALUES ('BB', 2);
-- T06.005- Inserta en la tabla la fila (2,'BB').
INSERT INTO xx VALUES (2, 'BB');
-- T06.006- Consulta la tabla XX.
SELECT * FROM xx;
-- T06.007- Cierra la sesión e identifícate de nuevo (“salte y vuelve a entrar” o "desconecta" y "conecta" ).
SELECT * FROM xx;
-- T06.008- Borra la tabla XX.
DROP TABLE xx;
-- T06.009- Crea una tabla YY con 3 columnas.
CREATE TABLE yy
(
	col1 integer,
	col2 char(2),
	col3 varchar(10),
	PRIMARY KEY (col1, col2)
);
-- T06.010- Inserta los siguientes datos y consulta la tabla para ver los datos almacenados.
INSERT INTO yy VALUES (1, 'AA', 'primera');
INSERT INTO yy VALUES (2, 'AA', 'segunda');
INSERT INTO yy VALUES (2, 'BB', 'tercera');
INSERT INTO yy VALUES (1, 'AA', 'cuarta');
INSERT INTO yy VALUES (NULL, NULL, 'quinta');
INSERT INTO yy VALUES (NULL, 'CC', 'sexta');
INSERT INTO yy VALUES (3, NULL, 'septima');
INSERT INTO yy VALUES (0,"", "octava");
INSERT INTO yy VALUES (3, 'AA', NULL);
-- T06.011- Ejecuta lo siguiente: 
create table T1(a int,b int,c int,
primary key(a));
create table T2(a int,d int,e int,
primary key(d),foreign key(a) references T1(a)); 



