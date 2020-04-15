# Select

ex.

SELECT Somethingrow
AS Newrowname
FROM Sometable
WHERE some condition
ORDER BY
LIMIT

You can acess data with Alias.data Newrowname.price

Used first. must specify the name of row you are querying
You can also print onto a column any string `SELECT 'HELLO SQL'`

### (optional) DISTINCT

Using SELECT DINSTINC something will only query unique items and skip repeats

Can only be used for one selector.
DISTINCT \* won't do anything

### OTHER FUNCTIONS IN SELECT - AVG(), COUNT(), MAX)(), MIN(), SUM)()

`SELECT AVG(price) FROM table WHERE product_id=10`

These will return ONE value, so they can't be combined with other values that return more than 1.

## FROM

Name of table you are querying from

## AS (optional)

Used after SELECT when you want to rename the data as something else

SELECT Car AS AwesomeCar
FROM ToysTable

CAN NOT use in conjuction with other select functions like AVG() or COUNT() as they will just be named by the function name

A good way to assign a table to a variable. You can use dot notation to access their rows.

### You can use FROM (SELECT .... sub query) AS alias

To query from an internal query

## WHERE

Some condition like greater or less than to a number.
Numbers can be written as is, but strings must have single quotes

### Can chain with AND, AND NOT, OR. AND operator goes first (write in ANDs and AND NOTs in same line for clarity)

```
SELECT * FROM table
WHERE year=4 AND type='sport' AND NOT color='green'
OR
year=3 AND type='Academics'
```

Not equal operators can be written as `!=` or `<>`

### WHERE rowName IN() more than ONE value selectors

If you want to select more than one value and it can't be expressed with a simple < , <=, value

ALWAYS add parens! Add single quotes inside those parens for string values

```
SELECT *
FROM database
WHERE year IN (1970, 1971, 1972)
```

### WHERE rowName NOT IN()

Used for multiple cases of the not equal operator

### WHERE rowName LIKE 'string%'

    To select things that start with a string

    `SELECT * FROM database WHERE name LIKE 'Bob%'`

    NO PARENS
    % for rest of string - only for STARTING WITH these strings
    Doens't work for other data types like numbers

### You can chain all of these with AND

```
SELECT *
FROM table
WHERE year=1970
AND subject NOT IN('History', 'Geography')
AND name LIKE('Patricia%')
```

Select all data from the table with the year 1970 with the subject that is NOT 'History' or 'Geography' for all names that start with 'Patricia'

### WHERE row IS NULL

Used if you want the field to be null. Do not use equal signs
Also used for JOINS. See below

## UNION()

Adding UNION() will append another SELECT after the first SELECT. Both queries MUST have the same SELECT value (or comma separated row names). All query information for the 2nd query goes inside the parens in union.

```
SELECT *
FROM table
WHERE year=2 AND genre='Jazz'
UNION(
  SELECT * FROM table
  WHERE year=3
  AND genre='Classical'
  )
```

## ORDER BY, ORDER BY DESC

name the row that you want to order by. The default is INCREASING. If you want it decreasing, add keyword DESC AFTER the row now

ORDER BY age
ORDER BY age DESC

ORDER BY will only sort AFTER the initial query is finished, so if you want to get something before the query for GROUP BY based on an id, use MIN or MAX

### Second value separated by comma will be the backup ORDER BY in case two items have the same value as the first sort

ORBER BY level, name

if level is the same, then sort by name alphabetically

## LIMIT

Takes in 2. First number is the number of total queries. Second is the offset (what index number to start from)

LIMIT 1,4  
this will query 1 thing on the 5th row

## GROUP BY

Group rows with the same values into a summary row. Used in confuction with SUM(), COUNT(), etc..

```
SELECT COUNT(id), shoes
FROM clothing_inventory
GROUP BY shoes
```

Return a row with the number of different types of shoes in the table

## VARIABLES

Use select functions to get a number, then plug into WHERE

Find everything about the lowest height

```
SELECT *
FROM table
WHERE height=(
  SELECT MIN(height) FROM table
)
```

## JOINS - Use a common key to join two tables

1. INNER JOIN

```
SELECT *
FROM table_A
INNER JOIN table_B ON A.key=B.key
```

This selects all from a new table that contains all the info for rows that have the same "key" value assigned to both tables. If it only exists in one table, that info is not in the new table

2. LEFT JOIN `SELECT * FROM table_A LEFT JOIN table_B ON A.key=B.key`
   This will add the key info of B to all of the info on left
   1. LEFT JOIN WITH RIGHT NULL `SELECT * FROM table_A LEFT JOIN table_B ON A.key=B.key WHERE B.key IS NULL`
      This will take away the section of table A that has a common key with table B.
3. RIGHT JOIN - Same as left join, but in reverse order
4. RIGHT JOIN WITH LEFT NULL
5. FULL OUTER JOIN - Fully combines both tables
6. FULL OUTER JOIN WHERE A IS NULL AND B IS NULL - Excludes only the inner join part of both tables

## DOUBLE SELECT

A common way to use variables is by SELECT(SELECT stuff)
This will return a number or a string based on the inner select
When using the variable in WHERE with an operator, make sure to use parens around the entire variable like `(SELECT(SELECT query that returns a num or str))`

A lot of flexibility if you combine this with aliases and their dot notation

## Empty String VS NULL

A query with an outerfunction that doesn't meet requirements will return an empty string
A SELECT that maps OVER that empty value will return NULL

ex..

`SELECT 200` will output a row with 200
`SELECT (SELECT price FROM price_list WHERE price=200)` is the same as SELECT 200
<br />

`SELECT blabla stuff that doesn't exist in table` output is empty string ''
`SELECT (SELECT stuff that doesn't return anything)` will return NULL

A WHERE clause that doesn't meet requirements will also return NULL

## NON-SELECT COMMANDS

In MYSQL, DELETE (and probably other non-SELECT commands) have a loop prevention where you can't reference the table you are deleting from.

ex. This does NOT run!

```
DELETE
FROM Person
WHERE Id NOT IN (
             SELECT Id
            FROM Person
            GROUP BY Email
            )
```

The solution to this problem is to assign this inner SELECT to a different name, then get the dot notation to get the data

```
DELETE
FROM Person
WHERE Id NOT IN ( SELECT Sub.Id FROM
                 (
             SELECT Id
            FROM Person
            GROUP BY Email
            ) Sub )
```

To do that, we add another pair of parens, and add the variable name AFTER the inner Select call, in this case called 'Sub' for sub-table

Then in the first part, we add another SELECT Sub.\_\_\_\_ FROM to access that data.

## DATE_SUB, DATE_ADD

You can add date types by

`(SELECT DATE_ADD('5-1-2022', INTERVAL 1 day)) // will return a date type`

You can use the current select table with this
`(SELECT DATE_ADD(something.date, INTERVAL 1 day)) // will return a date type`

## Selecting and having a variable without using AS

When you want access to multiple tables, you can use AS but it also sets the final row now.

If you want access while having flexibility, you can

`SELECT table_1.Id` This sets the variable table_1 for future use and the row name will be 'Id'

## TWO FROMS

You can also do something similar as above with 2 froms

```
SELECT t_1.Id
FROM Customers AS t_1, Customers AS t_2
WHERE (now you have access to t_1 and t_2 at the same time)
```

This can be shortened without AS

```
SELECT t_1.Id
FROM Customers t_1, Customers t_2
WHERE (now you have access to t_1 and t_2 at the same time)
```

## Performance

When comparing something like 2 rows, UNION is faster than OR

OR method

```
SELECT name, population, area
FROM World
WHERE area > 3000000 OR population > 25000000
```

```
SELECT name, population, area
FROM World
WHERE area > 3000000

UNION

SELECT name, population, area
FROM World
WHERE population > 25000000
```

## HAVING

Having is the same as WHERE if there is no GROUP BY call
If HAVING is set after GROUP BY, it is a filter on to GROUP BY

```
SELECT class
FROM courses
GROUP BY class
HAVING count(distinct student) >= 5
```

## A common pattern

Using distinct inside count

`SELECT class, COUNT(distinct row) FROM bla GROUP BY something`

## CASE

If, then conditional that selects a value
in mySQL, ALL of the clause must be wrapped in parens!

Syntax

```
variable = (CASE WHEN  condition THEN value
     WHEN  condition2 THEN another value
     END)
```

You can also use ELSE at the end

```
variable = (CASE WHEN condition THEN ifValue
           ELSE elseValue
           END)
          // if the first condition is not true, then all other cases will be the elseValue
          // having and else takes MORE computing time than having multiple WHEN THEN clauses (based on leedcode result)
```

Used inside an update to swap the nubmers 1 to 2 and 2 to 1

```
UPDATE salary
Set num = (CASE WHEN num = 1 THEN 2
            WHEN num = 2 THEN 1 END)
```

Depending on usage, you may need to wrap the case in a SUM() function

```
SELECT id,
    SUM(case when color='Red' then quantity else 0 end) as red_quantity,
    SUM(case when color='Yellow' then quantity else 0 end) as yellow_quantity,
    SUM(case when color='Blue' then quantity else 0 end) as blue_quantity
from test group by id
```

# UPDATE

Doesn't print any values, but it updates.

Basic syntax

```
UPDATE tableName
SET rowName = 'something'
WHERE condition
```

You can't have more than one SET statement inside one UPDATE.
