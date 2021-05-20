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

### Writing dimensions and measures inside a view

- dimensions and measures are defined inside a view
- Looker automatically creates dimensions for every field in the view
- `${TABLE}` references the table that is defined in the view
- as dimensions and measures are defined, those can also be used as `${measure_or_dimension_name}` in other dimensions and measures.
- convention to use lowercase_snake_casing for dimension/measure names
- use double semilcolons after `sql` values
- best practice to reference LookML obejects with ${} when possible

example View code

```

dimension: sale_price {
  type: number
  sql: ${TABLE}.sale_price ;;
}

measure: total_revenue {
  type: sum
  sql: ${sale_price} ;;
}

measure: average_revenue {
  type: average
  sql: ${sale_price} ;;
}

// note that in the meaures, sale_price is available as a variable
```

### Dimension Types

- `string` (default), used for text
- `number` used with date calculations and basic row-level math across fields
- `yesno` defines logical condition in SQL parameter. outputs yes or no
- `tier` buckets a dimension using CASE statements.

  - tier styles include `classic`, `interval`, `integer`, and `relational`

- `||` operator is a concat
- DATEDIFF is a sql function that takes 3 args

```
dimension: full_name {
  type: string // defaults to string but best practice to state explicitely
  sql: ${first_name} || ${last_name}  ;;

}

dimension: days_since_signup {
  type: number
  sql: DATEDIFF(day, ${created_date}, current_date) ;;
}

dimension: is_new_customer {
  type: yesno
  sql: ${days_since_signup} <= 90 ;;
}

dimension: days_since_signup_tier {
  type: tier
    tiers: [0, 30, 90, 180]
  sql: ${days_since_signup} ;;
  style: integer
}
```

### Dimension Groups Types

#### Time

- Looker can cast a date or timestamp into different forms of time
- `dimension_group` can use the timeframes parameter to specifiy date and time parts options include `[raw, time, date, hour, hour_of_day, day_of_week, day_of_week_index, time_of_day, week, month_num, month, year, quarter, quareter_of_year ]`
- each timeframe array item will create a new field which can be referenced by underscore`${dimensionGroupName_timeframeItem}`

```
// example data is providing epoch time integers

dimension_group: ending {
type: time
timeframes: [date]
datatype: epoch // sql data is in epoch milliseconds. convert to seconds for looker support
sql: DIV(${TABLE}.date_ending, 1000);;
}

// timeframes array can be any number. array length will determine number of dimension fields

dimension_group: created {
  type: time
  timeframes: [time, date, hour]
  sql: ${TABLE}.created_at ;;
}

// this will create 3 fields
// they can be referenced by `${created_time}, ${created_date}, ${created_hour}`

```

// if epoch time was in seconds instead of MS, don't use DIV() func

#### Duration

- dimension group type Duration is used to calculate a set of interval-based durations
- use the `intervals` parameter to specify the specific date and time durations includes `[second, minute, hour, day, week, month, querter, year]`
- needs sql_start and sql_end paramters

```
dimension_group : enrolled {
  type: duration
  intervals: [second, minute, hour]
  sql_start: ${TABLE.enrollment_date} ;;
  sql_end: ${TABLE.graduation_date} ;;
}
```

### Measure Types (3 most common)

- sum
- average
- count (2 types)

  - first type, `count` counts rows in that table and does not require an SQL paramter. system generated
  - `count_distinct` computers a distinct count of the filed in the SQL paramter

- sum and average examples

```
dimension: cost {
  type: number
  sql: ${TABLE}.cost ;;
}

measure: total_cost {
  type: sum
  sql: ${cost} ;;
}

measure: average_cost {
  type: average
  sql: ${cost} ;;
}
```

- count examples

```

measure: count_items_ordered {
  type: count
}

meaure: count_users {
  type: count_distinct
  sql: ${user_id} ;;
}
```

#### Filtered Measures

- measures can have a `filter` paramter which acts like a WHERE clause in a measure
- the filter can be an existing dimention type, even from outside views as long as the 2 views are joined in an explore

```
measure: count_female_users {
  type: count
  filters: [gender: "female"] // gender is a string type
}

measure: total_sales_new_users {
  type: sum
  sql: ${sale_price} ;;
  filters: [user.is_new_user: "Yes"]
  // user is another view and is_new_user is a yesno dimension type inside user
}
```

#### Advanced Measures - using measures to define other measures

- for complex calculations, nested measures
- in this case only, the type will be `number`

```
mesure: percentage_female_users {
  type: number
  value_format_name: percent_1   // percentage to the nearest 10th
  sql: 1.0*${count_female_users}/NULLIF(${count}, 0) ;;

  // NULLIF to avoid divide by 0 error
}
```

### Helpful measure/dimension field parameters

- `hidden` hides a field from user while making it available for modeling. great for fields like primary keys or ids that are not meaningful to users
- `label` changes field name in Field Picker
- `description` displays details about a field onHover
- `value_format_name` sets unit for numbers like usd, percent, or even custom format names
- `drill_fields` controls what fields are shown to user when a table cell is clicked when exploring. Most likely used for measures and not dimensions
- `group_label` combines fields into custom groups within a view in the Field Picker for better UI

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

- contains connection info (where the data is comning from)
- info on which views to include (views are sharable across all models within the same project)
- individual Explore definitions
- can restrict user access to specific Explores
- can separate and organize Explores by business area

## Project (LookML Project)

- highest-level looker object, consisting or 1 or more model files, each containing Explore options and joins
- has multiple view files, each corresponding to a databse table or a derived table
- 1 or more dashboard files which define a project's data and layout if you choose to use `LookML Dashboards` in addition to User-Defined Dashboards
- used per different data source
- View files cannot be shared between different Projects (without using a project import)

## 3 Roles

- 4 tabs on top available `Browse`, `Explore`, `Develop`, `Admin`
- Admin has access to all 4 tabs
- Developers has access to all except 'admin'
- Users just have "browse" and "explore"

## Prod vs Dev Mode (Ctr + Shift + d) or Develop Dropdown -> Switch "Development Mode" Toggle

- Production Mode is used to explore data in Looker. Data is shared across all users and LookMl files (model, explore, view) are treated as read-only. This is the default view.

- Dev Mode is on a different branch and uses a separate copy of the data model to edit. Making changes to LookMl files can only be done in dev mode (adding Views, Explores, Models)

## workflow - starting looker

- in dev dropdown -> Manage LookML Projects -> New LookML Project btn -> setting
- add files

## Errors

- try replacing double quotes with single quotes
- debugging brackets. in model or view layer, click on the file drop down to the right of `thing.model`, click `Fold LookML`

## extends

Views can be extended using `extends: [view_to_extend]`

## substitution syntax vs liquid template

- substitution syntax`${}` can be used for pre-mapped variables within view files like view, measures, table
- liquid syntax `{% %}` can be used for stuff beyond tables

```

```
