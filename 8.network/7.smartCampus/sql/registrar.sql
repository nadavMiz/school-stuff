CREATE DATABASE Registrar;

use Registrar;

CREATE TABLE Sections(
	id INT PRIMARY KEY AUTO_INCREMENT,
    section_name VARCHAR(256),
    ip VARCHAR(256),
    msg_port INT,
    registration_port INT
);

INSERT INTO Sections(section_name, ip, msg_port, registration_port) VALUES
("mainHub", "127.0.0.1", 2004, 2003),
("otherHub", "127.0.0.1", 5000, 5001);

SELECT * FROM Sections WHERE section_name = 'otherHub'