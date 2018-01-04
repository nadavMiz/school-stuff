USE sakila;
SELECT fm.title, cat.name, dt.CountofCategory
FROM film fm 
INNER JOIN film_category fc ON fc.film_id = fm.film_id
INNER JOIN category cat ON cat.category_id = fc.category_id
INNER JOIN 
	(	SELECT COUNT(*) AS CountofCategory, fc.category_id
		FROM film_category fc
		GROUP BY fc.category_id) dt ON dt.category_id = fc.category_id;

