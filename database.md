# Overview

SQL stands for Structured Query Language
Databases are usually SQL (postgress, mySQL) or NoSQL (MongoDB)

Databases are connected from the server and is just a big computer
In dev, databases might be stored on the same machine but it is best in production to separate server from db

SQL = Relational DB
NoSQL = Non relational

## 3 Types of Storing Databases

Tables - SQL
Documents - NoSQL
Key-Value

Both Documents and Key-Value are classified as non relational, NoSQL.

## SQL & Tables

ALL relational databses (SQL) are `ACID` Compliant

A relational database (SQL) `model` is defined as one or more `tables`.
Tables are constructed based on a strict `schema`

Table has columns. Columns DO NOT change as they are defined in a schema.
Columns are also known as `attributes` or `fields`

Table has rows. Rows are instances of new records and are added continuously.
Rows are also known as `records`

you cannot have a table INSIDE of a table but you can reference other tables through ids.

## NoSQL & Collections

NoSQL are NOT ACID Compliant.
There are SOME ACID compliant qualities, but generally NOT completely ACID compliant.

A non relational database (NoSQL) 'mode' is defined as `documents`
Documents are written close to JSON.

Instead of tables like in SQL, you have a collection of documents.

- each document is a JS object
- You have the ability to nest tables
- Built with an emphasis on SPEED.

The most popular db in the js stack is `MongoDB`

NoSQL dbs are used in big data and real-time web applications. (e-commerce)
Motivations include simplicity of design, simpler horizontal scaling of clusters of machines, and finer control over availability.
Generally considered FASTER and more FLEXIBLE.
NoSQL's don't use schemas, so it's not as solid but more flexible.

THE MORE Acid compliant you make a NoSQL db, the less fast/flexible it will be.

## key-value store

The third type after Tables, Documents

A Key-Value store are stored WITHOUT nesting (as opposed to NoSQL).
Redis is a prime representative of a key-value system db.

The data does NOT persist if there is a power outage.
Sensitive or valuable data is not used in a key-value store.

## ACID compliance

Properties of db transactions intended to guarantee validity event in the event of errors, power failures, etc..

`A` Atomicity - Requires that a transaction be 'all or nothing'. If one part fails, the whole transaction fails and db state is unchanged

`C` Consistency - Any data written to the db will follow the schema and follow the guidelines (constraints, cascades, triggers, etc)

`I` Isolation - Concurrency control. Concurrent execution of transactions result in a state that would be obtained if they were run one after the other.

`D` Durability - Once a transaction is committed, the data will persist, even if there is a crash or power loss.

## SQL vs NoSQL

Since SQL databases are ACID compliant, it is more 'solid' in general.
Important database transactions like financial processes all use SQL.

NoSQL databases are not as solid but faster and more flexible BECAUSE it doesn't use a traditional schema. NoSQL lookups are fast because the data is formed as JSON (object lookup)

For HUGE apps, possible to use both an SQL and a NoSQL in one app.

## PostgreSQL

a relational database with emphasis on extensibility and standards-compliance
It is `ACID compliant`, supporting industry best practices as well as great documentation!

To see tables in the terminal, use `\d`

See more inside MYSQL.md

## MongoDB

a non-relational database that is common in the JS stack.

A free open-source cross-platform document-oriented database.
uses JSON-like documents with dynamic schemas (flexible)

Features:

Indexing - any field can be indexed
Replication - stores data as a replica set of two or more copies
Load balancing - Mongo scales horizontally using sharding
Aggregation - MapReduce can be used for batch processing of data and aggregation operations.

## Redis

Prime example of a key-value store.
A data structure server
Holds its entire dataset in RAM, and syncs back to the disc every 2 seconds
Very fast because data is memcached but a power outage will destroy some data.

A good choice if you want a highly scalable data store shared by multiple processes or multiple applications.

## Schema

A schema is a map of what your data looks like.

In an SQL - defined the columns in your tables and the rules that data in rows must follow
In a NoSQL, defines the object

In a key-value, there is no schema at all.

## SQL relationships

One to One
One to Many
Many to Many

Linking model to model happens by establishing relationships through the creation of foreign keys

Often, ID fields are used for this but any common field can be used.

model Users id, name, email
model Houses id, name, user_id (which equals the Users id)

The id is the primary key for Users
The id is the primary key for Houses
The user_id is the FOREIGN key for Houses that links to Users.
