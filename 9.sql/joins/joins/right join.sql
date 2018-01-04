-- Create table 1
CREATE TABLE table1
(ID INT, Value VARCHAR(10));
INSERT INTO Table1 (ID, Value)
SELECT 1,'First'
UNION ALL
SELECT 2,'Second'
UNION ALL
SELECT 3,'Third'
UNION ALL
SELECT 4,'Fourth'
UNION ALL
SELECT 5,'Fifth';

-- Create table 2
CREATE TABLE table2
(ID INT, Value VARCHAR(10));
INSERT INTO Table2 (ID, Value)
SELECT 1,'First'
UNION ALL
SELECT 2,'Second'
UNION ALL
SELECT 3,'Third'
UNION ALL
SELECT 6,'Sixth'
UNION ALL
SELECT 7,'Seventh'
UNION ALL
SELECT 8,'Eighth';

SELECT *
FROM Table1;
SELECT *
FROM Table2;

/* RIGHT JOIN */
SELECT 	t1.ID AS T1ID, t1.Value AS T1Value, 
		t2.ID T2ID, t2.Value AS T2Value
FROM Table1 t1
RIGHT OUTER JOIN Table2 t2 ON t1.ID = t2.ID;

/* LEFT JOIN */
SELECT 	t1.ID AS T1ID, t1.Value AS T1Value, 
		t2.ID T2ID, t2.Value AS T2Value
FROM Table2 t2
LEFT JOIN Table1 t1 ON t1.ID = t2.ID;

-- Clean up
DROP TABLE table1;
DROP TABLE table2;












