# Looker

data visualization service that takes in an underlying database (bigQuery) and makes configurable looks.

allows the dev team to shape the data with LookML and non-technical team members to shape the table based on the available data

## Views

- View = table
- can join like tables

`dimensions` are fields within a view and are automatically created for all fields in a table

## dimension vs measure

- dimension is a data element (database column equivalent)
- measure is an aggregate (count)

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
