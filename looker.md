# Looker

- data visualization service that takes in an underlying database (bigQuery) and makes configurable looks.
- a model layer that sits between database and user
- allows the dev team to shape the data with LookML and non-technical team members to shape the table based on the available data
- uses abstracted SQL

## TLDR

- Project (per data source) -> Model (connection info, access, explore groupings) -> Explore (View joins) -> View -> Dimension/Measures
- File Browser will contain models and views only. Model files will define explores (made up of views) and View files will have dimension/measures
- when in dev, put the cursor on where you are and click on the info button on the top right to see all available params for that object

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
- timeframe.raw is not exposed to the user, and usually just used for modeling
- For BigQuery, Do Not Use timeframe.time! use second instead. timeframe.time will get the most detailed time unit for some SQL dialects, but NOT For STANDARD SQL (bigQuery)!! Better to leave off time so the user is not confused, and use seconds as that's what it rounds up to anyway.

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

### Building Explores

- explores defined inside Model files
- each join will be a user selectable field in explore view
- Explore Parameters (properties)
  - `explore` explore name, which is name of view
    - if you want to keep the `join` value the same as the view, but rename in the explorer view, add `label` to rename Explore name
    - `description`
    - `view_label` changes the label of the view within explorer field picker
- it is possible just to not join anything and make an explore that is just a view
  examples
- If using join, `join` is the name of 2nd view you want to join with
  - 3 Required Join Parameters
    - `type` join type (left_outer by default)
    - `sql_on` fields that should be used for join
    - `relationship` ex. many_to_one
  - optional join params
    - `from` if you want to declare the join name as something else in `join`, also include a `from` inside the join the declare which view you are joining
    - `fields` limit the scope of fields for Explore or View level
- indirect joins are possible when A is joined to B and in that same explore, B is joined to C

```
// explore === view with no join
explore: some_view_name {}

// joins a view called inventory_items with products
explore: inventory_items {
  join: products {
    type: left_outer
    sql_on:   ${inventory_items.product_id} = ${products.id} ;;
    relationship: many_to_one
  }
}

```

### Symmetric Aggregation and the Fan Out problem

- in some joins, an explore will fan out the table in a way that duplicates data.
- Looker can solve this by using Symeetric Aggregation via the following 2 steps:

1. Specify Primary keys in the joined View files under dimension.primary_key (bool).
2. Correctly specify the correct join.relationship parameter

- to figure out the correct relationship, ask the question "is this a primary key?". if the answer is yes, that side of the relationship equation is `one`. no will mean `many`

- how does this work? Under the hood, Looker is adding a distinct count for primary keys

### Filtering Explores - optimize and avoid sending unnecessarily big reports

- filters are used for opimization so users don't accidentally send a gigantic query to all databases

- most commonly utilized options for applying Explore default filters are:

1. `sql_always_where` and `sql_always_having`

- an automatic filter that the user is not even aware of

2. `always_filter`

- always_filter is a REQUIREMENT on the user to filter when selecting this explore

3. `conditionally_filter`

- a rare case where a default filter can be removed if at least one of the specified fields in `unless` are selected

## Model

- contains connection info (where the data is coming from)
- info on which views to include (views are sharable across all models within the same project)
- individual Explore definitions
- can restrict user access to specific Explores
- can separate and organize Explores by business area

## Project (LookML Project)

- highest-level looker object, consisting or 1 or more model files, each containing Explore options and joins
- has multiple view files, each corresponding to a database table or a derived table
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

## Caching

- Looker has internal queryIds and caches recent queries
- When running a query, Looker will always first check if it's cached before making the query
- default caching policy can be changed

### Datagroups

- datagroups are named looker caching policies that can be applied to Models, Explores, or Persisted Derived Tables (PDT).
- datagroups are defined at the `model` level
- each caching policy requires separate datagroup definitions

### Configuring Datagroups

- `sql_trigger` parameter that returns one row with one column to determine if the cache should be busted
- `max_cache_age` longst time a query should be cached
- only 1 required, but both is best practice
- in this example, the cache is good for 24 hours. all users using this datagroup will use cached results, UNLESS the sql_trigger shows something different from the cache

```
datagroup: daily_etl {
  max_cache_age: "24 hours"
  sql_trigger: SELECT max(id) FROM my_tablename ;;
}
```

### Implmenting Datagroups Cache Policies

- implementation methods (after datagroups have been defined on the model level)
  - at the model file `persist_with` at top will apply to ALL explores in that model
  - adding `persist_with` inside an individual explore will be specific to that explore
  - in a `PDT` definition: use `datagroup_trigger`
  - on Looks and Dashboards: build schedules that trigger based on datagroups to cause content to run and send immediately after the cache has been invalidated, thus warming the cache with the latest results

## Errors

- try replacing double quotes with single quotes
- debugging brackets. in model or view layer, click on the file drop down to the right of `thing.model`, click `Fold LookML`

## extends

Views can be extended using `extends: [view_to_extend]`

## substitution syntax vs liquid template

- substitution syntax`${}` can be used for pre-mapped variables within view files like view, measures, table
- liquid syntax `{% %}` can be used for stuff beyond tables

## Derived Tables

- used when you need a view beyond the existing data
- manually written query whose result set can be queried like a regular database table
- integrated as Looker views
- can be joined in Explores like standard Views
- they can be ephemeral or written into the database (persisted)

### 2 types of Derived Tables

1.  SQL derived tabled (most common)

- easy to learn and understand
- uses complex joins, calculations, and functions such as UNION
- implmentation
  - Develop Tab -> SQL Runner -> Type out a query
  - Gear button on upper right -> import SQL runner -> add a name to the view
- to persist
  - add 2 parameters to a derived table
    1. Table Refresh Logic
    - `datagroup_trigger`: triggered by some change in underlying data as defined within a datagroup (most recommended)
    - `sql_trigger_value`: triggered by a change in the direct defined underlying data
    - `persist_for` : a set time period
    2. Indexes
    - A single or multi index for most dbs
    - sort key(s) and a distribution key for Redshift
    - cluster key(s) and partition key(s) for BigQuery

2. Native Derived Table

- maximum code reusablility
- easier to maintain
- easier to read and understand

# Access Filter

- all users have access to all explores, but individual rows are restricted based on rules in Users
- defined in the model file, inside explore definition

## General Best Practices

- use lowercase underscore casing
- name measures with aggregate function or common terms `total_users` for sum, `count_users`, `avg_users`
- name `yesno` dimensions clearly with Is somewhere `User Is New` instead of `User`
- avoid words `date` or `time` in a dimension group because Looker will append each timeframe array unit to the end of the name.. `created_date` will become `created_date_date`

## Explore Design Best Practices

- don't join in extraneous views
- use fields parameter to limit fields surfaced to the end user
- comment out or delete extra auto-generated explores in the model file
- if joining something that you just want to keep in the same field (the user doesn't care of displayName came from a join), use `view_label` and add that to the original explore name camel cased
- if you are using an indirect join and want to hide the middle join, use join param `fields` with an empty [].

## Model Design Best Practices

- join many to one from the most granular level for the best query performance
- use the fewest number of explores possible
- organize using `group_label` to help end user find the correct explore easily

## Join Design Best Practices

- use ${date_raw} when joining on a date
- always define a relationship
- always declare a primary key in the View file

## Persistent Derived Table Usage Best Practices

- choose the parameter `datagroup_trigger` over `persist_for` when you want to have data ready the first time someone runs an explore or on a schedule
- evalute `datagroup_trigger` schedules such that tables are not building during business hours/peak usage. Trigger the tables late in the night or early in the morning when ETL is completed
- always define indexes, distribution keys/sortkeys, and cluster keys/cpartition keys to optimize performance
- indexes should generally be applied to primary keys and date or time columns
