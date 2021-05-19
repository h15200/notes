# Looker

- data visualization service that takes in an underlying database (bigQuery) and makes configurable looks.
- a model layer that sits between database and user
- allows the dev team to shape the data with LookML and non-technical team members to shape the table based on the available data
- uses abstracted SQL

## Dimension vs Measure

- both Dimensions and Measures are defined in View files

### dimension

- dimension is a data element (database column equivalent)
- always in the GROUP BY part of any query
- automatically created for all fields within a table

### measure

- measure is a function of fields that have already been aggregated
- always part of any aggregate function

for example, `users.city` is a dimension and the `users.count` is a measure

```
// get all cities and their occurances
SELECT users.city AS "users.city", COUNT(*) AS "users.count"

FROM public.users AS users
// if using SELECT with one field and another count, must be grouped

GROUP BY 1  // 1 = users.city
ORDER BY 2 DESC // 2 = count
LIMIT 500

```

## Views

Can correspond to 3 types

1. Tables in Database (Standard View)
2. Looker-defined virtual tables (Derived Tables)
3. Looker-defined physically written tables (materialized View) to database (Persistent Derived Table)

- One or more view files jointed together = `Explore`

## Explore

- Made from 1 or more view files
- Views become headers in Explores

- Used for analysis. Clearly organize Explores around business themes to minimize confusion for end user
- ex. Users, Orders, Inventory

- explores are defined inside `Models`

## Model

- contains data connection info and Explore definitions
- can restrict user access to specific Explores
- can separate and organize Explores by business area

## Project (LookML Project)

- highest-level looker object
- used per different data source
- View files cannot be shared between different Projects (without using a project import)

## date

if bigQuery data is providing epoch time INTS, use `dimension_group` like this

dimension_groups are used to slice TIME

```
  dimension_group: ending {
    type: time
    timeframes: [date]
    datatype: epoch
    # sql data is in epoch milliseconds. convert to seconds for looker support
    sql: DIV(${TABLE}.date_ending, 1000);;
  }
```

// if epoch time was in seconds instead of MS, don't use DIV() func

## extends

Views can be extended using `extends: [view_to_extend]`

## substitution syntax vs liquid template

- substitution syntax`${}` can be used for pre-mapped variables within view files like view, measures, table
- liquid syntax `{% %}` can be used for stuff beyond tables
