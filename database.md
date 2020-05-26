# Overview

SQL stands for Structured Query Language
Databases are usually SQL (postgress, mySQL) or NoSQL (MongoDB)

Databases are connected from the server and is just a big computer
In dev, databases might be stored on the same machine but it is best in production to separate server from db

## Types of Databses

Tables - SQL
Documents - NoSQL
Key-Value

## SQL & Tables

Relational databses are `ACID` Compliant

A relational database (SQL) `model` is defined as one or more `tables`.

Table has columns. Columns DO NOT change as they are defined in a schema.
Columns are also known as `attributes` or `fields`

Table has rows. Rows are instances of new records and are added continuously.
Rows are also known as `records`

you cannot have a table INSIDE of a table but you can reference other tables through ids.

## NoSQL & Collections

A non relational database (NoSQL) 'mode' is defined as `documents`

## PostgreSQL

a relational database with emphasis on extensibility and standards-compliance
It is `ACID compliant`, supporting industry best practices as well as great documentation!

## ACID compliance

Properties of db transactions intended to guarantee validity event in the event of errors, power failures, etc..

`A` Atomicity - Requires that a transaction be 'all or nothing'. If one part fails, the whole transaction fails and db state is unchanged

`C` Consistency - Any data written to the db will follow the schema and follow the guidelines (constraints, cascades, triggers, etc)

`I` Isolation - Concurrency control. Concurrent execution of transactions result in a state that would be obtained if they were run one after the other.

`D` Durability - Once a transaction is committed, the data will persist, even if there is a crash or power loss.

## SQL vs NoSQL

Since SQL databases are ACID compliant, it is more 'solid' in general.

Important database transactions like financial processes all use SQL.
