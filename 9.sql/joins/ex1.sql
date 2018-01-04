create database ex1;

use ex1;


show tables;

create table Student (id INT(10) primary KEY auto_increment,
						FirstName varchar(30) NOT NULL,
                        LastName varchar (30) NOT NULL,
                        Enrol_data timestamp);                    
    
INSERT INTO Student(FirstName,LastName,Enrol_data) 
VALUES ("yaodav","rosenbereg",now()),
('gal','rosental',now()),
('ido','nave',now()),
('nadav','mizrahi',now());
   
    
create table Email(email varchar(30) primary key,
		FirstName varchar(30) NOT NULL,
        LastName varchar(30) Not NULL,
        id INT(10) NOT null);

INSERT INTO Email(email, FirstName,LastName,id) VALUES
	('yaodav5@yahoo.com','yaodav','rosenberg',1),
    ('yaodav5@gmail.com','yaodav','rosenberg',1),
    ('gal@gmail.com','gal','rosental',2),
    ('ido@gmail.com','ido','nave',3),
    ('nadav@gmail.com','nadav','mizrahi',4),
    ('nadav@yahoo.com','nadav','mizrahi',4),
    ('ido@yahoo.com','ido','nave',3);
   
create table Phones(id INT(10) NOT null, phone varchar(12));

INSERT INTO Phones(id, phone) VALUES
	(1, '0533456789'),
    (1, '0501234567'),
    (2, '0521234567'),
    (3, '0512345678'),
    (3, '0502343223'),
    (3, '1231235432');
   
select Email.FirstName 
from Email
where Email.id = 4;
   
SELECT * FROM Student;

SELECT Student.id, Student.FirstName, Student.LastName, Phones.phone 
FROM (Student LEFT JOIN Phones ON Student.id = Phones.id)
ORDER BY Student.id;

SELECT actor.first_name, film.title 
FROM actor JOIN film_actor
ON actor.actor_id = film_actor.actor_id
JOIN film 
ON film.film_id = film_actor.film_id
WHERE actor.actor_id 
in
(SELECT fa.actor_id FROM film_actor fa JOIN film f ON fa.film_id = f.film_id
JOIN actor a ON a.actor_id = fa.actor_id
WHERE f.title like 'MATRIX%')
ORDER BY film.title;


SELECT customer.first_name FROM customer, rental WHERE customer.customer_id = rental.rental_id AND rental.return_date IS NULL;SELECT customer.first_name FROM customer, rental WHERE customer.customer_id = rental.rental_id AND rental.return_date IS NULL;

