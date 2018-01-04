use sakila;

SELECT A.first_name, A.last_name, F.title FROM actor A, film F, film_actor FA 
WHERE F.title = 'ALABAMA DEVIL' AND F.film_id = FA.film_id AND FA.actor_id = A.actor_id;

SELECT * FROM film;

SELECT * FROM actor WHERE (NOT first_name between 'A%' and 'G%')
AND (NOT first_name between 'I%' and 'Z%');

SELECT * FROM actor WHERE first_name LIKE '%joh%';

SELECT NOW();
SELECT CURDATE();
SELECT CURTIME();

SELECT A.actor_id FROM actor A, film F, film_actor FA 
WHERE F.title = 'ALABAMA DEVIL' AND F.film_id = FA.film_id AND FA.actor_id = A.actor_id;

SELECT actor_id, film_id FROM film_actor 
WHERE actor_id in(SELECT A.actor_id FROM actor A, film F, film_actor FA 
WHERE F.title = 'ALABAMA DEVIL' AND F.film_id = FA.film_id AND FA.actor_id = A.actor_id);

SELECT actor.first_name, actor.last_name, film.title FROM actor, film,
(SELECT actor_id, film_id FROM film_actor 
WHERE actor_id in(SELECT A.actor_id FROM actor A, film F, film_actor FA 
WHERE F.title = 'ALABAMA DEVIL' AND F.film_id = FA.film_id AND FA.actor_id = A.actor_id)) ids
WHERE actor.actor_id = ids.actor_id and film.film_id = ids.film_id;


SELECT title FROM film WHERE title LIKE '%MATRIX%';

SELECT fa.actor_id, f.title FROM film_actor fa JOIN film f on f.film_id = fa.film_id
LIMIT 10; 