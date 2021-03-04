# Looker

data visualization service that takes in an underlying database (bigQuery) and makes configurable looks.

allows the dev team to shape the data with LookML and non-technical team members to shape the table based on the available data

## date

if bigQuery data is providing epoch time INTS, use `dimension_group` like this

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
