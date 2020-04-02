# SQL QUERIES

## Syntax - best practice to capitalize all reserved words for readability

ex. 

SELECT Somethingrow 
AS Newrowname
FROM Sometable
WHERE some condition
ORDER BY 
LIMIT 



## SELECT 

Used first. must specify the name of row you are querying
You can also print onto a column any string `SELECT 'HELLO SQL'`

### (optional) DISTINCT


Using SELECT DINSTINC will only query unique items and skip repeats


## FROM
Name of table you are querying from

## AS (optional)

Used after SELECT when you want to rename the data as something else

SELECT Car 
FROM ToysTable
AS AwesomeCar

## WHERE

Some condition like greater or less than
 
## ORDER BY, ORDER BY DESC
name the row that you want to order by. The default is INCREASING. If you want it decreasing, add keyword DESC AFTER the row now

ORDER BY age 
ORDER BY age DESC

## LIMIT   

Takes in 2. First number is the number of total queries. Second is the offset (what index number to start from)

LIMIT 1,4  
this will query 1 thing on the 5th row
