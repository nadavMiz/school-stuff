USE sakila;

/*
Problem Statement:
Find all the customer's payments which are over their average payment.
*/

SELECT  payment_id, cust.first_name, cust.last_name, amount
FROM payment pt
INNER JOIN customer cust ON cust.customer_id = pt.customer_id
WHERE amount <
		(	SELECT AVG(amount)
			FROM payment pt1
			WHERE pt1.customer_id = pt.customer_id)
ORDER BY cust.customer_id;

















SELECT  cust.first_name, cust.last_name, COUNT(payment_id) CountofPayment
FROM payment pt
INNER JOIN customer cust ON cust.customer_id = pt.customer_id
WHERE amount >
		(	SELECT AVG(amount)
			FROM payment pt1
			WHERE pt1.customer_id = pt.customer_id)
GROUP BY cust.first_name, cust.last_name
ORDER BY cust.customer_id;











SELECT AVG(amount), cust.first_name, cust.last_name
FROM payment pt
INNER JOIN customer cust ON cust.customer_id = pt.customer_id
GROUP BY cust.first_name, cust.last_name
ORDER BY cust.customer_id;