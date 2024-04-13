# Postgres

## DBML syntax

- use `dbdiagram.io` with `DBML` to translate to SQL for now
- brackets for additional into

  - comma separated values
  - includes `pk`, `not null`, `notes`, `ref: > someTable.someColumn`

- can add `Indexes`

```
// Use DBML to define your database structure
// Docs: https://dbml.dbdiagram.io/docs

// using postgres syntax
Table account as A {
  id serial [pk] // auto increment not null is automatically added to pks
  owner varchar [not null]
  balance bigint [not null]// probably should be a separate money type
  currency varchar [not null]
  created_at timestamp [not null, default: `now()`]

  // add indexes to speed up searches with a slightly slower write
  Indexes {
    owner
  }
}

// always declare fk in the many table
Table entries as E {
  id serial [pk]
  account_id int [Ref: > A.id] // many to one
  // foreign keys can be nullable in postgres,
  // and can be useful
  amount bigint [not null, note: 'can be negative or positive']
  created_at timestamp [not null, default: `now()`]

  Indexes {
    account_id // probably most common search
  }
}

// records all transfers between accounts

Table transfers as T {
  id serial [pk]
  from_account_id int [Ref: > A.id]
  to_account_id int [Ref: > A.id]
  amount bigint [not null, note: 'must be positive']
  created_at timestamp [not null, default: `now()`]

  Indexes {
    from_account_id
    to_account_id
    // a composite type to specify only transfers between two specific types
    (from_account_id, to_account_id)
  }
}
```

- diff between varchar and text
  - varchar requires an upper bound for string length
