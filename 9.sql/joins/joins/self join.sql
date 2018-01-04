-- Create a Table
CREATE TABLE Employee(
EmployeeID INT PRIMARY KEY,
Name NVARCHAR(50),
ManagerID INT
);

-- Insert Sample Data
INSERT INTO Employee
SELECT 1, 'Mike', 3
UNION ALL
SELECT 2, 'David', 3
UNION ALL
SELECT 3, 'Roger', NULL
UNION ALL
SELECT 4, 'Marry',2
UNION ALL
SELECT 5, 'Joseph',2
UNION ALL
SELECT 7, 'Ben',2;

-- Check the data
SELECT *
FROM Employee;

-- Inner Join
SELECT e1.Name EmployeeName, e2.name AS ManagerName
FROM Employee e1
INNER JOIN Employee e2
ON e1.ManagerID = e2.EmployeeID;

-- Outer Join
SELECT e1.Name EmployeeName, IFNULL(e2.name, 'Top Manager') AS ManagerName
FROM Employee e1
LEFT JOIN Employee e2
ON e1.ManagerID = e2.EmployeeID;

-- Clean up
DROP TABLE Employee;




















